//[einirv] - commented out (no malloc.h in OS X)
//#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <math.h>
#include "cquadpak.h"
#include "dqdefs.h"

#define P   0.9

/* DQAWF - Approximation to Fourier integral. (From QUADPACK)
 *
 *
 * PARAMETERS:
 *
 *	f() - double precision function to be integrated.
 *
 *	a - lower limit of integration.
 *
 *	omega - parameter in weight function.
 *
 *	sincos - indicates which weight function to use:
 *		sincos = COSINE (= 1) --- use cos(omega*x)
 *		sincos = SINE   (= 2) --- use sin(omega*x)
 *
 *	epsabs - absolute accuracy requested.
 *
 */ 	
double dqawf(double f(double, void*),void * cbData,double a,double omega,int sincos,
	double epsabs,double *abserr,int *neval,int *ier)
{
    double **chebmo,erlst[50];
	double result,rslst[50];

    int ierlst[50],i;
    int limlst;

	if ((chebmo = (double **)calloc(MAXP1,sizeof(double *))) == NULL) {
		fprintf(stderr,"Out of memory in dqawf!\n");
		exit(1);
	}
	for (i = 0;i < MAXP1; i++) {
		if ((chebmo[i] = (double *)calloc(25,sizeof(double))) == NULL) {
			fprintf(stderr,"Out of memory in dqawf!\n");
			exit(1);
		}
	}
	*ier = 6;
	*neval = 0;
	result = 0.0;
	*abserr = 0.0;
	
/* Dimensioning parameters.
 *	limlst - upper bound on number of cycles,	
 *	MAXP1 - upper bound on the number of Chebyshev moments.
 */
 	limlst = 50;
 	
 /* Check validity of limlst and MAXP1. */
 	if ((limlst < 3) || (MAXP1 < 1))
 		goto _10;
	
/* Prepare call for dqawfe. */
      result=dqawfe(f,cbData,a,omega,sincos,epsabs,limlst,MAXP1,
        abserr,neval,ier,rslst,erlst,ierlst,chebmo);
_10:
	for (i = 0; i < MAXP1; i++)
		free(chebmo[i]);
	free(chebmo); 
	return result;
}	
