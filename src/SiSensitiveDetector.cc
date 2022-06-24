#include <G4HCofThisEvent.hh>
#include <G4OpticalPhoton.hh>
#include <G4SDManager.hh>
#include <G4Step.hh>
#include <G4THitsCollection.hh>
#include <G4TouchableHistory.hh>

#include <SiHit.hh>
#include <SiSensitiveDetector.hh>

namespace {
    static const G4String SI_SENS_DET_SUFFIX = "_si_sens_det";
}

SiSensitiveDetector::
SiSensitiveDetector(const G4String& detectorName) :
    G4VSensitiveDetector(detectorName),
    thisCollectionName(detectorName + SI_SENS_DET_SUFFIX),
    hitsCollectionId(-1)
{
    collectionName.insert(thisCollectionName);
}

SiSensitiveDetector::~SiSensitiveDetector()
{ }

void SiSensitiveDetector::
Initialize(G4HCofThisEvent* hcote)
{
    // FIXME: copied from the scintillator class. maybe we should just subclass? ugh.
    // polymorphism in the hitscollection
    hitsCollection = new G4THitsCollection<VirtualHit>(
        SensitiveDetectorName, thisCollectionName);
    hitsCollectionId = G4SDManager::GetSDMpointer()->GetCollectionID(thisCollectionName);

    hcote->AddHitsCollection(hitsCollectionId, hitsCollection);
}

G4bool SiSensitiveDetector::
ProcessHits(G4Step*, G4TouchableHistory*)
{
    /* G4cout << "*** in optical" << G4endl; */
    // with 100% efficiency hits don't really register...
    /* if (step->GetTrack()->GetParticleDefinition() == G4OpticalPhoton::Definition()) */
        /* processOptical(step); */

    return false;
}

void SiSensitiveDetector::
processOptical(const G4Step* step)
{
    auto edep = step->GetTotalEnergyDeposit();
    if (edep == 0)
        return;

    auto pos = step->GetPostStepPoint()->GetPosition();
    // we want GlobalTime because it's the time since the last *event* started!
    // LocalTime is the time since the track was created (we don't want this)
    auto t = step->GetPostStepPoint()->GetGlobalTime();
    auto* hit = new SiHit(pos, t, edep);
    hitsCollection->insert(hit);
}
