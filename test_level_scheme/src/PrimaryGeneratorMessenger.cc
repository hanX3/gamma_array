#include "PrimaryGeneratorMessenger.hh"

//
PrimaryGeneratorMessenger::PrimaryGeneratorMessenger(PrimaryGeneratorAction *pri_gen)
 : generator(pri_gen)
{
  // simulation mode command
  mode_cmd = new G4UIcmdWithAString("/Mode", this);
  mode_cmd->AvailableForStates(G4ApplicationState::G4State_Idle);
  mode_cmd->SetCandidates("Source Test");
  mode_cmd->SetGuidance("Set simulation mode");
}

//
PrimaryGeneratorMessenger::~PrimaryGeneratorMessenger()
{
  delete mode_cmd;
}

//
void PrimaryGeneratorMessenger::SetNewValue(G4UIcommand *command, G4String new_value)
{
  if(command == mode_cmd){
    generator->SetMode(new_value);
    G4cout << "Simulation mode: " << new_value << G4endl;
  }

  return;
}