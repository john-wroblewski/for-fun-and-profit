#ifndef _QUEUE_H_
#define _QUEUE_H_

struct tok{
  void * data;
  struct tok * linked_tok;
};

struct tok_queue{
  struct tok * front;
  struct tok * back;
};

struct tok * newtok(void *);                                    // create a new token using malloc... must be free'd
void   tok_queue_enq(struct tok_queue *, const struct tok *);   // enqueue new token at back of queue
struct tok * tok_queue_deq(struct tok_queue *);                 // dequeue token from front of queue
void   free_queue(struct tok_queue *);                          // free every token in queue

#endif // _QUEUE_H__
