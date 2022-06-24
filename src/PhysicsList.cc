#include "PhysicsList.hh"

PhysicsList::PhysicsList() :
    FTFP_BERT()
{
    // updates to FTFP_BERT lists
    ReplacePhysics(new G4EmStandardPhysics_option4);
    RegisterPhysics(new G4OpticalPhysics);
} 
    
PhysicsList::~PhysicsList()
{ }   
