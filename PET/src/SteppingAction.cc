//
// $Id: SteppingAction.cc 15.10.2018 A. Fijalkowska $
//
/// \file SteppingAction.cc
/// \brief Implementation of the SteppingAction class
//
//
#include "SteppingAction.hh"
#include "G4SteppingManager.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4String.hh"
#include <iostream>

SteppingAction::SteppingAction():G4UserSteppingAction()
{

}

SteppingAction::~SteppingAction() {}


void SteppingAction::UserSteppingAction(const G4Step* theStep)
{
    //wyświetl krok tylko jeśli miał on miejsce w materiale o nazwie "G4_BONE_COMPACT_ICRU"
    /*G4Track* track = theStep->GetTrack();
    G4VPhysicalVolume* physVol = track->GetVolume();
    G4LogicalVolume* logicVolume = physVol->GetLogicalVolume();
    G4Material* material = logicVolume->GetMaterial();
    G4String materialName = material->GetName();*/
    
    G4String materialName = theStep->GetTrack()->GetVolume()->GetLogicalVolume()->GetMaterial()->GetName();
    
    if(materialName == "G4_SODIUM_IODIDE" /*&& copyNumber == 39*/)
    {
        int copyNumber = theStep->GetPostStepPoint()->GetTouchable()->GetReplicaNumber(1);
        //PrintStep(theStep);
        //zwraca depozyt energii w kroku
        if(copyNumber == 39)
        {
            double energyDepInStep = theStep->GetTotalEnergyDeposit();
            totalEnergyDeposit += energyDepInStep;
        }
        //std::cout << totalEnergyDeposit << std::endl;
    }
}




void SteppingAction::PrintStep(const G4Step* theStep)
{
    
    G4Track* theTrack = theStep->GetTrack();
    G4String processName =theStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
    G4String particleName = theTrack->GetDefinition()->GetParticleName();    
    G4String volumeName = theTrack->GetVolume()->GetName();
    G4double deltaEn = theStep->GetDeltaEnergy();

    std::cout << " particle: " << particleName
		      << " process: " << processName
		      << " delta en: " << deltaEn
		      << " voulme name: " << volumeName << std::endl;

}


double SteppingAction::totalEnergyDeposit = 0;
