/******************************************************************* 
 *  Copyright(c) 2001-2016 Changyou 17173
 *  All rights reserved. 
 *   
 *  �ļ�����: cyrw_lock.cpp
 *  ��Ҫ����: ��д��������ʹ�ÿ��Զ����У�дʱ�ż���
 *  
 *  
 *   
 *  ��������: 2016-01-26
 *  ����: ����
 *  ˵��: �����ļ�
 *	1.
 *	
 *  ��������: 
 *	1.���ڶ�������Ȼ����������˸߲���ʱ�Ի���ƿ��
 *  2.��д˳�򲢲��Ŷӣ���˿��ܻ����һֱ�Ƕ�����дһֱ�ڵȴ�
 *
 *  �ο���http://blog.csdn.net/raomeng1/article/details/7685421
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
