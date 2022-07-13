#ifndef SiSD_h
#define SiSD_h 1

#include "G4VSensitiveDetector.hh"
#include "SiHit.hh"

#include <vector>

class G4Step;
class G4HCofThisEvent;  //  save multi SD hitcollection objects

class SiSD: public G4VSensitiveDetector
{
public:
  SiSD(const G4String &sd_name, const G4String &hits_collection_name);
  virtual ~SiSD();

  //  methods from base class
  virtual void  Initialize(G4HCofThisEvent *hit_collection);
  virtual G4bool ProcessHits(G4Step *step, G4TouchableHistory *);
  virtual void   EndOfEvent(G4HCofThisEvent *hit_collection);

private:
  SiHitsCollection *hits_collection;
};

#endif
