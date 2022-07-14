#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"

#include "globals.hh"
#include "Constants.hh"

class RootIO;
class TFile;

// Event action class
class EventAction: public G4UserEventAction
{
public:
  EventAction(RootIO *io);
  virtual ~EventAction();

  virtual void  BeginOfEventAction(const G4Event* );
  virtual void    EndOfEventAction(const G4Event* );

private:
  G4double ge_e;
#ifdef CSIARRAY
  G4int csi_hit_num;
  G4int csi_id[N_OF_CSI_DETECTOR];
  G4double csi_e[N_OF_CSI_DETECTOR];
#endif

#ifdef SIPINARRAY
  G4int si_hit_num;
  G4int si_id[N_OF_SI_PIN_DETECTOR];
  G4double si_e[N_OF_SI_PIN_DETECTOR];
#endif

  RootIO *root_IO;
};

#endif
