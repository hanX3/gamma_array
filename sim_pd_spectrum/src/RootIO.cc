#include "TH1D.h"
#include "TFile.h"
#include "TTree.h"

#include "RootIO.hh"

#include <iostream>
#include <stdio.h>
#include <time.h>
#include <fstream>
#include <sstream>
#include "G4UnitsTable.hh"
#include "G4ThreeVector.hh"

//
RootIO::RootIO(G4int save)
: flag_save(save),
  file_in(NULL)
{
}

//
RootIO::~RootIO()
{
  if(file_in){
    delete file_in;
    file_in = NULL;
  }    
}

//
void RootIO::Open()
{
  if(flag_save){
		time_t t;
		struct tm* tt;
		t=time(0);
		tt=localtime(&t);
		sprintf(file_name, "%d%02d%02d_%02dh%02dm%02ds", tt->tm_year+1900, tt->tm_mon, tt->tm_mday, tt->tm_hour, tt->tm_min, tt->tm_sec);
    G4cout << "\n----> Tree file is opened in " << file_name << G4endl;

    std::stringstream ss;
		ss << "../data/" << file_name << ".root";

    file_in = new TFile(ss.str().c_str(), "RECREATE");
    //  check file_in
    if(!file_in){
      G4cout << " RootIO::book :" << " problem creating the ROOT TFile!!!" << G4endl;
      return ;
    }

    //  creat tree
    tr = new TTree("tr", "simulation data");
		tr->Branch("ge_e", &ge_e, "ge_e/D");
#ifdef CSIARRAY
    tr->Branch("csi_hit_num", &csi_hit_num, "csi_hit_num/I");
    tr->Branch("csi_id", csi_id, "csi_id[csi_hit_num]/I");
    tr->Branch("csi_e", csi_e, "csi_e[csi_hit_num]/D");
#endif

#ifdef SIPINARRAY
    tr->Branch("si_hit_num", &si_hit_num, "si_hit_num/I");
    tr->Branch("si_id", si_id, "si_id[si_hit_num]/I");
    tr->Branch("si_e", si_e, "si_e[si_hit_num]/D");
#endif

    if(!tr){
			G4cout << "\n can't create tree" << G4endl;
      return ;
		}
		
    std::ofstream fo;
    fo.open("../../data/cata.dat", std::ofstream::app);
    fo << file_name << "  ";
    fo.close();

		G4cout << "\n----> Tree file is opened in " << ss.str() << G4endl;
  }
}

//
void RootIO::FillTree(G4double ee, G4int n, G4int *id, G4double *e)
{
  ge_e = ee;

#ifdef CSIARRAY
  csi_hit_num = n;
  for(int i=0;i<n;i++){
    csi_id[i] = id[i];
    csi_e[i] = e[i];
  }
#endif

#ifdef SIPINARRAY
  si_hit_num = n;
  for(int i=0;i<n;i++){
    si_id[i] = id[i];
    si_e[i] = e[i];
  }
#endif

	tr->Fill();
}

//
void RootIO::Close()
{
  if(!file_in){
    return;
  }

  tr->Write();
  file_in->Close();

  G4cout << "\n----> RootIO is saved.\n" << G4endl;
}