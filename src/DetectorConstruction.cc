#include "DetectorConstruction.hh"
#include "CrystalSensitiveDetector.hh"
#include "SiSensitiveDetector.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4Orb.hh"
#include "G4OpticalSurface.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SubtractionSolid.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"

#include "Materials.hh"

static G4OpticalSurface* siOpticalSurface();

// anonymous namespace so other files can't access these
namespace {
  G4bool checkOverlaps = true;
  void attachTeflonOpticalSurf(G4LogicalVolume* lv)
  {
    G4ThreadLocal static G4OpticalSurface* ts = nullptr;
    if (ts == nullptr) {
      ts = new G4OpticalSurface("teflon_optical_surf");
      ts->SetType(dielectric_dielectric);
      ts->SetModel(unified);
      ts->SetFinish(groundfrontpainted);
      ts->SetSigmaAlpha(0.);
      ts->SetMaterialPropertiesTable(
          G4NistManager::Instance()->
          FindOrBuildMaterial(Materials::kNIST_TEFLON)->
          GetMaterialPropertiesTable());
    }

    (void) new G4LogicalSkinSurface("teflon_skin_surf", lv, ts);
  }

  void attachAlOpticalSurface(G4LogicalVolume* lv)
  {
    G4ThreadLocal static G4OpticalSurface* as = nullptr;
    if (as == nullptr) {
      as = new G4OpticalSurface("al_optical_surf");
      as->SetModel(unified);
      as->SetType(dielectric_metal);
      as->SetFinish(polished);
      as->SetMaterialPropertiesTable(
        G4Material::GetMaterial(Materials::kAL)->
        GetMaterialPropertiesTable());
    }
    (void) new G4LogicalSkinSurface("al_skin_surf", lv, as);
  }
}

DetectorConstruction::DetectorConstruction() :
  G4VUserDetectorConstruction(),
  worldPlacement(nullptr),
  worldLogVol(nullptr)
{
  Materials::makeMaterials();
}

DetectorConstruction::~DetectorConstruction()
{ }

G4VPhysicalVolume* DetectorConstruction::Construct()
{  
  makeWorld();
  makeCeBr3();
  finishCrystalSides();

  bool doMakeTeflon = true;
  if (doMakeTeflon) makeTeflon();
  bool doMakeAluminum = true;
  if (doMakeAluminum) makeAluminum();

  makeSiDetector();
  
  return worldPlacement;
}

void DetectorConstruction::ConstructSDandField()
{
  attachCrystalSensitiveDetector();
  attachSiSensitiveDetector();
}

void DetectorConstruction::makeWorld()
{
  G4VisAttributes va;

  G4Material* vac = G4Material::GetMaterial(Materials::kVACUUM);
  const G4double worldSize = 5*cm;
  G4Box* worldBox =    
    new G4Box("World",
       0.5*worldSize, 0.5*worldSize, 0.5*worldSize);
      
  worldLogVol = new G4LogicalVolume(
      worldBox, vac, "World");
  va.SetColor(1, 1, 1, 0.05);
  va.SetVisibility(true);
  worldLogVol->SetVisAttributes(va);

  worldPlacement = 
    new G4PVPlacement(
      nullptr, G4ThreeVector(), worldLogVol,
      "World", nullptr, false, 0, checkOverlaps);
}

void DetectorConstruction::makeSiDetector()
{
  G4VisAttributes va;
  auto* si = G4NistManager::Instance()->FindOrBuildMaterial(Materials::kNIST_SI);
  auto* siBox = new G4Box(
      "si_box", SI_SIDE/2, SI_SIDE/2, SI_THICK/2);

  siLogVol = new G4LogicalVolume(
    siBox, si, "si_log");
  va.SetColor(0, 0, 1, 0.5);
  va.SetVisibility(true);
  siLogVol->SetVisAttributes(va);

  G4ThreeVector translate(0, 0, CRYST_SIZE/2 + SI_THICK/2);
  (void) new G4PVPlacement(
    nullptr, translate, siLogVol,
    "si_phys", worldLogVol, false, 0, checkOverlaps);

    auto* siSurf = siOpticalSurface();
    (void) new G4LogicalSkinSurface(
      "si_skin", siLogVol, siSurf);
}

void DetectorConstruction::makeCeBr3()
{
  G4VisAttributes va;
  auto* cebr3 = G4Material::GetMaterial(Materials::kCEBR3);

  auto* crystBox = new G4Box(
    "cebr3_box", CRYST_SIZE/2, CRYST_SIZE/2, CRYST_SIZE/2);

  crystLogVol = new G4LogicalVolume(
    crystBox, cebr3, "cebr3_log");
  va.SetColor(0.35, 0.5, 0.92, 0.8);
  va.SetVisibility(true);
  crystLogVol->SetVisAttributes(va);

  crystPlacement = new G4PVPlacement(
    nullptr, G4ThreeVector(), crystLogVol,
    "cebr3_phys", worldLogVol, false, 0, checkOverlaps);
}

void DetectorConstruction::makeTeflon()
{
  G4VisAttributes va;

  const G4double precutHalfThick = (AIR_GAP + TEF_THICK + CRYST_SIZE)/2;

  auto* ptfe = G4NistManager::Instance()->FindOrBuildMaterial(Materials::kNIST_TEFLON);
  auto* preCutPtfeBox = new G4Box(
    "precut_ptfe", precutHalfThick, precutHalfThick, precutHalfThick);

  auto addAirGapHalfXyz = 0.5 * (CRYST_SIZE + AIR_GAP);
  auto* crystPlusAirGap = new G4Box(
    "", addAirGapHalfXyz, addAirGapHalfXyz, addAirGapHalfXyz);
  G4ThreeVector translateSubtract(0, 0, 0);
  auto* slicedPtfe = new G4SubtractionSolid(
    "sliced_ptfe", preCutPtfeBox, crystPlusAirGap, nullptr, translateSubtract);

  translateSubtract = G4ThreeVector(0, 0, 1.8 * cm);
  auto* cutCap = new G4Box("", precutHalfThick + 5*mm, precutHalfThick + 5*mm, precutHalfThick);
  auto* slicedPtfeOpen = new G4SubtractionSolid(
    "sliced_ptfe_open", slicedPtfe, cutCap, nullptr, translateSubtract);

  auto* ptfeLogVol = new G4LogicalVolume(
    slicedPtfeOpen, ptfe, "ptfe_log");
  va.SetColor(0, 1, 0, 0.1);
  va.SetVisibility(true);
  ptfeLogVol->SetVisAttributes(va);
  attachTeflonOpticalSurf(ptfeLogVol);

  (void) new G4PVPlacement(
    nullptr, G4ThreeVector(), ptfeLogVol,
    "ptfe_phys", worldLogVol, false, 0, checkOverlaps);
}

void DetectorConstruction::makeAluminum()
{
  G4VisAttributes va;
  const G4double sliceCapThick = 0.5 * (TEF_THICK + CRYST_SIZE + AL_THICK + 2*AIR_GAP) + 5*mm;
  const G4double precutHalfThick = sliceCapThick - 5*mm;
  const G4double sliceOutHalfThick = precutHalfThick - 0.5 * AL_THICK;

  auto* al = G4Material::GetMaterial(Materials::kAL);
  auto* precut = new G4Box("", precutHalfThick, precutHalfThick, precutHalfThick);
  auto* cutThisOut = new G4Box("", sliceOutHalfThick, sliceOutHalfThick, sliceOutHalfThick);
  auto* cutOffEnd = new G4Box("", sliceCapThick, sliceCapThick, 6*mm);
  auto* hollow = new G4SubtractionSolid(
    "hollow_al", precut, cutThisOut, nullptr, G4ThreeVector());

  G4ThreeVector translateSubtract(0, 0, sliceCapThick);
  auto* open = new G4SubtractionSolid(
    "hollow_open_al", hollow, cutOffEnd, nullptr, translateSubtract);
  
  auto* alLogVol = new G4LogicalVolume(open, al, "al_log");
  va.SetColor(1, 0., 0., 0.1);
  va.SetVisibility(true);
  alLogVol->SetVisAttributes(va);
  attachAlOpticalSurface(alLogVol);

  (void) new G4PVPlacement(
    nullptr, G4ThreeVector(), alLogVol,
    "al_phys", worldLogVol, false, 0, checkOverlaps);
}

void DetectorConstruction::attachCrystalSensitiveDetector()
{
  auto* csd = new CrystalSensitiveDetector("crystal_sens_det");
  crystalSensDet.Put(csd);

  G4SDManager::GetSDMpointer()->AddNewDetector(csd);
  crystLogVol->SetSensitiveDetector(csd);
}

void DetectorConstruction::attachSiSensitiveDetector()
{
  auto* sisd = new SiSensitiveDetector("si_sens_det");
  siSensDet.Put(sisd);

  G4SDManager::GetSDMpointer()->AddNewDetector(sisd);
  siLogVol->SetSensitiveDetector(sisd);
}

void DetectorConstruction::finishCrystalSides()
{
  auto* surf = new G4OpticalSurface("cebr3_optical_edge");
  // See G4 documentation on UNIFIED model
  surf->SetType(dielectric_LUTDAVIS);
  surf->SetModel(DAVIS);
  surf->SetFinish(Rough_LUT);
  (void) new G4LogicalBorderSurface(
    "cebr3_logical_border_surf", 
    crystPlacement, worldPlacement, surf);
}

static G4OpticalSurface* siOpticalSurface()
{
    static G4ThreadLocal G4OpticalSurface* ss = nullptr;
    if (ss) return ss;
    ss = new G4OpticalSurface("si_surf");
    ss->SetMaterialPropertiesTable(
        G4NistManager::Instance()
        ->FindOrBuildMaterial(Materials::kNIST_SI)
        ->GetMaterialPropertiesTable());
    ss->SetModel(unified);
    ss->SetFinish(polished);
    ss->SetType(dielectric_dielectric);
    return ss;
}

