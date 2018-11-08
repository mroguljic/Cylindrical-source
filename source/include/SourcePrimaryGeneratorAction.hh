#ifndef SourcePrimaryGeneratorAction_h
#define SourcePrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class G4GeneralParticleSource;
class G4Event;
class G4Box;

class SourcePrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    SourcePrimaryGeneratorAction();    
    virtual ~SourcePrimaryGeneratorAction();

    // method from the base class
    virtual void GeneratePrimaries(G4Event*);         
  
    // method to access particle source/gun
    const G4GeneralParticleSource* GetParticleGun() const { return fParticleGun; }
  
  private:
    G4GeneralParticleSource*  fParticleGun;
    G4Box* fEnvelopeBox;
};


#endif
