#include "PolarizedParticle.hh"

//
PolarizedParticle::PolarizedParticle(G4ParticleDefinition *def, G4int Z, G4int A, G4double J, G4double ex)
: part(def),
  spin(J)
{
  polar = new G4NuclearPolarization(Z, A, ex);
}

//
PolarizedParticle::~PolarizedParticle()
{

}