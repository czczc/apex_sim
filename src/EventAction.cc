#include "EventAction.hh"
#include "RunAction.hh"

#include "G4Event.hh"
#include "G4AnalysisManager.hh"
#include "G4Trajectory.hh"
#include "G4TrajectoryContainer.hh"
#include "G4VVisManager.hh"


EventAction::EventAction(RunAction* run)
:fRun(run)
{}


EventAction::~EventAction()
{}


void EventAction::BeginOfEventAction(const G4Event* evt)
{  

}


void EventAction::EndOfEventAction(const G4Event* evt)
{

  // G4TrajectoryContainer* trjContainer = evt->GetTrajectoryContainer();
  // if (!trjContainer) {
  //   G4cout << "no trajectory!" << G4endl;
  // }

  // G4int nTrj = trjContainer ? trjContainer->entries() : 0;

  // // extract the trajectories and draw them
  // if(G4VVisManager::GetConcreteInstance())
  // {
  //   for(G4int i = 0; i < nTrj; ++i)
  //   {
  //     auto trj = (*trjContainer)[i];
  //     G4cout << "track " << trj->GetTrackID() << ", " 
  //       << trj->GetParticleName() << ", " 
  //       << trj->GetPointEntries() << " points" 
  //       << G4endl;
  //     // if(trj->GetParticleName() == "opticalphoton")
  //     // {
  //     //   trj->SetForceDrawTrajectory(fForcedrawphotons);
  //     //   trj->SetForceNoDrawTrajectory(fForcenophotons);
  //     // }
  //     // trj->DrawTrajectory();
  //   }
  // }
  
  G4int evtID = evt->GetEventID();
  G4cout << "Event " << evtID << " done." << G4endl;


  auto man = G4AnalysisManager::Instance();

  man->FillNtupleIColumn(0, 0, evtID);
  // man->FillNtupleIColumn(0, 1, nTrj);

  man->AddNtupleRow(); 

}
  

