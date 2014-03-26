/*
 * File:
 *   coupling.c
 * Author(s):
 */

#include "seq.h"

sval_t
seq_delete(intset_t *set, skey_t key)
{
  node_t *curr, *next;
  sval_t res = 0;
	
  curr = set->head;
  if (curr->next != NULL)
    {
    }
  next = curr->next;
	
  while (next != NULL && next->key < key) 
    {
      curr = next;
      if (next->next != NULL)
	{
	}
      next = next->next;
    }

  if (next != NULL && key == next->key)
    {
      res = next->val;
      curr->next = next->next;
      node_delete(next);
    } 
  else 
    {
      if (next != NULL)
	{
	}
    }  

  return res;
}

sval_t
seq_find(intset_t *set, skey_t key) 
{
  node_t *curr, *next; 
  sval_t res = 0;
	
  curr = set->head;
  if (curr->next != NULL)
    {
    }
  next = curr->next;
	
  while (next != NULL && next->key < key) 
    {
      curr = next;
      if (next->next != NULL)
	{
	}
      next = curr->next;
    }	
  if (next != NULL && key == next->key)
    {
      res = next->val;
    }
  if (next != NULL)
    {
    }
  return res;
}

int
seq_insert(intset_t *set, skey_t key, sval_t val) 
{
  node_t *next, *newnode;
  volatile node_t* curr;
  int found;
	
  curr = set->head;
  if (curr->next != NULL)
    {
    }
  next = curr->next;
	
  while (next != NULL && next->key < key) 
    {
      curr = next;
      if (next->next != NULL)
	{
	}
      next = curr->next;
    }
  found = (next != NULL && key == next->key);
  if (!found) 
    {
      newnode =  new_node(key, val, next, 1);
      curr->next = newnode;
    }
  if (next != NULL)
    {
    }
  return !found;
}
