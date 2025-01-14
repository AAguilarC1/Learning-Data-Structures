#include "queue.h"

queue_t qe_create_queue(void) {
    queue_t queue;
    queue.front = NULL;
    queue.rear = NULL;
    queue.size = 0;
    return queue;
}

int qe_enqueue(queue_t *queue, void *data) {
    if (qe_is_null(queue)) {
        return -1;
    }
    
    q_node_t *node = n_create_node(data);
    
    if (qe_is_null(node)) {
        return -1;
    }
    
    if (qe_isEmpty(queue)) {
        queue->front = node;
        queue->rear = node;
        queue->size++;
        return 0;
    }

    if(qe_length(queue) == 1) {
        queue->front->next = node;
        queue->rear = node;
        queue->size++;
        return 0;

    }

    queue->rear->next = node;
    queue->rear = node;

    queue->size++;
    return 0;
}

int qe_dequeue(queue_t *queue){
  if(qe_is_null(queue)){
    return -1;
  }  
  
  if(qe_isEmpty(queue))
  {
    return 0;
  }

  q_node_t* temp;
  int ret = 0;
  temp = queue->front;
  ret = temp->data;
  queue->front = queue->front->next;

  n_free_node(temp);
  queue->size--;
  return ret;
}

void qe_print_queue(queue_t *queue) {
    if (qe_is_null(queue)) {
        return;
    }
    
    q_node_t *current = queue->front;
    
    while (qe_is_not_null(current)) {
        n_print_node(current);
        current = current->next;
    }
}

void qe_free_queue(queue_t *queue) {
    if (qe_is_null(queue)) {
        return;
    }
    
    q_node_t *current= queue->front;
    q_node_t *next = NULL;
    
    while (qe_is_not_null(current)) {
        next = current->next;
        n_free_node(current);
        current = next;
    }
   return;
}

void qe_freeDeep_queue(queue_t *queue) {
    if (qe_is_null(queue)) {
        return;
    }

    qe_free_queue(queue);
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
    
}
