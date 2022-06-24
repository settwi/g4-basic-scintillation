#pragma once

namespace Materials {
    static const G4String kNIST_TEFLON = "G4_TEFLON";
    
    // to be better filled in once precise teflon type is known (if necessary)
    static const std::vector<G4double> TEFLON_REFR_IDX_ENERGIES = {
        0.1*eV, 100*eV
    };

    static const std::vector<G4double> TEFLON_REFR_IDXS = {
        1.38, 1.38
    };
    
    // 23 February 2022
    // Teflon reflects ~97% of UV light so just make it 1 for simplicity.
    static const std::vector<G4double> TEFLON_REFLECTIVITY = {
        1., 1.
    };

    static const std::vector<G4double> TEFLON_TRANSMITTANCE = {
        0., 0.
    };
}
