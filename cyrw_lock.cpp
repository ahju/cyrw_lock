/******************************************************************* 
 *  Copyright(c) 2001-2016 Changyou 17173
 *  All rights reserved. 
 *   
 *  文件名称: cyrw_lock.cpp
 *  简要描述: 读写互斥锁，使得可以读并行，写时才加锁
 *  
 *  
 *   
 *  创建日期: 2016-01-26
 *  作者: 阿祖
 *  说明: 创建文件
 *	1.
 *	
 *  存在问题: 
 *	1.对于读变量仍然存在锁，因此高并发时仍会有瓶颈
 *  2.读写顺序并不排队，因此可能会出现一直是读，而写一直在等待
 *
 *  参考：http://blog.csdn.net/raomeng1/article/details/7685421
 *   
 ******************************************************************/

#include "cyrw_lock.h"
	

cyrw_lock::cyrw_lock()
{
	m_read_count = 0;
	pthread_mutex_init(&m_read_mux,NULL);
	pthread_mutex_init(&m_write_mux,NULL);
}

cyrw_lock::~cyrw_lock()
{
}

void cyrw_lock::read_lock()
{
	pthread_mutex_lock(&m_read_mux);
	if(++m_read_count == 1)
	{
		pthread_mutex_lock(&m_write_mux);
	}
	pthread_mutex_unlock(&m_read_mux);
}


void cyrw_lock::read_unlock()
{
	pthread_mutex_lock(&m_read_mux);
	if(--m_read_count == 0)
	{
		pthread_mutex_unlock(&m_write_mux);
	}
	pthread_mutex_unlock(&m_read_mux);
}

void cyrw_lock::write_lock()
{
	pthread_mutex_lock(&m_write_mux);
}

void cyrw_lock::write_unlock()
{
	pthread_mutex_unlock(&m_write_mux);
}
