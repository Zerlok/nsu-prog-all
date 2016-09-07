# -*-coding: utf-8-*-
from plotter import show_charts
from sf56spectrum import show_spectrums, read_sf
from optics import build_absorption_chart, build_cri_index_chart


sbras0_t = read_sf('data/ITO_T1.sf', u"T")
sbras0_r9 = read_sf('data/ITO_R1_09deg.sf', u"R(9)")
sbras0_r45 = read_sf('data/ITO_R1_45deg.sf', u"R(45)")
sbras0_r9_real = read_sf('data/ITO_R1_09deg_real.sf', u"R(9)")
sbras0_r45_real = read_sf('data/ITO_R1_45deg_real.sf', u"R(45)")
sbras0_a = build_absorption_chart(sbras0_t, sbras0_r9_real)

sbras1_t = read_sf('data/ITO_tr_69om.sf', u"T")
sbras1_r9 = read_sf('data/ITO_ref_69om_09deg.sf', u"R(9)")
sbras1_r45 = read_sf('data/ITO_ref_69om_45deg.sf', u"R(45)")
sbras1_r9_real = read_sf('data/ITO_ref_69om_09deg_real.sf', u"R(9)")
sbras1_r45_real = read_sf('data/ITO_ref_69om_45deg_real.sf', u"R(45)")
sbras1_a = build_absorption_chart(sbras1_t, sbras1_r9_real)

sbras2_t = read_sf('data/ITO_tr_19om.sf', u"T")
sbras2_r9 = read_sf('data/ITO_ref_19om_09deg.sf', u"R(9)")
sbras2_r45 = read_sf('data/ITO_ref_19om_45deg.sf', u"R(45)")
sbras2_r9_real = read_sf('data/ITO_ref_19om_09deg_real.sf', u"R(9)")
sbras2_r45_real = read_sf('data/ITO_ref_19om_45deg_real.sf', u"R(45)")
sbras2_a = build_absorption_chart(sbras2_t, sbras2_r9_real)

# show_spectrums(sbras0_t, sbras0_r9_real, sbras0_r45_real, sbras0_a)
# show_spectrums(sbras1_t, sbras1_r9_real, sbras1_r45_real, sbras1_a)
# show_spectrums(sbras2_t, sbras2_r9_real, sbras2_r45_real, sbras2_a)

# sbras0_a.name = u"A0"
# sbras1_a.name = u"A1"
# sbras2_a.name = u"A2"
# show_spectrums(sbras0_a, sbras1_a, sbras2_a)

cri0 = build_cri_index_chart(sbras0_a, 210*10**-9)
cri1 = build_cri_index_chart(sbras1_a, 135*10**-9)
cri2 = build_cri_index_chart(sbras2_a, 125*10**-9)
cri0.name = u"m0"
cri1.name = u"m1"
cri2.name = u"m2"
show_charts(
		cri0, cri1, cri2,
		x_name = u"\u03BB",
		x_units = u"м",
		y_name = u"m(\u03BB)",
		y_range=(0, 0.5)
)
