#include <Arduino.h>

#include "Config.h"
#include "Scheduler.h"
#include "Altimeter.h"

void setup()
{

	DEBUGSERIAL.begin(DEBUG_BAUD_RATE);
	delay(2000);

	DEBUGSERIAL.print("booting....\n");

	Altimeter::init();
	Scheduler::init();



	//Scheduler::addTask(LOW_PRIORITY, ([]() { DEBUGSERIAL.printf("avg alt: %.2f m\n", Altimeter::getAltitude()); }), 1000000lu, 0, "get Alt value");
	Scheduler::addTask(LOW_PRIORITY, Altimeter::getNewSample, 100000lu, 1000000lu, "get Alt sample");
	
	//Scheduler::addTask(LOW_PRIORITY, ([]() { DEBUGSERIAL.printf("Free mem: %lu kB\n", FreeMem()/1000); }), 5000000lu, 0, "mem usage");

}

void loop()
{
	Scheduler::tickSoft();
	delayMicroseconds(100);
}


uint32_t FreeMem()
{
    uint32_t stackTop;
    uint32_t heapTop;

    // current position of the stack.
    stackTop = (uint32_t) &stackTop;

    // current position of heap.
    void* hTop = malloc(1);
    heapTop = (uint32_t) hTop;
    free(hTop);

    // The difference is (approximately) the free, available ram.
    return stackTop - heapTop;
}

