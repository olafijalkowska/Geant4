#include "SpineHit.hh"

SpineHit::SpineHit(G4double hitEnergyDep, G4double hitTime) : G4VHit()
{
    energyDep = hitEnergyDep;
    time = hitTime;
}

SpineHit::~SpineHit() {}


SpineHit::SpineHit(const SpineHit &right) : G4VHit()
{
   energyDep = right.energyDep;
   time = right.time;
}

//operator przypisania
const SpineHit& SpineHit::operator=(const SpineHit &right)
{
    time = right.time;
    energyDep = right.energyDep;
    return *this;
}

//operator porownania
G4int SpineHit::operator==(const SpineHit &right) const
{
    return (this==&right) ? 1 : 0;
}

G4ThreadLocal G4Allocator<SpineHit>* SpineHitAllocator=0;
