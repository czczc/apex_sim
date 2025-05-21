#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
// RunAction.hh is already included by G4UserEventAction or indirectly,
// but explicit include is fine. If it causes issues, it can be removed.
// For now, let's assume it's needed or harmless.
#include "RunAction.hh"

class RunAction; // Forward declaration
class PrimaryGeneratorAction; // Forward-declare PrimaryGeneratorAction

class EventAction : public G4UserEventAction
{
  public:
    EventAction(RunAction* run, PrimaryGeneratorAction* primaryGenerator); // Modified constructor
    virtual ~EventAction();

  public:
    virtual void   BeginOfEventAction(const G4Event*);
    virtual void   EndOfEventAction(const G4Event*);
    
  private:
    RunAction* fRun;
    PrimaryGeneratorAction* fPrimaryGenerator; // Added private member
    
  };

#endif
  
