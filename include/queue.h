#ifndef QUEUE_H
#define QUEUE_H
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "node.h"

#define qe_isEmpty(__queue__) ((__queue__)->size == 0)
#define qe_is_null(__queue__) ((__queue__) == NULL)
#define qe_is_not_null(__queue__) ((__queue__) != NULL)
#define qe_length(__queue__) ((__queue__)->size)

typedef sl_node_t q_node_t;

typedef struct queue {
    unsigned int size;
    q_node_t *front;
    q_node_t *rear;
};
typedef struct queue queue_t;

queue_t qe_create_queue(void);

int qe_enqueue(queue_t *queue, void *data);
int qe_dequeue(queue_t *queue);

inline int qe_peek_front(queue_t *queue){
  return queue->front->data;
}

inline int qe_peek_rear(queue_t *queue){
  return queue->rear->data;
}

void qe_print_queue(queue_t *queue);

void qe_free_queue(queue_t *queue);
void qe_freeDeep_queue(queue_t *queue);

#endif // QUEUE_H
