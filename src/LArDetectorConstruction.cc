#include "LArDetectorConstruction.hh"
#include "SensitiveDetector.hh" // Include the SD header

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4GenericMessenger.hh"
#include "G4SDManager.hh"         // Include SD Manager header
#include "G4LogicalVolumeStore.hh" // Include LV Store header
#include "G4LogicalVolume.hh"      // Include LV header
#include "G4RunManager.hh"         // Include Run Manager for checking initialization
#include "G4MaterialPropertiesTable.hh" // Include for Material Properties Table
#include "G4Exception.hh" // Include for G4Exception

LArDetectorConstruction::LArDetectorConstruction()
  :DetectorConstruction(),
  fScYield(20000)
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
  // Construct() must be called before ConstructSDandField()
  // G4RunManager takes care of the calling order
  G4VPhysicalVolume* vol = DetectorConstruction::Construct();
  UpdateMaterials();

  return vol;

}

void LArDetectorConstruction::UpdateMaterials()
{
  G4cout << "LArDetectorConstruction: Updating Materials" << G4endl;

  // Check if material exists before getting properties
  if (!fDefaultMaterial) {
      G4Exception("LArDetectorConstruction::UpdateMaterials", "NoDefaultMat", FatalException,
                  "fDefaultMaterial is null. Make sure DefineMaterials() is called first.");
      return; // Or handle appropriately
  }
  G4MaterialPropertiesTable *lAr_pt = fDefaultMaterial->GetMaterialPropertiesTable();

  // Check if properties table exists before adding properties
  if (!lAr_pt) {
      // If the material exists but has no properties table, create one
      lAr_pt = new G4MaterialPropertiesTable();
      fDefaultMaterial->SetMaterialPropertiesTable(lAr_pt);
      G4cout << "LArDetectorConstruction: Created new MaterialPropertiesTable for fDefaultMaterial." << G4endl;
  }

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

  // --- Add RINDEX property for Acrylic ---
  G4cout << "LArDetectorConstruction: Updating Acrylic Material Properties" << G4endl;
  if (!facrylic) {
      G4Exception("LArDetectorConstruction::UpdateMaterials", "NoAcrylicMat", FatalException,
                  "facrylic material pointer is null. Make sure DefineMaterials() in base class was successful.");
      return;
  }
  G4MaterialPropertiesTable* acrylic_pt = facrylic->GetMaterialPropertiesTable();
  if (!acrylic_pt) {
      // If acrylic exists but has no properties table, create one
      acrylic_pt = new G4MaterialPropertiesTable();
      facrylic->SetMaterialPropertiesTable(acrylic_pt);
      G4cout << "--> Created new MaterialPropertiesTable for facrylic." << G4endl;
  }

  // Define energy points for RINDEX (can use a simple range for constant RINDEX)
  const G4int nEntries_acrylic = 2;
  G4double acrylic_photonEnergy[nEntries_acrylic] = { 1.0*eV, 10.0*eV }; // Example energy range
  G4double acrylic_rindex[nEntries_acrylic] = { 1.49, 1.49 }; // Constant RINDEX

  acrylic_pt->AddProperty("RINDEX", acrylic_photonEnergy, acrylic_rindex, nEntries_acrylic);
  G4cout << "--> Added RINDEX property (1.49) to facrylic." << G4endl;
  // ----------------------------------------
// --- Add RINDEX property for Mylar ---
  G4cout << "LArDetectorConstruction: Updating Mylar Material Properties" << G4endl;
  if (!fMylar) {
      G4Exception("LArDetectorConstruction::UpdateMaterials", "NoMylarMat", FatalException,
                  "fMylar material pointer is null. Make sure DefineMaterials() in base class was successful.");
      // return; // No return here, might want to continue updating other materials if possible
  } else {
      G4MaterialPropertiesTable* mylar_pt = fMylar->GetMaterialPropertiesTable();
      if (!mylar_pt) {
          // If mylar exists but has no properties table, create one
          mylar_pt = new G4MaterialPropertiesTable();
          fMylar->SetMaterialPropertiesTable(mylar_pt);
          G4cout << "--> Created new MaterialPropertiesTable for fMylar." << G4endl;
      }

      // Define energy points for RINDEX (use a simple range for constant RINDEX)
      // Placeholder value - consult material data for accurate RINDEX if needed.
      const G4int nEntries_mylar = 2;
      G4double mylar_photonEnergy[nEntries_mylar] = { 1.0*eV, 10.0*eV }; // Example energy range
      G4double mylar_rindex[nEntries_mylar] = { 1.65, 1.65 }; // Placeholder constant RINDEX for Mylar

      // Check if RINDEX already exists before adding
      if (!mylar_pt->GetProperty("RINDEX")) {
          mylar_pt->AddProperty("RINDEX", mylar_photonEnergy, mylar_rindex, nEntries_mylar);
          G4cout << "--> Added RINDEX property (~1.65) to fMylar." << G4endl;
      } else {
          G4cout << "--> RINDEX property already exists for fMylar." << G4endl;
      }
  }
  // ----------------------------------------

}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Method to construct Sensitive Detectors and Fields
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void LArDetectorConstruction::ConstructSDandField()
{
  G4cout << "LArDetectorConstruction: Constructing Sensitive Detectors..." << G4endl;

  // Call base class method (good practice, though it might be empty)
  // DetectorConstruction::ConstructSDandField(); // Base class doesn't have this method

  // Get SD manager
  G4SDManager* sdManager = G4SDManager::GetSDMpointer();
  G4String sdName;

  // --- Check if SD already exists ---
  SensitiveDetector* arapucaSD = dynamic_cast<SensitiveDetector*>(sdManager->FindSensitiveDetector(sdName="/ArapucaSD", false)); // false -> don't warn if not found

  if (!arapucaSD) {
      // Create Sensitive Detector instance if it doesn't exist
      // The name "/ArapucaSD" should be unique
      arapucaSD = new SensitiveDetector(sdName = "/ArapucaSD");
      sdManager->AddNewDetector(arapucaSD); // Register with manager
      G4cout << "--> Created and registered Sensitive Detector: /ArapucaSD" << G4endl;
  } else {
      G4cout << "--> Found existing Sensitive Detector: /ArapucaSD" << G4endl;
  }


  // Get Logical Volume Store
  G4LogicalVolumeStore* lvStore = G4LogicalVolumeStore::GetInstance();

  // Find the logical volumes by name and attach SD
  G4LogicalVolume* logicArapuca = lvStore->GetVolume("Arapuca");
  if (logicArapuca) {
    logicArapuca->SetSensitiveDetector(arapucaSD);
    G4cout << "--> Attached Sensitive Detector to Logical Volume: Arapuca" << G4endl;
  } else {
    G4cerr << "!!! WARNING: Logical Volume 'Arapuca' not found in ConstructSDandField!" << G4endl;
  }

  G4LogicalVolume* logicArapucaShort = lvStore->GetVolume("ArapucaShort");
  if (logicArapucaShort) {
    logicArapucaShort->SetSensitiveDetector(arapucaSD);
     G4cout << "--> Attached Sensitive Detector to Logical Volume: ArapucaShort" << G4endl;
  } else {
     G4cerr << "!!! WARNING: Logical Volume 'ArapucaShort' not found in ConstructSDandField!" << G4endl;
  }
// --- Define and attach Cathode Optical Surface ---
  G4cout << "--> Defining and attaching Cathode Optical Surface..." << G4endl;
  G4LogicalVolume* logicCathode = lvStore->GetVolume("Cathode");
  if (logicCathode) {
      G4OpticalSurface* CathodeSurface = new G4OpticalSurface("CathodeSurface");
      CathodeSurface->SetType(dielectric_metal);
      CathodeSurface->SetModel(unified);
      CathodeSurface->SetFinish(ground); // Assuming similar finish to anode
      CathodeSurface->SetSigmaAlpha(0.0*deg);

      // Use same energy points and reflectivity as Anode from DetectorConstruction.cc
      const G4int nEntries_cathode = 8;
      G4double Cathode_PhotonEnergy[nEntries_cathode] =
        { 2.5*eV, 5.0*eV, 7.0*eV, 7.5*eV, 8.0*eV, 9.0*eV, 9.5*eV, 10.136*eV};
      G4double Cathode_r[nEntries_cathode] = {0.20, 0.20, 0.20, 0.20, 0.0, 0.0, 0.0, 0.0}; // Same as Anode_r
      G4double Cathode_e[nEntries_cathode] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}; // Same as Anode_e

      G4MaterialPropertiesTable* CathodeSurface_pt = new G4MaterialPropertiesTable();
      CathodeSurface_pt->AddProperty("REFLECTIVITY", Cathode_PhotonEnergy, Cathode_r, nEntries_cathode);
      CathodeSurface_pt->AddProperty("EFFICIENCY", Cathode_PhotonEnergy, Cathode_e, nEntries_cathode);

      CathodeSurface->SetMaterialPropertiesTable(CathodeSurface_pt);

      new G4LogicalSkinSurface("CathodeSkinSurface", logicCathode, CathodeSurface);
      G4cout << "--> Attached Optical Surface to Logical Volume: Cathode" << G4endl;

  } else {
       G4cerr << "!!! WARNING: Logical Volume 'Cathode' not found when trying to attach optical surface!" << G4endl;
  }
  // ---------------------------------------------

  // Note: We are assigning the *same* SD instance to both logical volumes.
  // The SensitiveDetector class will need to handle hits from both types
  // (e.g., by checking the volume name or copy number in the G4Step).
}
