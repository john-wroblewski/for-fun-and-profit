
#ifndef CONDVAR_H
#define CONDVAR_H

struct tok_queue;

struct condvar {
  struct tok_queue q;
};

void cv_init(struct condvar* cv);
void cv_wait(struct condvar* cv, struct mutex* mtx);
void cv_signal(struct condvar* cv);
void _cv_signal(struct condvar* cv);   //signal helper (requires cv to have queued thread)
void cv_broadcast(struct condvar* cv);

#endif
