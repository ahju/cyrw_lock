#include <stdio.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include "cyrw_lock.h"
using namespace std;

int g_count = 0;
cyrw_lock g_lock;

int g_readcount = 2;
int g_writecount = 2; 

void *readthread(void *parm)
{
	int *num = (int *)parm;
	while(1)
	{
		g_lock.read_lock();
		printf("thread %d read g_count=%d-----------------\n", *num, g_count);
		g_lock.read_unlock();
		//usleep(1);
	}
}

void *writethread(void *parm)
{
	int *num = (int *)parm;
	while(1)
	{
		g_lock.write_lock();
		g_count++;
		printf("+++++++++++++++++thread %d write g_count=%d\n", *num, g_count);
		g_lock.write_unlock();
		//usleep(1);
	}
}

main()
{
	int *readnum = new int[g_readcount];
	for(int i=0;i<g_readcount; i++)
	{
		pthread_t read_pid;
		readnum[i] = i;
		if(pthread_create(&read_pid,NULL,readthread,&readnum[i]))
		{
			exit(1);
		}
	}

	int *writenum = new int[g_writecount];
	for(int i=0;i<g_writecount; i++)
	{
		pthread_t write_pid;
		writenum[i] = i;
		if(pthread_create(&write_pid,NULL,writethread,&writenum[i]))
		{
			exit(1);
		}
	}
	
	sleep(360);
}
