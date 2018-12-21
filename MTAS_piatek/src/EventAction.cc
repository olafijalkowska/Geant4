
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
    G4HCofThisEvent *hitsCollOfThisEvent = anEvent->GetHCofThisEvent();
    if(!hitsCollOfThisEvent)
        return;
        
    //chcemy poznać uniklane ID kolekcji
    G4SDManager* SDmanager = G4SDManager::GetSDMpointer();
    G4int siliCollId = SDmanager->GetCollectionID("siliSensitiveDet/eDep");
    
    //chcemy dostać się do kolekcji
   G4THitsMap<G4double>* siliEnDepMap = dynamic_cast <G4THitsMap<G4double>* > 
                                          (hitsCollOfThisEvent->GetHC (siliCollId));
   
   G4double enDepIn0Copy(0), enDepIn1Copy(0);
   //depozyt energii w pierwszej kopii (0):
   if((*siliEnDepMap)[0] != 0L)
       enDepIn0Copy =*((*siliEnDepMap)[0]);

   //
   if((*siliEnDepMap)[1] != 0L)
       enDepIn1Copy =*((*siliEnDepMap)[1]);
     
   std::cout << enDepIn0Copy/keV << " " << enDepIn1Copy/keV << std::endl;  
     
     /*                                            
    for(int i =0; i!= 2; ++i)
    {
        if((*siliEnDepMap)[i] != 0L)
        {
            G4double depozytEnergii =*((*siliEnDepMap)[i]);

        }
    }*/
}



