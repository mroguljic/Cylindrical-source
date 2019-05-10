#ifndef SourceDetectorConstruction_h
#define SourceDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;


class SourceDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    SourceDetectorConstruction(G4int option);
    virtual ~SourceDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    
    G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }
    void SetLayoutOptions(G4int options){ LayoutOptions = options; }
    G4int GetLayoutOptions() const { return LayoutOptions; }
  protected:
    G4LogicalVolume*  fScoringVolume;
    G4int LayoutOptions = 0;
};

#endif

