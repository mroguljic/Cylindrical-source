#ifndef SourceEventAction_h
#define SourceEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class SourceRunAction;


class SourceEventAction : public G4UserEventAction
{
  public:
    SourceEventAction(SourceRunAction* runAction);
    virtual ~SourceEventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void AddEdep(G4double edep) 		 { fEdep += edep; }

  private:
    SourceRunAction* fRunAction;
    G4double     fEdep;
};


#endif

    
