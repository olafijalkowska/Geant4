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
#include "G4Polyhedra.hh"//wielościan
#include "G4ThreeVector.hh" //trzyelementowy wektor wbudowany w geant
#include "globals.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4SDManager.hh"
#include "G4PSEnergyDeposit.hh"


DetectorConstruction::DetectorConstruction()
{
    worldLogic = 0L;
    aluLogic = 0L;
    siliDetLogic = 0L;
    naILogic = 0L;
    teflonLogic=0L;
    man = G4NistManager::Instance();
}



DetectorConstruction::~DetectorConstruction() {}


G4VPhysicalVolume* DetectorConstruction::Construct()
{
    G4VPhysicalVolume* worldPhys = ConstructWorld();
    ConstructWholeDetector();
    ConstructSiliconDetectors();
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

void DetectorConstruction::ConstructSiliconDetectors()
{
    G4Element* Si = man->FindOrBuildElement("Si");
    //G4Element * 	FindOrBuildElement (G4int Z, G4bool isotopes=true)
    
    
    G4Material* siliconMaterial = new G4Material("siliconMat", 2.3290*g/cm3, 1);
    siliconMaterial->AddElement(Si, 1);
    
    G4double radius = 5*cm;
    G4double thick = 3*mm;
    G4Tubs* siliSolid = new G4Tubs("siliSolid", 0, radius, thick/2., 0*deg, 360*deg);
    siliDetLogic = new G4LogicalVolume(siliSolid, siliconMaterial, "siliLogic");
    
    G4VisAttributes* siliVisAtt = new G4VisAttributes(G4Colour(0.5, 0.5, 0.5));
	siliVisAtt->SetForceAuxEdgeVisible(true);// Can see outline when drawn with lines
	siliVisAtt->SetForceSolid(true);
	siliDetLogic->SetVisAttributes(siliVisAtt);
	G4RotationMatrix* siliRot = new G4RotationMatrix();
	siliRot->rotateX(90*deg);
	G4ThreeVector pos1(0, 1*cm, 0);
	new G4PVPlacement(siliRot, pos1, siliDetLogic, "siliPhys", worldLogic, 0, 0, 0);
	G4ThreeVector pos2(0, -1*cm, 0);
	new G4PVPlacement(siliRot, pos2, siliDetLogic, "siliPhys", worldLogic, 0, 1, 0);
}


void DetectorConstruction::ConstructAluHousing()
{
    G4Material* aluMat = man->FindOrBuildMaterial("G4_Al");
    G4double zPlane[] = {-25.4*cm, 25.4*cm};
    G4double side = 6.8*cm;
    G4double rInner[] = {0,0,0,0,0,0};
    G4double rOuter[] = {side,side,side,side,side,side};
    G4Polyhedra* aluSolid = new G4Polyhedra("aluSolid",0*deg, 360*deg, 6, 2, zPlane,rInner,rOuter);
    
    aluLogic = new G4LogicalVolume(aluSolid, aluMat, "aluLogic");
    G4VisAttributes* aluVisAtt = new G4VisAttributes(G4Colour(0.5, 0.9, 0.5));
	aluVisAtt->SetForceAuxEdgeVisible(true);// Can see outline when drawn with lines
	aluLogic->SetVisAttributes(aluVisAtt);
	
	G4ThreeVector pos(12*cm, 0, 0);
    new G4PVPlacement(0, pos, aluLogic, "aluPhys", worldLogic, 0, 0, 0);
    
}

void DetectorConstruction::ConstructTeflonHousing()
{
    G4Material* teflonMat = man->FindOrBuildMaterial("G4_TEFLON");
    G4double zPlane[] = {-25.1*cm, 25.1*cm};
    G4double side = 6.2*cm;
    G4double rInner[] = {0,0,0,0,0,0};
    G4double rOuter[] = {side,side,side,side,side,side};
    G4Polyhedra* teflonSolid = new G4Polyhedra("teflonSolid",0*deg, 360*deg, 6, 2, zPlane,rInner,rOuter);
    
    teflonLogic = new G4LogicalVolume(teflonSolid, teflonMat, "teflonLogic");
    G4VisAttributes* teflonVisAtt = new G4VisAttributes(G4Colour(0.5, 0.5, 0.9));
	teflonVisAtt->SetForceAuxEdgeVisible(true);// Can see outline when drawn with lines
	teflonLogic->SetVisAttributes(teflonVisAtt);
   
    G4ThreeVector pos(0, 0, 0);
    new G4PVPlacement(0, pos, teflonLogic, "teflonPhys", aluLogic, 0, 0, 0);

}

void DetectorConstruction::ConstructNaIDetector()
{
    G4Material* naIMat = man->FindOrBuildMaterial("G4_SODIUM_IODIDE");
    G4double zPlane[] = {-25*cm, 25*cm};
    G4double side = 6*cm;
    G4double rInner[] = {0,0,0,0,0,0};
    G4double rOuter[] = {side,side,side,side,side,side};
    G4Polyhedra* naISolid = new G4Polyhedra("naISolid",0*deg, 360*deg, 6, 2, zPlane,rInner,rOuter);
    
    naILogic = new G4LogicalVolume(naISolid, naIMat, "naILogic");
    G4VisAttributes* naIVisAtt = new G4VisAttributes(G4Colour(0.9, 0.5, 0.5));
	naIVisAtt->SetForceAuxEdgeVisible(true);// Can see outline when drawn with lines
	naIVisAtt->SetForceSolid(true);
	naILogic->SetVisAttributes(naIVisAtt);

    G4ThreeVector pos(0, 0, 0);
    new G4PVPlacement(0, pos, naILogic, "naIPhys", teflonLogic, 0, 0, 0);
}

void DetectorConstruction::ConstructWholeDetector()
{
    ConstructAluHousing();
    ConstructTeflonHousing();
    ConstructNaIDetector();
}


	
void DetectorConstruction::ConstructSDandField() 
{

}






