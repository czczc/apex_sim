#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"

class G4Event;
class G4ParticleGun;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  PrimaryGeneratorAction();    
  ~PrimaryGeneratorAction();

  void GeneratePrimaries(G4Event*);

private:
  G4ParticleGun*           fParticleGun;
};

#endif


