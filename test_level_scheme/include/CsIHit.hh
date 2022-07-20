#ifndef CsIHit_h
#define CsIHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"

class CsIHit: public G4VHit
{
public:
  CsIHit();
  CsIHit(const CsIHit&);
  virtual ~CsIHit();

  //  operator
  const CsIHit& operator=(const CsIHit&);
  G4int operator==(const CsIHit&) const;

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

typedef G4THitsCollection<CsIHit> CsIHitsCollection;

extern G4ThreadLocal G4Allocator<CsIHit>* CsIHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* CsIHit::operator new(size_t)
{
  if(!CsIHitAllocator)
      CsIHitAllocator = new G4Allocator<CsIHit>;
  return (void *) CsIHitAllocator->MallocSingle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void CsIHit::operator delete(void *hit)
{
  CsIHitAllocator->FreeSingle((CsIHit*) hit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
