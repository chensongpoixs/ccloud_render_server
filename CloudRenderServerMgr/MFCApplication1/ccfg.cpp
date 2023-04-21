/***********************************************************************************************
				created: 		2019-05-01

				author:			chensong

				purpose:		ccfg
************************************************************************************************/
#include "ccfg.h"
#include "clog.h"
namespace chen {
	ccfg g_cfg;
	
	ccfg::ccfg()
	{
	}


	ccfg::~ccfg()
	{
	}
	bool ccfg::init(const char * file_name)
	{
		if (!cconfig::init(ECI_Max, file_name))
		{
			return false;
		}
		// 默认值
		 
//#if _DEBUG
//		set_uint32(ECI_LogLevel, "log_level", ELogLevel_Num);
//#endif // _DEBUG

		
		set_int32(ECI_TimeAdjust, "time_adjust", 0);
		
		 
		 

		set_uint32(ECI_LogLevel, "log_level", ELogLevel_Num);

		 

		set_string(ECI_GmCmdIp, "gm_cmd_ip", "0.0.0.0");
		set_uint32(ECI_GmCmdPort, "gm_cmd_port", 9800);


		set_string(ECI_GlobalDbHost, "global_db_host", "127.0.0.1");
		set_string(ECI_GlobalDbUsername, "global_db_user", "root");
		set_string(ECI_GlobalDbPassword, "global_db_psd", "");
		set_string(ECI_GlobalDbName, "global_db_name", "global_table");
		set_uint32(ECI_GlobalDbPort, "global_db_port", 3306);

		//配置表的值
		load_cfg_file();

		return true;
	}
	void ccfg::destroy()
	{
		cconfig::destroy();
	}
}//namespace chen 
