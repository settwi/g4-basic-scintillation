#include "Materials.hh"

// forward declare here; don't put in header
namespace Materials {
    void configureTeflon();
    void makeCeBr3();
    void configureCeBr3Scintillation();
    void makeVacuum();
    void makeAluminum();
    void configureQuartz();
    void makeBeryllium();
    void makeHousingAluminumAlloy();
    void makeSilicon();
}

namespace {
    static const G4bool useSpline = true;
}

namespace Materials
{
    void makeMaterials()
    {
        if (!G4Material::GetMaterial(kVACUUM))
            makeVacuum();

        if (!G4Material::GetMaterial(kCEBR3)) {
            makeCeBr3();
            configureCeBr3Scintillation();
        }

        auto* nMan = G4NistManager::Instance();
        if (!nMan->FindOrBuildMaterial(kNIST_SIO2)->GetMaterialPropertiesTable())
            configureQuartz();
        if (!nMan->FindOrBuildMaterial(kNIST_TEFLON)->GetMaterialPropertiesTable())
            configureTeflon();
        if (!nMan->FindOrBuildMaterial(kNIST_SI)->GetMaterialPropertiesTable())
            makeSilicon();

        if (!G4Material::GetMaterial(kAL))
            makeAluminum();
        if (!G4Material::GetMaterial(kBE))
            makeBeryllium();
    }

    void configureTeflon()
    {
        auto* nistMan = G4NistManager::Instance();
        auto* teflon = nistMan->FindOrBuildMaterial(kNIST_TEFLON);
        auto* tefPt = new G4MaterialPropertiesTable;

        tefPt->AddProperty(kREFR_IDX, TEFLON_REFR_IDX_ENERGIES, TEFLON_REFR_IDXS, useSpline);
        tefPt->AddProperty(kREFLECTIVITY, TEFLON_REFR_IDX_ENERGIES, TEFLON_REFLECTIVITY, useSpline);

        teflon->SetMaterialPropertiesTable(tefPt);
    }

    void makeCeBr3()
    {
        auto* nMan = G4NistManager::Instance();
        G4Element* ce = nMan->FindOrBuildElement("Ce");
        G4Element* br = nMan->FindOrBuildElement("Br");
        auto* cebr3 = new G4Material(
            kCEBR3,
            CEBR3_DENSITY,
            2.0,
            kStateSolid,
            SATELLITE_TEMP /* atmospheric pressure b/c hermetically sealed */);
        cebr3->AddElement(br, BR_MASS_FRAC);
        cebr3->AddElement(ce, CE_MASS_FRAC);
    }

    void configureCeBr3Scintillation() 
    {
        // to change optical parameters
        // see https://geant4-userdoc.web.cern.ch/UsersGuides/ForApplicationDeveloper/html/TrackingAndPhysics/physicsProcess.html#id1
        auto* opp = G4OpticalParameters::Instance();
        if (!opp) {
            G4Exception(
                "src/Materials.cc configureScintillation()",
                "[no error code]",
                RunMustBeAborted,
                "Optical parameters table not instantiated");
        }

        // can be modified . . .
        opp->SetScintFiniteRiseTime(false);

        auto* cebr3 = G4Material::GetMaterial(kCEBR3);
        if (!cebr3) {
            G4Exception(
                "src/Materials.cc configureScintillation()",
                "[no error code]",
                RunMustBeAborted,
                "Cerium bromide not loaded before configuring scintillation");
        }

        auto* scintPt = new G4MaterialPropertiesTable;

        scintPt->AddConstProperty(kSCINT_YIELD, CEBR3_SCINT_YIELD);
        scintPt->AddProperty(kREFR_IDX, CEBR3_REFR_IDX_ENERGIES, CEBR3_REFR_IDXS, useSpline);

        // updated in v11
        scintPt->AddProperty(
            kONLY_SCINT_COMPONENT, CEBR3_SCINT_OPTICAL_ENERGIES,
            CEBR3_SCINT_OPTICAL_INTENSITIES, useSpline);
        scintPt->AddConstProperty(kONLY_TIME_CONSTANT, CEBR3_DECAY_TIME_CONSTANT);

        // # of photons emitted = RESOLUTION_SCALE * sqrt(mean # of photons)
        scintPt->AddConstProperty(kRESOLUTION_SCALE, CEBR3_SCINT_RESLN_SCALE);
        scintPt->AddProperty(kABSORPTION_LEN, CEBR3_ABS_LEN_ENERGIES, CEBR3_ABS_LEN, useSpline);
        // skip optical Rayleigh scattering (not important)
        // skip Mie scattering (doesn't apply)

        cebr3->SetMaterialPropertiesTable(scintPt);
    }

    void makeVacuum()
    {
        auto* vacMat = new G4Material(
            kVACUUM,
            VACUUM_ATOMIC_NUMBER,
            VACUUM_MOLAR_DENSITY, 
            universe_mean_density,
            kStateGas,
            VACUUM_TEMPERATURE,
            VACUUM_PRESSURE);

        auto* vacPt = new G4MaterialPropertiesTable;

        std::vector<G4double> indices(CEBR3_REFR_IDX_ENERGIES.size(), 1.);
        vacPt->AddProperty(kREFR_IDX, CEBR3_REFR_IDX_ENERGIES, indices, useSpline);

        vacMat->SetMaterialPropertiesTable(vacPt);
    }

    void makeAluminum()
    {
        auto* nistMan = G4NistManager::Instance();
        auto* alElt = nistMan->FindOrBuildElement("Al");
        if (alElt == nullptr) G4cerr << "Nist manager gave nullptr for aluminum" << G4endl;

        auto* al = new G4Material(
            kAL,
            AL_DENSITY,
            AL_NUM_COMPONENTS,
            kStateSolid,
            SATELLITE_TEMP);

        al->AddElement(alElt, G4double(1.0));
        auto* alPt = new G4MaterialPropertiesTable;

        // DO NOT ADD JUST RINDEX!!!!!!!!!!!!!!!!!!!1
        // IT WILL CAUSE PROGRAM TO CRASH IF YOU PUT A SKIN AROUND THE MATERIAL
        /* alPt->AddProperty(kREFR_IDX, AL_REFR_IDX_ENERGIES, AL_REFR_IDX_REAL); */
        alPt->AddProperty(kREFR_IDX_REAL, AL_REFR_IDX_ENERGIES, AL_REFR_IDX_REAL);
        alPt->AddProperty(kREFR_IDX_IMAG, AL_REFR_IDX_ENERGIES, AL_REFR_IDX_IMAG);
        al->SetMaterialPropertiesTable(alPt);
    }

    void configureQuartz()
    {
        auto* qz = G4NistManager::Instance()->FindOrBuildMaterial(kNIST_SIO2);
        auto* qzPt = new G4MaterialPropertiesTable;
        qzPt->AddProperty("RINDEX", QZ_REFR_IDX_ENERGIES, QZ_REFR_IDXS);
        // do not add real/imag refractive indices to materials. they areo nly for surface indices.
        /* qzPt->AddProperty(kREFR_IDX_REAL, QZ_REFR_IDX_ENERGIES, QZ_REFR_IDXS); */
        /* qzPt->AddProperty(kREFR_IDX_IMAG, QZ_REFR_IDX_ENERGIES, std::vector<G4double>(QZ_REFR_IDXS.size(), 0.0)); */

        qz->SetMaterialPropertiesTable(qzPt);
    }

    void makeBeryllium()
    {
        auto* beElt = G4NistManager::Instance()->FindOrBuildElement("Be");
        
        auto* be = new G4Material(
            kBE,
            BE_DENSITY,
            BE_NUM_COMPONENTS,
            kStateSolid,
            SATELLITE_TEMP);
        be->AddElement(beElt, G4int(1));

        auto* bePt = new G4MaterialPropertiesTable;
        bePt->AddProperty(kREFR_IDX, BE_REFR_IDX_ENERGIES, BE_REFR_IDX_REAL);
        bePt->AddProperty(kREFR_IDX_REAL, BE_REFR_IDX_ENERGIES, BE_REFR_IDX_REAL);
        bePt->AddProperty(kREFR_IDX_IMAG, BE_REFR_IDX_ENERGIES, BE_REFR_IDX_IMAG);
        be->SetMaterialPropertiesTable(bePt);
    }

    void makeSilicon()
    {
        auto* si = G4NistManager::Instance()->FindOrBuildMaterial(kNIST_SI);
        if (!si) {
            G4Exception(
                "src/Materials.cc makeSilicon()",
                "[no error code]",
                RunMustBeAborted,
                "Silicon can't be loaded from NIST manager");
        }

        auto* simpt = new G4MaterialPropertiesTable;

        // set to one and apply detection in post-processing (?)
        simpt->AddProperty(kOP_DET_EFF, SI_DET_EFF_ENERGIES, SI_DET_EFF, useSpline);
        std::vector<G4double> refl(SI_BROADCOM_NUMBERS.size(), 0.);
        simpt->AddProperty(kREFLECTIVITY, SI_DET_EFF_ENERGIES, refl, useSpline);
        simpt->AddProperty(kTRANSMITTANCE, SI_DET_EFF_ENERGIES, SI_TRANSMITTANCE, useSpline);
        simpt->AddProperty(kREFR_IDX, SI_REFR_IDX_ENERGY, SI_REFR_IDX_REAL, useSpline);
        simpt->AddProperty(kREFR_IDX_REAL, SI_REFR_IDX_ENERGY, SI_REFR_IDX_REAL, useSpline);
        simpt->AddProperty(kREFR_IDX_IMAG, SI_REFR_IDX_ENERGY, SI_REFR_IDX_IMAG, useSpline);

        si->SetMaterialPropertiesTable(simpt);
    }
}
