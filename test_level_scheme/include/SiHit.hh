#ifndef SiHit_h
#define SiHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"

class SiHit: public G4VHit
{
public:
  SiHit();
  SiHit(const SiHit&);
  virtual ~SiHit();

  //  operator
  const SiHit& operator=(const SiHit&);
  G4int operator==(const SiHit&) const;

  inline void *operator new(size_t);
  inline void  operator delete(void*);

  // methods from base class
  virtual void Draw();
  virtual void Print();

  // Set methods

public:
  void SetID(G4int n) { id = n; }
  G4int GetID() const { return id; }

  void SetEdep (G4double de) { e_dep = de; }
  void AddEdep (G4double de) { e_dep += de; }
  G4double GetEdep() const { return e_dep; }

private:
  G4int id;
  G4double e_dep;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

typedef G4THitsCollection<SiHit> SiHitsCollection;

extern G4ThreadLocal G4Allocator<SiHit>* SiHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* SiHit::operator new(size_t)
{
  if(!SiHitAllocator)
      SiHitAllocator = new G4Allocator<SiHit>;
  return (void *) SiHitAllocator->MallocSingle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void SiHit::operator delete(void *hit)
{
  SiHitAllocator->FreeSingle((SiHit*) hit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
