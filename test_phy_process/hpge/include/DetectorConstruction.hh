#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "tls.hh"
#include "Constants.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
class G4UserLimits;
class G4GlobalMagFieldMessenger;

class DetectorConstruction: public G4VUserDetectorConstruction
{
public:
  DetectorConstruction();
  virtual ~DetectorConstruction();

  virtual G4VPhysicalVolume *Construct();

  // other methods
  G4LogicalVolume *GetGeArrayLog(G4String ge_array_name);
  G4LogicalVolume *GetGeLog(G4String ge_name);
  G4LogicalVolume *GetMylarLog(G4String mylar_name);
  G4LogicalVolume *GetCsIArrayLog(G4String csi_array_name);
  G4LogicalVolume *GetCsILog(G4String csi_name);
  G4LogicalVolume *GetSiLog(G4String si_name);
  G4LogicalVolume *GetSiPINArrayLog(G4String si_pin_array_name);
  G4LogicalVolume *GetSiPINLog(G4String si_pin_name);
  G4LogicalVolume *GetPCBLog(G4String pcb_name);
  G4LogicalVolume *GetChamberLog(G4String chamber_name);
  G4LogicalVolume *GetChamberVaccumLog(G4String chamber_vaccum_name);

private:
  void DefineMaterials();
  G4VPhysicalVolume *DefineVolumes();

  G4Material *mat_vaccum;
  G4Material *mat_air;
  G4Material *mat_ge;
  G4Material *mat_csi;
  G4Material *mat_al;
  G4Material *mat_mylar;
  G4Material *mat_si;
  G4Material *mat_pcb;
};

#endif
