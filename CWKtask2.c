#include <stdio.h>                /* include libraries to use functions like rand (), srand (), sqrt ()*/
#include <stdlib.h>
#include <time.h>
#include <math.h>


         double rand_u (double Lower, double Upper);          /*declaration of functions rand_u and pci*/
         double pci (double mean, double variance, int N);
         

         int main(void)  {
             int N=10000, n;                                                                    /* declaration of an array and n which is going to be used as the number of samples*/
             double mean=0, sum=0, sample_variance, var,  a[N], variance, percent;              /*declaration of all the variables to be used in main*/
             srand((unsigned) time(NULL));

               n=1;                                                                             /*store the first random value in variables sum and var to continue with the calculations*/
               a[n] = rand_u (0.0, 1.0);
               sum = a[n];
               var = (a[n]*a[n]);

                 for (n=2; n<N; n++){                                                           /*for loop from the second value taking into account the first random value too which was stored in variable before.  */
               a[n] = rand_u (0.0, 1.0);                                                        /*this was made to avoid percent =0 when computing just the first value*/
               sum += a[n];
               mean=(sum/n);
               var+= (a[n]*a[n]);
               sample_variance= ((var/n) - (mean*mean));
               percent = pci(mean, sample_variance, n);
               if(percent < 5.00){                                                               /*when pci is less than 0 then the loop finishes execution and we get the values required*/
                            break;
                                 }
               }



             if (n >30) {                                                                        /*calculation of variance just when the number of samples is greater than 30*/
               variance = (sample_variance/(n));}

                                                                                                 /*print and show all the required values*/
               printf ("No. of samples = %d\n", n);
               printf ("Sample mean = %lf\n", mean);
               printf ("Variance = %lf\n", variance);
               printf ("Sample Variance = %lf\n", sample_variance);
               printf ("Percentage confidence interval = %lf", pci(mean, sample_variance, n));
               return 0;

               } /* end main */
 

         double rand_u (double Lower, double Upper){                              /*Function to get random values from 0.0 to 1.0*/
          return Lower + (rand() / (double) RAND_MAX) * (Upper - Lower);
          }       /*end rand_u*/


         double pci (double mean, double sample_variance, int n_samples){          /*Function to calculate the percentage confidence interval*/
           return ((2*1.96*sqrt(sample_variance)*100)/(sqrt(n_samples)*mean));
         }       /*end pci*/




