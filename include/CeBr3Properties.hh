#pragma once

namespace Materials {
    static const G4String kCEBR3 = "cebr3";
    static const G4double CEBR3_DENSITY = 5.1 * g / cm3;
    static constexpr G4double BR_MASS_FRAC = 0.631108;
    static constexpr G4double CE_MASS_FRAC = 1 - BR_MASS_FRAC;


    static const G4double CEBR3_SCINT_RESLN_SCALE = 1;
    // Quarati et al (not encapsulated)
    static const G4double CEBR3_SCINT_YIELD = 60000 / MeV;
    static const G4double CEBR3_DECAY_TIME_CONSTANT = 20 * ns;

    // Quarati et al, 2.5mm thickness
    // energies of cebr3 emission spectrum
    const std::vector<G4double> CEBR3_SCINT_OPTICAL_ENERGIES = {
        2.58558e+00*eV, 2.60375e+00*eV, 2.62735e+00*eV, 2.65348e+00*eV, 2.68122e+00*eV, 2.71175e+00*eV, 2.74185e+00*eV, 2.77033e+00*eV,
        2.79940e+00*eV, 2.83029e+00*eV, 2.86188e+00*eV, 2.88540e+00*eV, 2.90805e+00*eV, 2.93235e+00*eV, 2.94140e+00*eV, 2.95443e+00*eV,
        2.96758e+00*eV, 2.98485e+00*eV, 2.99962e+00*eV, 3.01317e+00*eV, 3.03098e+00*eV, 3.04899e+00*eV, 3.06159e+00*eV, 3.07005e+00*eV,
        3.08139e+00*eV, 3.09426e+00*eV, 3.10724e+00*eV, 3.12032e+00*eV, 3.12911e+00*eV, 3.13942e+00*eV, 3.14683e+00*eV, 3.15726e+00*eV,
        3.16475e+00*eV, 3.17228e+00*eV, 3.17984e+00*eV, 3.19049e+00*eV, 3.20429e+00*eV, 3.21976e+00*eV, 3.23224e+00*eV, 3.24482e+00*eV,
        3.25274e+00*eV, 3.25910e+00*eV, 3.27189e+00*eV, 3.28155e+00*eV, 3.28802e+00*eV, 3.29941e+00*eV, 3.31417e+00*eV, 3.32574e+00*eV,
        3.33572e+00*eV, 3.34576e+00*eV, 3.35249e+00*eV, 3.36094e+00*eV, 3.36943e+00*eV, 3.37967e+00*eV, 3.38998e+00*eV, 3.40035e+00*eV,
        3.41079e+00*eV, 3.42129e+00*eV, 3.43185e+00*eV, 3.43893e+00*eV, 3.44782e+00*eV, 3.45676e+00*eV, 3.46574e+00*eV, 3.47477e+00*eV,
        3.48385e+00*eV, 3.49480e+00*eV, 3.50767e+00*eV, 3.52063e+00*eV, 3.53556e+00*eV, 3.55820e+00*eV, 3.57729e+00*eV, 3.59658e+00*eV,
        3.62001e+00*eV, 3.64375e+00*eV, 3.67588e+00*eV, 3.70036e+00*eV, 3.75876e+00*eV, 3.81466e+00*eV, 3.86776e+00*eV
    };

    // relative intensities of emission spectrum
    const std::vector<G4double> CEBR3_SCINT_OPTICAL_INTENSITIES = {
        3.95471e-04, 4.54059e-04, 4.54059e-04, 4.54059e-04, 4.54059e-04, 5.71236e-04, 6.88413e-04, 7.47001e-04,
        8.64178e-04, 9.81354e-04, 1.15712e-03, 1.39147e-03, 1.74300e-03, 2.09453e-03, 2.32889e-03, 2.79759e-03,
        3.26630e-03, 4.02795e-03, 4.84818e-03, 5.66842e-03, 7.13313e-03, 8.77360e-03, 1.00625e-02, 1.11757e-02,
        1.24647e-02, 1.40465e-02, 1.55113e-02, 1.68002e-02, 1.77376e-02, 1.86750e-02, 1.93781e-02, 2.01397e-02,
        2.06670e-02, 2.11357e-02, 2.15459e-02, 2.17802e-02, 2.20731e-02, 2.23661e-02, 2.27176e-02, 2.31277e-02,
        2.34207e-02, 2.35964e-02, 2.38894e-02, 2.40652e-02, 2.43581e-02, 2.50026e-02, 2.59400e-02, 2.67602e-02,
        2.74633e-02, 2.78734e-02, 2.81663e-02, 2.83421e-02, 2.82835e-02, 2.81663e-02, 2.76390e-02, 2.67016e-02,
        2.54127e-02, 2.40066e-02, 2.18974e-02, 2.03155e-02, 1.83235e-02, 1.63315e-02, 1.43981e-02, 1.25233e-02,
        1.08242e-02, 9.06654e-03, 7.19172e-03, 5.66842e-03, 4.32089e-03, 2.97336e-03, 1.86018e-03, 1.15712e-03,
        6.88413e-04, 3.36883e-04, 1.61118e-04, 4.39412e-05, 4.39412e-05, 4.39412e-05, 4.39412e-05
    };


    // 2022 February 04: refractive index experimentially is about 2.09 for the emisison range, and relatively constant.
    // update to reflect that here.
    const std::vector<G4double> CEBR3_REFR_IDX_ENERGIES = {0.1*eV, 5*eV};
    const std::vector<G4double> CEBR3_REFR_IDXS = { 2.09, 2.09 };

    const std::vector<G4double> CEBR3_ABS_LEN_ENERGIES = {0.1*eV, 5*eV};

    // Typical absorption length for an inorganic scintillator
    const std::vector<G4double> CEBR3_ABS_LEN(CEBR3_ABS_LEN_ENERGIES.size(), 20. * cm);
}
