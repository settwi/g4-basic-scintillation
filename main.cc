#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"
#include "PhysicsList.hh"

#include "G4RunManagerFactory.hh"

#include "G4UImanager.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "Randomize.hh"
#include "G4OpticalParameters.hh"

int main(int argc,char** argv)
{
  G4UIExecutive* ui = nullptr;
  if (argc == 1) {
    ui = new G4UIExecutive(argc, argv);
  }

  auto* runManager =
    G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);

  runManager->SetUserInitialization(new DetectorConstruction());
  runManager->SetUserInitialization(new PhysicsList());
  runManager->SetUserInitialization(new ActionInitialization());
  
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  // need to enable scintillation
  G4OpticalParameters::Instance()->SetProcessActivation("Scintillation", true);
  // I have found Cherenkov radiation to be error-prone
  G4OpticalParameters::Instance()->SetProcessActivation("Cerenkov", true);

  auto* uiMan = G4UImanager::GetUIpointer();
  bool batchMode = (ui == nullptr);
  if (batchMode) { 
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    uiMan->ApplyCommand(command + fileName);
  }
  else { 
    uiMan->ApplyCommand("/control/execute macros/init_vis.mac");
    ui->SessionStart();
    delete ui;
  }
  
  delete visManager;
  delete runManager;
}
