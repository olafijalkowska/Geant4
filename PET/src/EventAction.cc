
// $Id: EventAction.cc 15.10.2018 A. Fijalkowska $
//
/// \file EventAction.cc
/// \brief Implementation of the EventAction class
//
//
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include "G4THitsMap.hh"
#include "SpineHit.hh"

EventAction::EventAction()
{
    outputFile = new OutputFile("EnergyInSpine.root");
}
 
EventAction::~EventAction()
{
     delete outputFile;
}


void EventAction::BeginOfEventAction(const G4Event* anEvent)
{

}
 

void EventAction::EndOfEventAction(const G4Event* anEvent)
{
    //zacznę od znaleziania unikalnego ID naszej kolekcji 
    G4SDManager* SDmanager = G4SDManager::GetSDMpointer();
    G4int collId = SDmanager->GetCollectionID("naISensitiveDet/eDep");
    G4int spineCollId = SDmanager->GetCollectionID("spineHitCollection");
    G4HCofThisEvent *hitsCollOfThisEvent = anEvent->GetHCofThisEvent();
    G4int eventID = anEvent->GetEventID();
    if(!hitsCollOfThisEvent)
        return;
    
    //wyciagamy kolekcje kregoslupowa
    SpineHitsCollection* spineHitColl = (SpineHitsCollection*)( hitsCollOfThisEvent->GetHC(spineCollId) );
    
    G4int size = spineHitColl->entries();
    //std::cout << "evnt " << eventID << " " << "size " << size << " ";
    G4double energyDepInEvent = 0;
    for(G4int i=0; i!=size; i++)
    {
         G4double energyDep = (*spineHitColl)[i]->GetEnDep();
         energyDepInEvent +=energyDep;
         //std::cout << energyDep << " " ;
         G4double time = (*spineHitColl)[i]->GetTime();
    }
    outputFile->AddEnergy(energyDepInEvent);
    
    //std::cout << std::endl;
    //energyDepInEvent - zmienna, która trzyma całkowiety depozyt energii.

/*        
    G4THitsMap<G4double>* myEnDepMap = dynamic_cast <G4THitsMap<G4double>* > 
                                          (hitsCollOfThisEvent->GetHC (collId));
    int nrOfDets = 40;
    G4int eventID = anEvent->GetEventID();
    for(int i =0; i!= nrOfDets; ++i)
    {
        if((*myEnDepMap)[i] != 0L)
        {
            G4double depozytEnergii =*((*myEnDepMap)[i]);
            std::cout << eventID << " " << "numer kopii: " << i << " enDep: " << depozytEnergii/keV << " " 
                      << SteppingAction::totalEnergyDeposit/keV << std::endl;
        }
    }
	//tu chcemy wyciągnąć informacje o calkowiym depozycie energii, wpisać ja do pliku i wyzerować
	//std::cout << SteppingAction::totalEnergyDeposit/keV << std::endl;

  SteppingAction::totalEnergyDeposit = 0;
  if( eventID % 10 == 0 )
  {
    G4cout << "Finished Running Event # " << eventID << G4endl;
  }*/
  
}



