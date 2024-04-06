#ifndef SAMPLEQUEUE_H
#define SAMPLEQUEUE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h> 
#include <limits.h>
#include <unistd.h>

// "Instance".
/*  To explain, this works by chessing compilation in C.
    The compiler does not need to know what "queue_instance_t" is to know that "queue_t" is a valid type, at least at first.
    This is done via forward declaration, meaning the compiler knows "queue_t" exists but not its complete definition.
    When the header file is included via the preprocessor, the compiler gains access to the full definition of "queue_t".
    This allows the compiler to understand "queue_t" in its entirety, thus correct compilation.
*/
typedef struct queue_instance_t queue_t; // https://stackoverflow.com/questions/750178/is-it-a-good-idea-to-typedef-pointers

/* "Methods" */
// Constructor
queue_t* createQueue(unsigned short capacity);

// Accessors / Mutators.
unsigned short getQueueCapacity(queue_t* instance);
unsigned short getQueueSize(queue_t* instance);
bool isEmpty(queue_t* instance);
bool isFull(queue_t* instance);
bool enqueue(queue_t* instance, const char* data);
bool dequeue(queue_t* instance, char* buffer, int bufferSize);

// Destructor.
void destroyQueue(queue_t* instance);

#endif