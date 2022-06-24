#pragma once

#include "G4Types.hh"

namespace Materials {
    static const G4String kBE = "beryllium";
    static const G4double BE_DENSITY = 1.85 * g / cm3;
    static const G4int BE_NUM_COMPONENTS = 1;
    const std::vector<G4double> BE_REFR_IDX_ENERGIES = {
        2.00000e-02*eV, 2.05626e-02*eV, 2.11411e-02*eV, 2.17360e-02*eV, 2.23475e-02*eV, 2.29762e-02*eV, 2.36228e-02*eV, 2.42873e-02*eV,
        2.49706e-02*eV, 2.56733e-02*eV, 2.63953e-02*eV, 2.71383e-02*eV, 2.79017e-02*eV, 2.86868e-02*eV, 2.94934e-02*eV, 3.03236e-02*eV,
        3.11769e-02*eV, 3.20538e-02*eV, 3.29552e-02*eV, 3.38829e-02*eV, 3.48358e-02*eV, 3.58160e-02*eV, 3.68233e-02*eV, 3.78601e-02*eV,
        3.89251e-02*eV, 4.00207e-02*eV, 4.11457e-02*eV, 4.23039e-02*eV, 4.34941e-02*eV, 4.47177e-02*eV, 4.59763e-02*eV, 4.72699e-02*eV,
        4.85984e-02*eV, 4.99674e-02*eV, 5.13732e-02*eV, 5.28177e-02*eV, 5.43028e-02*eV, 5.58311e-02*eV, 5.74027e-02*eV, 5.90176e-02*eV,
        6.06784e-02*eV, 6.23851e-02*eV, 6.41408e-02*eV, 6.59455e-02*eV, 6.77991e-02*eV, 6.97089e-02*eV, 7.16672e-02*eV, 7.36861e-02*eV,
        7.57572e-02*eV, 7.78893e-02*eV, 8.00828e-02*eV, 8.23323e-02*eV, 8.46482e-02*eV, 8.70309e-02*eV, 8.94805e-02*eV, 9.19969e-02*eV,
        9.45867e-02*eV, 9.72501e-02*eV, 9.99792e-02*eV, 1.02798e-01*eV, 1.05689e-01*eV, 1.08663e-01*eV, 1.11718e-01*eV, 1.14864e-01*eV,
        1.18091e-01*eV, 1.21410e-01*eV, 1.24832e-01*eV, 1.28344e-01*eV, 1.31956e-01*eV, 1.35668e-01*eV, 1.39485e-01*eV, 1.43409e-01*eV,
        1.47444e-01*eV, 1.51592e-01*eV, 1.55857e-01*eV, 1.60242e-01*eV, 1.64750e-01*eV, 1.69387e-01*eV, 1.74152e-01*eV, 1.79051e-01*eV,
        1.84089e-01*eV, 1.89269e-01*eV, 1.94592e-01*eV, 2.00068e-01*eV, 2.05698e-01*eV, 2.11483e-01*eV, 2.17432e-01*eV, 2.23552e-01*eV,
        2.29839e-01*eV, 2.36304e-01*eV, 2.42954e-01*eV, 2.49792e-01*eV, 2.56818e-01*eV, 2.64043e-01*eV, 2.71472e-01*eV, 2.79112e-01*eV,
        2.86961e-01*eV, 2.95039e-01*eV, 3.03340e-01*eV, 3.11871e-01*eV, 3.20646e-01*eV, 3.29666e-01*eV, 3.38940e-01*eV, 3.48476e-01*eV,
        3.58284e-01*eV, 3.68365e-01*eV, 3.78728e-01*eV, 3.89385e-01*eV, 4.00336e-01*eV, 4.11593e-01*eV, 4.23183e-01*eV, 4.35078e-01*eV,
        4.47322e-01*eV, 4.59916e-01*eV, 4.72843e-01*eV, 4.86155e-01*eV, 4.99835e-01*eV, 5.13903e-01*eV, 5.28357e-01*eV, 5.43218e-01*eV,
        5.58512e-01*eV, 5.74214e-01*eV, 5.90373e-01*eV, 6.06992e-01*eV, 6.24071e-01*eV, 6.41607e-01*eV, 6.59666e-01*eV, 6.78213e-01*eV,
        6.97324e-01*eV, 7.16920e-01*eV, 7.37080e-01*eV, 7.57850e-01*eV, 7.79138e-01*eV, 8.01087e-01*eV, 8.23596e-01*eV, 8.46771e-01*eV,
        8.70614e-01*eV, 8.95128e-01*eV, 9.20310e-01*eV, 9.46155e-01*eV, 9.72806e-01*eV, 1.00020e+00*eV, 1.02832e+00*eV, 1.05725e+00*eV,
        1.08701e+00*eV, 1.11758e+00*eV, 1.14896e+00*eV, 1.18136e+00*eV, 1.21458e+00*eV, 1.24875e+00*eV, 1.28388e+00*eV, 1.31999e+00*eV,
        1.35714e+00*eV, 1.39532e+00*eV, 1.43457e+00*eV, 1.47493e+00*eV, 1.51642e+00*eV, 1.55910e+00*eV, 1.60296e+00*eV, 1.64805e+00*eV,
        1.69442e+00*eV, 1.74208e+00*eV, 1.79111e+00*eV, 1.84150e+00*eV, 1.89332e+00*eV, 1.94659e+00*eV, 2.00136e+00*eV, 2.05766e+00*eV,
        2.11555e+00*eV, 2.17505e+00*eV, 2.23625e+00*eV, 2.29915e+00*eV, 2.36385e+00*eV, 2.43035e+00*eV, 2.49872e+00*eV, 2.56903e+00*eV,
        2.64133e+00*eV, 2.71562e+00*eV, 2.79206e+00*eV, 2.87060e+00*eV, 2.95137e+00*eV, 3.03437e+00*eV, 3.11973e+00*eV, 3.20754e+00*eV,
        3.29780e+00*eV, 3.39051e+00*eV, 3.48593e+00*eV, 3.58398e+00*eV, 3.68485e+00*eV, 3.78855e+00*eV, 3.89508e+00*eV, 4.00466e+00*eV,
        4.11743e+00*eV, 4.23328e+00*eV, 4.35231e+00*eV, 4.47483e+00*eV, 4.60070e+00*eV, 4.73005e+00*eV, 4.86327e+00*eV, 4.99997e+00*eV,

    };

    const std::vector<G4double> BE_REFR_IDX_REAL = {
        9.40750e+01, 9.15210e+01, 8.89980e+01, 8.65080e+01, 8.40500e+01, 8.16260e+01, 7.92350e+01, 7.68790e+01,
        7.45580e+01, 7.22730e+01, 7.00250e+01, 6.78140e+01, 6.56410e+01, 6.35060e+01, 6.14110e+01, 5.93560e+01,
        5.73420e+01, 5.53690e+01, 5.34370e+01, 5.15480e+01, 4.97020e+01, 4.78990e+01, 4.61390e+01, 4.44230e+01,
        4.27510e+01, 4.11230e+01, 3.95400e+01, 3.80000e+01, 3.65050e+01, 3.50540e+01, 3.36480e+01, 3.22840e+01,
        3.09650e+01, 2.96880e+01, 2.84540e+01, 2.72610e+01, 2.61110e+01, 2.50010e+01, 2.39320e+01, 2.29020e+01,
        2.19100e+01, 2.09570e+01, 2.00410e+01, 1.91610e+01, 1.83160e+01, 1.75060e+01, 1.67300e+01, 1.59860e+01,
        1.52740e+01, 1.45920e+01, 1.39400e+01, 1.33170e+01, 1.27220e+01, 1.21540e+01, 1.16110e+01, 1.10940e+01,
        1.06010e+01, 1.01310e+01, 9.68310e+00, 9.25680e+00, 8.85100e+00, 8.46510e+00, 8.09800e+00, 7.74920e+00,
        7.41770e+00, 7.10290e+00, 6.80410e+00, 6.52050e+00, 6.25150e+00, 5.99640e+00, 5.75460e+00, 5.52560e+00,
        5.30870e+00, 5.10340e+00, 4.90910e+00, 4.72540e+00, 4.55170e+00, 4.38770e+00, 4.23280e+00, 4.08660e+00,
        3.94870e+00, 3.81870e+00, 3.69630e+00, 3.58110e+00, 3.47280e+00, 3.37100e+00, 3.27540e+00, 3.18580e+00,
        3.10190e+00, 3.02340e+00, 2.95010e+00, 2.88170e+00, 2.81810e+00, 2.75890e+00, 2.70410e+00, 2.65350e+00,
        2.60680e+00, 2.56380e+00, 2.52460e+00, 2.48880e+00, 2.45640e+00, 2.42730e+00, 2.40130e+00, 2.37830e+00,
        2.35820e+00, 2.34090e+00, 2.32640e+00, 2.31450e+00, 2.30520e+00, 2.29840e+00, 2.29400e+00, 2.29210e+00,
        2.29240e+00, 2.29510e+00, 2.30000e+00, 2.30700e+00, 2.31630e+00, 2.32760e+00, 2.34100e+00, 2.35650e+00,
        2.37400e+00, 2.39340e+00, 2.41470e+00, 2.43790e+00, 2.46290e+00, 2.48960e+00, 2.51800e+00, 2.54810e+00,
        2.57960e+00, 2.61250e+00, 2.64660e+00, 2.68200e+00, 2.71830e+00, 2.75550e+00, 2.79330e+00, 2.83160e+00,
        2.87020e+00, 2.90890e+00, 2.94740e+00, 2.98560e+00, 3.02330e+00, 3.06020e+00, 3.09610e+00, 3.13090e+00,
        3.16440e+00, 3.19640e+00, 3.22680e+00, 3.25540e+00, 3.28220e+00, 3.30700e+00, 3.32980e+00, 3.35050e+00,
        3.36900e+00, 3.38530e+00, 3.39940e+00, 3.41130e+00, 3.42090e+00, 3.42820e+00, 3.43320e+00, 3.43600e+00,
        3.43660e+00, 3.43480e+00, 3.43080e+00, 3.42460e+00, 3.41610e+00, 3.40540e+00, 3.39240e+00, 3.37720e+00,
        3.35970e+00, 3.34000e+00, 3.31800e+00, 3.29370e+00, 3.26700e+00, 3.23810e+00, 3.20680e+00, 3.17310e+00,
        3.13700e+00, 3.09840e+00, 3.05740e+00, 3.01380e+00, 2.96770e+00, 2.91900e+00, 2.86780e+00, 2.81390e+00,
        2.75740e+00, 2.69830e+00, 2.63660e+00, 2.57230e+00, 2.50550e+00, 2.43620e+00, 2.36460e+00, 2.29070e+00,
        2.21470e+00, 2.13680e+00, 2.05730e+00, 1.97630e+00, 1.89420e+00, 1.81120e+00, 1.72780e+00, 1.64440e+00,

    };

    const std::vector<G4double> BE_REFR_IDX_IMAG = {
        1.60420e+02, 1.58200e+02, 1.55990e+02, 1.53780e+02, 1.51590e+02, 1.49390e+02, 1.47210e+02, 1.45030e+02,
        1.42850e+02, 1.40680e+02, 1.38510e+02, 1.36350e+02, 1.34190e+02, 1.32040e+02, 1.29890e+02, 1.27750e+02,
        1.25610e+02, 1.23480e+02, 1.21360e+02, 1.19240e+02, 1.17130e+02, 1.15030e+02, 1.12940e+02, 1.10860e+02,
        1.08790e+02, 1.06730e+02, 1.04680e+02, 1.02650e+02, 1.00630e+02, 9.86220e+01, 9.66310e+01, 9.46580e+01,
        9.27010e+01, 9.07630e+01, 8.88440e+01, 8.69440e+01, 8.50660e+01, 8.32080e+01, 8.13730e+01, 7.95610e+01,
        7.77720e+01, 7.60070e+01, 7.42670e+01, 7.25520e+01, 7.08630e+01, 6.91990e+01, 6.75620e+01, 6.59520e+01,
        6.43680e+01, 6.28120e+01, 6.12830e+01, 5.97820e+01, 5.83080e+01, 5.68620e+01, 5.54440e+01, 5.40530e+01,
        5.26900e+01, 5.13550e+01, 5.00460e+01, 4.87650e+01, 4.75110e+01, 4.62830e+01, 4.50830e+01, 4.39080e+01,
        4.27590e+01, 4.16360e+01, 4.05390e+01, 3.94660e+01, 3.84180e+01, 3.73940e+01, 3.63950e+01, 3.54180e+01,
        3.44650e+01, 3.35350e+01, 3.26270e+01, 3.17400e+01, 3.08760e+01, 3.00320e+01, 2.92090e+01, 2.84060e+01,
        2.76240e+01, 2.68600e+01, 2.61160e+01, 2.53900e+01, 2.46820e+01, 2.39920e+01, 2.33200e+01, 2.26650e+01,
        2.20260e+01, 2.14030e+01, 2.07960e+01, 2.02050e+01, 1.96290e+01, 1.90680e+01, 1.85210e+01, 1.79880e+01,
        1.74680e+01, 1.69630e+01, 1.64700e+01, 1.59900e+01, 1.55220e+01, 1.50670e+01, 1.46230e+01, 1.41910e+01,
        1.37700e+01, 1.33610e+01, 1.29620e+01, 1.25730e+01, 1.21950e+01, 1.18270e+01, 1.14690e+01, 1.11200e+01,
        1.07810e+01, 1.04510e+01, 1.01290e+01, 9.81720e+00, 9.51360e+00, 9.21860e+00, 8.93200e+00, 8.65370e+00,
        8.38350e+00, 8.12130e+00, 7.86710e+00, 7.62080e+00, 7.38230e+00, 7.15150e+00, 6.92830e+00, 6.71280e+00,
        6.50490e+00, 6.30450e+00, 6.11160e+00, 5.92620e+00, 5.74820e+00, 5.57770e+00, 5.41450e+00, 5.25860e+00,
        5.10990e+00, 4.96830e+00, 4.83380e+00, 4.70620e+00, 4.58540e+00, 4.47120e+00, 4.36350e+00, 4.26200e+00,
        4.16660e+00, 4.07700e+00, 3.99310e+00, 3.91450e+00, 3.84120e+00, 3.77280e+00, 3.70910e+00, 3.64990e+00,
        3.59510e+00, 3.54420e+00, 3.49730e+00, 3.45400e+00, 3.41420e+00, 3.37770e+00, 3.34430e+00, 3.31390e+00,
        3.28630e+00, 3.26140e+00, 3.23900e+00, 3.21910e+00, 3.20130e+00, 3.18580e+00, 3.17230e+00, 3.16060e+00,
        3.15080e+00, 3.14270e+00, 3.13620e+00, 3.13120e+00, 3.12750e+00, 3.12500e+00, 3.12380e+00, 3.12350e+00,
        3.12410e+00, 3.12550e+00, 3.12750e+00, 3.13000e+00, 3.13280e+00, 3.13580e+00, 3.13880e+00, 3.14150e+00,
        3.14390e+00, 3.14560e+00, 3.14660e+00, 3.14640e+00, 3.14500e+00, 3.14200e+00, 3.13720e+00, 3.13020e+00,
        3.12100e+00, 3.10910e+00, 3.09440e+00, 3.07660e+00, 3.05540e+00, 3.03080e+00, 3.00240e+00, 2.97020e+00,

    };

}
