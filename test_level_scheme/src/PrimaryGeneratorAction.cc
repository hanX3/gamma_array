#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"

#include "G4ParticleGun.hh"

#include "G4GenericIon.hh"
#include "G4Gamma.hh"
#include "G4RandomDirection.hh"
#include "G4IonTable.hh"
#include "G4PhysicalConstants.hh"
#include "G4RunManager.hh"
#include "G4EmCalculator.hh"

//
PrimaryGeneratorAction::PrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction()
{
  messenger = new PrimaryGeneratorMessenger(this);

  particle_gun = new G4ParticleGun(1);

  source = new GammaSource();
}

//
PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete messenger;
  delete particle_gun;
  delete source;
}

//
void PrimaryGeneratorAction::GeneratePrimaries(G4Event *an_event)
{
  switch(mode){
    case MODE::Source:{
      GenerateSourcePrimaries(an_event);
      break;
    }
    case MODE::Reaction:{
      // GenerateReactionPrimaries(an_event);
      break;
    }
  }

  return;
}

//
void PrimaryGeneratorAction::GenerateSourcePrimaries(G4Event *event)
{
  //simple isotropic gamma
  if(source->GetEnergy()>0.0*MeV){
    particle_gun->SetParticleDefinition(G4Gamma::Definition());
    particle_gun->SetParticlePosition(G4ThreeVector());
    particle_gun->SetParticleEnergy(source->GetEnergy());
    particle_gun->SetParticleMomentumDirection(G4RandomDirection());
    particle_gun->GeneratePrimaryVertex(event);

    return;
  }

  //remove polarization
  source->Unpolarize();

  //choose excited state
  G4int state_index = source->ChooseState();

  //make vertex
  particle_gun->SetParticleDefinition(source->GetDefinition(state_index));
  particle_gun->SetParticleEnergy(0.0*MeV);
  particle_gun->SetParticlePosition(G4ThreeVector());
  particle_gun->SetParticleMomentumDirection(G4ThreeVector());
  particle_gun->GeneratePrimaryVertex(event);

  return;
}

//
void PrimaryGeneratorAction::Update()
{
  switch(mode){
    case MODE::Source:{
      source->BuildLevelScheme();
      break;
    }
    case MODE::Reaction:{
      //todo
      break;
    }
  }
}

//
void PrimaryGeneratorAction::SetMode(G4String md)
{
  if(md=="Source"){
    mode = MODE::Source;

    return;
  }

  if(md=="Reaction"){
    mode = MODE::Reaction;

    return;
  }

  return;
}