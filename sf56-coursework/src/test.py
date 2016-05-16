# -*-coding: utf-8-*-
from plotter import Chart, show_charts
from sf56spectrum import show_spectrums
from optics import build_cri_index_chart, build_absorption_chart_from_sf_files, build_theoretical_cri_chart


# n1, n2, n3, h, wl, a = symbols("n1, n2, n3, h, wl, a")
# x, d, t, r = symbols("x, d, t, r")
# r12tm = (n2**2*cos(a) - n1*sqrt(n2**2 - n1**2*sin(a)**2)) / (n2**2*cos(a) + n1*sqrt(n2**2 - n1**2*sin(a)**2))
# r12te = (n1*cos(a) - sqrt(n2**2 - n1**2*sin(a)**2)) / (n1*cos(a) + sqrt(n2**2 - n1**2*sin(a)**2))
# r23tm = (n3**2*sqrt(n2**2 - n1**2*sin(a)**2) - n2**2*sqrt(n3**2 - n1**2*sin(a)**2)) / (n3**2*sqrt(n2**2 - n1**2*sin(a)**2) + n2**2*sqrt(n3**2 - n1**2*sin(a)**2))
# r23te = (sqrt(n2**2 - n1**2*sin(a)**2) - sqrt(n3**2 - n1**2*sin(a)**2)) / (sqrt(n2**2 - n1**2*sin(a)**2) + sqrt(n3**2 - n1**2*sin(a)**2))


ab_corning = build_absorption_chart_from_sf_files('data/ITO_T1.sf', 'data/ITO_R1_09deg_real.sf')
ab_corning.name = u"ITO Corning 1737"
cri_corning = build_cri_index_chart(ab_corning, 220*10**-9)

ab_sbras1 = build_absorption_chart_from_sf_files('data/ITO_tr_69om.sf', 'data/ITO_ref_69om_09deg_real.sf')
ab_sbras1.name = u"ITO СО РАН (1)"
cri_sbras1 = build_cri_index_chart(ab_sbras1, 134*10**-9)

ab_sbras2 = build_absorption_chart_from_sf_files('data/ITO_tr_19om.sf', 'data/ITO_ref_19om_09deg_real.sf')
ab_sbras2.name = u"ITO СО РАН (2)"
cri_sbras2 = build_cri_index_chart(ab_sbras2, 120*10**-9)


theoretical_cri = build_theoretical_cri_chart(ab_corning.axis_x[100:])
# theoretical_ab = build_absorption_chart_from_cri(theoretical_cri, 220*10**-9)
# title = u"Спектры поглощения плёнок"
# show_spectrums(ab_corning, ab_sbras1, ab_sbras2, theoretical_ab, title=title)


title = u"Комплексный показатель преломления трёх плёнок"
show_charts(
		cri_corning, cri_sbras1, cri_sbras2, theoretical_cri,
		title = title,
		x_name=u"Длина волны", x_units="m",
		y_name = u"Косплексный показатель преломления",
)
