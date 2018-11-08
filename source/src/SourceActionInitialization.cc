#include "SourceActionInitialization.hh"
#include "SourcePrimaryGeneratorAction.hh"
#include "SourceRunAction.hh"
#include "SourceEventAction.hh"
#include "SourceSteppingAction.hh"


SourceActionInitialization::SourceActionInitialization()
 : G4VUserActionInitialization()
{}


SourceActionInitialization::~SourceActionInitialization()
{}


void SourceActionInitialization::BuildForMaster() const
{
  SourceRunAction* runAction = new SourceRunAction;
  SetUserAction(runAction);
}


void SourceActionInitialization::Build() const
{
  SetUserAction(new SourcePrimaryGeneratorAction);

  SourceRunAction* runAction = new SourceRunAction;
  SetUserAction(runAction);
  
  SourceEventAction* eventAction = new SourceEventAction(runAction);
  SetUserAction(eventAction);
  
  SetUserAction(new SourceSteppingAction(eventAction));
}  

