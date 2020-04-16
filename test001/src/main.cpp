#include<stdio.h>
#include <unistd.h>
//#include <string.h>
#include "YAThread.h"

void* task(void * str){

//	sleep(1);
	printf((char*)str);
}

int main(int argc, char const *argv[])
{
      int loop = 0;
	   YAThread  th = YAThread();
	   th.createFixedPools(1,100,2048);
	 	while (loop<10000)
		 {
			 loop++;
			 sleep(3);
			 char str[] = "Helloworld-----------------------------------------------------------33\n";
	 		 printf("put task  0x%x\n",loop);
			 th.threadpool_add_task(task,str);
			
		 }
		return 0;
}
