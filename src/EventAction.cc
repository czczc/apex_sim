#include "EventAction.hh"
#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh" // Added include

#include "G4Event.hh"
#include "G4AnalysisManager.hh"
#include "G4Trajectory.hh"
#include "G4TrajectoryContainer.hh"
#include "G4VVisManager.hh"


EventAction::EventAction(RunAction* run, PrimaryGeneratorAction* primaryGenerator)
: G4UserEventAction(), fRun(run), fPrimaryGenerator(primaryGenerator) // Modified constructor
{}


EventAction::~EventAction()
{}


void EventAction::BeginOfEventAction(const G4Event* evt)
{  

}


void EventAction::EndOfEventAction(const G4Event* evt)
{
  G4AnalysisManager* man = G4AnalysisManager::Instance();
  G4int evtID = evt->GetEventID();

  // Fill Generator Information Ntuple (ID 0)
  if (fPrimaryGenerator) // Good practice to check pointer
  {
    G4int genPDG = fPrimaryGenerator->GetPrimaryPDG();
    G4double genEnergy = fPrimaryGenerator->GetPrimaryEnergy();
    const G4ThreeVector& genPos = fPrimaryGenerator->GetPrimaryPosition();
    const G4ThreeVector& genMom = fPrimaryGenerator->GetPrimaryMomentumDirection();

    // Assuming Ntuple ID 0 is "GenInfo" and columns are in order:
    // evtID, gen_pdg, gen_energy, gen_pos_x, gen_pos_y, gen_pos_z, gen_mom_x, gen_mom_y, gen_mom_z
    man->FillNtupleIColumn(0, 0, evtID);
    man->FillNtupleIColumn(0, 1, genPDG);
    man->FillNtupleDColumn(0, 2, genEnergy);
    man->FillNtupleDColumn(0, 3, genPos.x());
    man->FillNtupleDColumn(0, 4, genPos.y());
    man->FillNtupleDColumn(0, 5, genPos.z());
    man->FillNtupleDColumn(0, 6, genMom.x());
    man->FillNtupleDColumn(0, 7, genMom.y());
    man->FillNtupleDColumn(0, 8, genMom.z());
    man->AddNtupleRow(0);
  }

  // The old code for filling eventID into (old) Ntuple 0 and trajectory processing is now removed.
  // Optical photon data will be handled in SteppingAction.
  // Trajectory visualization code can be kept if needed, but is not part of this task.
  // For example, the G4VVisManager related code can remain if visualization is desired.
  // The line "G4cout << "Event " << evtID << " done." << G4endl;" can also be kept.

  // If there was trajectory processing code that is still desired for visualization,
  // it should be placed here, separate from Ntuple filling.
  // For instance:
  // G4TrajectoryContainer* trjContainer = evt->GetTrajectoryContainer();
  // if (G4VVisManager::GetConcreteInstance() && trjContainer)
  // {
  //   G4int nTrj = trjContainer->entries();
  //   for(G4int i = 0; i < nTrj; ++i)
  //   {
  //     auto trj = (*trjContainer)[i];
  //     // Potentially draw trajectory
  //     // trj->DrawTrajectory();
  //   }
  // }
  
  G4cout << "Event " << evtID << " done." << G4endl; // Keep this line
}

