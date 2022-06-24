#include "RunAction.hh"
#include "Analysis.hh"
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"

#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4SystemOfUnits.hh"
#include "G4Threading.hh"

RunAction::RunAction() :
  G4UserRunAction()
{}

RunAction::~RunAction()
{}

void RunAction::BeginOfRunAction(const G4Run*)
{ 
  Analysis::instance().initFiles(IsMaster());
}

void RunAction::EndOfRunAction(const G4Run*)
{
  Analysis::instance().saveFiles(IsMaster());
}
