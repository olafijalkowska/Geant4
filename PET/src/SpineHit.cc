#include "SpineHit.hh"

G4ThreadLocal G4Allocator<SpineHit>* SpineHitAllocator=0;

SpineHit::SpineHit(G4double enDepVal, G4double hitTimeVal)
{
    enDep = enDepVal; 
    time = hitTimeVal;
}
SpineHit::~SpineHit() {}

SpineHit::SpineHit(const SpineHit &right) : G4VHit()
{
    enDep = right.enDep;
    time = right.time;
}

//operator przypisania
const SpineHit& SpineHit::operator=(const SpineHit &right)
{
    enDep = right.enDep;
    time = right.time;
    return *this;
}

//operator porownania
G4int SpineHit::operator==(const SpineHit &right) const
{
return (this==&right) ? 1 : 0;
}
