#include "RunAction.hh"
#include "RootIO.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4ios.hh"
#include "G4Timer.hh"
#include "G4UnitsTable.hh"
#include "G4ParticleGun.hh"
#include "unistd.h"
#include <fstream>
#include <string>

//
RunAction::RunAction(RootIO *r, PrimaryGeneratorAction *p)
: G4UserRunAction(),
  root_io(r),
  pri_gen(p)
{ 
  // set printing event number per each 100000 events
  G4RunManager::GetRunManager()->SetPrintProgress(100000);

  timer = new G4Timer;     
}

//
RunAction::~RunAction()
{
  delete timer;
  timer = NULL;
}

//
void RunAction::BeginOfRunAction(const G4Run *)
{ 
  // inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);

  // creat RootIO file
  G4cout << "---" << G4endl;
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
  root_io->Open();

  timer->Start();
}

//
void RunAction::EndOfRunAction(const G4Run *run)
{
  root_io->Close();
  G4cout << "number of event " << run->GetNumberOfEvent() << G4endl;
  G4cout << "particle energy " << pri_gen->GetParticleGun()->GetParticleEnergy() << G4endl;

  timer->Stop();
  G4cout << " time:  " << *timer << G4endl;
}