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
  G4ParticleDefinition *particle_definition = G4ParticleTable::GetParticleTable()->FindParticle("gamma");

  particle_gun->SetParticleDefinition(particle_definition);
}

//
PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete particle_gun;
}

//
void PrimaryGeneratorAction::GeneratePrimaries(G4Event *an_event)
{
  //particle_gun->SetParticleMomentumDirection(G4RandomDirection());
  
  G4double x;
  G4double y;
  G4double z;
  G4double condizione;

  x =  CLHEP::RandFlat::shoot(-0.3,0.3);
  y =  CLHEP::RandFlat::shoot(-0.3,0.3);
  z =  0.8;

  condizione = std::sqrt(x*x + y*y + z*z);
  x = x/condizione;
  y = y/condizione;
  z = z/condizione;

  particle_gun->SetParticleMomentumDirection(G4ThreeVector(x, y, z));
  particle_gun->SetParticlePosition(G4ThreeVector(0., 0., 0));
  particle_gun->GeneratePrimaryVertex(an_event);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
