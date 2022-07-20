#ifndef GammaSourceMessenger_h
#define GammaSourceMessenger_h 1

#include "GammaSource.hh"

#include "G4UImessenger.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

class GammaSource;

//
class GammaSourceMessenger : public G4UImessenger
{
public:
  GammaSourceMessenger(GammaSource *src);
  virtual ~GammaSourceMessenger();

private:
  GammaSource *source;

  void SetNewValue(G4UIcommand *command, G4String new_value);

  G4UIdirectory *source_dir; //Source directory
  G4UIcmdWithADoubleAndUnit *en_cmd;
  G4UIcmdWithAString *fn_cmd;
  G4UIcmdWithADouble *gs_cmd;
};

#endif