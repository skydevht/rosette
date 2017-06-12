//
// Created by Hash on 4/29/2016.
//

#ifndef ROSETTE_DATA_STRUCT_H
#define ROSETTE_DATA_STRUCT_H

#include "../board.h"

typedef enum{
    STACK, QUEUE
} Structure;

typedef struct DataStructure {
    Structure type;
    struct Node *first;
    struct Node *last;
    int count;
}DataStructure;

typedef struct Node {
    Intersection *inter;
    struct Node *next;
    struct Node *prev;
} Node;

DataStructure *init_data_structure(Structure type);

int intersection_queue_enqueue(DataStructure *queue, Intersection *inter);
Intersection* intersection_queue_dequeue(DataStructure *queue);
int intersection_stack_push(DataStructure *stack, Intersection *inter);
Intersection* intersection_stack_pop(DataStructure* stack);
Node* init_intersection_queue_node(Intersection *inter);

#endif //ROSETTE_DATA_STRUCT_H
