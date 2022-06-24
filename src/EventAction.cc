#include <Analysis.hh>
#include "EventAction.hh"
#include "RunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

EventAction::EventAction() :
    G4UserEventAction()
{
  scintillatedPhotonsPerEvent.Put(0);
} 

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event*)
{
  scintillatedPhotonsPerEvent.Put(0);
}

void EventAction::EndOfEventAction(const G4Event* evt)
{
  if (!evt) return;
  auto& anInst = Analysis::instance();
  anInst.saveEvent(evt);
  anInst.saveScintillated(scintillatedPhotonsPerEvent.Get());
}
