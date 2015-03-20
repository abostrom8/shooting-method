#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define v 140
#define out_file "output.dat"
#define num_evals 10

double E[num_evals]

void euler(double u[], double dudt[], double h, int theta, double E){
    dudt[0]=u[1];
    dudt[1]=-(E+theta)*v*u[0];
    u[0]+=dudt[0]*h;
    u[1]+=dudt[1]*h;
    // u[0] corresponds to u, u[1] corresponds to w
}

int main(int argc, char *argv[]){
    double h=0.0001,E;
    double u[2],dudt[2];
    int i,j,theta;
    
    // Initial conditions
    u[0]=0.0;
    u[1]=1.0;
    
    // Create pointer to output file
    FILE *fp=fopen(out_file,"w");
    
    // Print initial conditions to output file
    fprintf(fp,"%lf %lf\n",0.0,u[0]);
    
    // Create a pointer to input file
    FILE *infile=fopen(argv[1],"r");
    // Error message if no file specified
    if (infile==NULL){
        printf("\nUsage: %s filename\n",argv[0]);
        return 0;
    }
    //Read input file into array of E values
    for(i=;i<num_evals;i++){
        fscanf(infile,"%f",&E[i]);
    }
    
    for(j=0;j<num_evals;j++){
        for(i=1;i<2e4;i++) {
            /* Step function */
            if(i*h<=1.0){
                theta=1.0;
            }
            if(i*h>1.0){
                theta=0.0;
            }
            E=E[j];
            // Integrate
            euler(u,dudt,h,theta,E);
            // Print results to output file as r/a u
            fprintf(fp,"%lf %lf\n",i*h,u[0]);
        }
    }
}
