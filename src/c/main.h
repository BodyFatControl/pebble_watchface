#pragma once

#include "pebble.h"

#define NUM_CLOCK_TICKS 11

#define PBL_DISPLAY_WIDTH_HALF PBL_DISPLAY_WIDTH / 2
#define PBL_DISPLAY_HEIGHT_HALF PBL_DISPLAY_HEIGHT / 2

static const GPathInfo MINUTE_HAND_POINTS = {
  3, (GPoint []) {
    { -8, 20 },
    { 8, 20 },
    { 0, -80 }
  }
};

static const GPathInfo HOUR_HAND_POINTS = {
  3, (GPoint []){
    {-6, 20},
    {6, 20},
    {0, -60}
  }
};
