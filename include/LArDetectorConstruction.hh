// Module 3 simulation
// Authors: L. Paulucci & F. Marinho
// Date: 7th October 2022
//
// Added modifications should be reported in arapuca.cc header comments

#ifndef LArDetectorConstruction_h
#define LArDetectorConstruction_h 1

#include "DetectorConstruction.hh"
#include "globals.hh" // For G4bool, etc.

// Forward declarations
class G4GenericMessenger;
class G4LogicalVolume;
class SensitiveDetector;

class LArDetectorConstruction : public DetectorConstruction
{
public:

  LArDetectorConstruction();
  ~LArDetectorConstruction();

  G4VPhysicalVolume* Construct();

  void UpdateMaterials();
  virtual void ConstructSDandField(); // Override SD method
    
  G4double fScYield; // photons per MeV

  G4GenericMessenger *fMessenger;
};

#endif
