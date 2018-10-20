
#include "types.h"
#include "user.h"

void cv_init(struct condvar* cv)
{
  tok_queue_init(&cv->q);
}

void cv_wait(struct condvar* cv, struct mutex* mtx)
{
  tok_queue_enq(&cv->q, newtok((void *)getpid()));
  setpark();
  mutex_unlock(mtx);
  park();
  mutex_lock(mtx);
}

void cv_signal(struct condvar* cv)
{
  if(!tok_queue_empty(&cv->q))
    _cv_signal(cv);
}

void _cv_signal(struct condvar* cv)
{
  struct tok * token = tok_queue_deq(&cv->q);
  unpark((int)token->data);
  free(token);
}

void cv_broadcast(struct condvar* cv)
{
  while(!tok_queue_empty(&cv->q))
  {
    _cv_signal(cv);
  }
}
