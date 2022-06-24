#include "Analysis.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4GeneralParticleSource.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction() :
  G4VUserPrimaryGeneratorAction(),
  gps(std::make_unique<G4GeneralParticleSource>())
{
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  gps->GeneratePrimaryVertex(anEvent);
  double e = gps->GetParticleEnergy();
  Analysis::instance().addIncidentEnergy(e);
}
