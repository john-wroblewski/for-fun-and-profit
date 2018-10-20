#include "tools.h"


// create a new linked list node using malloc
// initially unlinked
// returns node, or 0 on error
struct ll_node *
ll_newnode(void * val)
{
  struct ll_node * node = (struct ll_node *)malloc(sizeof(struct ll_node *));

  if(node)
  {
    node->next = 0;
    node->data = val;
  }

  return node;
}


// appends a new node to the front of list pointed to by head
// returns address of (new) head
struct ll_node *
ll_append(void * val, struct ll_node * head)
{
  struct ll_node * node = ll_newnode(val);

  if(node)
  {
    node->next = head;
    return node;
  }

  return head;
}


// search list for node with data matching val
// return pointer to 1st occurence on success, 0 on failure
struct ll_node *
ll_search(void * val, struct ll_node * head)
{
  struct ll_node * node = head;

  while(node)
  {
    if(*(int *)node->data == *(int *)val)  // *** HUGE HACKY-NESS HERE *** data is assumed to be an int
    {                                      // TODO: use function ptr for comparison to take advantage of void *
      break;
    }
    node = node->next;
  }

  return node;
}


// deletes node pointed to by np if present in list
// returns (new) head
struct ll_node *
ll_delete(struct ll_node * np, struct ll_node * head)
{
  if(!np || !head)
    return 0;

  struct ll_node * p, * q = 0;
  for(p = head;p != np && p;p = p->next)
    q = p;

  if(!p)  // np not found
    return head;

  if(!q)  // deleting head node
  {
    free(np);
    return p->next;
  }

  q->next = p->next;
  free(np);
  return head;
}

void
freelist(struct ll_node * head)
{
  struct ll_node * q, * p = head;

  while(p)
  {
    q = p;
    p = p->next;
    free(q);
  }
}
