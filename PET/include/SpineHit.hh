#ifndef SpineHit_H
#define SpineHit_H 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"

class SpineHit : public G4VHit
{
public:
    SpineHit(G4double enDep, G4double hitTime);
    virtual ~SpineHit();
    //konstruktor kopiujący
    SpineHit(const SpineHit &right);
    //operator przypisania
    const SpineHit& operator=(const SpineHit &right);
    //operator porównania 
    G4int operator==(const SpineHit &right) const;
    inline void *operator new(size_t);
    inline void operator delete(void *aHit);
    G4double GetEnDep(){return enDep;}
    G4double GetTime(){return time;}
    
    private:
    G4double enDep;
    G4double time;
};


//WAZNE i OBOWIĄZKOWE, zawsze wyglada tak samo
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
