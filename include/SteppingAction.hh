#pragma once

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class EventAction;

class G4LogicalVolume;
class G4VPhysicalVolume;

class SteppingAction : public G4UserSteppingAction
{
  public:
    SteppingAction();
    virtual ~SteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);

  private:
    void trackScintillation(const G4Step* step);
    void processOptical(const G4Step* step);
    void processDetected(const G4VPhysicalVolume* preVol, const G4VPhysicalVolume* postVol, const G4Step* step);
};
