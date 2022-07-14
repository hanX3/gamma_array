#include "CsIHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include <iomanip>

G4ThreadLocal G4Allocator<CsIHit>* CsIHitAllocator = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CsIHit::CsIHit()
: G4VHit(),
  id(0),
  e_dep(0.)
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CsIHit::~CsIHit() 
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CsIHit::CsIHit(const CsIHit& right)
: G4VHit(),
  id(right.id),
  e_dep(right.e_dep)
{
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const CsIHit& CsIHit::operator=(const CsIHit& right)
{
  id = right.id;
  e_dep = right.e_dep;

  return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4int CsIHit::operator==(const CsIHit& right) const
{
  return ( this == &right ) ? 1 : 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CsIHit::Draw()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CsIHit::Print()
{
  G4cout << "id: " << std::setw(7) << id << G4endl;
  G4cout << "e_dep: " << std::setw(7) << e_dep << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
