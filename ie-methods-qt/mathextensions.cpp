#include "mathextensions.h"

long double math::Si( long double x )
{
   long double sum;
   long double xx = - x * x;
   int n = (int) (3.42 * xx + 7.46 * fabsl(x) + 6.95);
   int k = n + n;

       // If the argument is sufficiently small use the approximation //
                         // Si(x) = x exp(-x^2/18) //

   if ( fabsl(x) <= 0.0003L ) return x * expl(xx / 18.0L);

        // Otherwise evaluate the power series expansion for Si(x). //

   sum = xx / ( (k + 1) * (k + 1) * k) + 1.0L / (k - 1);
   for (k--; k >= 3; k -=2) {
      sum *= xx / ( k * (k - 1) );
      sum += 1.0L / (k - 2);
   }
   return x * sum;
}
