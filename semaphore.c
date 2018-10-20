
#include "types.h"
#include "user.h"

void sem_init(struct semaphore* sem, int initval)
{
  sem->count = initval;
  mutex_init(&sem->lock);
  cv_init(&sem->cv);
}

void sem_wait(struct semaphore* sem)
{
  mutex_lock(&sem->lock);
  while(sem->count <= 0)
    cv_wait(&sem->cv, &sem->lock);
  sem->count--;
  mutex_unlock(&sem->lock);
}

void sem_post(struct semaphore* sem)
{
  mutex_lock(&sem->lock);
  sem->count++;
  cv_signal(&sem->cv);
  mutex_unlock(&sem->lock);
}

