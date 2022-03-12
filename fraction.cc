#include "fraction.hh"

#include <numeric>
#include <cmath>
#include <stdexcept>

// may this class benefit from other kinds of constructors?
// if implement this as ordered pairs and operations in a separate namespace...
// does providing a general support for numbered pairs make sense? fractions represent a position
//   on the number line, numbered pairs don't but rather a point in a plane. also a fraction may
//   be a part of an ordered pair
// design decision of only making possible for the numerator being negative was for saving a variable
// and simplify some logic (while perhaps obfuscating some), because a fraction represents a single
// point in the number line it doesn't make much sense to keep track of denominator and numerator
// signs separately. may even consider taking symbol apart after all.
// it there any scenario where I would want to keep a non-reduced fraction?
// rather than making numerator and denominator accesible separately, if need to print provide a
//   representation for ostream instead, doesn't make sense in other scenario since it's a position
//   on the number line
// check out for negative cases on modular arithmetic

Fraction::Fraction(int64_t const p_a = 0, int64_t const p_b = 1)
{
  if (p_b == 0)
  {
    throw std::runtime_error("math error: zero denominator");
  }

  m_a = ((p_a < 0 != p_b < 0)? -std::abs(p_a) : std::abs(p_a));
  m_b = std::abs(p_b);

  reduce();
}

Fraction Fraction::inverse() const
{
  return Fraction(m_b, m_a);
}

Fraction Fraction::abs() const
{
  return Fraction(std::abs(m_a), m_b);
}

// modifies member variables of the class so it should not be const at the end
// should I make a non-destructive version of this?
// should I reduce fractions each time they are modified? it can be done on constructor too!
// in the case of above, it might be worth to implement this in constructor instead.
void Fraction::reduce()
{
  const int64_t gcd = std::gcd(m_a, m_b);
  m_a /= gcd;
  m_b /= gcd;
}

Fraction Fraction::operator +(Fraction const& p_other) const
{
  return Fraction(m_a * p_other.m_b + p_other.m_a * m_b, m_b * p_other.m_b);
}

Fraction Fraction::operator +(int64_t const p_int) const
{
  return Fraction(m_a + p_int * m_b, m_b);
}

Fraction& Fraction::operator +=(Fraction const& p_other)
{
  m_a = m_a * p_other.m_b + p_other.m_a * m_b;
  m_b *= p_other.m_b;
  reduce();
  return *this;
}

Fraction& Fraction::operator +=(int64_t const p_int)
{
  m_a += p_int * m_b;
  reduce();
  return *this;
}

Fraction Fraction::operator -(Fraction const& p_other) const
{
  return Fraction(m_a * p_other.m_b - p_other.m_a * m_b, m_b * p_other.m_b);
}

Fraction Fraction::operator -(int64_t const p_int) const
{
  return Fraction(m_a - p_int * m_b, m_b);
}

Fraction& Fraction::operator -=(Fraction const& p_other)
{
  m_a = m_a * p_other.m_b + p_other.m_a * m_b;
  m_b *= p_other.m_b;
  reduce();
  return *this;
}

Fraction& Fraction::operator -=(int64_t const p_int)
{
  m_a -= p_int * m_b;
  return *this;
}

Fraction Fraction::operator *(Fraction const& p_other) const
{
  return Fraction(m_a * p_other.m_a, m_b * p_other.m_b);
}

Fraction Fraction::operator *(int64_t const p_int) const
{
  return Fraction(m_a * p_int, m_b);
}

Fraction& Fraction::operator *=(Fraction const& p_other)
{
  m_a *= p_other.m_a;
  m_b *= p_other.m_b;
  reduce();
  return *this;
}

Fraction& Fraction::operator *=(int64_t const p_int)
{
  m_a *= p_int;
  reduce();
  return *this;
}

Fraction Fraction::operator /(Fraction const& p_other) const
{
  return Fraction(m_a * p_other.m_b, p_other.m_a * m_b);
}

Fraction Fraction::operator /(int64_t const p_int) const
{
  return Fraction(m_a, p_int * m_b);
}

Fraction& Fraction::operator /=(Fraction const& p_other)
{
  if (p_other.m_a == 0)
  {
    throw std::runtime_error("math error: zero denominator");
  }
  m_a = std::abs(m_a) * ((m_a < 0 != p_other.m_a < 0)? -p_other.m_b : p_other.m_b);
  m_b *= std::abs(p_other.m_a);
  reduce();
  return *this;
}

Fraction& Fraction::operator /=(int64_t const p_int)
{
  if (p_int == 0)
  {
    throw std::runtime_error("math error: zero denominator");
  }
  m_a = (m_a < 0 != p_int < 0)? -std::abs(m_a) : std::abs(m_a);
  m_b *= std::abs(p_int);
  reduce();
  return *this;
}

// should we make denominator and numerator accessible after all? perhaps just keep the class as barebones as possible. this might even be considered as an ordered pair, however there is the current rule that only numerator can be negative
Fraction Fraction::operator %(Fraction const& p_other) const
{
  Fraction division_fraction((m_a * p_other.m_b) % (p_other.m_a * m_b), m_b * p_other.m_b);
  return Fraction((m_a * p_other.m_b) % (p_other.m_a * m_b), m_b * p_other.m_b);
}

Fraction Fraction::operator %(int64_t const p_int) const
{
  return Fraction(m_a % (p_int * m_b), m_b);
}

Fraction Fraction::operator %=(Fraction const& p_other)
{
  if (p_other.m_a == 0)
  {
    throw std::runtime_error("math error: zero denominator");
  }
m_a = (m_a * p_other.m_b) % (p_other.m_a * m_b);
  m_b *= p_other.m_b;
  reduce();
  return *this;
}

Fraction Fraction::operator %=(int64_t const p_int)
{
  if (p_int == 0)
  {
    throw std::runtime_error("math error: zero denominator");
  }
  m_a %= p_int * m_b;
  reduce();
  return *this;
}

bool Fraction::operator <(Fraction const& p_other) const
{
  return m_a * p_other.m_b < p_other.m_a * m_b;
}

bool Fraction::operator <(int64_t const p_int) const
{
  return m_a < p_int * m_b;
}

bool Fraction::operator <=(Fraction const& p_other) const
{
  return m_a * p_other.m_b <= p_other.m_a * m_b;
}

bool Fraction::operator <=(int64_t const p_int) const
{
  return m_a <= p_int * m_b;
}

bool Fraction::operator >(Fraction const& p_other) const
{
  return m_a * p_other.m_b > p_other.m_a * m_b;
}

bool Fraction::operator >(int64_t const p_int) const
{
  return m_a > p_int * m_b;
}

bool Fraction::operator >=(Fraction const& p_other) const
{
  return m_a * p_other.m_b >= p_other.m_a * m_b;
}

bool Fraction::operator >=(int64_t const p_int) const
{
  return m_a > p_int * m_b;
}

bool Fraction::operator ==(Fraction const& p_other) const
{
  return m_a * p_other.m_b == p_other.m_a * m_b;
}

bool Fraction::operator ==(int64_t const p_int) const
{
  return m_a % m_b == 0 && m_a / m_b == p_int;
}

bool Fraction::operator !=(Fraction const& p_other) const
{
  return m_a * p_other.m_b != p_other.m_a * m_b;
}

bool Fraction::operator !=(int64_t const p_int) const
{
  return m_a % m_b != 0 || m_a / m_b != p_int;
}
