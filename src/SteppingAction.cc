#include "SteppingAction.hh"

// Required Headers
#include "G4RunManager.hh"
#include "G4OpticalPhoton.hh"
#include "G4VProcess.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh" // Already present
#include "G4EventManager.hh"
#include "G4Event.hh"

#include "G4SteppingManager.hh" // Already present

#include "RunAction.hh" // Already present
#include "EventAction.hh" // Already present
#include "DetectorConstruction.hh" // Already present
#include "G4AnalysisManager.hh" // Already present

#include "G4PhysicalVolumeStore.hh" // Already present, might not be needed for this specific logic


SteppingAction::SteppingAction(RunAction* run, DetectorConstruction* det)
  :fRun(run),fDetector(det)
{ 
  // Constructor remains the same
}

SteppingAction::~SteppingAction()
{
}


void SteppingAction::UserSteppingAction(const G4Step* aStep)
{ 
  G4AnalysisManager* man = G4AnalysisManager::Instance();
  G4Track* track = aStep->GetTrack();

  // Check if the particle is an optical photon
  if (track->GetDefinition()->GetParticleName() == "opticalphoton")
  {
    // Record info at the creation of the optical photon (first step)
    if (track->GetCurrentStepNumber() == 1)
    {
      G4int evtID = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();
      
      G4ThreeVector pos = track->GetPosition();
      G4double time = track->GetGlobalTime();
      
      // Calculate wavelength from energy. Ensure h_Planck * c has correct units for desired wavelength unit.
      // (1.23984193 eV*um) is h*c in eV*um. If energy is in MeV, convert.
      // Geant4 standard energy unit is MeV.
      G4double energy = track->GetKineticEnergy() / eV; // Convert MeV (default) to eV for the formula
      G4double wavelength = 0.0; // Default to 0 if energy is zero
      if (energy > 0) {
        wavelength = (1.23984193 /* eV*um */) / energy * 1000; // Convert um to nm
      }

      G4ThreeVector momDir = track->GetMomentumDirection();
      G4ThreeVector pol = track->GetPolarization();

      G4String creatorProcessName = "primary"; // Default for primary particles
      const G4VProcess* creatorProcess = track->GetCreatorProcess();
      if (creatorProcess) {
        creatorProcessName = creatorProcess->GetProcessName();
      }

      G4int trackID = track->GetTrackID();
      G4int parentID = track->GetParentID();
      G4int pdgCode = track->GetDefinition()->GetPDGEncoding();

      // Fill "OpticalPhotons" Ntuple (ID 1)
      // Column order: evtID, x, y, z, t, wlen, pdg, mom_x, mom_y, mom_z, pol_x, pol_y, pol_z, creator_process, track_id, parent_id
      man->FillNtupleIColumn(1, 0, evtID);
      man->FillNtupleDColumn(1, 1, pos.x() / mm); 
      man->FillNtupleDColumn(1, 2, pos.y() / mm);
      man->FillNtupleDColumn(1, 3, pos.z() / mm);
      man->FillNtupleDColumn(1, 4, time / ns);    
      man->FillNtupleDColumn(1, 5, wavelength);  // Already in nm
      man->FillNtupleIColumn(1, 6, pdgCode);
      man->FillNtupleDColumn(1, 7, momDir.x());
      man->FillNtupleDColumn(1, 8, momDir.y());
      man->FillNtupleDColumn(1, 9, momDir.z());
      man->FillNtupleDColumn(1, 10, pol.x());
      man->FillNtupleDColumn(1, 11, pol.y());
      man->FillNtupleDColumn(1, 12, pol.z());
      man->FillNtupleSColumn(1, 13, creatorProcessName);
      man->FillNtupleIColumn(1, 14, trackID);
      man->FillNtupleIColumn(1, 15, parentID);
      
      man->AddNtupleRow(1);
    }
  }

  // The existing complex logic for filling a different Ntuple 1 has been effectively
  // removed by replacing the content of UserSteppingAction with the new logic above.
  // If any part of the old logic needs to be preserved for other purposes (e.g. different Ntuples),
  // it would need to be re-added carefully, ensuring no Ntuple ID conflicts.
  // The specific filtering `if (processName == "eIoni" || ... ) return;` is also removed
  // as it was part of the old logic.
}
