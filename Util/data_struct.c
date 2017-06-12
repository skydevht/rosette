//
// Created by Hash on 4/29/2016.
//

#include "data_struct.h"

DataStructure *init_data_structure(Structure type) {
    DataStructure *data = malloc(sizeof(DataStructure));
    data->type = type;
    data->first = NULL;
    data->last = NULL;
    data->count = 0;
    return data;
}

Node* init_intersection_queue_node(Intersection *inter){
    Node *first = malloc(sizeof(Node));
    first->inter;
    first->next = NULL;
    return first;
}

int intersection_queue_enqueue(DataStructure *queue, Intersection *inter) {
    Node *last = malloc(sizeof(Node));
    last->inter = inter;
    last->next = NULL;
    last->prev = queue->last;
    if (queue->last) queue->last->next = last;
    if (!queue->first) queue->first = last;
    queue->last = last;
    queue->count++;
}

Intersection* intersection_queue_dequeue(DataStructure *queue) {
    if (queue->count != 0) {
        Intersection *inter = queue->first->inter;
        Node *new_first = queue->first->next;
        free(queue->first);
        queue->first = new_first;
        queue->count--;
        if (queue->count == 0) {
            queue->first = queue->last = NULL;
        }
        return inter;
    }
    return NULL;
}

Node* init_intersection_stack_node(Intersection *intersection){

}

int intersection_stack_push(DataStructure *stack, Intersection *inter){
    Node *last = malloc(sizeof(Node));
    last->inter = inter;
    last->next = NULL;
    last->prev = (stack->last)?stack->last : NULL;
    if (stack->last) stack->last->next = last;
    if (!stack->first) stack->first = last;
    stack->last = last;
    stack->count++;
}

Intersection* intersection_stack_pop(DataStructure* stack){
    if (stack->count != 0) {
        Node *old_last = stack->last;
        stack->last = old_last->prev;
        Intersection *inter = old_last->inter;
        free(old_last);
        if (stack->last) stack->last->next = NULL;
        stack->count--;
        if (stack->count == 0) stack->first = stack->last = NULL;
        return inter;
    }
    return NULL;
}