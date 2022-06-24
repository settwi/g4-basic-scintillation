#pragma once

#include <G4UserEventAction.hh>
#include <G4Cache.hh>

class RunAction;

class EventAction : public G4UserEventAction
{
  public:
    EventAction();
    virtual ~EventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void addScintPhot(std::size_t numToAdd)
    { scintillatedPhotonsPerEvent.Put(scintillatedPhotonsPerEvent.Get() + numToAdd); }
  private:
    G4Cache<std::size_t> scintillatedPhotonsPerEvent;
};
