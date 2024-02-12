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
  SetUserAction(new PrimaryGeneratorAction());
  auto runAction = new RunAction();
  SetUserAction(runAction);
  SetUserAction(new EventAction(runAction));
  SetUserAction(new SteppingAction(runAction,fDetector));
}  


