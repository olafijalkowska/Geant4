//
// $Id: DetectorConstruction.cc 12.16.2016 A. Fijalkowska $
//
/// \file DetectorConstruction.cc
/// \brief DetectorConstruction class
//
//
#include "DetectorConstruction.hh"
#include "G4PVPlacement.hh" //tworzenie physical volume
#include "G4SystemOfUnits.hh" //jednostki
#include "G4VisAttributes.hh" //sposob wyświetlania, kolory itp
#include "G4Material.hh" //materiały
#include "G4Box.hh" //prostopadłościan
#include "G4Tubs.hh" //walec
#include "G4Polyhedra.hh"
#include "G4ThreeVector.hh" //trzyelementowy wektor wbudowany w geant
#include "globals.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4SDManager.hh"
#include "G4PSEnergyDeposit.hh"


DetectorConstruction::DetectorConstruction()
{
    worldLogic = 0L;
    siliLogic = 0L;
    aluLogic = 0L;
    teflonLogic = 0L;
    naILogic = 0L;
    man = G4NistManager::Instance();
}



DetectorConstruction::~DetectorConstruction() {}


G4VPhysicalVolume* DetectorConstruction::Construct()
{
    G4VPhysicalVolume* worldPhys = ConstructWorld();
    ConstructSiliDetectors();
    ConstructAluLayer();
    return worldPhys;
}


G4VPhysicalVolume* DetectorConstruction::ConstructWorld()
{

    G4double worldX = 1.5*m;
    G4double worldY = 1.5*m;
    G4double worldZ = 1.5*m;
    G4Material* vaccum = new G4Material("GalacticVacuum", 1., 1.01*g/mole,
                           CLHEP::universe_mean_density, 
                           kStateGas, 3.e-18*pascal, 2.73*kelvin);
  
    G4Box* worldSolid = new G4Box("worldSolid",worldX,worldY,worldZ);
    worldLogic = new G4LogicalVolume(worldSolid, vaccum,"worldLogic", 0,0,0);
                                             
    //worldLogic->SetVisAttributes(G4VisAttributes::Invisible);
    G4VPhysicalVolume* worldPhys = new G4PVPlacement(0, G4ThreeVector(), worldLogic, "world", 0, false, 0);
    return worldPhys;

}

void DetectorConstruction::ConstructSiliDetectors()
{
    //tworzenie krzemu
    G4Material* silicon = man->FindOrBuildMaterial("G4_Si");
    G4double rMin = 0;
    G4double rMax = 5*cm;
    G4double height = 3*mm;
    G4double phiMin = 0*deg;
    G4double phiMax = 360*deg;
    G4Tubs* siliShape = new G4Tubs("siliColid", rMin, rMax, height/2., phiMin, phiMax);
    
    
    siliLogic = new G4LogicalVolume(siliShape, silicon, "siliLogic");
    
    G4VisAttributes* siliVisAtt = new G4VisAttributes( G4Colour::Red());
	siliVisAtt->SetForceAuxEdgeVisible(true);// Can see outline when drawn with lines
	siliVisAtt->SetForceSolid(true);
	siliLogic->SetVisAttributes(siliVisAtt);
	
	
	G4RotationMatrix* rot = new G4RotationMatrix();
	rot->rotateX(90*deg);
	G4ThreeVector place(0,1*cm,0);
    new G4PVPlacement(rot, place, siliLogic, "siliPhys", worldLogic, 0, 0);
    place = G4ThreeVector(0,-1*cm,0);
    new G4PVPlacement(rot, place, siliLogic, "siliPhys", worldLogic, 0, 1);
	
	
}


void DetectorConstruction::ConstructAluLayer()
{
   //kształt
    G4double zPlane[] = {-25.6 *cm, 25.6*cm};
    G4double rInner[] = {0,0,0,0,0,0};
    G4double radius = 6.6*cm;
    G4double rOuter[] = {radius, radius, radius, radius, radius, radius};
    G4Polyhedra* aluSolid = new G4Polyhedra ("aluSolid", 0*deg,360*deg, 6, 2, zPlane, rInner, rOuter);
   
    G4Material* aluminum = man->FindOrBuildMaterial("G4_Al");
    aluLogic = new G4LogicalVolume(aluSolid, aluminum, "aluLogic");
   
    G4VisAttributes* aluVisAtt = new G4VisAttributes( G4Colour::Blue());
    aluVisAtt->SetForceAuxEdgeVisible(true);// Can see outline when drawn with lines
    aluLogic->SetVisAttributes(aluVisAtt);
    
    //powstawanie kolejnych warstw
    ConstructTeflonLayer();
    ConstructNaIDetectors();
    
    double D = 13.2*cm;
    for(int i = 0; i!=6; ++i)
    {
        double alpha = 60*deg*i;
        G4ThreeVector place(D*sin(alpha),D*cos(alpha),0);
	    new G4PVPlacement(0, place, aluLogic, "aluPhys", worldLogic, 0, i);
	}
    
}

void DetectorConstruction::ConstructTeflonLayer()
{
   //kształt
    G4double zPlane[] = {-25.1 *cm, 25.1*cm};
    G4double rInner[] = {0,0,0,0,0,0};
    G4double radius = 6.1*cm;
    G4double rOuter[] = {radius, radius, radius, radius, radius, radius};
    G4Polyhedra* solid = new G4Polyhedra ("teflonSolid", 0*deg,360*deg, 6, 2, zPlane, rInner, rOuter);
   
    G4Material* teflon = man->FindOrBuildMaterial("G4_TEFLON");
    teflonLogic = new G4LogicalVolume(solid, teflon, "teflonLogic");
   
    G4VisAttributes* visAtt = new G4VisAttributes( G4Colour::Grey());
    visAtt->SetForceAuxEdgeVisible(true);// Can see outline when drawn with lines
    teflonLogic->SetVisAttributes(visAtt);
    G4ThreeVector place(0,0,0);
	new G4PVPlacement(0, place, teflonLogic, "teflonPhys", aluLogic, 0, 0);
}

void DetectorConstruction::ConstructNaIDetectors()
{
   //kształt
    G4double zPlane[] = {-25. *cm, 25.*cm};
    G4double rInner[] = {0,0,0,0,0,0};
    G4double radius = 6.*cm;
    G4double rOuter[] = {radius, radius, radius, radius, radius, radius};
    G4Polyhedra* solid = new G4Polyhedra ("aluSolid", 0*deg,360*deg, 6, 2, zPlane, rInner, rOuter);
   
    G4Material* naI = man->FindOrBuildMaterial("G4_SODIUM_IODIDE");
    naILogic = new G4LogicalVolume(solid, naI, "naILogic");
   
    G4VisAttributes* visAtt = new G4VisAttributes( G4Colour::Green());
    visAtt->SetForceAuxEdgeVisible(true);// Can see outline when drawn with lines
    visAtt->SetForceSolid(true);
    naILogic->SetVisAttributes(visAtt);
    G4ThreeVector place(0,0,0);
	new G4PVPlacement(0, place, naILogic, "naIPhys", teflonLogic, 0, 0);
}




/*
G4LogicalVolume* DetectorConstruction::ConstructNaICrystal(G4double sizeX, 
                                                          G4double sizeY, 
                                                          G4double sizeZ)
{
	G4Box* naISolid = new G4Box("naISolid", sizeX/2., sizeY/2., sizeZ/2.);
    G4Material* naIMat = man->FindOrBuildMaterial("G4_SODIUM_IODIDE");
	naILog = new G4LogicalVolume(naISolid, naIMat, "naILog");
	
	G4VisAttributes* naIVisAtt = new G4VisAttributes( G4Colour(0,1,0.5, 1.));
	naIVisAtt->SetForceAuxEdgeVisible(true);// Can see outline when drawn with lines
	naIVisAtt->SetForceSolid(true);
	naILog->SetVisAttributes(naIVisAtt);
    return naILog;
}*/





	
void DetectorConstruction::ConstructSDandField() 
{
    G4MultiFunctionalDetector* detector =
     new G4MultiFunctionalDetector("siliSensitiveDet");
    G4SDManager* SDmanager = G4SDManager::GetSDMpointer();
    SDmanager->AddNewDetector(detector);
    siliLogic->SetSensitiveDetector(detector);
    G4int depth = 0;
    G4VPrimitiveScorer* energyDepScorer = new G4PSEnergyDeposit("eDep",depth);
    detector->RegisterPrimitive(energyDepScorer);
}






