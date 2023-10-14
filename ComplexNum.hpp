#ifndef COMPLEXNUM_H
#define COMPLEXNUM_H

#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

class ComplexNum{
  private:
	  double mRe = 0;
	  double mIm = 0;

  public:
	  ComplexNum();

	  ComplexNum(const double& a);

	  ComplexNum(const double& a, const double& b);

	  void setRe(double Re);

	  void setIm(double Im);

	  double getModulus() const;

	  double getRe() const;

	  double getIm() const;

	  friend std::ostream& operator<<(std::ostream& out, const ComplexNum& num);

	  friend ComplexNum operator+(const ComplexNum& lhs, const ComplexNum& rhs);

	  friend ComplexNum operator-(const ComplexNum& lhs, const ComplexNum& rhs);

	  friend ComplexNum operator*(const ComplexNum& num, const double& k);

	  friend bool operator< (const ComplexNum& lhs, const ComplexNum& rhs);
};

#endif
