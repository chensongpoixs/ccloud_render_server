/***********************************************************************************************
			created: 		2019-05-01

			author:			chensong

			purpose:		ccfg
************************************************************************************************/
#ifndef _C_CFG_H_
#define _C_CFG_H_
//#include "cconfig.h"
#include "cconfig.h"
//#include "csingleton.h"


namespace chen {

 
 

	enum ECNGIndex
	{

		ECI_TimeZone,
		ECI_TimeAdjust,
		  
		ECI_LogLevel,
		


		ECI_GmCmdIp,
		ECI_GmCmdPort,
		ECI_GlobalDbHost,
		ECI_GlobalDbPort,
		ECI_GlobalDbName,
		ECI_GlobalDbUsername,
		ECI_GlobalDbPassword,
		 
		ECI_Max,
	};
	class ccfg : public cconfig
	{
	public:
	    explicit	ccfg();
		virtual	~ccfg();
	public:
		bool init(const char *file_name);
		void destroy();
	};

	extern 	ccfg g_cfg;
} //namespace chen

#endif //!#define _C_CFG_H_

