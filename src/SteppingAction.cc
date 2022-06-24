#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"
#include "SiSensitiveDetector.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4OpBoundaryProcess.hh"

namespace {
    static const std::map<size_t, const char*> optProcLookup = {
        {0, "Undefined"},
        {1, "Transmission"},
        {2, "FresnelRefraction"},
        {3, "FresnelReflection"},
        {4, "TotalInternalReflection"},
        {5, "LambertianReflection"},
        {6, "LobeReflection"},
        {7, "SpikeReflection"},
        {8, "BackScattering"},
        {9, "Absorption"},
        {10, "Detection"},
        {11, "NotAtBoundary"},
        {12, "SameMaterial"},
        {13, "StepTooSmall"},
        {14, "NoRINDEX"},
        {15, "PolishedLumirrorAirReflection"},
        {16, "PolishedLumirrorGlueReflection"},
        {17, "PolishedAirReflection"},
        {18, "PolishedTeflonAirReflection"},
        {19, "PolishedTiOAirReflection"},
        {20, "PolishedTyvekAirReflection"},
        {21, "PolishedVM2000AirReflection"},
        {22, "PolishedVM2000GlueReflection"},
        {23, "EtchedLumirrorAirReflection"},
        {24, "EtchedLumirrorGlueReflection"},
        {25, "EtchedAirReflection"},
        {26, "EtchedTeflonAirReflection"},
        {27, "EtchedTiOAirReflection"},
        {28, "EtchedTyvekAirReflection"},
        {29, "EtchedVM2000AirReflection"},
        {30, "EtchedVM2000GlueReflection"},
        {31, "GroundLumirrorAirReflection"},
        {32, "GroundLumirrorGlueReflection"},
        {33, "GroundAirReflection"},
        {34, "GroundTeflonAirReflection"},
        {35, "GroundTiOAirReflection"},
        {36, "GroundTyvekAirReflection"},
        {37, "GroundVM2000AirReflection"},
        {38, "GroundVM2000GlueReflection"},
        {39, "Dichroic"},
    };

    const G4OpBoundaryProcess* findOpticalBoundary(const G4Step* step)
    {
        const auto* pv = step->
            GetTrack()->
            GetDefinition()->
            GetProcessManager()->
            GetProcessList();

        for (size_t i = 0; i < pv->size(); ++i) {
            if ((*pv)[i]->GetProcessName() == "OpBoundary") {
                return static_cast<const G4OpBoundaryProcess*>((*pv)[i]);
            }
        }

        G4Exception(
            "ImpSteppingAction/findOpticalBoundary",
            "fob1", RunMustBeAborted, "issue finding optical boundary");

        return nullptr; 
    }
}

SteppingAction::SteppingAction()
: G4UserSteppingAction()
{}

SteppingAction::~SteppingAction()
{}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
    trackScintillation(step);
    auto* track = step->GetTrack();
    if (track->GetDefinition() == G4OpticalPhoton::Definition()) {
        processOptical(step);
    }
}

void SteppingAction::trackScintillation(const G4Step* step)
{
    const std::vector<const G4Track*>* secs;
    if ((secs = step->GetSecondaryInCurrentStep()) && secs->size() > 0) {
        size_t numOps = std::count_if(
            secs->begin(), secs->end(), [](const G4Track* t) {
            return t->GetParticleDefinition()->GetParticleName() == "opticalphoton"; });
        // store the number of optical photons generated
        // to be saved at end of event
        auto* ea = dynamic_cast<EventAction*>(
            G4EventManager::GetEventManager()->GetUserEventAction());
        if (ea) ea->addScintPhot(numOps);
    }
}

void SteppingAction::processOptical(const G4Step* step)
{
    static const G4ThreadLocal G4OpBoundaryProcess* boundary = findOpticalBoundary(step);
    if (boundary == nullptr) return;

    const auto* prePt = step->GetPreStepPoint();
    const auto* postPt = step->GetPostStepPoint();

    const auto* preVol = prePt? prePt->GetPhysicalVolume() : nullptr;
    const auto* postVol = postPt? postPt->GetPhysicalVolume() : nullptr;

    const G4String preName = preVol? preVol->GetName() : "";
    const G4String postName = postVol? postVol->GetName() : "";
    bool yesSilicon =
        G4StrUtil::contains(postName, "si") ||
        G4StrUtil::contains(preName, "si");

    if (postPt->GetStepStatus() == fGeomBoundary) {
        auto stat = boundary->GetStatus();
        switch (stat) {
            case Detection:
                // detect it here because it dies before it can actually register inside the detector
                processDetected(preVol, postVol, step);
                break;
            case Absorption:
            case TotalInternalReflection:
            case StepTooSmall:
            case Transmission:
            case FresnelRefraction:
            case FresnelReflection:
                break;
            case NoRINDEX:
                G4cout << "NoRINDEX: " << G4endl
                       << "pre vol" << preName << G4endl
                       << "post vol" << postName << G4endl;
            default:
                if (yesSilicon) {
                    G4cout << "something weird: " << optProcLookup.at(stat) << G4endl
                           << "pre volume " << preName << G4endl
                           << "post volume " << postName << G4endl;
                }
                break;
        }
    }
}

void SteppingAction::processDetected(
    const G4VPhysicalVolume* preVol, const G4VPhysicalVolume* postVol, const G4Step* step)
{
    std::array<const G4VPhysicalVolume*, 2> volz = {preVol, postVol};
    for (const auto* v : volz) {
        const auto* sdLogVol = v->GetLogicalVolume();
        if (sdLogVol == nullptr) {
            G4cout << "NO LOGICAL VOLUME" << G4endl; G4cout.flush();
            continue;
        }

        auto* siSd = dynamic_cast<SiSensitiveDetector*>(sdLogVol->GetSensitiveDetector());
        if (siSd) siSd->processOptical(step);
    }
}
