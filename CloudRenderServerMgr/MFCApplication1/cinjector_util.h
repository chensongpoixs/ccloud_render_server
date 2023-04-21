/***********************************************************************************************
created: 		2022-07-27

author:			chensong

purpose:		 cinjector_util
************************************************************************************************/

#ifdef _MSC_VER



//#include "cnet_type.h"

#include <Windows.h>
namespace chen {

	namespace cinjector_util {
	
	
		bool inject_library_full(DWORD process_id, const wchar_t* dll);
	}

}
#endif