#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "RunAction.hh"

class RunAction;

class EventAction : public G4UserEventAction
{
  public:
    EventAction(RunAction*);
    virtual ~EventAction();

  public:
    virtual void   BeginOfEventAction(const G4Event*);
    virtual void   EndOfEventAction(const G4Event*);
    
  private:
    RunAction* fRun;
    
  };

#endif  
  
