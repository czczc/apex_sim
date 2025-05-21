#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "SteppingAction.hh"
#include "EventAction.hh"


ActionInitialization::ActionInitialization(DetectorConstruction* det)
  : G4VUserActionInitialization(),
    fDetector(det)
{}


ActionInitialization::~ActionInitialization()
{}


void ActionInitialization::BuildForMaster() const
{
  SetUserAction(new RunAction());
}


void ActionInitialization::Build() const
{
  auto primaryGenerator = new PrimaryGeneratorAction();
  SetUserAction(primaryGenerator);

  auto runAction = new RunAction();
  SetUserAction(runAction);

  SetUserAction(new EventAction(runAction, primaryGenerator)); // Pass both runAction and primaryGenerator

  SetUserAction(new SteppingAction(runAction,fDetector));
}


