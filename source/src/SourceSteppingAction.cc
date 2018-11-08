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



SourceSteppingAction::SourceSteppingAction(SourceEventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fScoringVolume(0)
{}


SourceSteppingAction::~SourceSteppingAction()
{}



void SourceSteppingAction::UserSteppingAction(const G4Step* step)
{
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
      
  // check if we are in scoring volume
  if (volume != fScoringVolume) return;

  // collect energy deposited in this step
  G4double edepStep = step->GetTotalEnergyDeposit();

  fEventAction->AddEdep(edepStep);
}



