#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TMath.h"

#include "EventAction.hh"
#include "GeHit.hh"
#include "CsIHit.hh"
#include "SiHit.hh"
#include "RootIO.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4DCofThisEvent.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"

#include <string.h>

//
EventAction::EventAction(RootIO *io)
: G4UserEventAction(),
  root_IO(io)
{
  ge_e = 0;
#ifdef CSIARRAY
  csi_hit_num = 0;
  memset(csi_id, 0, sizeof(csi_id));
  memset(csi_e, 0, sizeof(csi_e));
#endif

#ifdef SIPINARRAY
  si_hit_num = 0;
  memset(si_id, 0, sizeof(si_id));
  memset(si_e, 0, sizeof(si_e));
#endif
}

//
EventAction::~EventAction()
{

}

//
void EventAction::BeginOfEventAction(const G4Event*)
{
  ge_e = 0;
#ifdef CSIARRAY
  csi_hit_num = 0;
  memset(csi_id, 0, sizeof(csi_id));
  memset(csi_e, 0, sizeof(csi_e));
#endif

#ifdef SIPINARRAY
  si_hit_num = 0;
  memset(si_id, 0, sizeof(si_id));
  memset(si_e, 0, sizeof(si_e));
#endif
}

//
void EventAction::EndOfEventAction(const G4Event* event)
{
  ge_e = 0;
#ifdef CSIARRAY
  csi_hit_num = 0;
  memset(csi_id, 0, sizeof(csi_id));
  memset(csi_e, 0, sizeof(csi_e));
#endif

#ifdef SIPINARRAY
  si_hit_num = 0;
  memset(si_id, 0, sizeof(si_id));
  memset(si_e, 0, sizeof(si_e));
#endif

  auto sdManager = G4SDManager::GetSDMpointer();
  // Ge
  G4int ge_idd = sdManager->GetCollectionID("GeSD/GeHitCollection");
  auto ge_hce = event->GetHCofThisEvent();
  auto ge_hc = static_cast<GeHitsCollection*>(ge_hce->GetHC(ge_idd));
  ge_e = (*ge_hc)[0]->GetEdep();
  ge_e /= keV;

#ifdef CSIARRAY
  // CsI
  G4int csi_idd = sdManager->GetCollectionID("CsISD/CsIHitCollection");
  auto csi_hce = event->GetHCofThisEvent();
  auto csi_hc = static_cast<CsIHitsCollection*>(csi_hce->GetHC(csi_idd));
  for(int i=0;i<N_OF_CSI_DETECTOR;i++){
    if((*csi_hc)[i]->GetEdep()==0)  continue;

    csi_id[csi_hit_num] = i;
    csi_e[csi_hit_num] = (*csi_hc)[i]->GetEdep();
    csi_e[csi_hit_num] /= keV;
    
    csi_hit_num++;
  }

  root_IO->FillTree(ge_e, csi_hit_num, csi_id, csi_e);
#endif

#ifdef SIPINARRAY
  // Si PIN
  G4int si_idd = sdManager->GetCollectionID("SiSD/SiHitCollection");
  auto si_hce = event->GetHCofThisEvent();
  auto si_hc = static_cast<SiHitsCollection*>(si_hce->GetHC(si_idd));
  for(int i=0;i<N_OF_SI_PIN_DETECTOR;i++){
    if((*si_hc)[i]->GetEdep()==0)  continue;

    si_id[si_hit_num] = i;
    si_e[si_hit_num] = (*si_hc)[i]->GetEdep();
    si_e[si_hit_num] /= keV;
    
    si_hit_num++;
  }

  root_IO->FillTree(ge_e, si_hit_num, si_id, si_e);
#endif


  // periodic printing
  G4int eventID = event->GetEventID();
  if(eventID<10 || eventID%100000==0){
    G4cout << ">>> Event: " << eventID  << G4endl;
		G4cout << "ge energy " << ge_e << G4endl;
#ifdef CSIARRAY
    for(int i=0;i<csi_hit_num;i++){
      G4cout << "csi " << csi_id[i] << "  energy " << csi_e[i] << G4endl;
    }
#endif

#ifdef SIPINARRAY
    for(int i=0;i<si_hit_num;i++){
      G4cout << "si " << si_id[i] << "  energy " << si_e[i] << G4endl;
    }
#endif
  }
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
