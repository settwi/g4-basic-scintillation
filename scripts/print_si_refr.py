import numpy as np
import astropy.units as u
import astropy.constants as con

fn = 'silicon_refr_idx_info.txt'
wav, n, k = np.loadtxt(fn, unpack=True)

energy = con.h * con.c / (wav << u.micron)
energy = energy.to_value(u.eV)

ordering = np.argsort(energy)

for (quant, unit) in zip((energy, n, k), ('eV', '1', '1')):
    for i, idx in enumerate(ordering):
        print(f'{quant[idx]:.2f}*{unit}', end=', ')
        if (i + 1) % 8 == 0:
            print()
    print()
    print()
