from sf56spectrum import *
from plotter import *
from optics import *


tr = read_sf('data/ITO_T1.sf')
ref = read_sf('data/ITO_R1_09deg_real.sf')
ref45 = read_sf('data/ITO_R1_45deg_real.sf')
summ = tr + ref

tr.name = "Transmit"
ref.name = "Reflect 9 degrees"
ref45.name = "Reflect 45 degrees"
summ.name = "Sum"

show_spectrums(tr, ref, summ, title="ITO Corning 1737")
# show_spectrums(ref, ref45, title="ITO Corning 1737")