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
  auto analysisManager = G4AnalysisManager::Instance();

  fRunAction->AddEdep(fEdep);
  if(fEdep>0.){
  analysisManager->FillNtupleDColumn(0, fEdep);
  analysisManager->AddNtupleRow();
  }
}

