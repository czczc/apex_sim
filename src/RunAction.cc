#include "RunAction.hh"
#include "G4AnalysisManager.hh"

#include "G4Run.hh"


RunAction::RunAction() 
{  
  G4AnalysisManager* man = G4AnalysisManager::Instance();

  man->SetDefaultFileType("root");
  man->SetNtupleMerging(true);
  man->SetVerboseLevel(0);
  man->SetFileName("out/sim");
  
  // G4cout << "Using " << man->GetType() << " analysis manager" << G4endl;

  // Open an output file
  // man->OpenFile("out/sim.root");
  // man->SetVerboseLevel(1);
  // man->SetNtupleMerging(true);

  man->SetFirstNtupleId(0); // Ntuple IDs start from 0

  // Ntuple ID 0: GenInfo
  man->CreateNtuple("GenInfo", "Generator Level Information");
  man->CreateNtupleIColumn("evtID");
  man->CreateNtupleIColumn("gen_pdg");
  man->CreateNtupleDColumn("gen_energy");
  man->CreateNtupleDColumn("gen_pos_x");
  man->CreateNtupleDColumn("gen_pos_y");
  man->CreateNtupleDColumn("gen_pos_z");
  man->CreateNtupleDColumn("gen_mom_x");
  man->CreateNtupleDColumn("gen_mom_y");
  man->CreateNtupleDColumn("gen_mom_z");
  man->FinishNtuple();

  // Ntuple ID 1: OpticalPhotons
  man->CreateNtuple("OpticalPhotons", "Optical Photon Data");
  man->CreateNtupleIColumn("evtID");
  man->CreateNtupleDColumn("x");
  man->CreateNtupleDColumn("y");
  man->CreateNtupleDColumn("z");
  man->CreateNtupleDColumn("t");
  man->CreateNtupleDColumn("wlen");
  man->CreateNtupleIColumn("pdg"); // Optical photon's PDG code
  man->CreateNtupleDColumn("mom_x");
  man->CreateNtupleDColumn("mom_y");
  man->CreateNtupleDColumn("mom_z");
  man->CreateNtupleDColumn("pol_x");
  man->CreateNtupleDColumn("pol_y");
  man->CreateNtupleDColumn("pol_z");
  man->CreateNtupleSColumn("creator_process");
  man->CreateNtupleIColumn("track_id");
  man->CreateNtupleIColumn("parent_id");
  man->FinishNtuple();

  // Ntuple ID 2: Hits
  man->CreateNtuple("Hits", "Hits");
  man->CreateNtupleIColumn("evtID");
  man->CreateNtupleDColumn("x");
  man->CreateNtupleDColumn("y");
  man->CreateNtupleDColumn("z");
  man->CreateNtupleDColumn("t");
  man->FinishNtuple();
   
}


RunAction::~RunAction()
{
}


void RunAction::BeginOfRunAction(const G4Run* run)
{
    G4cout << "### Run " << run->GetRunID() << " start." << G4endl;
    auto man = G4AnalysisManager::Instance();
		man->OpenFile();
}


void RunAction::EndOfRunAction(const G4Run* run)
{
  if(isMaster) {
    G4cout << "End of run " << run->GetRunID() 
      << ", total events: " << run->GetNumberOfEvent() 
      << G4endl; 
  } 

  G4AnalysisManager* man = G4AnalysisManager::Instance();
  // G4cout << "end of run: write root file" << G4endl;
  man->Write();
  man->CloseFile();
  
}







