// Module 3 APEX standalone light simulation
// Authors: L. Paulucci & F. Marinho
// Date: 7th October 2022
//
// Added modifications should be reported in pdunevd.cc header comments

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

class G4GenericMessenger;

#include "G4VUserDetectorConstruction.hh"
#include "G4Box.hh"
#include "G4SubtractionSolid.hh"
#include "G4Cons.hh"
#include "G4Material.hh"
#include "G4PVPlacement.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4UserLimits.hh"
#include "G4PVParameterised.hh"

#include "G4EqMagElectricField.hh"
#include "G4PropagatorInField.hh"
#include "G4TransportationManager.hh"
#include "G4ChordFinder.hh"
#include "G4ClassicalRK4.hh"

#include "G4GDMLParser.hh"

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:

  DetectorConstruction();
  ~DetectorConstruction();

  G4VPhysicalVolume* Construct() override;
  void ConstructSDandField() override;

    
private:
  G4bool fCheckOverlap;
  G4GenericMessenger *fMessenger;
  G4double fScYield;
  G4bool fCerenkovOn;

  G4double fthickness;

  G4double fLatY;
  G4double fLatZ;

  G4double fwindow;
  G4double fwindowY;
  G4double fwindowZ;

  G4double      fWorldSizeX;
  G4double      fWorldSizeY;
  G4double      fWorldSizeZ;
  G4double      fCryostat_x;
  G4double      fCryostat_y;
  G4double      fCryostat_z;
  G4double      fFC_x;
  G4double      fFC_y;
  G4double      fFC_z;
  G4double      fFCOut_x;
  G4double      fFCOut_y;
  G4double      fFCOut_z;
  G4double      fAra_x;
  G4double      fAra_y; 
  G4double      fAra_z;
  G4double      fAra_offset;
  G4double      fAras_yspacing;
  
  G4double      fCathode_x;
  G4double      fCathode_z;
  G4double      fAPA_x;
  G4double      fAPA_y;
  G4double      fAPA_z;

  G4double fptp_width;

  G4double fvert_bar_x;
  G4double fvert_bar_y;
  G4double fvert_bar_z;
  
  
// Materials

  G4Material*   fDefaultMaterial;
  G4Material*   fSteel;
  G4Material*   fAluminium;
  G4Material*   fG10;
  G4Material*   fBase;
  G4Material*   facrylic;
  G4Material*   fPTP;

// Volumes

  G4VPhysicalVolume* fPhysiWorld;
  G4LogicalVolume*   fLogicWorld;  
  G4Box*             fSolidWorld;
  
  G4VPhysicalVolume* fPhysiVol;
  G4LogicalVolume*   fLogicVol;  
  G4Box*             fSolidVol;

  G4LogicalVolume *fLogicArapuca, *fLogicArapucaShort;


  void DefineMaterials();
  G4VPhysicalVolume* ConstructLine();     

  G4GDMLParser fParser;
  
};

#endif
