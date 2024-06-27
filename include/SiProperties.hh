#pragma once

#include <G4String.hh>
#include <G4Types.hh>
#include <G4SystemOfUnits.hh>

namespace Materials
{
    static const G4String kNIST_SI = "G4_Si";
    static const G4double SI_DENSITY = 2.33 * g / cm3;

    // Optical detection has 100% efficiency: fix it in post-processing if desired
    const auto SI_DET_EFF_ENERGIES = {0.1 * eV, 5 * eV};
    const auto SI_DET_EFF = std::vector<double>(SI_DET_EFF_ENERGIES.size(), 1);

    const std::vector<G4double> SI_REFR_IDX_ENERGY = {
        1.50*eV, 1.60*eV, 1.70*eV, 1.80*eV, 1.90*eV, 2.00*eV, 2.10*eV, 2.20*eV,
        2.30*eV, 2.40*eV, 2.50*eV, 2.60*eV, 2.70*eV, 2.80*eV, 2.90*eV, 3.00*eV,
        3.10*eV, 3.20*eV, 3.30*eV, 3.40*eV, 3.50*eV, 3.60*eV, 3.70*eV, 3.80*eV,
        3.90*eV, 4.00*eV, 4.10*eV, 4.20*eV, 4.30*eV, 4.40*eV, 4.50*eV, 4.60*eV,
        4.70*eV, 4.80*eV, 4.90*eV, 5.00*eV, 5.10*eV, 5.20*eV, 5.30*eV, 5.40*eV,
        5.50*eV, 5.60*eV, 5.70*eV, 5.80*eV, 5.90*eV, 6.00*eV
    };

    const std::vector<G4double> SI_REFR_IDX_REAL = {
        3.67*1, 3.71*1, 3.75*1, 3.80*1, 3.85*1, 3.91*1, 3.97*1, 4.04*1,
        4.12*1, 4.21*1, 4.32*1, 4.44*1, 4.58*1, 4.75*1, 4.96*1, 5.22*1,
        5.57*1, 6.06*1, 6.71*1, 6.52*1, 5.61*1, 5.30*1, 5.16*1, 5.07*1,
        5.02*1, 5.01*1, 5.02*1, 4.89*1, 4.09*1, 3.12*1, 2.45*1, 1.99*1,
        1.76*1, 1.66*1, 1.60*1, 1.57*1, 1.57*1, 1.59*1, 1.58*1, 1.47*1,
        1.34*1, 1.25*1, 1.19*1, 1.13*1, 1.08*1, 1.01*1
    };

    const std::vector<G4double> SI_REFR_IDX_IMAG = {
        0.01*1, 0.01*1, 0.01*1, 0.01*1, 0.02*1, 0.02*1, 0.03*1, 0.03*1,
        0.05*1, 0.06*1, 0.07*1, 0.09*1, 0.13*1, 0.16*1, 0.20*1, 0.27*1,
        0.39*1, 0.63*1, 1.32*1, 2.71*1, 3.01*1, 2.99*1, 3.06*1, 3.18*1,
        3.35*1, 3.59*1, 3.98*1, 4.64*1, 5.39*1, 5.34*1, 5.08*1, 4.68*1,
        4.28*1, 3.98*1, 3.75*1, 3.56*1, 3.43*1, 3.35*1, 3.35*1, 3.37*1,
        3.30*1, 3.21*1, 3.12*1, 3.04*1, 2.98*1, 2.91*1
    };
}
