#include "../inc/sampleQueue.h"

#define DATA_STRING_SIZE 256

// Actual queue implementation.
struct queue_instance_t {
    unsigned short capacity;
    unsigned short size;
    unsigned short front;
    unsigned short back;
    char (*data)[DATA_STRING_SIZE];
};



// Constructor.
queue_t* createQueue(unsigned short capacity) {
    queue_t* instance = malloc(sizeof(struct queue_instance_t));
    
    if (instance == NULL) {
        return NULL;
    }

    instance->data = malloc(capacity * sizeof(char) * DATA_STRING_SIZE);

    if (instance-> data == NULL) {
        free(instance);
        return NULL;
    }

    instance->capacity = capacity;
    instance->size = 0;
    instance->front = 0;
    instance->back = 0;

    return instance;
}



// Accessors.
unsigned short getQueueCapacity(queue_t* instance) {
    return (instance == NULL) ? 0 : instance->capacity;
}



unsigned short getQueueSize(queue_t* instance) {
    return (instance == NULL) ? 0 : instance->size;
}



bool isEmpty(queue_t* instance) {
    return (instance == NULL) ? false : instance->size == 0;
}



bool isFull(queue_t* instance) {
    return (instance == NULL) ? false : instance->size == instance->capacity;
}



// Mutators.
bool enqueue(queue_t* instance, const char* data) {
    if (instance == NULL || data == NULL || isFull(instance)) {
        return false;    
    }

    snprintf(instance->data[instance->back], DATA_STRING_SIZE, "%s", data);
    instance->back = (instance->back + 1) % instance->capacity;
    instance->size++;

    return true;
}



bool dequeue(queue_t* instance, char* buffer, int bufferSize) {
    if (instance == NULL || buffer == NULL || bufferSize <= 0 || isEmpty(instance)) {
        return false;    
    }

    snprintf(buffer, bufferSize, "%s", instance->data[instance->front]);
    instance->front = (instance->front + 1) % instance->capacity;
    instance->size--;

    return true;
}



// Destructor.
void destroyQueue(queue_t* instance) {
    if (instance != NULL) {
        free(instance->data);
        free(instance);
        instance = NULL;
    }
}