#include <iostream>
#include "fraction.hh"
int main(int argc, char* argv[])
{
  std::cout << "hello world!" << std::endl;

  Fraction a_fraction(20, 12);
  Fraction b_fraction(8, 12);
  Fraction ab_fraction = a_fraction % b_fraction;
std::cout << ab_fraction.m_a << ", " << ab_fraction.m_b << std::endl;
  return 0;
}
