
// $Id: PrimaryGeneratorAction.cc 15.10.2018 A Fijalkowska $
//
/// \file PrimaryGeneratorAction.cc
/// \brief Implementation of the PrimaryGeneratorAction class

#include "PrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "Randomize.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"


PrimaryGeneratorAction::PrimaryGeneratorAction() : G4VUserPrimaryGeneratorAction()
{
    particleGun = new G4ParticleGun();
    particleTable = G4ParticleTable::GetParticleTable();
	SetUpDefault();
}


PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete particleGun;
}

void PrimaryGeneratorAction::SetUpDefault()
{
	
	G4ParticleDefinition* particle = particleTable->FindParticle("gamma");
	particleGun->SetParticleDefinition(particle);
	particleGun->SetParticlePosition(G4ThreeVector(0.0*cm,0.0*cm,0.0*cm));
	particleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
	particleGun->SetParticleEnergy(500.0*keV);

}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{	
    GeneratePositronIncident(anEvent);
    //particleGun->GeneratePrimaryVertex(anEvent);
}	

void PrimaryGeneratorAction::GeneratePositronIncident(G4Event* anEvent)
{
    //1. wybieranie pozytonu
	G4ParticleDefinition* particle = particleTable->FindParticle("e+");
	particleGun->SetParticleDefinition(particle);		
    //2. wysyłanie ze środka
    particleGun->SetParticlePosition(G4ThreeVector(0.0*cm,0.0*cm,0.0*cm));
    //3. energia 600 keV
    particleGun->SetParticleEnergy(587*keV);
    //4. izotropowo
    particleGun->SetParticleMomentumDirection(GenerateIsotropicDirection());
    //5. wyślij tą cząstkę
    particleGun->GeneratePrimaryVertex(anEvent);
}

G4ThreeVector PrimaryGeneratorAction::GenerateIsotropicDirection()
{
   G4double randomPhi = G4UniformRand()*2.*M_PI;
   G4double randomCosTheta = G4UniformRand()*2. - 1.;
   G4double randomTheta = acos(randomCosTheta);
   G4double x = sin(randomTheta)*sin(randomPhi);
   G4double y = sin(randomTheta)*cos(randomPhi);
   G4double z = cos(randomTheta);
   return G4ThreeVector(x, y,z);
}



