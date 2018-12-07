#ifndef SpineSD_h
#define SpineSD_h 1
#include "G4VSensitiveDetector.hh"
#include "SpineHit.hh"

class SpineSD : public G4VSensitiveDetector
{
  public:
    SpineSD(G4String name);
    ~SpineSD();
    virtual void Initialize(G4HCofThisEvent* );
    virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* );
  private:
    SpineHitsCollection* spineHitsCollection;

};

#endif

