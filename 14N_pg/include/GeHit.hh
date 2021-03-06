#ifndef GeHit_h
#define GeHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"

class GeHit: public G4VHit
{
public:
  GeHit();
  GeHit(const GeHit&);
  virtual ~GeHit();

  //  operator
  const GeHit& operator=(const GeHit&);
  G4int operator==(const GeHit&) const;

  inline void *operator new(size_t);
  inline void  operator delete(void*);

  // methods from base class
  virtual void Draw();
  virtual void Print();

  // Set methods

public:
  void SetEdep (G4double de) { e_dep = de; }
  void AddEdep (G4double de) { e_dep += de; }
  G4double GetEdep() const { return e_dep; }

private:
  G4double e_dep;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

typedef G4THitsCollection<GeHit> GeHitsCollection;

extern G4ThreadLocal G4Allocator<GeHit>* GeHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* GeHit::operator new(size_t)
{
  if(!GeHitAllocator)
      GeHitAllocator = new G4Allocator<GeHit>;
  return (void *) GeHitAllocator->MallocSingle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void GeHit::operator delete(void *hit)
{
  GeHitAllocator->FreeSingle((GeHit*) hit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
