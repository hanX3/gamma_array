#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

using namespace std;

//
class G4Run;
class G4Timer;
class RootIO;
class PrimaryGeneratorAction;

class RunAction: public G4UserRunAction
{
public:
  RunAction(RootIO *r, PrimaryGeneratorAction *p);
  virtual ~RunAction();

  virtual void BeginOfRunAction(const G4Run *);
  virtual void   EndOfRunAction(const G4Run *run);

private:
  G4Timer *timer;
  RootIO *root_io;
  PrimaryGeneratorAction *pri_gen;
};

#endif