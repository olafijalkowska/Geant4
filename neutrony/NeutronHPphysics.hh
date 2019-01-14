
// $Id: NeutronHPphysics.hh 2016-15-11 A Fijalkowska $
//
/// \file NeutronHPphysics.hh
/// \brief Definition of the NeutronHPphysics class
/// Class taken from example hadronic/Hadr04
//


#ifndef NeutronHPphysics_h
#define NeutronHPphysics_h 1

#include "globals.hh"
#include "G4VPhysicsConstructor.hh"

class NeutronHPphysics : public G4VPhysicsConstructor
{
  public:
    NeutronHPphysics(const G4String& name="neutron");
   ~NeutronHPphysics();

  public:
    virtual void ConstructParticle() { };
    virtual void ConstructProcess();
    
  public:
    void SetThermalPhysics(G4bool flag) {fThermal = flag;};  
    
  private:
    G4bool  fThermal; 
};

#endif

