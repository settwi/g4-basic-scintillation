#pragma once

#include <G4String.hh>
#include <G4VSensitiveDetector.hh>

#include <VirtualHit.hh>

class G4HCofThisEvent;
class G4Step;
class G4TouchableHistory;
template <class T> class G4THitsCollection;

class SiSensitiveDetector : public G4VSensitiveDetector
{
    public:
        SiSensitiveDetector(const G4String& detectorName);
        ~SiSensitiveDetector();

        void Initialize(G4HCofThisEvent* hcote) override;
        G4bool ProcessHits(G4Step* step, G4TouchableHistory*) override;
        void processOptical(const G4Step* step);
    private:
        G4String thisCollectionName;
        G4THitsCollection<VirtualHit>* hitsCollection;
        G4int hitsCollectionId;
};
