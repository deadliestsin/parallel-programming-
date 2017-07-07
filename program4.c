#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


double random_double(){
return (random() / ((double)RAND_MAX + 1));
}

int main (int argc, char *argv[]) 
{
time_t t;
t = clock();
int w;
double pi;
double x, y;
double pInCircle;
double NUM_OF_SLAVES = 100;
int totalPoints = 1000000;

omp_set_num_threads(NUM_OF_SLAVES); 	
#pragma omp parallel
	{	
		pInCircle = 0;
		srandom((unsigned)time(NULL));
		#pragma omp for private(x,y) reduction(+:pInCircle)
				for (w = 0; w < totalPoints; w++){
					x = ( random_double() * 2 ) - 1;
					y = ( random_double() * 2 ) - 1;
					if( sqrt (x*x + y*y) > 1 ){
						pInCircle++;
					}
				}
	}
	t = clock() - t;
	double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
	pi = 4*pInCircle/totalPoints;
	printf("%f\n", pi);
	printf("%f\n", time_taken);
	return 0;
}

  
  









