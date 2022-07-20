#ifndef GammaDecay_h
#define GammaDecay_h 1

#include "G4VDecayChannel.hh"
#include "PolarizedParticle.hh"
#include "G4PolarizationTransition.hh"
#include "G4NuclearPolarization.hh"
#include "G4HadronicException.hh"

class GammaDecay : public G4VDecayChannel
{
public:
  GammaDecay(PolarizedParticle *parent, PolarizedParticle *daughter, G4double BR, G4int L0, G4int Lp, G4double del, G4double cc);
  GammaDecay(G4ParticleDefinition *parent, G4ParticleDefinition *daughter, G4double BR);
  virtual ~GammaDecay();

  virtual G4DecayProducts *DecayIt(G4double);

  static G4double Pmx(G4double e, G4double p1, G4double p2);

private:
  G4double parent_mass;
  const G4double *the_daughter_masses;

  G4PolarizationTransition *trans;
  PolarizedParticle *p_parent;
  PolarizedParticle *p_daughter;

  G4int trans_l;
  G4int trans_lp;
  G4double delta;

  G4double conv_coef;
};

//
inline G4double GammaDecay::Pmx(G4double e, G4double p1, G4double p2)
{
  // calculate momentum of daughter particles in two-body decay
  if((e-p1-p2)<0){
    throw G4HadronicException(__FILE__, __LINE__, "G4GeneralPhaseSpaceDecay::Pmx energy in cms > mass1+mass2");
  }

  G4double ppp = (e+p1+p2)*(e+p1-p2)*(e-p1+p2)*(e-p1-p2)/(4.0*e*e);

  if(ppp>0){
    return std::sqrt(ppp);
  }
  else{
    return -1;
  }
}

#endif