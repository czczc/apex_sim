#include "SensitiveDetector.hh"

#include "G4Step.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4StepPoint.hh"
#include "G4ThreeVector.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"

SensitiveDetector::SensitiveDetector(G4String name): G4VSensitiveDetector(name)
{
  G4cout << "construct sensitive detector: " << this << G4endl;

}

SensitiveDetector::~SensitiveDetector()
{}

//----------------------------------------
G4bool SensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory* )
{
  G4AnalysisManager* man = G4AnalysisManager::Instance();
  G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

  // G4cout << "hit! DE: " << aStep->GetTotalEnergyDeposit() << G4endl;
  G4Track *track = aStep->GetTrack();
  G4int pdg = track->GetDynamicParticle()->GetPDGcode();

  // track->SetTrackStatus(fStopAndKill);
  G4StepPoint *point = aStep->GetPostStepPoint();    
  G4ThreeVector posPhoton = point->GetPosition();
  G4ThreeVector momPhoton = point->GetMomentum();
  G4double t = point->GetGlobalTime();
  G4double wlen = 1239.841939*eV/momPhoton.mag(); // wavelength in nm.

  man->FillNtupleIColumn(0, 0, evt);
  man->FillNtupleDColumn(0, 1, posPhoton[0]);
  man->FillNtupleDColumn(0, 2, posPhoton[1]);
  man->FillNtupleDColumn(0, 3, posPhoton[2]);
  man->FillNtupleDColumn(0, 4, t);
  man->FillNtupleDColumn(0, 5, wlen);
  man->FillNtupleIColumn(0, 6, pdg);

  man->AddNtupleRow(0);

  G4double ara_eff = 0.02;
  if(pdg == -22 && G4UniformRand() < ara_eff) {
    auto vol = point->GetTouchable()->GetVolume();
    auto posDet = vol->GetTranslation();
    // G4cout << "hit sd" << vol->GetName() << " @" << posDet 
    //     << ", " << aStep->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName() 
    //     << G4endl;
    man->FillNtupleIColumn(1, 0, evt);
    man->FillNtupleDColumn(1, 1, posDet[0]);
    man->FillNtupleDColumn(1, 2, posDet[1]);
    man->FillNtupleDColumn(1, 3, posDet[2]);
    man->FillNtupleDColumn(1, 4, t);
    man->AddNtupleRow(1); 
  }


  
  return true;
}

