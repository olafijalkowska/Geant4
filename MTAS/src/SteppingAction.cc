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


