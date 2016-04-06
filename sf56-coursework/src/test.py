from sf56spectrum import *
from plotter import *
from optics import *


tr = read_sf('data/ITO_tr_69om.sf')
ref = read_sf('data/ITO_ref_69om_09deg_real.sf')
ref45 = read_sf('data/ITO_ref_69om_45deg_real.sf')
summ = tr + ref

tr.name = "Transmit"
ref.name = "Reflect 9 degrees"
ref45.name = "Reflect 45 degrees"
summ.name = "Sum"

show_spectrums(tr, ref, summ, title="ITO 69 Om")