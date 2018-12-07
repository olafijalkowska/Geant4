#ifndef SpineHit_h
#define SpineHit_h 1
#include "G4VHit.hh"
#include "G4THitsCollection.hh"

class SpineHit : public G4VHit
{
public:
   SpineHit(G4double hitEnergyDep, G4double hitTime);
   virtual ~SpineHit();
   
   SpineHit(const SpineHit &right);
   const SpineHit& operator=(const SpineHit &right);
   G4int operator==(const SpineHit &right) const;
   inline void *operator new(size_t);
   inline void operator delete(void *aHit);
   G4double GetEnergy() { return energyDep;}
   G4double GetTime() {return time;}

private:
    G4double energyDep;
    G4double time;
};

typedef G4THitsCollection<SpineHit> SpineHitsCollection;

extern G4ThreadLocal G4Allocator<SpineHit>* SpineHitAllocator;
inline void* SpineHit::operator new(size_t)
{
   if(!SpineHitAllocator)
      SpineHitAllocator = new G4Allocator<SpineHit>;
   return (void *) SpineHitAllocator->MallocSingle();
}

inline void SpineHit::operator delete(void *aHit)
{
    SpineHitAllocator->FreeSingle((SpineHit*) aHit);
}


#endif
