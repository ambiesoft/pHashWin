#include "phcomplex.h"

std::complex<double> polar_to_complex(const double r, const double theta) {
	std::complex<double> result;
	result.real(r*cos(theta));
	result.imag(r*sin(theta));
	return result;
}
std::complex<double> add_complex(const std::complex<double> a, const std::complex<double> b) {
	std::complex<double> result;
	result.real(a.real() + b.real());
	result.imag(a.imag() + b.imag());
	return result;
}
std::complex<double> sub_complex(const std::complex<double> a, const std::complex<double> b) {
	std::complex<double> result;
	result.real(a.real() - b.real());
	result.imag(a.imag() - b.imag());
	return result;
}
std::complex<double> mult_complex(const std::complex<double> a, const std::complex<double> b) {
	std::complex<double> result;
	result.real((a.real()*b.real()) - (a.imag()*b.imag()));
	result.imag((a.real()*b.imag()) + (a.imag()*b.real()));
	return result;
}

