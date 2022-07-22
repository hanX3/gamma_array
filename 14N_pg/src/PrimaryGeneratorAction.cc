#include "PrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4RandomDirection.hh"
#include "G4IonTable.hh"
#include "G4Geantino.hh"

#include "Randomize.hh"

//
PrimaryGeneratorAction::PrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction()
{
  G4int n_of_particles = 1;
  particle_gun = new G4ParticleGun(n_of_particles);

  // default particle kinematic
  particle_gun->SetParticleEnergy(0*eV);
  particle_gun->SetParticlePosition(G4ThreeVector(0.,0.,0.));
  particle_gun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
}

//
PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete particle_gun;
}

//
void PrimaryGeneratorAction::GeneratePrimaries(G4Event *an_event)
{
  if(particle_gun->GetParticleDefinition()==G4Geantino::Geantino()){
    G4int Z = 27, A = 60;
    G4double ion_charge   = 0.*eplus;
    G4double excit_energy = 0.*keV;

    G4ParticleDefinition *ion = G4IonTable::GetIonTable()->GetIon(Z, A, excit_energy);
    particle_gun->SetParticleDefinition(ion);
    particle_gun->SetParticleCharge(ion_charge);
  }

  particle_gun->GeneratePrimaryVertex(an_event);
}
