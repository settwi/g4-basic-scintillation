#pragma once

#include "G4Types.hh"

namespace Materials {
    static const G4String kAL = "aluminum";
    static const G4int AL_NUM_COMPONENTS = 1;
    // https://www.engineeringtoolbox.com/metal-alloys-densities-d_50.html
    static const G4double AL_DENSITY = 2.712 * g / cm3;
    
    // https://refractiveindex.info/?shelf=main&book=Al&page=Cheng
    const std::vector<G4double> AL_REFR_IDX_ENERGIES = {
        1.9997*eV, 2.5200*eV, 3.0020*eV, 3.5024*eV,
        4.0255*eV
    };

    const std::vector<G4double> AL_REFR_IDX_REAL = {
        0.798, 0.465, 0.333, 0.255, 0.202
    };

    const std::vector<G4double> AL_REFR_IDX_IMAG = {
        5.495, 4.71, 3.933, 3.341, 2.865
    };

}
