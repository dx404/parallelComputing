#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <math.h>

#define T_NUM 16
#define npts 5000 /* the number of bodies */
/*#define MAX_X 1000   /* the positions (x_i,y_i) of bodies are randomly picked */
#define MIN_X 0   /* where x_i is in MIN_X to MAX_X and  y_i is in MIN_Y to MAX_Y */

#define MAX_Y 1000  
#define MIN_Y 0

#define Max_M 1000   /* the weights w_i of bodies are randomly picked */
#define MIN_M 0   /* where w_i is in MIN_M to MAX_X */

#define MAX_V 1000    /* the velocities (vx_i,vy_i) of bodies are randomly picked */
#define MIN_V 0        /* where vx_i,vy_i are in MIN_V to MAX_V */*/
#define ITERATION 10    /* run in ITERATION times */ 
#define dt 0.001  


/* Gravitational constant */
const double G = 1 ;


    double b1m[npts];
    double b2m[npts];
    double b1x[npts];
    double b1y[npts];
    double b2x[npts];
    double b2y[npts];
    double b1vx[npts];
    double b1vy[npts];
    double b2vx[npts];
    double b2vy[npts];
    double ax[npts];        /* for calculate each body's acceleration */
    double ay[npts];
    
double wctime(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec + 1E-6 * tv.tv_usec);
} 


int main(int argc, char* argv[]){
    

    omp_set_num_threads(T_NUM);
   
    //setenv OMP_NUM_THREADS 16
    
    /* N-Body variables */
    int i,j,k;

    double mx,my;
    double mx1,my1;

    double td;
    double rate;
    
    double t1,t2;
    
    /* initialize N-body */
    srand(time(NULL));
    
    /* with random initial condition
    for(i=0;i<npts;i++){
	
        b1m[i] = rand() / (double)(RAND_MAX);        
        b1x[i] = rand() / (double)(RAND_MAX);
	b1y[i] = rand() / (double)(RAND_MAX);
        b1vx[i] = rand() / (double)(RAND_MAX);
        b1vy[i] = rand() / (double)(RAND_MAX);
        
	ax[i] = 0;
	ay[i] = 0; 
              
    }
     */
    
        /* with Pf Prins' initial condition*/
    for(i=0;i<npts;i++){
	double f_i = ((double) i) / npts;
        b1m[i] = 1 - f_i;        
        b1x[i] = f_i;
	b1y[i] = f_i;
        b1vx[i] = - f_i;
        b1vy[i] = f_i;
        
	ax[i] = 0;
	ay[i] = 0; 
              
    }
    
    mx=0;
    my=0;
    
    for(i =0; i<npts; i++){
        mx+=b1m[i]*b1vx[i];
        my+=b1m[i]*b1vy[i];
    }
    
    //printf("Number of processors used: , n = %d \n", npts);
    printf("sequential all-pairs n-body, n = %d \n", npts);
    printf("Simulation n = %d, G = %f, deltaT = %f \n", npts, G, dt);
    
    /*
    printf("Initial state: \n");
    for(i =0; i<npts; i++){
        printf("[ Body %d] m(%f) r(%f,%f) v(%f,%f)\n", i, b1m[i], b1x[i], b1y[i], b1vx[i], b1vy[i]);
    }
    */
    
    printf("Total momentum = (%f,%f) magnitude = %f\n", mx, my, sqrt(mx*mx+my*my));
    
        
    t1=wctime();
    
    for(k=0;k<ITERATION;k++){
    
	/* Calculate the position of bodies by point-to-point in each iteration */
        #pragma omp parallel for private(i,j)
	for(i=0;i<npts;i++){
            double ax_tem = 0;
            double ay_tem = 0;
            
            //#pragma omp parallel for shared(i) private(j) reduction(+: ax_tem, ay_tem)
            for(j=0;j<i;j++) {
                double delta_x    = b1x[j] - b1x[i];
                double delta_y    = b1y[j] - b1y[i];
                double dist       = delta_x*delta_x + delta_y*delta_y;
		double dist_cubic = dist * sqrt(dist);
                double temp       = G *b1m[j]/(dist_cubic);
		ax_tem     +=  temp * delta_x;
                ay_tem    +=  temp * delta_y;
            }
            
            //#pragma omp parallel for shared(i) private(j) reduction(+: ax_tem, ay_tem)
             for(j=i+1;j<npts;j++) {
                double delta_x    = b1x[j] - b1x[i];
                double delta_y    = b1y[j] - b1y[i];
                double dist       = delta_x*delta_x + delta_y*delta_y;
		double dist_cubic = dist * sqrt(dist);
                double temp       = G *b1m[j]/(dist_cubic);
		ax_tem     +=  temp * delta_x;
                ay_tem    +=  temp * delta_y;
            }
                ax[i] = ax_tem;
                ay[i] = ay_tem;
            
        }

        /* update the new p sition and velocity  */
        //#pragma omp parallel for
        for(i = 0; i < npts; i++){
            b1x[i]   += dt * b1vx[i] ;
            b1y[i]   += dt * b1vy[i] ;
            b1vx[i]  += dt * ax[i];
            b1vy[i]  += dt * ay[i];
            ax[i] = 0;
            ay[i] = 0;

        }

    /*//printf("Momentum(%f,%f),",mx1[k],my1[k]);
            	////printf("This is the %d time step\n",k);
        //printf("[ (%f,%f),",b1x[0],b1y[0]);
	for (i =1; i<npts-1; i++){
            //printf("(%f,%f),",b1x[i],b1y[i]);
        }
        //printf("(%f,%f) ]\n",b1x[npts-1],b1y[npts-1]);
      */ 
    
    }
            //printf("Final Momentum (%f,%f)\n\n\n",mx1[ITERATION-1],my1[ITERATION-1]);
    t2=wctime();
    td=(t2-t1);
    rate=1e-6*ITERATION*npts*npts/td;
    
    
    mx1=0;
    my1=0;
    for(i =0; i<npts; i++){
        mx1+=b1m[i]*b1vx[i];
        my1+=b1m[i]*b1vy[i];
    }
   
    /*
    printf("State after %d time steps (t = %f)\n", k, k*dt);
    for(i =0; i<npts; i++){
        printf("[ Body %d] m(%f) r(%f,%f) v(%f,%f)\n", i, b1m[i], b1x[i], b1y[i], b1vx[i], b1vy[i]);
    }
    */
    
    printf("Total momentum = (%f,%f) magnitude = %f\n", mx1, my1, sqrt(mx1*mx1+my1*my1));
    
    
    // Program Finished
        printf(" 1st method: reactions: %f,\n", rate);
    return 0;
}


