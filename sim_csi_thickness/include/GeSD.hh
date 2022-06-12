#ifndef GeSD_h
#define GeSD_h 1

#include "G4VSensitiveDetector.hh"
#include "GeHit.hh"

#include <vector>

class G4Step;
class G4HCofThisEvent;  //  save multi SD hitcollection objects

class GeSD: public G4VSensitiveDetector
{
public:
  GeSD(const G4String &sd_name, const G4String &hits_collection_name);
  virtual ~GeSD();

  //  methods from base class
  virtual void  Initialize(G4HCofThisEvent *hit_collection);
  virtual G4bool ProcessHits(G4Step *step, G4TouchableHistory *);
  virtual void   EndOfEvent(G4HCofThisEvent *hit_collection);

private:
  GeHitsCollection *hits_collection;
};

#endif
