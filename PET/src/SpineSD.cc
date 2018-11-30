#include "SpineSD.hh"
#include "G4SDManager.hh"

SpineSD::SpineSD(G4String name): G4VSensitiveDetector(name)
{
    collectionName.insert("spineHitCollection");
}

SpineSD::~SpineSD() {}

void SpineSD::Initialize(G4HCofThisEvent* hitsCE)
{
    spineHitCollection = new SpineHitsCollection(SensitiveDetectorName,
                                                 collectionName[0]);
    static G4int hitCID = -1;
    if (hitCID<0) 
    {
         hitCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    }
    hitsCE->AddHitsCollection( hitCID, spineHitCollection);
}

G4bool SpineSD::ProcessHits(G4Step* aStep, G4TouchableHistory* )
{
    G4double enDep = GetEnDep(aStep);
    G4double time = GetTime(aStep);
    SpineHit* aHit = new SpineHit(enDep, time);
    spineHitCollection->insert( aHit );
    return true;
}

G4double SpineSD::GetEnDep(G4Step* aStep)
{
    G4double eDep = aStep->GetTotalEnergyDeposit();
    return eDep;
}

G4double SpineSD::GetTime(G4Step* aStep)
{
    G4StepPoint* preStepPoint = aStep->GetPreStepPoint(); 
    return preStepPoint->GetGlobalTime();
}

