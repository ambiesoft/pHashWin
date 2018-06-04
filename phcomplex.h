#include <stdlib.h>
#include <math.h>
#include <complex>
#ifndef _PH_COMPLEX_H
#define _PH_COMPLEX_H

//typedef struct phcomplex {
//     double re;
//     double im;
//} Complexd;

std::complex<double> polar_to_complex(const double r, const double theta);

std::complex<double> add_complex(const std::complex<double> a, const std::complex<double> b);

std::complex<double> sub_complex(const std::complex<double> a, const std::complex<double> b);

std::complex<double> mult_complex(const std::complex<double> a, const std::complex<double> b);

#endif
