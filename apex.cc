#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"

#include "G4RunManagerFactory.hh"
#include "FTFP_BERT.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4OpticalParameters.hh"
#include "G4OpticalPhysics.hh"

#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#include "G4Types.hh"
#include "Randomize.hh"

// #include "QGSP_BERT_HP.hh"

int main(int argc, char **argv)
{
  // choose the Random engine && set random seed with system time
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  G4long seed = time(NULL);
  CLHEP::HepRandom::setTheSeed(seed);

  // detect interactive mode (if no arguments) and define UI session
  G4UIExecutive* ui = nullptr;
  if(argc == 1)
  {
    ui = new G4UIExecutive(argc, argv);
  }

  // new way since 10.7.1 
  // (old way is using G4MTRunManager or G4RunManager depending on if G4MULTITHREADED is defined)
  auto runManager = G4RunManagerFactory::CreateRunManager();


  //---------------------------------------------------------------
  // set physics list

  // auto physics = new PhysicsList();
  // runManager->SetUserInitialization(physics);
  G4VModularPhysicsList* physicsList = new FTFP_BERT;
  physicsList->ReplacePhysics(new G4EmStandardPhysics_option4());

  G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();
  auto opticalParams               = G4OpticalParameters::Instance();

  opticalParams->SetProcessActivation("Cerenkov", false); // turn off Cerenkov light by default since PD is not sensitive to it
  // opticalParams->SetProcessActivation("Scintillation", false);
  opticalParams->SetBoundaryInvokeSD(true); // IMPORTANT! default is false

  // opticalParams->SetWLSTimeProfile("delta");

  opticalParams->SetScintTrackSecondariesFirst(true);

  opticalParams->SetCerenkovMaxPhotonsPerStep(100);
  opticalParams->SetCerenkovMaxBetaChange(10.0);
  opticalParams->SetCerenkovTrackSecondariesFirst(true);

  physicsList->RegisterPhysics(opticalPhysics);
  runManager->SetUserInitialization(physicsList);
  //---------------------------------------------------------------


  DetectorConstruction *det = new DetectorConstruction;
  runManager->SetUserInitialization(det);
  
  runManager->SetUserInitialization(new ActionInitialization(det));

  // ** You need set those at the beginning of the .mac file
  // runManager->SetNumberOfThreads(2);
  // runManager->Initialize();


  // visualization manager
  G4VisManager *visManager = new G4VisExecutive;
  visManager->Initialize();

  G4UImanager *UImanager = G4UImanager::GetUIpointer();
  // set .mac file search path to include mac/ directory
  UImanager->ApplyCommand("/control/macroPath .:mac"); 
  if (ui) 
  {
    // interactive mode
    UImanager->ApplyCommand("/control/execute vis.mac");
    if(ui->IsGUI())
    {
      UImanager->ApplyCommand("/control/execute gui.mac");
    }
    ui->SessionStart();
    delete ui;
  }
  else 
  {
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command + fileName);
  }

  // job termination
  delete visManager;
  delete runManager;
  return 0;
}
