#include "SpineSD.hh"
#include "G4SDManager.hh"

SpineSD::SpineSD(G4String name) : G4VSensitiveDetector(name)
{
    //obowiązkowa, jest zawszee
    collectionName.insert("spineHitsCollection");

}

SpineSD::~SpineSD() {}

//metoda obowiązkowa, tworzenie kolekcji i dodanie do obiektu
//G4HitsCollectionofThisEvent

void SpineSD::Initialize(G4HCofThisEvent* hitsCE)
{
    spineHitsCollection = new SpineHitsCollection(SensitiveDetectorName,collectionName[0]);
    static G4int hitCID = -1;
    if (hitCID<0) {
      hitCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    }
    hitsCE->AddHitsCollection( hitCID, spineHitsCollection);
}

//tutaj bierzemy kroki i wyciągamy z nich interesujące rzeczy
G4bool SpineSD::ProcessHits(G4Step* aStep, G4TouchableHistory* )
{
   //na moment ją zostawmy
   //szukamy depozytu energii w kroku
   G4double energyDep = aStep->GetTotalEnergyDeposit();
   //szukamy czasu w jakim nastąpił krok
   G4double time = aStep->GetPreStepPoint()->GetGlobalTime();
   //tworzmy obiekt SpineHit z energią i czasem jako parametry
   SpineHit* hit = new SpineHit(energyDep, time);
   //powiększamy spineHitsCollction o nowy hit
   spineHitsCollection->insert(hit);
   //zwracamy prawdę
   return true;
}
