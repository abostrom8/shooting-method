#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define v 140
#define E -0.0882721 /* E/V0 */
#define out_file "output2.dat"

// Try using a shell script to run code, plot in real time, and change energy?

void euler(double u[], double dudt[], double h, int theta){
    dudt[0]=u[1];
    dudt[1]=-(E+theta)*v*u[0];
    u[0]+=dudt[0]*h;
    u[1]+=dudt[1]*h;
    // u[0] corresponds to u, u[1] corresponds to w
}

int main(){
    double h=0.0001;
    double u[2],dudt[2];
    int i,theta;
    
    // Initial conditions
    u[0]=0.0;
    u[1]=1.0;
    
    // Create pointer to output file
    FILE *fp=fopen(out_file,"w");
    
    // Print initial conditions to output file
    fprintf(fp,"%lf %lf\n",u[0],0.0);
    
    for(i=1;i<3e4;i++) {
        /* Step function */
        if(i*h<=1.0){
            theta=1.0;
        }
        if(i*h>1.0){
            theta=0.0;
        }
        // Integrate
        euler(u,dudt,h,theta);
        // Print results to output file as u r/a
        fprintf(fp,"%lf %lf\n",u[0],i*h);
    }
}