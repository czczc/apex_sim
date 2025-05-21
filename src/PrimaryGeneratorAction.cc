#include "PrimaryGeneratorAction.hh"

#include "G4SystemOfUnits.hh"
// G4ThreeVector.hh is included via PrimaryGeneratorAction.hh
#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleDefinition.hh" // Added for GetPDGEncoding()

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
  G4int n_particle = 1;
  fParticleGun     = new G4ParticleGun(n_particle);

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();

  // G4String particleName = "mu-";
  G4String particleName = "e-";

  fParticleGun->SetParticleDefinition(particleTable->FindParticle(particleName));
  fParticleGun->SetParticleEnergy(5. * MeV);
  fParticleGun->SetParticlePosition(G4ThreeVector(0., -3.0*m, 0.));
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1., 0., 0.));

  // Store primary particle properties
  fPrimaryPDG = fParticleGun->GetParticleDefinition()->GetPDGEncoding();
  fPrimaryEnergy = fParticleGun->GetParticleEnergy();
  fPrimaryPosition = fParticleGun->GetParticlePosition();
  fPrimaryMomentumDirection = fParticleGun->GetParticleMomentumDirection();
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{  
  fParticleGun->GeneratePrimaryVertex(anEvent);
}
