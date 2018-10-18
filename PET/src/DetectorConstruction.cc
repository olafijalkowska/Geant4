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
#include "G4NistManager.hh"  //wbudowane materiały
#include "G4Box.hh" //prostopadłościan
#include "G4Tubs.hh" //walec
#include "G4ThreeVector.hh" //trzyelementowy wektor wbudowany w geant
#include "globals.hh"

DetectorConstruction::DetectorConstruction()
{
  worldLogic = 0L;
}



DetectorConstruction::~DetectorConstruction() {}


G4VPhysicalVolume* DetectorConstruction::Construct()
{
    G4VPhysicalVolume* worldPhys = ConstructWorld();
    ConstructHumanFantom();
    return worldPhys;
}


G4VPhysicalVolume* DetectorConstruction::ConstructWorld()
{

    G4double worldX = 5.*m;
    G4double worldY = 5.*m;
    G4double worldZ = 5.*m;
    G4Material* vaccum = new G4Material("GalacticVacuum", 1., 1.01*g/mole,
                           CLHEP::universe_mean_density, 
                           kStateGas, 3.e-18*pascal, 2.73*kelvin);
  
    G4Box* worldSolid = new G4Box("worldSolid",worldX,worldY,worldZ);
    worldLogic = new G4LogicalVolume(worldSolid, vaccum,"worldLogic", 0,0,0);
                                             
    //worldLogic->SetVisAttributes(G4VisAttributes::Invisible);
    G4VPhysicalVolume* worldPhys = new G4PVPlacement(0, G4ThreeVector(), worldLogic, "world", 0, false, 0);
    return worldPhys;

}

void DetectorConstruction::ConstructHumanFantom()
{

    G4NistManager* man = G4NistManager::Instance();
    G4Element* H = man->FindOrBuildElement("H");
    G4Element* O = man->FindOrBuildElement("O");
    G4Material* water = new G4Material("water", 1.0*g/cm3, 2);
    water->AddElement(H, 2);
    water->AddElement(O, 1);

    G4double radiusMin = 0;
    G4double radiusMax = 60*cm;
    G4double length = 170*cm;
    G4Tubs* fantomSolid = new G4Tubs("fantomSolid", radiusMin, radiusMax, length/2., 0*deg, 360*deg);
    G4LogicalVolume* fantomLogVol = new G4LogicalVolume(fantomSolid, water, "fantomLogVol");

     
    G4VisAttributes* fantomVisAtt = new G4VisAttributes( G4Colour(1,0.8,0.8));
	fantomVisAtt->SetForceAuxEdgeVisible(true);// Can see outline when drawn with lines
	fantomVisAtt->SetForceSolid(true);
	fantomLogVol->SetVisAttributes(fantomVisAtt);

	G4ThreeVector pos(0,0,0);    
	new G4PVPlacement(0, pos, fantomLogVol, "fantom", worldLogic, 0, 0);
	


}

void DetectorConstruction::ConstructSDandField() 
{
    //ustalanie mierzących elementów detektora
}






