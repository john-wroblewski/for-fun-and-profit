
#ifndef MUTEX_H
#define MUTEX_H

struct tok_queue;

struct mutex {
  int flag;
  int guard;
  struct tok_queue * q;
};

void mutex_init(struct mutex* mtx);
void mutex_lock(struct mutex* mtx);
void mutex_unlock(struct mutex* mtx);


#endif
