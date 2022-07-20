#include "GammaSourceMessenger.hh"

//
GammaSourceMessenger::GammaSourceMessenger(GammaSource *src)
: source(src)
{
  source_dir = new G4UIdirectory("/Source/");

  en_cmd = new G4UIcmdWithADoubleAndUnit("/Source/Energy", this);
  en_cmd->AvailableForStates(G4ApplicationState::G4State_Idle);
  en_cmd->SetGuidance("Set energy of simple isotropic gamma-ray");

  fn_cmd = new G4UIcmdWithAString("/Source/LevelScheme", this);
  fn_cmd->AvailableForStates(G4ApplicationState::G4State_Idle);
  fn_cmd->SetGuidance("Set the name of the level scheme file for the gamma-ray source");

  gs_cmd = new G4UIcmdWithADouble("/Source/GroundStateSpin", this);
  gs_cmd->AvailableForStates(G4ApplicationState::G4State_Idle);
  gs_cmd->SetGuidance("Set the ground state spin of the gamma-ray source");
}

//
GammaSourceMessenger::~GammaSourceMessenger()
{
  delete source_dir;

  delete en_cmd;
  delete fn_cmd;
  delete gs_cmd;
}

//
void GammaSourceMessenger::SetNewValue(G4UIcommand *command, G4String new_value)
{
  if(command==en_cmd){
    source->SetEnergy(en_cmd->GetNewDoubleValue(new_value));
    G4cout << "Setting gamma-ray energy to " << new_value << G4endl;

    return;
  }
  if(command==fn_cmd){
    source->SetFileName(new_value);
    G4cout << "Setting source level scheme file to " << new_value << G4endl;

    return;
  }
  if(command==gs_cmd){
    source->SetGroundStateSpin(gs_cmd->GetNewDoubleValue(new_value));
    G4cout << "Setting the spin of the gamma-ray source ground state to " << new_value << G4endl;

    return;
  }

  return;
}