/*
Author: @shubham0204
Implementation of Huffman encoding in C
primary ref: https://www.programiz.com/dsa/huffman-coding
Other refs:
1. https://github.com/mcinglis/c-style
2. https://stackoverflow.com/questions/65945630/ways-to-create-a-recursive-data-structure-in-c
*/

#include <stdlib.h>
#include <stdio.h>

#define PRINTLN(s) (printf("%s\n",s))

typedef unsigned int uint32 ;

typedef struct heap_node_t {
    char                 data ; 
    uint32               freq ;
    struct heap_node_t*  left ;
    struct heap_node_t*  right ;
} heap_node_t ; 

typedef struct {
    heap_node_t** nodes ; 
    uint32    size ; 
    uint32    capacity ;
} heap_t ;

heap_node_t* create_min_heap_node(
    char         data , 
    uint32 freq 
) {
    heap_node_t* new_node = (heap_node_t*) malloc( sizeof( heap_node_t ) ) ;
    new_node -> left = NULL ; 
    new_node -> right = NULL ; 
    new_node -> freq = freq ; 
    new_node -> data = data ;
    return new_node ;
}

heap_t* create_min_heap(
    uint32 capacity
) {
    heap_t* heap = (heap_t*) malloc( sizeof( heap_t ) ) ;
    heap -> capacity = capacity ; 
    heap -> size = 0 ;
    heap -> nodes = (heap_node_t**) malloc( sizeof( heap_node_t* ) * capacity ) ;
    return heap ; 
}

void insert_min_heap(
    heap_t*         heap ,
    heap_node_t*    node
) {
    heap -> size++ ; 
    int i = heap -> size - 1; 
    while (
        i > 0 &&
        node -> freq  < heap -> nodes[( i - 1 ) / 2] -> freq
    ) {
        heap -> nodes[i] = heap -> nodes[(i - 1) / 2] ; 
        i = (i - 1) / 2; 
    }
    heap -> nodes[i] = node ;
}

void heapify(
    heap_t* heap , 
    uint32  node_idx
) {
    uint32 smallest = node_idx ; 
    uint32 left_node_idx = 2 * node_idx + 1 ;
    uint32 right_node_idx = 2 * node_idx + 2 ;
    if (
        left_node_idx < heap -> size &&
        (heap -> nodes[left_node_idx] -> freq) > (heap -> nodes[smallest] -> freq)
    ) {
        smallest = left_node_idx ; 
    }
    if (
        right_node_idx < heap -> size &&
        (heap -> nodes[right_node_idx] -> freq) > (heap -> nodes[smallest] -> freq)
    ) {
        smallest = right_node_idx ; 
    }
    if (smallest != node_idx) {
        heap_node_t** temp = heap -> nodes[smallest] ; 
        heap -> nodes[smallest] = heap -> nodes[node_idx] ; 
        heap -> nodes[node_idx] = temp ; 
        heapify( heap , smallest ) ; 
    }
}



int main(
    int argc , 
    char** argv
) {
    printf( "Hello World from C!" ) ;
}