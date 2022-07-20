#ifndef GammaSource_h
#define GammaSource_h 1

#include "PolarizedParticle.hh"
#include "GammaSourceMessenger.hh"

#include "G4ParticleDefinition.hh"

class GammaSourceMessenger;

//
class GammaSource
{
public:
  GammaSource();
  ~GammaSource();

  void BuildLevelScheme();
  void Unpolarize();

  G4int ChooseState();
  G4double GetEnergy() {return source_energy;}

  G4ParticleDefinition *GetDefinition(G4int index) {return levels.at(index)->GetDefinition();}

  void SetEnergy(G4double e) {source_energy = e;}
  void SetFileName(G4String name) {file_name = name;}
  void SetGroundStateSpin(G4double spin) {GSS = spin;}

private:
  GammaSourceMessenger *messenger;

  G4double source_energy;
  G4double GSS; //ground state spin
  G4String file_name;

  std::vector<PolarizedParticle*> levels;
  std::vector<G4double> probs;
};

//

#endif