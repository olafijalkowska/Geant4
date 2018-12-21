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
#include "G4ThreeVector.hh" //trzyelementowy wektor wbudowany w geant
#include "globals.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4SDManager.hh"
#include "G4PSEnergyDeposit.hh"


DetectorConstruction::DetectorConstruction()
{
    worldLogic = 0L;
    siliLogic = 0L;
    man = G4NistManager::Instance();
}



DetectorConstruction::~DetectorConstruction() {}


G4VPhysicalVolume* DetectorConstruction::Construct()
{
    G4VPhysicalVolume* worldPhys = ConstructWorld();
    ConstructSiliDetectors();
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






