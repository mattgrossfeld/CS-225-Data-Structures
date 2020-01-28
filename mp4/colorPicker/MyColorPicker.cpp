#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
MyColorPicker::MyColorPicker(double increment)
  : saturation(0), increment(increment) { }

HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  HSLAPixel pixel(180, saturation, 0.5);
  saturation += increment;
  if (saturation >= 1) { saturation -= 1; }
  if (saturation < 0) { saturation += 1; }
  return pixel;
}
