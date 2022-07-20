#include "GammaDecay.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleMomentum.hh"
#include "G4DynamicParticle.hh"
#include "G4DecayProducts.hh"
#include "G4PhysicalConstants.hh"
#include "Randomize.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4HadronicException.hh"

///
GammaDecay::GammaDecay(PolarizedParticle *parent, PolarizedParticle *daughter, G4double BR, G4int L0, G4int Lp, G4double del, G4double cc)
: GammaDecay(parent->GetDefinition(), daughter->GetDefinition(), BR)
{
  trans = new G4PolarizationTransition();

  p_parent = parent;
  p_daughter = daughter;

  trans_l = L0;
  trans_lp = Lp;
  delta = del;

  conv_coef = cc;
}

//
GammaDecay::GammaDecay(G4ParticleDefinition *parent, G4ParticleDefinition *daughter, G4double BR)
: G4VDecayChannel("Phase Space", parent->GetParticleName(), BR, 2, daughter->GetParticleName(), "gamma"),
  the_daughter_masses(0)
{
  SetParent(parent);
  parent_mass = parent->GetPDGMass();

  SetDaughter(0, daughter);
  SetDaughter(1, "gamma");
}

//
GammaDecay::~GammaDecay()
{

}

//
G4DecayProducts *GammaDecay::DecayIt(G4double)
{
  if(GetVerboseLevel()>1){
    G4cout << "G4GeneralPhaseSpaceDecay::TwoBodyDecayIt()" << G4endl;
  }
  G4cout << "G4GeneralPhaseSpaceDecay::TwoBodyDecayIt()" << G4endl;

  // daughters mass
  G4double daughter_mass[2];
  G4double daughter_momentum;
  if(the_daughter_masses){
    daughter_mass[0] = *(the_daughter_masses);
    daughter_mass[1] = *(the_daughter_masses+1);
  }
  else{
    daughter_mass[0] = G4MT_daughters[0]->GetPDGMass();
    daughter_mass[1] = G4MT_daughters[1]->GetPDGMass();
  }

  // create parent G4DynamicParticle at rest
  G4ParticleMomentum dummy;
  G4DynamicParticle *parent_particle = new G4DynamicParticle(G4MT_parent, dummy, 0.0);

  // create G4Decayproducts  @@GF why dummy parentparticle?
  G4DecayProducts *products = new G4DecayProducts(*parent_particle);
  delete parent_particle;

  // calculate daughter momentum
  daughter_momentum = Pmx(parent_mass, daughter_mass[0], daughter_mass[1]);

  G4double costheta;
  G4double phi;
  trans->SampleGammaTransition(p_parent->GetNuclearPolarization(), p_parent->TwoJ(), p_daughter->TwoJ(), trans_l, trans_lp, delta, costheta, phi);

  p_daughter->SetPolarization(p_parent->GetPolarization());

  G4double sintheta = std::sqrt((1.0 - costheta)*(1.0 + costheta));
  G4ParticleMomentum direction(sintheta*std::cos(phi), sintheta*std::sin(phi), costheta);

  // create daughter G4DynamicParticle
  G4double e_total= std::sqrt(daughter_mass[0]*daughter_mass[0] + daughter_momentum*daughter_momentum);
  G4DynamicParticle *daughter_particle = new G4DynamicParticle(G4MT_daughters[0], e_total, direction*daughter_momentum);
  products->PushProducts(daughter_particle);

  G4double prob = 1.0/(conv_coef + 1.0);
  if(G4UniformRand()<prob){
    e_total= std::sqrt(daughter_mass[1]*daughter_mass[1] + daughter_momentum*daughter_momentum);
    daughter_particle = new G4DynamicParticle(G4MT_daughters[1], e_total, direction*(-1.0*daughter_momentum));
    products->PushProducts(daughter_particle);
  }

  if(GetVerboseLevel()>1){
    G4cout << "G4GeneralPhaseSpaceDecay::TwoBodyDecayIt ";
    G4cout << "  create decay products in rest frame " << G4endl;
    products->DumpInfo();
  }

  return products;
}