//#include "kernel.h"
#include "Thread.h"
/*
 	 Test: razlicita vremena izvrsavanja i velicine steka
*/
extern int syncPrintf(const char *format, ...);

volatile Time ts;

void tick()
{
	syncPrintf("timeSlice=%d\n",ts);
}

class TestThread : public Thread
{
private:
	Time myTimeSlice;
public:

	TestThread(StackSize stackSize, Time timeSlice): Thread(stackSize,timeSlice), myTimeSlice(timeSlice) {};
	~TestThread()
	{
		waitToComplete();
	}
protected:

	void run();

};

void TestThread::run()
{
	for(unsigned i=0;i<32000;i++)
	{
		for(unsigned int j=0;j<32000;j++)
		{
			ts = myTimeSlice;
		}
	}
}


int userMain(int argc, char** argv)
{
	syncPrintf("Test starts.\n");
	TestThread t1(64,1), t2(4096,32), t3(1024,16), t4(4096,0);
	t1.start();

	t1.waitToComplete();

	syncPrintf("Test ends.\n");
	return 0;
}


