// https://www.embedded.com/incomplete-types-as-abstractions/ (gives a statically sized example as well)
// https://interrupt.memfault.com/blog/opaque-pointers#the-opaque-pointer-pattern
// Can get sweatier (see 'eruciform' comment): https://www.reddit.com/r/learnprogramming/comments/pe3a5c/have_functions_inside_a_struct_in_c_using/
// And https://stackoverflow.com/questions/17052443/c-function-inside-struct
// At that point, just use C++...

#include "../inc/sampleQueue.h"



int main(void) {
    // Create queue.
    queue_t* myQueue = createQueue(USHRT_MAX);
    printf("Queue created.\n");
    sleep(2);

    // Try to over-populate it.
    for (int i = 0; i < (USHRT_MAX * 2); i++) {
        if (!enqueue(myQueue, "Here is the opening scene of Skyrim: Ralof: Hey you, you're finally awake. You were trying to cross the border right? Walked right into that Imperial ambush same as us and that thief over there. Lokir: Damn you Stormcloaks... Skyrim was fine until you came along! Empire was nice and lazy. If they hadn't been looking for you I'd have stolen that horse and been halfway to Hammerfell. Looks at Dragonborn You there, you and me, we shouldn't be here. It's these Stormcloaks the Empire wants.")) {
            printf("Capacity reached! (%d)\n", getQueueSize(myQueue));
            break;
        }
    }

    sleep(2);

    char buffer[61] = { '\0' };

    // Remove data from it, attempting to go out of bounds.
    for (int i = 0; i < (USHRT_MAX * 2); i++) {
        if (!dequeue(myQueue, buffer, sizeof(buffer))) {
            printf("Queue is empty! (%d)\n", getQueueSize(myQueue));
            printf("What is in our buffer? '%s'\n", buffer);
            break;
        }
    }

    sleep(2);

    // Random stuff.
    enqueue(myQueue, "Item 1");
    enqueue(myQueue, "Item 2");

    printf("What is the size now after enqueue() of 2 items? '%d'\n", getQueueSize(myQueue));
    sleep(2);

    dequeue(myQueue, buffer, sizeof(buffer));

    printf("What did we just get from the queue (now size of '%d')? '%s'\n", getQueueSize(myQueue), buffer);
    sleep(2);
    
    // Main issue, caller is responsible for freeing resources.
    // Personally, I'd avoid malloc()/free() where possible.
    destroyQueue(myQueue);

    return 0;
}