#ifndef MATHEXTENSIONS_H
#define MATHEXTENSIONS_H

#include <cmath>

namespace math {
    ////////////////////////////////////////////////////////////////////////////////
    // File: power_series_Si.c                                                    //
    // Routine(s):                                                                //
    //    xPower_Series_Si                                                        //
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    // long double xPower_Series_Si( long double x )                              //
    //                                                                            //
    //  Description:                                                              //
    //     The sin integral, Si(x), is the integral with integrand                //
    //                             sin(t) / t                                     //
    //     where the integral extends from 0 to x.                                //
    //     The power series representation for Si(x) is                           //
    //               x Sum (-x^2)^j / [(2j+1) (2j+1)!] where the sum extends      //
    //     over j = 0, ,,,.                                                       //
    //                                                                            //
    //  Arguments:                                                                //
    //     long double  x                                                         //
    //                The argument of the sin integral Si().                      //
    //                                                                            //
    //  Return Value:                                                             //
    //     The value of the sin integral Si evaluated at x.                       //
    //                                                                            //
    //  Example:                                                                  //
    //     long double y, x;                                                      //
    //                                                                            //
    //     ( code to initialize x )                                               //
    //                                                                            //
    //     y = xPower_Series_Si( x );                                             //
    ////////////////////////////////////////////////////////////////////////////////

    long double Si( long double x );
}

#endif // MATHEXTENSIONS_H
