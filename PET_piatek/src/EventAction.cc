
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
    
    file = new TFile("plik_wynikowy.root", "recreate");
    tree = new TTree("drzewo", "drzewo");
    tree->Branch("galaz_energia",&tempEnergy); 
    
    tree2 = new TTree("energy_time", "energy_time");

    double tempEnStep;
    double tempTimeStep;
    
       
}
 
EventAction::~EventAction()
{
    file->Write();
    file->Close();
    delete file;
}


void EventAction::BeginOfEventAction(const G4Event* anEvent)
{

}
 

void EventAction::EndOfEventAction(const G4Event* anEvent)
{
    G4HCofThisEvent *hitsCollOfThisEvent = anEvent->GetHCofThisEvent();
    if(!hitsCollOfThisEvent)
        return;
        
        
        
    //zacznę od znaleziania unikalnego ID naszej kolekcji 
    G4SDManager* SDmanager = G4SDManager::GetSDMpointer();
    int spineCollId=SDmanager->GetCollectionID("spineSD/spineHitsCollection");
    
    //std::cout << spineCollId << std::endl;
    SpineHitsCollection* spineHC = (SpineHitsCollection*) (hitsCollOfThisEvent->GetHC(spineCollId));
    
    int size = spineHC->entries();
    G4int eventID = anEvent->GetEventID();
    double sumOfEnergy = 0;
    //std::cout << "eventId: " << eventID << " " ;
    for(int i = 0; i != size; ++i)
    {
        SpineHit* hit = (*spineHC)[i];
        double energy = hit->GetEnergy();
        double time = hit->GetTime();
        sumOfEnergy += energy/keV;
        //std::cout << energy/keV << " " ;
    
    }
    //std::cout << sumOfEnergy << std::endl;
    tempEnergy = sumOfEnergy;
    tree->Fill();
    
    //to wszystko dotyczy prostego licznika
    /*
    G4int collId = SDmanager->GetCollectionID("naISensitiveDet/eDep");

            
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
  }
  */
}



