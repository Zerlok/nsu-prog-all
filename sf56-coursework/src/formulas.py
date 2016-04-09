# -*- coding: utf-8 -*-
from re import sub as re_sub, compile as re_compile
from sympy import *
init_printing()

PY_INDEX_PTRN = re_compile(r'(\w+)(\d+)')
PY_DIV_PTRN = re_compile(r'[(]?([A-Za-z0-9_*( )+-]+)[)]?\/[(]?([A-Za-z0-9_*( )+-]+)[)]?')
LIBRE_INDEX_PTRN = r'\1_\2 '
LIBRE_DIV_PTRN = r'(\1) over (\2)'


def to_libremath(expr):
    s = re_sub(PY_INDEX_PTRN, LIBRE_INDEX_PTRN, str(expr))
    s = s.replace('varphi', '%varphi').replace('delta', '%delta').\
            replace('exp', ' e^').\
            replace('**', '^').\
            replace('(', '{').replace(')', '}').\
            replace('*', '').replace('/', ' over ').\
            replace('I', 'i')
    return s

    
def show(**kwargs):
    print "r12 =", kwargs.get('r12')
    print "r23 =", kwargs.get('r23')
    print "  R =", kwargs.get('r')    
    print "t12 =", kwargs.get('t12')
    print "t23 =", kwargs.get('t23')
    print "  T =", kwargs.get('t')


def show_libremath(**kwargs):
    print "r12 =", to_libremath(kwargs.get('r12'))
    print "r23 =", to_libremath(kwargs.get('r23'))
    print "  R =", to_libremath(kwargs.get('r'))
    print "t12 =", to_libremath(kwargs.get('t12'))
    print "t23 =", to_libremath(kwargs.get('t23'))
    print "  T =", to_libremath(kwargs.get('t'))


def set_formulas_version(version):
    return version['t'], version['r']


# Known arguments.
N1, N3, phi1, wavelen, height = symbols("N1 N3 phi1 wl h")
# Unknown arguments.
N2, phi2, phi3, r12, r23, t12, t23, delta, phase_delta = symbols("N2 phi2 phi3 r12 r23 t12 t23 delta phase_delta")

# Expressions.
cos_phi2 = cos(phi2)
cos_phi3 = cos(phi3)
cos_phi2_1 = sqrt(N2**2 - N1**2 * sin(phi1)**2) / N2
cos_phi3_1 = cos_phi2.copy().subs(N2, N3)
sub_cos = [(cos_phi3, cos_phi3_1), (cos_phi2, cos_phi2_1)]
phase_delta = (4*pi / wavelen) * height * N2 * cos_phi2


versions = (
    # formuled
    {
        'r12': r12,
        'r23': r23,
        't12': t12,
        't23': t23,
    },
    # default
    {
        'r12': (N2 * cos(phi1) - N1 * cos_phi2) / (N2 * cos(phi1) + N1 * cos_phi2),
        'r23': (N3 * cos_phi2 - N2 * cos_phi3) / (N3 * cos_phi2 + N2 * cos_phi3),
        't12': (2 * N1 * cos(phi1)) / (N1 * cos(phi1) + N2 * cos_phi2),
        't23': (2 * N2 * cos_phi2) / (N2 * cos_phi2 + N3 * cos_phi3),
    },
    {
        'r12': (N1**2*N2**2 - 2*N1*N2**3*cos(phi1)*cos_phi2 + N2**4*cos(phi1)**2 - N1**4*sin(phi1)**2)/(N1**4*sin(phi1)**2 - N1**2*N2**2 + N2**4*cos(phi1)**2),
        't12': 2*N1*cos(phi1) / (N1**2 - N2**2) * (N1*cos(phi1) - N2*cos_phi2),
        'r23': (N3 - N2) / (N3 + N2),
        't23': 2*N2 / (N2 + N3),
    },
    {
        'r12': (N1**2*N2**2 - 2*N1*N2**2*sqrt(N2**2 - N1**2*sin(phi1)**2)*cos(phi1) + N2**4*cos(phi1)**2 - N1**4*sin(phi1)**2)/(N1**4*sin(phi1)**2 - N1**2*N2**2 + N2**4*cos(phi1)**2),
        't12': 2*N1*cos(phi1) / (N1**2 - N2**2) * (N1*cos(phi1) - sqrt(N2**2 - N1**2*sin(phi1)**2)),
        'r23': (N3 - N2) / (N3 + N2),
        't23': 2*N2 / (N2 + N3),
    },
)

for v in versions:
    v['r'] = (v['r12'] + v['r23'] * exp(I * delta)) / (1 + v['r12'] * v['r23'] * exp(I * delta))
    v['t'] = (v['t12'] * t23 * exp(I * delta / 2)) / (1 + exp(I * delta) * (v['t12'] + 1) * (v['t23'] - 1))

print "%s versions of T and R created." % len(versions)

formuled = versions[0]
default = versions[1]
last = versions[-1]

T, R = set_formulas_version(default)
print "The default version of T and R was set."
