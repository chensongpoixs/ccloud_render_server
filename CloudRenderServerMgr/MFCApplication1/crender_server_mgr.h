/***********************************************************************************************
				created: 		2019-05-01

				author:			chensong

				purpose:		ccfg
************************************************************************************************/

#ifndef _C_RENDER_SERVER_MGR_H_
#define _C_RENDER_SERVER_MGR_H_
#include "cprocess_define.h"
#include <windows.h>
#include <processthreadsapi.h>
#include <Windows.h>
namespace chen {
	class crender_server_mgr
	{
	public:
		crender_server_mgr() 
			: m_process_type(EProcessNone)
			//, m_app_info()
			, m_timestamp(0)
		{}
		virtual ~crender_server_mgr();
	public:
		bool update();
		bool startup(const std::string & render_wan_port, const std::string &media_wan_ip, const std::string & media_wan_port);
		void destroy();
	public:
		void close_app();
		EProcessStateType get_render_server_status();
	protected:
	private:

		EProcessStateType		m_process_type;
		PROCESS_INFORMATION		m_app_info;
		uint64_t					m_timestamp;
	};
}

#endif //_C_RENDER_SERVER_MGR_H_