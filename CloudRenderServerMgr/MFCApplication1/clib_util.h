/***********************************************************************************************
created: 		2019-05-12

author:			chensong

purpose:		clib_util
************************************************************************************************/

#ifndef _C_LIB_UTIL_H_
#define _C_LIB_UTIL_H_
#include <thread>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <iostream>
namespace chen
{
	 
	void csleep(unsigned int milliseconds)
	{
		
		std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
	}
}
#endif // !#define _C_LIB_UTIL_H_

