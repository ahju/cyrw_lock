#ifndef __CYRW_LOCK_H
#define __CYRW_LOCK_H

#include <iostream>
#include <string.h>
#include <stdlib.h>
	

class cyrw_lock
{
private:
	pthread_mutex_t m_read_mux;
	pthread_mutex_t m_write_mux;
	int m_read_count;
private:
	//拷贝构造函数，不允许拷贝
	cyrw_lock & operator = (const cyrw_lock &); 
public:
	cyrw_lock();
	~cyrw_lock();
	void read_lock();
	void read_unlock();
	void write_lock();
	void write_unlock();
};
	
#endif
