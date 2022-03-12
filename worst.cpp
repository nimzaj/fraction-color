#include <iostream>
#include <algorithm>

struct Fraction // may actually use a template in fraction to adapt to circunstances
{
  int32_t numerator;
  int32_t denominator;
};

void getHSB(uint8_t const p_red, uint8_t const p_green, uint8_t const p_blue)
{
  // check whether r, g, b are within the range
  // may want to change variable names, as they don't exactly mirror those used in equations

  uint8_t max = std::max(p_red, std::max(p_blue, p_green));
  uint8_t min = std::min(p_red, std::min(p_blue, p_green));
  uint8_t delta = max - min;

  std::cout << +max << " " << +min << " " << +delta << std::endl;

  // loss of precision as this is not a fraction, store in fraction
  // for future reference and accuracy
  uint8_t saturation = (max == 0)? 0 : delta;
  uint8_t brightness = max; // fraction for accuracy
  int32_t hue = 0; // this is a transitional hue, it should have delta as den at the end;

  if (delta > 0)
  {
    if (max == p_red)
    {
      hue = 60 * (p_green - p_blue);
    }
    else
    {
      if (max == p_green)
      {
        hue = 60 * (p_blue - p_red + delta * 2);
      }
      else
      {
        hue = 60 * (p_red - p_green + delta * 4);
      }
    }

    if (hue < 60 * delta)
    {
      hue = (hue + 360 * delta) % 91800; // is this the only place where modulo should apply?
      // if so just use it here to save operations
      // might replace the word delta for chroma
      // the only possible case where we can deal with full 91800 is when rgb is 255, 0, 0
      // negative cases end up with a less than 91800 due compensation, delta is greater than
      // 0 here thus 0, 255, 0 and 0, 0, 255 are 510 * 60 and 1020 * 60 respectively thus don't enter
      // enter this course since they are at least 2 * delta * 60 each.
    }
  }

  std::cout << "rgb(" << +p_red << ", " << +p_green << ", " << +p_blue << ") = hsb(" << hue << "/" << +delta << ", " << +saturation << "/" << +max << ", " << +brightness << "/" << 255 << ")" << std::endl;
}

int main()
{
  getHSB(255, 0, 255);
  return 0;
}
