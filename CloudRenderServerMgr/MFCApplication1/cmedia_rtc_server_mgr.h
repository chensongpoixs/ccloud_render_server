/***********************************************************************************************
				created: 		2019-05-01

				author:			chensong

				purpose:		ccfg
************************************************************************************************/

#ifndef _C_MEDIA_RTC_SERVER_MGR_H_
#define _C_MEDIA_RTC_SERVER_MGR_H_
#include "cprocess_define.h"
#include "resource.h"
 
 namespace chen {



	 
	class cmedia_rtc_server_mgr
	{
	public:
		cmedia_rtc_server_mgr()
			: m_process_type(EProcessNone)
			, m_app_info()
			, m_timestamp(0)
		{}
		virtual ~cmedia_rtc_server_mgr();
	public:
		bool update();
		bool startup(const std ::string& wan_ip, const std::string& media_wan_port, const std::string& media_min_port, const std::string&  media_max_port, const std::string& media_timeouts);
		void destroy();
	public:
		void close_app();
		EProcessStateType get_media_server_status();
	protected:
	private:
		EProcessStateType		m_process_type;
		PROCESS_INFORMATION		m_app_info;
		uint64_t					m_timestamp;
	};
	//extern cmedia_rtc_server_mgr g_media_rtc_server_mgr;
 }


#endif // _C_MEDIA_RTC_SERVER_MGR_H_