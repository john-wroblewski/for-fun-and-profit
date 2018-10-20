/*
 * I wrote this during a probability course I was taking where we were learning about expected value.
 * Probability allows us to calculate the expected number of rolls of die it takes to have a certain side land facing up.
 * This code was to empirically prove to myself that the math checked out. It turns out the math is scarely accurate.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ITERS    100000000
#define SIDE_CNT 6

int die_roll(unsigned int);
float average(unsigned int *);

int main(){

//  unsigned int longest = 0;
  unsigned int i = 0;
  unsigned int * experiments = malloc(sizeof(unsigned int) * ITERS);

  if(!experiments)
  {
    puts("malloc");
    return 1;
  }

  srand((int)time(NULL));

  printf("\n\n\n.....begin experiment with a %d-sided die...\n",SIDE_CNT);

  while(i++ < ITERS)
  {
    unsigned int j;
    for(j = 1;die_roll(SIDE_CNT) != 0;j++)
    {  }
    experiments[i] = j;
//    if(j > longest)
//      longest = j;
  }

  puts(".....end   experiment...");

  printf("average rolls needed: %f\n", average(experiments));
//  printf("longest roll: %d\n", longest);

  return 0;
}

int
die_roll(unsigned int side_count)
{
  return rand() % side_count;
}

float
average(unsigned int * list)
{
  unsigned int i;
  unsigned long sum = 0;

  for(i = 0;i < ITERS;i++)
  {
    sum += list[i];
  }

  return (float)sum / ITERS;
}
