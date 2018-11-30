#ifndef SpineSD_H
#define SpineSD_H 1

#include "G4VSensitiveDetector.hh"
#include "SpineHit.hh"
class SpineSD : public G4VSensitiveDetector
{
public:
    SpineSD(G4String name);
    virtual ~SpineSD();
    virtual void Initialize(G4HCofThisEvent* );
    virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* );
private:

    G4double GetEnDep(G4Step* aStep);
    G4double GetTime(G4Step* aStep);
    SpineHitsCollection* spineHitCollection;

};

#endif
