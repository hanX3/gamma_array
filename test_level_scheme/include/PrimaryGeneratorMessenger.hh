#ifndef PrimaryGeneratorMessenger_h
#define PrimaryGeneratorMessenger_h 1

#include "PrimaryGeneratorAction.hh"

#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"

class PrimaryGeneratorAction;

class PrimaryGeneratorMessenger: public G4UImessenger
{
public:
  PrimaryGeneratorMessenger(PrimaryGeneratorAction *pri_gen);
  ~PrimaryGeneratorMessenger();

  void SetNewValue(G4UIcommand *command, G4String new_value);

private:
  PrimaryGeneratorAction *generator;

private:
  //mode command
  G4UIcmdWithAString *mode_cmd;
};

#endif
