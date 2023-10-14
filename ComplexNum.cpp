#include "ComplexNum.hpp"

ComplexNum::ComplexNum()
	:mRe(0), mIm(0){}

ComplexNum::ComplexNum(const double& a)
	:mRe(a), mIm(0){}

ComplexNum::ComplexNum(const double& a, const double& b)
	:mRe(a), mIm(b){}

void ComplexNum::setRe(double Re){
	mRe = Re;
}

void ComplexNum::setIm(double Im){
	mIm = Im;
}

double ComplexNum::getModulus() const{
	return sqrt(mRe*mRe + mIm*mIm);
}

double ComplexNum::getRe() const{ 
	return mRe;
}

double ComplexNum::getIm() const{
	return mIm;
}

std::ostream& operator<<(std::ostream& out, const ComplexNum& num){
	return out << num.mRe << " + " << num.mIm << "i" << std::endl;
}

ComplexNum operator+(const ComplexNum& lhs, const ComplexNum& rhs){
	return ComplexNum(lhs.mRe + rhs.mRe, lhs.mIm + rhs.mIm);
}

ComplexNum operator-(const ComplexNum& lhs, const ComplexNum& rhs){
	return ComplexNum(lhs.mRe - rhs.mRe, lhs.mIm - rhs.mIm);
}

ComplexNum operator*(const ComplexNum& num, const double& k){
	return ComplexNum(k * num.mRe, k * num.mIm);
}

bool operator< (const ComplexNum& lhs, const ComplexNum& rhs){
	return lhs.getModulus() < rhs.getModulus();
}
