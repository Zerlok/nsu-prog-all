#!/usr/bin/python3

from os.path import dirname, join
from numpy import pi


# Paths.
PROJ_DIR = dirname(__file__)
# PROJ_DIR = dirname(SRC_DIR)
DATA_DIR = join(PROJ_DIR, "data")


DEFAULT_IMG_SIZE = 256


# Default paths.
DEFAULT_TARGET_PATH = join(DATA_DIR, "cameraman{}.png".format(DEFAULT_IMG_SIZE))
DEFAULT_PHASE_PATH = join(DATA_DIR, "concord{}.png".format(DEFAULT_IMG_SIZE))
DEFAULT_LOWRES_FILE = join(DATA_DIR, "lowres.npy")
DEFAULT_LOWRES_FORMAT = "led-{id:03}.png"
DEFAULT_HIGHRES_FILE = join(DATA_DIR, "result.png")

# Formats.
DURATION_FORMAT = "Duration is: {:.3f} ms"


# Optics constants.
WAVELEN = 0.63e-6
K = 2 * pi / WAVELEN
SAMPSIZE = 2.75e-6
QUALITY = 0.25
# SAMPSIZE = 1.4783e-6
# QUALITY = 0.125
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
