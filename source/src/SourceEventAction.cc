#include "SourceEventAction.hh"
#include "SourceRunAction.hh"
#include "SourceAnalysis.hh"


#include "G4Event.hh"
#include "G4RunManager.hh"


SourceEventAction::SourceEventAction(SourceRunAction* runAction)
: G4UserEventAction(),
  fRunAction(runAction),
  fEdep(0.)
{} 


SourceEventAction::~SourceEventAction()
{}


void SourceEventAction::BeginOfEventAction(const G4Event*)
{  
  fEdep = 0.;
}


void SourceEventAction::EndOfEventAction(const G4Event*)
{   

  fRunAction->AddEdep(fEdep);
}

