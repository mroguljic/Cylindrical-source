#ifndef SourceSteppingAction_h
#define SourceSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class SourceEventAction;

class G4LogicalVolume;

class SourceSteppingAction : public G4UserSteppingAction
{
  public:
    SourceSteppingAction(SourceEventAction* eventAction);
    virtual ~SourceSteppingAction();

    virtual void UserSteppingAction(const G4Step*);

  private:
    SourceEventAction*  fEventAction;
    G4LogicalVolume* fScoringVolume;
};



#endif
