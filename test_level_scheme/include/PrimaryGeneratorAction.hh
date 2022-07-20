#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

#include "GammaSource.hh"
#include "PrimaryGeneratorMessenger.hh"

class G4ParticleGun;
class G4Event;
class PrimaryGeneratorMessenger;

enum MODE {Source, Reaction};

//
class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  PrimaryGeneratorAction();    
  virtual ~PrimaryGeneratorAction();

public:
  void SetMode(G4String md);
  MODE GetMode() {return mode;}

public://source
  G4bool IsSimpleSource() {return source->GetEnergy() > 0.0;}

public://beam
  // void SetBeamX(G4double x) {beam_x = x;}
  // void SetBeamY(G4double y) {beam_y = y;}
  // void SetBeamAX(G4double ax) {beam_ax = ax;}
  // void SetBeamAY(G4double ay) {beam_ay = ay;}
  // void SetBeamEn(G4double en) {beam_en = en;}

  // void SetSigmaX(G4double sig_x) {sigma_x = sig_x;}
  // void SetSigmaY(G4double sig_y) {sigma_Y = sig_y;}
  // void SetSigmaAX(G4double sig_ax) {sigma_ax = sig_ax;}
  // void SetSigmaAY(G4double sig_ay) {sigma_ay = sig_ay;}
  // void SetSigmaEn(G4double sig_e) {sigma_en = sig_e;}

public://reaction
  // void SetDeltaE(G4double de) {delta_e = de;}
  // G4String GetProjectileName() {return projGS->GetParticleName();}
  // G4String GetRecoilName() {return recoilGS->GetParticleName();}

public:
  virtual void GeneratePrimaries(G4Event *);
  void Update();

//
private:
  PrimaryGeneratorMessenger *messenger;
  MODE mode;
  G4ParticleGun *particle_gun;

private://source
  void GenerateSourcePrimaries(G4Event *event);
  GammaSource *source;

private://used for incoming energy loss in target
   // G4double dedx;
   // G4double width;

private://beam
  // G4double beam_x; //x position of beam
  // G4double beam_y; //y position of beam
  // G4double beam_ax; //x angle of beam
  // G4double beam_ay; //y angle of beam
  // G4double beam_en; //kinetic energy of beam

  // G4double sigma_x;  //spread in x position
  // G4double sigma_y;  //spread in y position
  // G4double sigma_ax; //spread in angle about x axis
  // G4double sigma_ay; //spread in angle about y axis
  // G4double sigma_en; //spread in energy

private://reaction
  // void GenerateReactionPrimaries(G4Event *event);

  // Reaction *reac;
  // G4double delta_e; //For inelastic scattering
  // Excitation *excite;

  // G4ParticleDefinition* projGS; //Projectile ground state
  // G4ParticleDefinition* recoilGS; //Recoil ground state
};

#endif
