// Module 3 simulation
// Authors: L. Paulucci & F. Marinho
// Date: 7th October 2022
//
// Added modifications should be reported in arapuca.cc header comments

#ifndef LArDetectorConstruction_h
#define LArDetectorConstruction_h 1

#include "DetectorConstruction.hh"

class G4GenericMessenger;

class LArDetectorConstruction : public DetectorConstruction
{
public:

  LArDetectorConstruction();
  ~LArDetectorConstruction();

  G4VPhysicalVolume* Construct();

  void UpdateMaterials();
    
  G4double fScYield; // photons per MeV

  G4GenericMessenger *fMessenger;
};

#endif
