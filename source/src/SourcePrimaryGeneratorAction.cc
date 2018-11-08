#include "SourcePrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"


SourcePrimaryGeneratorAction::SourcePrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0), 
  fEnvelopeBox(0)
{
  fParticleGun  = new G4GeneralParticleSource();
}


SourcePrimaryGeneratorAction::~SourcePrimaryGeneratorAction()
{
  delete fParticleGun;
}


void SourcePrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  fParticleGun->GeneratePrimaryVertex(anEvent);
}


