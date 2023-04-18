/***********************************************************************************************
				created: 		2019-05-01

				author:			chensong

				purpose:		ccfg
************************************************************************************************/

#include "cutil.h"
namespace chen {
	std::string get_workdir(const std::string & path)
	{
		int count = 0;
		while (path[path.size() - 1 - count] != '\\' && path[path.size() - 1 - count] != '/')
		{
			++count;
		}
		++count;
		std::string work_path;
		//work_path.resize(path.size());
		for (size_t i = 0; i < path.size() - count; ++i)
		{
			work_path += (path[i]);
		}
		return work_path + "/";
	}
}