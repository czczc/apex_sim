#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh" // Added for G4ThreeVector

class G4Event;
class G4ParticleGun;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  PrimaryGeneratorAction();    
  ~PrimaryGeneratorAction();

  void GeneratePrimaries(G4Event*);

  // Getter methods for primary particle properties
  G4int GetPrimaryPDG() const { return fPrimaryPDG; }
  G4double GetPrimaryEnergy() const { return fPrimaryEnergy; }
  const G4ThreeVector& GetPrimaryPosition() const { return fPrimaryPosition; }
  const G4ThreeVector& GetPrimaryMomentumDirection() const { return fPrimaryMomentumDirection; }

private:
  G4ParticleGun*           fParticleGun;
  // Added private member variables
  G4int fPrimaryPDG;
  G4double fPrimaryEnergy;
  G4ThreeVector fPrimaryPosition;
  G4ThreeVector fPrimaryMomentumDirection;
};

#endif


