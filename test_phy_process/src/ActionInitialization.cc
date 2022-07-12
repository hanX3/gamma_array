#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "RootIO.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ActionInitialization::ActionInitialization(G4int thesaveFlag)
: G4VUserActionInitialization(),
  saveFlag(thesaveFlag)
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ActionInitialization::~ActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ActionInitialization::BuildForMaster() const
{
  PrimaryGeneratorAction* fPriGen = new PrimaryGeneratorAction();
  RootIO* fRootIO = new RootIO(saveFlag);

  SetUserAction(new RunAction(fRootIO, fPriGen));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ActionInitialization::Build() const
{
  PrimaryGeneratorAction* fPriGen = new PrimaryGeneratorAction();
  RootIO* fRootIO = new RootIO(saveFlag);
  DetectorConstruction *detconstruct = new DetectorConstruction();

  SetUserAction(fPriGen);
  SetUserAction(new RunAction(fRootIO, fPriGen));
  SetUserAction(new EventAction(fRootIO));
  //SetUserAction(new SteppingAction(detconstruct));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
