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
#include "SpineSD.hh"


DetectorConstruction::DetectorConstruction()
{
    worldLogic = 0L;
    fantomLogVol=0L;
    naILog = 0L;
    spineLogVol = 0L;
    man = G4NistManager::Instance();
}



DetectorConstruction::~DetectorConstruction() {}


G4VPhysicalVolume* DetectorConstruction::Construct()
{
    G4VPhysicalVolume* worldPhys = ConstructWorld();
    ConstructHumanFantom();
    ConstructCylinder();
    ConstructNaIDetector();
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

void DetectorConstruction::ConstructHumanFantom()
{   
    G4Element* H = man->FindOrBuildElement("H");
    G4Element* O = man->FindOrBuildElement("O");
    G4Material* water = new G4Material("water", 1.0*g/cm3, 2);
    water->AddElement(H, 2);
    water->AddElement(O, 1);

    G4double radiusMin = 0;
    G4double radiusMax = 15*cm;
    G4double length = 170*cm;
    G4Tubs* fantomSolid = new G4Tubs("fantomSolid", radiusMin, radiusMax, length/2., 0*deg, 360*deg);
    fantomLogVol = new G4LogicalVolume(fantomSolid, water, "fantomLogVol");

     
    G4VisAttributes* fantomVisAtt = new G4VisAttributes( G4Colour(1,0.8,0.8));
	fantomVisAtt->SetForceAuxEdgeVisible(true);// Can see outline when drawn with lines
	//fantomVisAtt->SetForceSolid(true);
	fantomLogVol->SetVisAttributes(fantomVisAtt);

	G4ThreeVector pos(0,0,0);    
	new G4PVPlacement(0, pos, fantomLogVol, "fantom", worldLogic, 0, 0);
	
	ConstructHumanSpine();
}

void DetectorConstruction::ConstructHumanSpine()
{
    G4double radiusMin = 0;
    G4double radiusMax = 2*cm;
    G4double length = 85*cm;
    G4Tubs* spineSolid = new G4Tubs("spineSolid", radiusMin, radiusMax, length/2., 0*deg, 360*deg);
    
    G4Material* boneMat = man->FindOrBuildMaterial("G4_BONE_COMPACT_ICRU");
    spineLogVol = new G4LogicalVolume(spineSolid, boneMat, "spineLogVol");
    
    G4VisAttributes* spineVisAtt = new G4VisAttributes( G4Colour(1,0.95,0.95));
	spineVisAtt->SetForceAuxEdgeVisible(true);// Can see outline when drawn with lines
	spineVisAtt->SetForceSolid(true);
	spineLogVol->SetVisAttributes(spineVisAtt); 
	
	
	G4ThreeVector pos(5*cm,0,length/2.);   
    new G4PVPlacement(0, pos, spineLogVol, "spinePhys", fantomLogVol, 0, 0);

}


void DetectorConstruction::ConstructNaIDetector()
{
    G4double sizeX = 6*cm;
    G4double sizeY = 10*cm;
    G4double sizeZ = 8*cm;
    G4double teflonThick = 2*mm;
    G4Box* teflonSolid = new G4Box("teflonSolid", 
                                   sizeX/2.+teflonThick, 
                                   sizeY/2.+teflonThick, 
                                   sizeZ/2.+teflonThick);
    
    G4Material* teflonMat = man->FindOrBuildMaterial("G4_TEFLON");
    G4LogicalVolume* teflonLog = new G4LogicalVolume(teflonSolid, teflonMat, "teflonLog");
    
    G4VisAttributes* teflonVisAtt = new G4VisAttributes( G4Colour(0,0.95,0.95, 0.2));
	teflonVisAtt->SetForceAuxEdgeVisible(true);// Can see outline when drawn with lines
	teflonVisAtt->SetForceSolid(true);
	teflonLog->SetVisAttributes(teflonVisAtt); 

	G4LogicalVolume* naICrystalLog = ConstructNaICrystal(sizeX, sizeY, sizeZ);
	
	
    G4ThreeVector naIPos(0, 0, 0);
    new G4PVPlacement(0, naIPos, naICrystalLog, "naIPhys", teflonLog, 0, 0);

    G4double radius = 46.1 * cm;
   int nrOfDets = 40;
   for(int i = 0; i!= nrOfDets; ++i)
   {
       G4double theta = i * 360.*deg/nrOfDets;
       G4ThreeVector pos(radius*sin(theta), radius*cos(theta), 0);
       G4RotationMatrix* rot = new G4RotationMatrix();
       rot->rotateZ(theta);
       new G4PVPlacement(rot, pos, teflonLog, "teflonPhys", theCylinderLogVol, 0, i);
   
   }



/*	
	G4LogicalVolume* naICrystalLog = ConstructNaICrystal(sizeX, sizeY, sizeZ);
	G4ThreeVector posNaI(0,0,0);   
    new G4PVPlacement(0, posNaI, naICrystalLog, "naIPhys", teflonLog, 0, 0);
    
	
	G4double radius = 46*cm;
	G4double nrOfDets = 25; 
	G4double deltaTheta = 2*M_PI/nrOfDets;
	for (int i = 0; i!= nrOfDets; ++i) 
	{
	    G4double theta = i*deltaTheta;
	    G4ThreeVector posDet(radius*sin(theta),radius*cos(theta),0);
	    G4RotationMatrix *rot = new G4RotationMatrix();
        rot->rotateZ(theta);
        new G4PVPlacement(rot, posDet, teflonLog, "teflonPhys", worldLogic, 0, i);
	
	}  */
}

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
}



void DetectorConstruction::ConstructCylinder()
{
     G4Material* ppy = man->FindOrBuildMaterial("G4_POLYPROPYLENE");
     G4double rMin = 40*cm;
     G4double rMax = 55*cm;
     G4double length = 15*cm;
     G4Tubs* theCylinder = new G4Tubs("theCylinder", rMin, rMax, length/2, 0*deg, 360*deg);
     theCylinderLogVol = new G4LogicalVolume(theCylinder, ppy, "theCylinderLogVol");

     G4VisAttributes* cylinderAtt = new G4VisAttributes(G4Colour(0.5,0.5,0.5, 0.7));
     cylinderAtt->SetForceAuxEdgeVisible(true);
     cylinderAtt->SetForceSolid(true);
     theCylinderLogVol->SetVisAttributes(cylinderAtt);

     G4ThreeVector pos(0,0, 0);
     new G4PVPlacement(0,pos,theCylinderLogVol, "cylinderPhy",worldLogic,0,0);
}

	
void DetectorConstruction::ConstructSDandField() 
{
    //ustalanie mierzących elementów detektora
    
    G4MultiFunctionalDetector* detector = new G4MultiFunctionalDetector("naISensitiveDet");
    G4SDManager* SDmanager = G4SDManager::GetSDMpointer();
    SDmanager->AddNewDetector(detector);
    naILog->SetSensitiveDetector(detector);
    G4int depth = 1;
    G4VPrimitiveScorer* energyDepScorer = new G4PSEnergyDeposit("eDep",depth);
    detector->RegisterPrimitive(energyDepScorer);




    //tworze instancję klasy SpineSDG4SDManager* SDmanager = G4SDManager::GetSDMpointer();
    SpineSD* spineSD = new SpineSD("spineSD");
    //dodaję sensitive detector do G4SDManager
    SDmanager->AddNewDetector(spineSD);
    //przypisuję sensitive detector do jakiejść zmiennej log vol
    spineLogVol->SetSensitiveDetector(spineSD);
}






