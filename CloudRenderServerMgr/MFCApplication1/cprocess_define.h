/***********************************************************************************************
				created: 		2019-05-01

				author:			chensong

				purpose:		ccfg
************************************************************************************************/

#ifndef _C_PROCESS_DEFINE_H_
#define _C_PROCESS_DEFINE_H_
#include <iostream>
#include "pch.h"
//
 namespace chen {
//

	enum EProcessStateType
	{
		EProcessNone = 0,
		EProcessStart,
		EProcessActive,
		EProcessKill
	};

 }

#endif // _C_PROCESS_DEFINE_H_
