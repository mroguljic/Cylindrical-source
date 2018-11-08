#ifndef SourceActionInitialization_h
#define SourceActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class SourceActionInitialization : public G4VUserActionInitialization
{
  public:
    SourceActionInitialization();
    virtual ~SourceActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};


#endif

    
