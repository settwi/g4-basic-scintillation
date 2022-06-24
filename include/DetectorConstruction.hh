#pragma once

#include <G4Cache.hh>
#include <G4SystemOfUnits.hh>
#include <G4VUserDetectorConstruction.hh>

class G4Box;
class G4VPhysicalVolume;
class G4LogicalVolume;
class CrystalSensitiveDetector;
class SiSensitiveDetector;

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    virtual ~DetectorConstruction();

    virtual G4VPhysicalVolume* Construct() override;
    void ConstructSDandField() override;
  private:
    void makeWorld();

    void makeCeBr3();
    void finishCrystalSides();
    void attachCrystalSensitiveDetector();

    void makeTeflon();
    void makeAluminum();

    void makeSiDetector();
    void attachSiSensitiveDetector();

    G4VPhysicalVolume* worldPlacement;
    G4LogicalVolume* worldLogVol;
    G4VPhysicalVolume* crystPlacement;
    G4LogicalVolume* crystLogVol;
    G4LogicalVolume* siLogVol;

    constexpr static G4double CRYST_SIZE = 2 * cm;

    constexpr static G4double SI_SIDE = 1 * cm;
    constexpr static G4double SI_THICK = 2 * mm;

    constexpr static G4double TEF_THICK = 1 * mm;
    constexpr static G4double AL_THICK = 1 * mm;
    constexpr static G4double AIR_GAP = 10 * mm;

    G4Cache<CrystalSensitiveDetector*> crystalSensDet;
    G4Cache<SiSensitiveDetector*> siSensDet;
};
