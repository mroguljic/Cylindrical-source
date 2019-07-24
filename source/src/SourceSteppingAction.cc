#include "SourceSteppingAction.hh"
#include "SourceEventAction.hh"
#include "SourceDetectorConstruction.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4String.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "g4root.hh"
#include "SourceAnalysis.hh"
#include "SourceRunAction.hh"

SourceSteppingAction::SourceSteppingAction(SourceEventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fScoringVolume(0)
{}


SourceSteppingAction::~SourceSteppingAction()
{}



void SourceSteppingAction::UserSteppingAction(const G4Step* step)
{

  auto analysisManager = G4AnalysisManager::Instance();


  if (!fScoringVolume) { 
    const SourceDetectorConstruction* detectorConstruction
      = static_cast<const SourceDetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = detectorConstruction->GetScoringVolume();   
  }


  // get volume of the current step
  G4LogicalVolume* volume 
    = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();

  G4double edepStep = step->GetTotalEnergyDeposit();
  
  // check if we are in scoring volume
  if (volume != fScoringVolume) return;
  if (edepStep == 0) return;

  // collect energy deposited in this step
  G4double z        = step->GetPreStepPoint()->GetPosition().z();
  G4double y        = step->GetPreStepPoint()->GetPosition().y();
  G4double x        = step->GetPreStepPoint()->GetPosition().x();
  analysisManager->FillNtupleDColumn(0,edepStep);
  analysisManager->FillNtupleDColumn(1,x);
  analysisManager->FillNtupleDColumn(2,y);
  analysisManager->FillNtupleDColumn(3,z);
  analysisManager->AddNtupleRow();
  fEventAction->AddEdep(edepStep);
}



