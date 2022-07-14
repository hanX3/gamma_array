#include "DetectorConstruction.hh"
#include "GeSD.hh"
#include "CsISD.hh"
#include "SiSD.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Torus.hh"
#include "G4Tubs.hh"
#include "G4Hype.hh"
#include "G4Trd.hh"
#include "G4Orb.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4VPhysicalVolume.hh"
#include "G4SDManager.hh"

// public methods
DetectorConstruction::DetectorConstruction()
: mat_vaccum(NULL),
  mat_air(NULL),
  mat_ge(NULL),
  mat_csi(NULL),
  mat_al(NULL),
  mat_mylar(NULL),
  mat_si(NULL),
  mat_pcb(NULL)
{

}

//
DetectorConstruction::~DetectorConstruction()
{

}

//
G4VPhysicalVolume *DetectorConstruction::Construct()
{
  // Define materials
  DefineMaterials();

  // Define volumes
  return DefineVolumes();
}

//
void DetectorConstruction::DefineMaterials()
{
  G4NistManager* nist = G4NistManager::Instance();
  mat_vaccum = nist->FindOrBuildMaterial("G4_Galactic");
  mat_air = nist->FindOrBuildMaterial("G4_AIR");
  mat_ge =  nist->FindOrBuildMaterial("G4_Ge");
  mat_csi = nist->FindOrBuildMaterial("G4_CESIUM_IODIDE");
  mat_al = nist->FindOrBuildMaterial("G4_Al");
  mat_mylar = nist->FindOrBuildMaterial("G4_MYLAR");
  mat_si = nist->FindOrBuildMaterial("G4_Si");
  mat_pcb = nist->FindOrBuildMaterial("G4_POLYCHLOROSTYRENE");

  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
	G4cout << "Define Materials sucefully" << G4endl;
}

//
G4LogicalVolume *DetectorConstruction::GetGeArrayLog(G4String ge_array_name)
{
  G4cout << " --->: GetGeArray, begin" << G4endl;

  G4LogicalVolume *ge_array_log = NULL;
  G4Sphere *solid_ge_array = new G4Sphere("Ge_Array", 0, Ge_ARRAY_R, 0, CLHEP::twopi, 0, CLHEP::pi);
  ge_array_log = new G4LogicalVolume(solid_ge_array, mat_air, ge_array_name);

  //  color
  G4VisAttributes  *p_vis_att = new G4VisAttributes(G4Colour(1.0, 1.0, 0.0, 0.));
  p_vis_att->SetForceSolid(false);
  ge_array_log->SetVisAttributes(p_vis_att);

  return ge_array_log;
}

//
G4LogicalVolume *DetectorConstruction::GetGeLog(G4String ge_name)
{
  G4cout << " --->: GetGe, begin" << G4endl;

  G4LogicalVolume *ge_log = NULL;
  G4Tubs *solid_ge = new G4Tubs("GeTubs", 0, GE_R, GE_HEIGHT, 0, CLHEP::twopi);
  G4Tubs *solid_ln2_hole = new G4Tubs("LN2HoleTubs", 0, LN2_HOLE_R, LN2_HOLE_DEEP, 0, CLHEP::twopi);
  G4SubtractionSolid *sub_ge = new G4SubtractionSolid("GeTubs-LN2HoleTubs", solid_ge, solid_ln2_hole, G4Transform3D(G4RotationMatrix(), G4ThreeVector(0,0,GE_HEIGHT-LN2_HOLE_DEEP)));
  ge_log = new G4LogicalVolume(sub_ge, mat_ge, ge_name);

  //  color
  G4VisAttributes  *p_vis_att = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0, 1.0));
  p_vis_att->SetForceSolid(true);
  ge_log->SetVisAttributes(p_vis_att);

  return ge_log;
}

//
G4LogicalVolume *DetectorConstruction::GetCsIArrayLog(G4String csi_array_name)
{
  G4cout << " --->: GetCsIArray, begin" << G4endl;

  G4LogicalVolume *csi_array_log = NULL;
  G4Sphere *solid_csi_array = new G4Sphere("CsI_Array", 0, CSI_ARRAY_R, 0, CLHEP::twopi, 0, CLHEP::pi);
  csi_array_log = new G4LogicalVolume(solid_csi_array, mat_vaccum, csi_array_name);

  //  color
  G4VisAttributes  *p_vis_att = new G4VisAttributes(G4Colour(1.0, 1.0, 0.0, 0.0));
  p_vis_att->SetForceSolid(false);
  csi_array_log->SetVisAttributes(p_vis_att);

  return csi_array_log;
}

//
G4LogicalVolume *DetectorConstruction::GetMylarLog(G4String mylar_name)
{
  G4cout << " --->: GetMylar, begin" << G4endl;

  G4LogicalVolume *mylar_log = NULL;
  G4Box *solid_mylar = new G4Box("Mylar", 0.5*MYLAR_SIZE_X, 0.5*MYLAR_SIZE_X, 0.5*MYLAR_THICKNESS);
  mylar_log = new G4LogicalVolume(solid_mylar, mat_mylar, mylar_name);

  //  color
  G4VisAttributes  *p_vis_att = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0, 0.1));
  p_vis_att->SetForceSolid(true);
  mylar_log->SetVisAttributes(p_vis_att);

  return mylar_log;
}

//
G4LogicalVolume *DetectorConstruction::GetCsILog(G4String csi_name)
{
  G4cout << " --->: GetCsI, begin" << G4endl;

  G4LogicalVolume *csi_log = NULL;
  G4Box *solid_csi = new G4Box("CsI", 0.5*CSI_SIZE_X, 0.5*CSI_SIZE_Y, 0.5*CSI_THICKNESS);
  csi_log = new G4LogicalVolume(solid_csi, mat_csi, csi_name);

  //  color
  G4VisAttributes  *p_vis_att = new G4VisAttributes(G4Colour(0.42, 0.35, 0.80, 0.4));
  p_vis_att->SetForceSolid(true);
  csi_log->SetVisAttributes(p_vis_att);

  return csi_log;
}

//
G4LogicalVolume *DetectorConstruction::GetSiLog(G4String si_name)
{
  G4cout << " --->: GetSi, begin" << G4endl;

  G4LogicalVolume *si_log = NULL;
  G4Box *solid_si = new G4Box("Si", 0.5*SI_SIZE_X, 0.5*SI_SIZE_Y, 0.5*SI_THICKNESS);
  si_log = new G4LogicalVolume(solid_si, mat_si, si_name);

  //  color
  G4VisAttributes  *p_vis_att = new G4VisAttributes(G4Colour(0., 1., 0.0, 0.3));
  p_vis_att->SetForceSolid(true);
  si_log->SetVisAttributes(p_vis_att);

  return si_log;
}

//
G4LogicalVolume *DetectorConstruction::GetSiPINArrayLog(G4String si_pin_array_name)
{
  G4cout << " --->: GetSiPINArray, begin" << G4endl;

  G4LogicalVolume *si_pin_array_log = NULL;
  G4Sphere *solid_si_pin_array = new G4Sphere("Si_PIN_Array", 0, SI_PIN_ARRAY_R, 0, CLHEP::twopi, 0, CLHEP::pi);
  si_pin_array_log = new G4LogicalVolume(solid_si_pin_array, mat_vaccum, si_pin_array_name);

  //  color
  G4VisAttributes  *p_vis_att = new G4VisAttributes(G4Colour(1.0, 1.0, 0.0, 0.));
  p_vis_att->SetForceSolid(false);
  si_pin_array_log->SetVisAttributes(p_vis_att);

  return si_pin_array_log;
}

//
G4LogicalVolume *DetectorConstruction::GetSiPINLog(G4String si_pin_name)
{
  G4cout << " --->: GetSiPIN, begin" << G4endl;

  G4LogicalVolume *si_pin_log = NULL;
  G4Box *solid_si_pin = new G4Box("SiPIN", 0.5*SI_PIN_SIZE_X, 0.5*SI_PIN_SIZE_Y, 0.5*SI_PIN_THICKNESS);
  si_pin_log = new G4LogicalVolume(solid_si_pin, mat_si, si_pin_name);

  //  color
  G4VisAttributes  *p_vis_att = new G4VisAttributes(G4Colour(1., 1., 0.0, 0.3));
  p_vis_att->SetForceSolid(true);
  si_pin_log->SetVisAttributes(p_vis_att);

  return si_pin_log;
}

//
G4LogicalVolume *DetectorConstruction::GetPCBLog(G4String pcb_name)
{
  G4cout << " --->: GetPCB, begin" << G4endl;

  G4LogicalVolume *pcb_log = NULL;
  G4Box *solid_pcb = new G4Box("PCB", 0.5*PCB_SIZE_X, 0.5*PCB_SIZE_Y, 0.5*PCB_THICKNESS);
  pcb_log = new G4LogicalVolume(solid_pcb, mat_pcb, pcb_name);

  //  color
  G4VisAttributes  *p_vis_att = new G4VisAttributes(G4Colour(0., 0.3, 0.0, 0.3));
  p_vis_att->SetForceSolid(true);
  pcb_log->SetVisAttributes(p_vis_att);

  return pcb_log;
}  

//
G4LogicalVolume *DetectorConstruction::GetChamberLog(G4String chamber_name)
{
  G4cout << " --->: GetChamber, begin" << G4endl;

  G4LogicalVolume *chamber_log = NULL;
  G4Sphere *solid_chamber = new G4Sphere("Chamber", CHAMBER_R_MIN, CHAMBER_R_MAX, 0, CLHEP::twopi, 0, CLHEP::pi);
  chamber_log = new G4LogicalVolume(solid_chamber, mat_al, chamber_name);

  //  color
  G4VisAttributes  *p_vis_att = new G4VisAttributes(G4Colour(0., 0.3, 0.3, 0.3));
  p_vis_att->SetForceSolid(true);
  chamber_log->SetVisAttributes(p_vis_att);

  return chamber_log;
}

//
G4LogicalVolume *DetectorConstruction::GetChamberVaccumLog(G4String chamber_vaccum_name)
{
  G4cout << " --->: GetChamberVaccum, begin" << G4endl;

  G4LogicalVolume *chamber_vaccum_log = NULL;
  G4Sphere *solid_chamber_vaccum = new G4Sphere("Chamber_Vaccum", 0, CHAMBER_R_MAX, 0, CLHEP::twopi, 0, CLHEP::pi);
  chamber_vaccum_log = new G4LogicalVolume(solid_chamber_vaccum, mat_vaccum, chamber_vaccum_name);

  //  color
  G4VisAttributes  *p_vis_att = new G4VisAttributes(G4Colour(0.3, 0.3, 0.3, 0.3));
  p_vis_att->SetForceSolid(true);
  chamber_vaccum_log->SetVisAttributes(p_vis_att);

  return chamber_vaccum_log;
}

//
G4VPhysicalVolume *DetectorConstruction::DefineVolumes()
{
  G4cout << " --->: Construct, begin" << G4endl;

  // Option to switch on/off checking of volumes overlaps
  G4bool check_overlaps = true;

  // define world
  G4Box *solid_world = new G4Box("World", 0.5*WORLD_SIZE_X, 0.5*WORLD_SIZE_Y, 0.5*WORLD_SIZE_Z);
  G4LogicalVolume *logic_world = new G4LogicalVolume(solid_world, mat_vaccum, "World");
  G4VPhysicalVolume *phys_world = new G4PVPlacement(0, G4ThreeVector(), logic_world, "World", 0, false, 0, check_overlaps);
  //  color
  G4VisAttributes  *p_vis_att = new G4VisAttributes(G4Colour(0., 0.3, 0.0, 0.));
  p_vis_att->SetForceSolid(false);
  logic_world->SetVisAttributes(p_vis_att);

  // Ge Array
  // G4ThreeVector position_ge_array = G4ThreeVector(0, 0, 0);
  // G4LogicalVolume *ge_array_log = GetGeArrayLog("Ge_Array");
  // new G4PVPlacement(0, position_ge_array, ge_array_log, "Ge_Array", logic_world, false, 0, check_overlaps);   

  // Ge
  G4ThreeVector position_ge = G4ThreeVector(0, 0, GE_POS_DIS);
  G4LogicalVolume *ge_log = GetGeLog("Ge");
  new G4PVPlacement(0, position_ge, ge_log, "Ge", logic_world, false, 0, check_overlaps); 

#ifdef CSIARRAY
  // CsI Array
  // G4ThreeVector position_csi_array = G4ThreeVector(0, 0, 0);
  // G4LogicalVolume *csi_array_log = GetCsIArrayLog("CsI_Array");
  // new G4PVPlacement(0, position_csi_array, csi_array_log, "CsI_Array", logic_world, false, 0, check_overlaps);  

  // CsI
  G4LogicalVolume *csi_log = GetCsILog("CsI");
  for(int i=0;i<N_OF_CSI_DETECTOR;i++){
    G4ThreeVector position_csi = G4ThreeVector(CSI_ARRAY_X[i], CSI_ARRAY_Y[i], CSI_POS_DIS);
    new G4PVPlacement(0, position_csi, csi_log, "CsI", logic_world, false, i, check_overlaps);
  }

#endif

#ifdef SIPINARRAY
  // Si PIN Array
  // G4ThreeVector position_si_pin_array = G4ThreeVector(0, 0, 0);
  // G4LogicalVolume *si_pin_array_log = GetSiPINArrayLog("Si_PIN_Array");
  // new G4PVPlacement(0, position_si_pin_array, si_pin_array_log, "Si_PIN_Array", logic_world, false, 0, check_overlaps);  

  G4LogicalVolume *si_pin_log = GetSiPINLog("SiPIN");
  for(int i=0;i<N_OF_SI_PIN_DETECTOR;i++){
    G4ThreeVector position_si_pin = G4ThreeVector(SI_PIN_ARRAY_X[i], SI_PIN_ARRAY_Y[i], SI_POS_DIS);
    new G4PVPlacement(0, position_si_pin, si_pin_log, "Si", logic_world, false, i, check_overlaps);
  }
#endif

  // Sensitive detectors
  G4SDManager *sd_man = G4SDManager::GetSDMpointer();

  GeSD *ge = new GeSD("GeSD", "GeHitCollection");
  ge_log->SetSensitiveDetector(ge);
  sd_man->AddNewDetector(ge);

#ifdef CSIARRAY
  CsISD *csi = new CsISD("CsISD", "CsIHitCollection");
  csi_log->SetSensitiveDetector(csi);
  sd_man->AddNewDetector(csi);
#endif

#ifdef SIPINARRAY
  SiSD *si = new SiSD("SiSD", "SiHitCollection");
  si_pin_log->SetSensitiveDetector(si);
  sd_man->AddNewDetector(si);
#endif  

  return phys_world;
}

