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
  G4int csi_hit_num;
  G4int csi_id[N_OF_CsI_DETECTOR];
  G4double csi_e[N_OF_CsI_DETECTOR];

  RootIO *root_IO;
};

#endif
