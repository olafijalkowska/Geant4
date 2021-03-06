
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

EventAction::EventAction()
{
}
 
EventAction::~EventAction()
{

}


void EventAction::BeginOfEventAction(const G4Event* anEvent)
{

}
 

void EventAction::EndOfEventAction(const G4Event* anEvent)
{
    //trzyma wszystkie kolekcje hitów
    G4HCofThisEvent *hitsCollOfThisEvent = anEvent->GetHCofThisEvent();
    if(!hitsCollOfThisEvent)
        return;
    
    int eventId = anEvent-> GetEventID();   
    //
    G4SDManager* SDmanager = G4SDManager::GetSDMpointer();
    G4int siliCollId = SDmanager->GetCollectionID("siliSensitiveDet/eDep");
    
    //wyciągamy mapę depozytów energii
    G4THitsMap<G4double>* siliEnDep = dynamic_cast <G4THitsMap<G4double>* > 
                                          (hitsCollOfThisEvent->GetHC(siliCollId));
                                          
    for(int i =0; i!= 2; ++i)
    {
        if((*siliEnDep)[i] != 0L)
        {
            G4double depozytEnergii =*((*siliEnDep)[i]);
            std::cout << eventId << " " << "numer kopii: " << i << " enDep: " << depozytEnergii/keV << std::endl;
        }
    }    
    
}



