
#include "types.h"
#include "user.h"
#include "x86.h"

void mutex_init(struct mutex* mtx)
{
  mtx->flag = mtx->guard = 0;
  tok_queue_init(mtx->q);
}

void mutex_lock(struct mutex* mtx)
{
  // spin on the guard
  while(xchg(&(mtx->guard), 1) != 0)
  { }

  if(mtx->flag == 0) // locked unheld.... grab it!
  {
    mtx->flag = 1;

    printf(1, "thread %d aquired lock\n", getpid());

    mtx->guard = 0;
  }
  else
  {
    tok_queue_enq(mtx->q, newtok((void *)getpid()));
    setpark();
    mtx->guard = 0;
    park();
    printf(1, "thread %d aquired lock\n", getpid());
    //mtx->flag is already set to 1 for us
  }
}

void mutex_unlock(struct mutex* mtx)
{
  // spin on the guard
  while(xchg(&(mtx->guard), 1) != 0)
  { }

  if(tok_queue_empty(mtx->q)) // no one waiting for lock... unlock it
  {
    mtx->flag = 0;
  }
  else  // wake up thread next in line for lock
  {
    struct tok * token = tok_queue_deq(mtx->q);
    unpark((int)token->data);
    free(token);
  }
  mtx->guard = 0;
}
