
#ifndef SEMAPHORE_H
#define SEMAPHORE_H

struct mutex;
struct condvar;

struct semaphore {
  int count;
  struct mutex lock;
  struct condvar cv;
};

void sem_init(struct semaphore* sem, int initval);
void sem_post(struct semaphore* sem);
void sem_wait(struct semaphore* sem);

#endif
