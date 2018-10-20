#ifndef _TOOLS_H_
#define _TOOLS_H_

typedef unsigned int uint;

struct ll_node{
  void * data;
  struct ll_node * next;
};

struct ll_node * ll_newnode(void *);                            // create a new node using malloc... free'd in delete
struct ll_node * ll_append(void *, struct ll_node *);           // append new node to front of list
struct ll_node * ll_search(void *, struct ll_node *);           // search list for a given value (assumed to be integer)
struct ll_node * ll_delete(struct ll_node *, struct ll_node *); // removes node from list
void             freelist(struct ll_node *);                    // free every node in list

#endif // _TOOLS_H__
