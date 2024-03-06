#include "LArDetectorConstruction.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4GenericMessenger.hh"

LArDetectorConstruction::LArDetectorConstruction()
  :DetectorConstruction(),
  fScYield(100)
{
  G4cout << "LArDetectorConstruction() called" << G4endl;

  fMessenger =  new G4GenericMessenger(this, "/detector/", "Detector Construction");
  fMessenger->DeclareProperty("scYield", fScYield, "scintillation yield (nPh / MeV)");
}

LArDetectorConstruction::~LArDetectorConstruction()
{

}

G4VPhysicalVolume* LArDetectorConstruction::Construct()
  
{
  G4VPhysicalVolume* vol = DetectorConstruction::Construct();
  UpdateMaterials();

  return vol;

}

void LArDetectorConstruction::UpdateMaterials()
{
  G4cout << "LArDetectorConstruction: Updating Materials" << G4endl;

  G4MaterialPropertiesTable *lAr_pt = fDefaultMaterial->GetMaterialPropertiesTable();

  std::vector<G4double> lar_Energy = { 9.6 * eV, 9.7 * eV, 9.8 * eV };
  std::vector<G4double> lar_SCINT = { 0.1, 1.0, 0.1 };
  lAr_pt->AddProperty("SCINTILLATIONCOMPONENT1", lar_Energy, lar_SCINT);
  lAr_pt->AddProperty("SCINTILLATIONCOMPONENT2", lar_Energy, lar_SCINT);
  lAr_pt->AddConstProperty("SCINTILLATIONYIELD", fScYield / MeV); // should be ~10,000
  lAr_pt->AddConstProperty("RESOLUTIONSCALE", 1.0);
  lAr_pt->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 6. * ns);
  lAr_pt->AddConstProperty("SCINTILLATIONTIMECONSTANT2", 1600. * ns);
  lAr_pt->AddConstProperty("SCINTILLATIONYIELD1", 0.3);
  lAr_pt->AddConstProperty("SCINTILLATIONYIELD2", 0.7);

}
