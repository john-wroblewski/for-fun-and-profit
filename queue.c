#include "queue.h"
#include "user.h"

struct tok *
newtok(void * d)
{
  struct tok * p = (struct tok *)malloc(sizeof(struct tok));
  if(p)
  {
    p->data = d;
    p->linked_tok = 0;
  }
  return p;
}

void
tok_queue_enq(struct tok_queue * tqp, const struct tok * tp)
{
  tp->linked_tok = 0;
  if(tqp->back)
    tqp->back->linked_tok = tp;
  else
    tqp->front = tp;
  tqp->back = tp;
}

struct tok *
tok_queue_deq(struct tok_queue * tqp)
{
  struct tok * token = tqp->front;
  if(tqp->front)
  {
    tqp->front = token->linked_tok;
    if(token == tqp->back) // end of queue
      tqp->back = 0;
    token->linked_tok = 0;
  }
  return token;
}

void
free_queue(struct tok_queue * queue)
{
  struct tok * token;
  for(token = queue->front;token;token = token->linked_tok)
    free(token);
}
