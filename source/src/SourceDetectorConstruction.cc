#include "SourceDetectorConstruction.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4SubtractionSolid.hh"
#include "G4Trap.hh"
#include "G4UnionSolid.hh"
#include "UserInput.hh"




SourceDetectorConstruction::SourceDetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }


SourceDetectorConstruction::~SourceDetectorConstruction()
{ }


G4VPhysicalVolume* SourceDetectorConstruction::Construct()
{  
  G4NistManager* nist           = G4NistManager::Instance();
  G4double env_sizeXY           = 1000*cm, env_sizeZ = 600*cm;
  G4bool checkOverlaps          = true;
  G4double world_sizeXY         = 1.2*env_sizeXY;
  G4double world_sizeZ          = 1.2*env_sizeZ;
  G4Material* world_mat         = nist->FindOrBuildMaterial("G4_AIR");

  G4Box* solidWorld             = new G4Box("World",0.5*world_sizeXY,0.5*world_sizeXY,0.5*world_sizeZ);
  G4LogicalVolume* logicWorld   = new G4LogicalVolume(solidWorld,world_mat,"World");
  G4VPhysicalVolume* physWorld  = new G4PVPlacement(0,G4ThreeVector(0,0,0),logicWorld,"World",0,false,0,checkOverlaps);

  G4Material* Aluminum          = nist->FindOrBuildMaterial("G4_Al");
  G4Material* StainlessSteel    = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
  G4Material* Cobalt            = nist->FindOrBuildMaterial("G4_Co");
  G4Material* Concrete          = nist->FindOrBuildMaterial("G4_CONCRETE");
  G4Material* Water             = nist->FindOrBuildMaterial("G4_WATER");

  //Pads around Co60
  G4double innerRadiusPads      = 0.6*cm;
  G4double outerRadiusPads      = 0.7*cm;
  G4double hzPads               = 17.5*cm;
  G4double startAngle           = 0.*deg;
  G4double spanningAngle        = 360.*deg; 
  G4Tubs* padsSolid             = new G4Tubs("Pads", innerRadiusPads, outerRadiusPads, hzPads, startAngle, spanningAngle);
  G4LogicalVolume* padsLog      = new G4LogicalVolume(padsSolid, StainlessSteel, "Pads");

  //Vertical protection
  G4double vProtRadius          = 10.*mm;
  G4double vProthLength         = 20.*cm; //halflength
  G4Tubs* vProtSolid            = new G4Tubs("vProt",0.,vProtRadius,vProthLength,startAngle,spanningAngle);
  G4LogicalVolume* vProtLog     = new G4LogicalVolume(vProtSolid,StainlessSteel,"vProt");

  //Cobalt fillings
  G4double innerRadiusFillings  = 0.*cm;
  G4double outerRadiusFillings  = 0.55*cm;
  G4double hzFillings           = 16.2*cm;
  G4Tubs* fillingsSolid         = new G4Tubs("Fillings", innerRadiusFillings, outerRadiusFillings, hzFillings, startAngle, spanningAngle);
  G4LogicalVolume* fillingsLog  = new G4LogicalVolume(fillingsSolid, Cobalt, "Fillings");

  G4double radiusSource         = 13.0*cm;  //Center of the Co60 source is at some radius from the radiation chamber, positions of pads and guides are on this radius

  //Guide tubes for pads
  G4double innerRadiusGuides    = 1.*cm;
  G4double outerRadiusGuides    = 1.1*cm;
  G4double hzGuides             = 74.5*cm;
  G4Tubs* guidesSolid           = new G4Tubs("Guides", innerRadiusGuides, outerRadiusGuides, hzGuides, startAngle, spanningAngle);
  G4LogicalVolume* guidesLog    = new G4LogicalVolume(guidesSolid, StainlessSteel, "Guides");


  double n_rods  = 24.;
  double guidesZ = hzGuides - 72.0*cm + 0.5*cm; //tune this so they nearly touch the floor

  //Placing the rods, pads and the sources
  //There is a better way to do it (without loops) - copies of G4PVP placement
  for( int i = 0; i < n_rods; i+=1 ) {
    double phi                = 7.5+i*360./n_rods;
    G4double x                = radiusSource*cos( phi * M_PI / 180.0 );
    G4double y                = radiusSource*sin( phi * M_PI / 180.0 );
    std::string padName       ="Pad"+std::to_string(phi);
    std::string guideName     ="Guide" + std::to_string(phi);
    std::string fillingName   ="Filing" + std::to_string(phi);
    std::string vProtName     ="vProt" + std::to_string(phi);
    G4ThreeVector guidesPos   = G4ThreeVector(x, y, guidesZ);
    G4ThreeVector fillingsPos = G4ThreeVector(x, y, 0*cm);
    G4ThreeVector vProtPos    = G4ThreeVector(x,y,hzFillings+vProthLength+1*mm);
    new G4PVPlacement(0,fillingsPos,padsLog,padName,logicWorld,false,0);
    new G4PVPlacement(0,guidesPos,guidesLog,guideName,logicWorld,false,0);
    new G4PVPlacement(0,fillingsPos,fillingsLog,fillingName,logicWorld,false,0);
    new G4PVPlacement(0,vProtPos,vProtLog,vProtName,logicWorld,false,0);
    }


  //Inner Casing
  G4ThreeVector casingPos             = G4ThreeVector(0.,0.,-2.5*cm);
  G4double innerRadiusInnerCasing     = 11.0*cm;
  G4double outerRadiusInnerCasing     = 11.1*cm;
  G4double hzInnerCasing              = 69.0*cm;
  G4Tubs* innerCasingSolid            = new G4Tubs("InnerCasing", innerRadiusInnerCasing, outerRadiusInnerCasing, hzInnerCasing, startAngle, spanningAngle);
  G4LogicalVolume* innerCasingLog     = new G4LogicalVolume(innerCasingSolid, Aluminum, "InnerCasing");
  new G4PVPlacement(0,casingPos,innerCasingLog,"InnerCasing",logicWorld,false,0);

  G4double innerRadiusOuterCasing     = 16.0*cm;
  G4double outerRadiusOuterCasing     = 16.1*cm;
  G4double hzOuterCasing              = 69.0*cm;
  G4Tubs* outerCasingSolid            = new G4Tubs("OuterCasing", innerRadiusOuterCasing, outerRadiusOuterCasing, hzOuterCasing, startAngle, spanningAngle);
  G4LogicalVolume* outerCasingLog     = new G4LogicalVolume(outerCasingSolid, Aluminum, "OuterCasing");
  new G4PVPlacement(0,casingPos,outerCasingLog,"OuterCasing",logicWorld,false,0);

  //Lid
  G4double lidThickness               = 2.0*cm;
  G4ThreeVector lidPos                = G4ThreeVector(0.,0.,guidesZ+hzGuides+lidThickness/2.);
  G4Tubs* lidSolid                    = new G4Tubs("Lid",0.,innerRadiusOuterCasing,lidThickness/2.0,0.,360.);
  G4LogicalVolume* lidLog             = new G4LogicalVolume(lidSolid,StainlessSteel,"Lid") ;
  new G4PVPlacement(0,lidPos,lidLog,"Lid",logicWorld,false,0);

  //Holder
  G4double holderThickness            = 2.0*mm;
  G4ThreeVector holderPos             = G4ThreeVector(0.,0.,-19.0*cm);
  G4Tubs* holderSolid                 = new G4Tubs("Holder",0.,innerRadiusInnerCasing,holderThickness/2.0,0.,360.);
  G4LogicalVolume* holderLog          = new G4LogicalVolume(holderSolid,StainlessSteel,"Holder") ;
  new G4PVPlacement(0,holderPos,holderLog,"Holder",logicWorld,false,0);

  //Walls
  G4double wallsHx                    = 195.0*cm;
  G4double wallsHy                    = 247.5*cm;
  G4double wallsHz                    = 149.0*cm;
  G4double wallsThickness             = 50.0*cm;


  G4VSolid *outerWalls                = new G4Box("outerWalls",wallsHx+wallsThickness,wallsHy+wallsThickness,wallsHz+wallsThickness);  //50 cm is the thickness of the wall
  G4VSolid *innerWalls                = new G4Box("innerWalls",wallsHx,wallsHy,wallsHz);
  G4VSolid *wallsSolid                = new G4SubtractionSolid("walls", outerWalls, innerWalls);

  //wallOpening
  G4double wallOpeningLength          = 100.*cm;
  G4VSolid *wallOpening               = new G4Box("wallOpening",30.0*cm,wallOpeningLength/2.0,wallsHz);
  G4ThreeVector  wallOpeningPos       = G4ThreeVector(220.0*cm, -(wallsHy-wallOpeningLength/2.0), 0*cm); //relative to the wallsPlacement
  G4RotationMatrix identityRot        = G4RotationMatrix();
  G4Transform3D openingTransform      = G4Transform3D(identityRot,wallOpeningPos);  
  G4VSolid *openWallsSolid            = new G4SubtractionSolid("openWalls",wallsSolid,wallOpening,openingTransform);
  G4LogicalVolume* wallsLogic         = new G4LogicalVolume(openWallsSolid, Concrete, "openWalls");
  G4ThreeVector wallsPlacement        = G4ThreeVector(-85.0*cm, -107.5*cm, 77.0*cm);  //center of the source is (0,0,0)
  new G4PVPlacement(0,wallsPlacement,wallsLogic,"openWalls",logicWorld,false,0);


  //steel boards on the floor
  G4double floorBoardThickness        = 3.0*mm;
  G4ThreeVector floorBoardPos         = G4ThreeVector(wallsPlacement.x(),wallsPlacement.y(),wallsPlacement.z()-wallsHz+floorBoardThickness/2.0); 
  G4VSolid *floorBoardSolid           = new G4Box("floorBoard",wallsHx,wallsHy,floorBoardThickness/2.0);
  G4LogicalVolume* floorBoardLog      = new G4LogicalVolume(floorBoardSolid, StainlessSteel, "floorBoard");
  new G4PVPlacement(0,floorBoardPos,floorBoardLog,"floorBoard",logicWorld,false,0,checkOverlaps);

  //aluminum board on right wall (+x)
  G4double  wallBoardThickness        = 2.0*mm;
  G4double  rightWallBoardHeight      = 200*cm;
  G4double  rightWallBoardLength      = 2*wallsHy-wallOpeningLength;
  G4ThreeVector rightWallBoardPos     = G4ThreeVector(wallsPlacement.x()+wallsHx-wallBoardThickness/2.0,wallsPlacement.y()+(wallsHy-rightWallBoardLength/2.0)-2*wallBoardThickness,wallsPlacement.z()-(wallsHz-rightWallBoardHeight/2.0)+floorBoardThickness);
  //This position places the bottom of the board on the floor which goes up to BoardHeight, but in the y direction goes from the back of the wall to the "hole (door)"
  G4VSolid *rightWallBoardSolid       = new G4Box("rightWallBoard",wallBoardThickness/2.0,rightWallBoardLength/2.0,rightWallBoardHeight/2.0);
  G4LogicalVolume* rightWallBoardLog  = new G4LogicalVolume(rightWallBoardSolid, Aluminum, "rightWallBoard");
  new G4PVPlacement(0,rightWallBoardPos,rightWallBoardLog,"rightWallBoard",logicWorld,false,0,checkOverlaps);


  //aluminum board on back wall (+y)
  G4double   backWallBoardHeight      = 200*cm;
  G4double   backWallBoardLength      = 149.0*cm;
  G4ThreeVector backWallBoardPos      = G4ThreeVector(wallsPlacement.x()+(wallsHx-backWallBoardLength/2.0),wallsPlacement.y()+wallsHy-wallBoardThickness,wallsPlacement.z()-(wallsHz-backWallBoardHeight/2.0)+floorBoardThickness);
  //This position places the bottom of the board on the floor which goes up to BoardHeight, but in the x direction goes from the right wall to the left by BoardLenght distance"
  G4VSolid *backWallBoardSolid        = new G4Box("backWallBoard",backWallBoardLength/2.0,wallBoardThickness,backWallBoardHeight/2.0);
  G4LogicalVolume* backWallBoardLog   = new G4LogicalVolume(backWallBoardSolid, Aluminum, "backWallBoard");
  new G4PVPlacement(0,backWallBoardPos,backWallBoardLog,"backWallBoard",logicWorld,false,0,checkOverlaps);


  UserInput config;
  G4VSolid* det_solid                = new G4Box("det",5.0*cm,5.0*cm,5.0*cm);
  G4LogicalVolume* det_logic         = new G4LogicalVolume(det_solid,Water,"det");

   //Placing the detector as a daughter volume of the shielding did not work for some reason!
   new G4PVPlacement(0,config.GetSetupPlacement1(),det_logic, "det", logicWorld, false, 0,checkOverlaps);   
   new G4PVPlacement(0,config.GetSetupPlacement2(),det_logic, "det", logicWorld, false, 0,checkOverlaps);   
   new G4PVPlacement(0,config.GetSetupPlacement3(),det_logic, "det", logicWorld, false, 0,checkOverlaps);   
   new G4PVPlacement(0,config.GetSetupPlacement4(),det_logic, "det", logicWorld, false, 0,checkOverlaps);   
   new G4PVPlacement(0,config.GetSetupPlacement5(),det_logic, "det", logicWorld, false, 0,checkOverlaps);   
   new G4PVPlacement(0,config.GetSetupPlacement6(),det_logic, "det", logicWorld, false, 0,checkOverlaps);   
   // Set det as scoring volume
   fScoringVolume = det_logic;

   //always return the physical World
   return physWorld;
}

