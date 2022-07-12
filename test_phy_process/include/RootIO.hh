#ifndef RootIO_H
#define RootIO_H 1

#include <globals.hh>

#include <fstream>
#include <map>

#include "Constants.hh"

class TFile;
class TH1D;
class TTree;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class RootIO
{
public:
  RootIO(G4int save);
  ~RootIO();

  void Open();
  void Close();

#ifdef CSIARRAY
  void FillTree(G4double ee, G4int n1, G4int *id1, G4double *e1, G4int n2, G4int *id2, G4double *e2);
#endif

#ifdef SIPINARRAY
  void FillTree(G4double ee, G4int n, G4int *id, G4double *e);
#endif

private:
  G4int flag_save;

	G4double ge_e;
#ifdef CSIARRAY  
  G4int csi_hit_num;
  G4int csi_id[N_OF_CSI_DETECTOR];
  G4double csi_e[N_OF_CSI_DETECTOR];

  G4int si_hit_num;
  G4int si_id[N_OF_CSI_DETECTOR];
  G4double si_e[N_OF_CSI_DETECTOR];
#endif

#ifdef SIPINARRAY
  G4int si_hit_num;
  G4int si_id[N_OF_SI_PIN_DETECTOR];
  G4double si_e[N_OF_SI_PIN_DETECTOR];
#endif

  char file_name[1024];

  TFile *file_in;
  TTree *tr;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
