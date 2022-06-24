#include <G4Gamma.hh>
#include "G4HCofThisEvent.hh"
#include "G4OpticalPhoton.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4THitsCollection.hh"
#include "G4TouchableHistory.hh"

#include "CrystalSensitiveDetector.hh"

namespace {
    static const G4String SCINT_SENS_DET_SUFFIX = "_scint_sens_det";
}

CrystalSensitiveDetector::
CrystalSensitiveDetector(const G4String& detectorName) :
    G4VSensitiveDetector(detectorName),
    thisCollectionName(detectorName + SCINT_SENS_DET_SUFFIX),
    hitsCollectionId(-1)
{
    collectionName.insert(thisCollectionName);
}

CrystalSensitiveDetector::
~CrystalSensitiveDetector()
{ }

void CrystalSensitiveDetector::
Initialize(G4HCofThisEvent* hcote)
{
    // polymorphism in the hitscollection
    hitsCollection = new G4THitsCollection<VirtualHit>(
        SensitiveDetectorName, thisCollectionName);
    hitsCollectionId = G4SDManager::GetSDMpointer()->GetCollectionID(thisCollectionName);

    hcote->AddHitsCollection(hitsCollectionId, hitsCollection);
}

G4bool CrystalSensitiveDetector::
ProcessHits(G4Step* step, G4TouchableHistory* /* unused */)
{
    auto def = step->GetTrack()->GetParticleDefinition();
    // we don't want optical photons to count as hits
    // especially if scintillation is on
    if (def == G4OpticalPhoton::Definition()) return false;

    G4double depositedEnergy = step->GetTotalEnergyDeposit();
    if (depositedEnergy == 0) return false;

    G4ThreeVector pos = step->GetPostStepPoint()->GetPosition();

    auto* hit = new CrystalHit(depositedEnergy, pos);
    hitsCollection->insert(hit);
    return true;
}
