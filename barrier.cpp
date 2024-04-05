#include "barrier.h"
#include <iostream>

namespace synchronization
{
   sem_t coutMut;

   sem_t counterMut;
   sem_t waitA;
   sem_t waitB;
   int threadCt;

   barrier::barrier(int numberOfThreads)
   {
      // Write your code here
      threadCt = numberOfThreads;
      sem_init(&coutMut, 0, 1);

      sem_init(&counterMut, 0, 1);
      sem_init(&waitA, 0, 0);
      sem_init(&waitB, 0, 0);
   }

   barrier::~barrier()
   {
      // Write your code here
      sem_destroy(&counterMut);
      sem_destroy(&waitA);
      sem_destroy(&waitB);
   }

   void barrier::arriveAndWait()
   {
      static int counter = 0;

      // Stage A
      sem_wait(&counterMut);
      counter++;

      if (counter < threadCt)
      {
         sem_post(&counterMut);
         sem_wait(&waitA);
      }

      else
      {
         for (int i = 0; i < threadCt - 1; i++) 
         {
            sem_post(&waitA);
         }
         sem_post(&counterMut);
      }

      // Stage B
      sem_wait(&counterMut);
      counter--;

      if (counter > 0)
      {
         sem_post(&counterMut);
         sem_wait(&waitB);
      }

      else
      {
         for (int i = 0; i < threadCt - 1; i++) 
         {
            sem_post(&waitB);
         }
         sem_post(&counterMut);
      }

   }

}
