#include <stdio.h>          /* include libraries to use functions like rand () srand ()*/
#include <stdlib.h>
#include <time.h>
         int rand_coin (int bin);     /*declaration of function to generate random heads or tails*/


int main(void)  {
   int a[2000], bin=0;                /*declaration of array to store values of 0s or 1s */
   srand((unsigned) time(NULL));
   for (int i=0; i<2000; i++)     {    /*for loop to generate 2000 random values for heads and tails*/
      a[i]= rand_coin (bin);
   }

   int heads=0;                         /*head=1, tail=0*/
   int tails=0;
   for (int i=0; i<2000; i++) {         /*for loop to determine how many heads or tails were generated before*/
      if (a[i]==1)
         heads++;
         else  tails ++;   }

   printf("Heads = %d, Tails = %d\n", heads, tails);       /*print the total number of heads and tails generated*/

    return 0;
} /* end main */

int rand_coin (int bin){         /*Function to generate random 0s or 1s*/
    bin = rand()%2;
    return bin;
}  /* end rand_coin*/