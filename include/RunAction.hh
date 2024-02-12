// Arapuca simulation
// Authors: L. Paulucci & F. Marinho
// Date: 20th September 2016
//
// Added modifications should be reported in arapuca.cc header comments

#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "DetectorConstruction.hh"
#include "globals.hh"

class G4Run;

class RunAction : public G4UserRunAction
{
public:
  RunAction();
  ~RunAction();
  
  void BeginOfRunAction(const G4Run*) override;
  void EndOfRunAction(const G4Run*) override;

};

#endif

