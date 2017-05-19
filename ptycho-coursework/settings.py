#!/usr/bin/python3

from os.path import dirname, join
from numpy import pi


# Paths.
PROJ_DIR = dirname(__file__)
# PROJ_DIR = dirname(SRC_DIR)
DATA_DIR = join(PROJ_DIR, "data")


# Default paths.
DEFAULT_TARGET_PATH = join(DATA_DIR, "cameraman.tif")
DEFAULT_PHASE_PATH = join(DATA_DIR, "westconcordorthphoto.bmp")
DEFAULT_RESULT_PATH = join(DATA_DIR, "result.png")
DEFAULT_LOWRES_DIR = join(DATA_DIR, "lowres")
DEFAULT_LOWRES_FORMAT = "led-{id:03}.bmp"


# Optics constants.
WAVELEN = 0.63e-6
K = 2 * pi / WAVELEN
SAMPSIZE = 2.75e-6
QUALITY = 0.25
PXSIZE = SAMPSIZE * QUALITY
KLIM = pi / SAMPSIZE
NA = 0.08


# LED grid defaults
# 15x15 LEDs shape
LEDS_NUM = 15
# 4mm between LEDs
LEDS_GAP = 4
# 90mm between LEDs and sample plate.
LEDS_HEIGHT = 90
DEFAULT_LEDS_ATTRS = {
	'num': LEDS_NUM,
	'gap': LEDS_GAP,
	'height': LEDS_HEIGHT,
}
