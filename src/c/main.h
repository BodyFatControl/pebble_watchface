#pragma once

#include "pebble.h"

static const GPathInfo MINUTE_HAND_POINTS = {
  4, (GPoint []) {
    { 0, 0 },
    { 6, -22 },
    { 0, -66 },
    { -6, -22 }
  }
};

static const GPathInfo HOUR_HAND_POINTS = {
  4, (GPoint []) {
    { 0, 0 },
    { 7, -19 },
    { 0, -41 },
    { -7, -19 }
  }
};


//static const GPathInfo MINUTE_HAND_POINTS = {
//  4, (GPoint []) {
//    { 0, 0 },
//    { 5, -21 },
//    { 0, -65 },
//    { -5, -21 }
//  }
//};
//
//static const GPathInfo HOUR_HAND_POINTS = {
//  4, (GPoint []) {
//    { 0, 0 },
//    { 6, -18 },
//    { 0, -40 },
//    { -6, -18 }
//  }
//};
