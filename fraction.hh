#ifndef __FRACTION_HH_
#define __FRACTION_HH_

#include <iostream>

class Fraction
{
public:

  int64_t m_a;
  uint64_t m_b;

// public:

  Fraction(int64_t const p_a, int64_t const p_b);

  Fraction inverse() const;
  Fraction abs() const;

  void reduce();

  void operator =(int64_t const p_int);

  Fraction operator +(Fraction const& p_other) const;
  Fraction operator +(int64_t const p_int) const;

  Fraction& operator +=(Fraction const& p_other);
  Fraction& operator +=(int64_t const p_int);

  Fraction operator -(Fraction const& p_other) const;
  Fraction operator -(int64_t const p_int) const;

  Fraction& operator -=(Fraction const& p_other);
  Fraction& operator -=(int64_t const p_int);

  Fraction operator *(Fraction const& p_other) const;
  Fraction operator *(int64_t const p_int) const;

  Fraction& operator *=(Fraction const& p_other);
  Fraction& operator *=(int64_t const p_int);

  Fraction operator /(Fraction const& p_other) const;
  Fraction operator /(int64_t const p_int) const;

  Fraction& operator /=(Fraction const& p_other);
  Fraction& operator /=(int64_t const p_int);

  Fraction operator %(Fraction const& p_other) const;
  Fraction operator %(int64_t const p_int) const;

  Fraction operator %=(Fraction const& p_other);
  Fraction operator %=(int64_t const p_int);

  bool operator <(Fraction const& p_other) const;
  bool operator <(int64_t const p_int) const;

  bool operator >(Fraction const& p_other) const;
  bool operator >(int64_t const p_int) const;

  bool operator <=(Fraction const& p_other) const;
  bool operator <=(int64_t const p_int) const;

  bool operator >=(Fraction const& p_other) const;
  bool operator >=(int64_t const p_int) const;

  bool operator ==(Fraction const& p_other) const;
  bool operator ==(int64_t const p_int) const;

  bool operator !=(Fraction const& p_other) const;
  bool operator !=(int64_t const p_int) const;
};

#endif /* __FRACTION_HH_ */
