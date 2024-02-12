#ifndef SensitiveDetector_h
#define SensitiveDetector_h 1

#include "G4VSensitiveDetector.hh"

class G4Step;
class G4TouchableHistory;

class SensitiveDetector : public G4VSensitiveDetector
{
public:

  SensitiveDetector(G4String);
  ~SensitiveDetector();

  G4bool ProcessHits(G4Step* aStep, G4TouchableHistory*) override;

private:
//;
  
};

#endif
