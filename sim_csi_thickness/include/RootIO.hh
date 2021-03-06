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
  void FillTree(G4double ee, G4int n, G4int *id, G4double *e);

private:
  G4int flag_save;

	G4double ge_e;
  G4int csi_hit_num;
  G4int csi_id[N_OF_CsI_DETECTOR];
  G4double csi_e[N_OF_CsI_DETECTOR];

  char file_name[1024];

  TFile *file_in;
  TTree *tr;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
