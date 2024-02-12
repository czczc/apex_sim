#include "RunAction.hh"
#include "G4AnalysisManager.hh"

#include "G4Run.hh"


RunAction::RunAction() 
{   
}


RunAction::~RunAction()
{
}


void RunAction::BeginOfRunAction(const G4Run* run)
{
   

  G4cout << "### Run " << run->GetRunID() << " start." << G4endl;
  
  G4AnalysisManager* man = G4AnalysisManager::Instance();
  
  // G4cout << "Using " << man->GetType() << " analysis manager" << G4endl;

  // Open an output file
  man->OpenFile("out/sim.root");
  man->SetVerboseLevel(1);
  man->SetNtupleMerging(true);

  // man->SetFirstNtupleId(1);

  // man->CreateNtuple("Run", "truth info");
  // man->CreateNtupleIColumn("evtID");
  // man->CreateNtupleIColumn("nTrj");
  // man->CreateNtupleIColumn("pdg");
  // man->CreateNtupleIColumn("id");
  // man->CreateNtupleIColumn("mid");
  // man->CreateNtupleDColumn("x");
  // man->CreateNtupleDColumn("y");
  // man->CreateNtupleDColumn("z");
  // man->CreateNtupleDColumn("de");
  // man->CreateNtupleDColumn("e");
  // man->CreateNtupleIColumn("vol");
  // man->CreateNtupleIColumn("volrep");
  // man->CreateNtupleIColumn("mvol");
  // man->CreateNtupleIColumn("mvolrep");
  // man->CreateNtupleIColumn("inter");

  man->CreateNtuple("OP", "OpticalPhotons");
  man->CreateNtupleIColumn("event");
  man->CreateNtupleDColumn("x");
  man->CreateNtupleDColumn("y");
  man->CreateNtupleDColumn("z");
  man->CreateNtupleDColumn("t");
  man->CreateNtupleDColumn("wlen");
  man->CreateNtupleIColumn("pdg");
  man->FinishNtuple(0);

  man->CreateNtuple("Hits", "Hits");
  man->CreateNtupleIColumn("event");
  man->CreateNtupleDColumn("x");
  man->CreateNtupleDColumn("y");
  man->CreateNtupleDColumn("z");
  man->CreateNtupleDColumn("t");
  man->FinishNtuple(1);
  
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







