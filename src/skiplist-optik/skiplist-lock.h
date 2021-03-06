/*   
 *   File: skiplist-lock.h
 *   Author: Vasileios Trigonakis <vasileios.trigonakis@epfl.ch>
 *   Description: 
 *   skiplist-lock.h is part of ASCYLIB
 *
 * Copyright (c) 2015 Vasileios Trigonakis <vasileios.trigonakis@epfl.ch>,
 *	      	      Distributed Programming Lab (LPD), EPFL
 *
 * ASCYLIB is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, version 2
 * of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <assert.h>
#include <getopt.h>
#include <limits.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <stdint.h>

#include "common.h"

#include <atomic_ops.h>
#include "lock_if.h"
#include "ssmem.h"
#include "optik.h"

extern unsigned int global_seed;
extern __thread ssmem_allocator_t* alloc;

extern unsigned int levelmax, size_pad_32;

typedef enum
  {
    ND_LINKING,
    ND_LINKED,
    ND_UNLINKING,
  } sl_node_state_t;

typedef volatile struct sl_node
{
  skey_t key;
  sval_t val; 
  uint32_t toplevel;
  sl_node_state_t state; 
  optik_t lock;
  volatile struct sl_node* next[1];
} sl_node_t;

static inline int
node_is_linking(sl_node_t* node)
{
  return (node->state == ND_LINKING);
}

static inline int
node_is_unlinking(sl_node_t* node)
{
  return (node->state == ND_UNLINKING);
}

static inline int
node_is_linked(sl_node_t* node)
{
  return (node->state == ND_LINKED);
}

static inline void
node_set_valid(sl_node_t* node)
{
  node->state = ND_LINKED;
}

static inline void
node_set_unlinking(sl_node_t* node)
{
  node->state = ND_UNLINKING;
}

typedef ALIGNED(CACHE_LINE_SIZE) struct sl_intset 
{
  sl_node_t *head;
  uint8_t padding[CACHE_LINE_SIZE - sizeof(sl_node_t*)];
} sl_intset_t;

int get_rand_level();
int floor_log_2(unsigned int n);

/* 
 * Create a new node without setting its next fields. 
 */
sl_node_t* sl_new_simple_node(skey_t key, sval_t val, int toplevel, int transactional);
/* 
 * Create a new node with its next field. 
 * If next=NULL, then this create a tail node. 
 */
sl_node_t *sl_new_node(skey_t key, sval_t val, sl_node_t *next, int toplevel, int transactional);
void sl_delete_node(sl_node_t* n);
sl_intset_t* sl_set_new();
void sl_set_delete(sl_intset_t* set);
int sl_set_size(sl_intset_t* cset);
