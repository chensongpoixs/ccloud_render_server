/***********************************************************************************************
created: 		2022-07-27

author:			chensong

purpose:		 cinjector_util
输赢不重要，答案对你们有什么意义才重要。

光阴者，百代之过客也，唯有奋力奔跑，方能生风起时，是时代造英雄，英雄存在于时代。或许世人道你轻狂，可你本就年少啊。 看护好，自己的理想和激情。


我可能会遇到很多的人，听他们讲好2多的故事，我来写成故事或编成歌，用我学来的各种乐器演奏它。
然后还可能在一个国家遇到一个心仪我的姑娘，她可能会被我帅气的外表捕获，又会被我深邃的内涵吸引，在某个下雨的夜晚，她会全身淋透然后要在我狭小的住处换身上的湿衣服。
3小时候后她告诉我她其实是这个国家的公主，她愿意向父皇求婚。我不得已告诉她我是穿越而来的男主角，我始终要回到自己的世界。
然后我的身影慢慢消失，我看到她眼里的泪水，心里却没有任何痛苦，我才知道，原来我的心被丢掉了，我游历全世界的原因，就是要找回自己的本心。
于是我开始有意寻找各种各样失去心的人，我变成一块砖头，一颗树，一滴水，一朵白云，去听大家为什么会失去自己的本心。
我发现，刚出生的宝宝，本心还在，慢慢的，他们的本心就会消失，收到了各种黑暗之光的侵蚀。
从一次争论，到嫉妒和悲愤，还有委屈和痛苦，我看到一只只无形的手，把他们的本心扯碎，蒙蔽，偷走，再也回不到主人都身边。
我叫他本心猎手。他可能是和宇宙同在的级别 但是我并不害怕，我仔细回忆自己平淡的一生 寻找本心猎手的痕迹。
沿着自己的回忆，一个个的场景忽闪而过，最后发现，我的本心，在我写代码的时候，会回来。
安静，淡然，代码就是我的一切，写代码就是我本心回归的最好方式，我还没找到本心猎手，但我相信，顺着这个线索，我一定能顺藤摸瓜，把他揪出来。


************************************************************************************************/
#ifdef _MSC_VER

#include "cinjector_util.h"
#include <cstdint>
//#include "clog.h"
#include <strstream>
#include <sstream>
#include <iostream>
namespace chen {

	namespace cinjector_util {


		typedef HANDLE(WINAPI* create_remote_thread_t)(HANDLE, LPSECURITY_ATTRIBUTES, SIZE_T, LPTHREAD_START_ROUTINE, LPVOID, DWORD, LPDWORD);
		typedef BOOL(WINAPI* write_process_memory_t)(HANDLE, LPVOID, LPCVOID, SIZE_T, SIZE_T*);
		typedef LPVOID(WINAPI* virtual_alloc_ex_t)(HANDLE, LPVOID, SIZE_T, DWORD, DWORD);
		typedef BOOL(WINAPI* virtual_free_ex_t)(HANDLE, LPVOID, SIZE_T, DWORD);
		typedef HANDLE(WINAPI * open_process_proc_t)(DWORD, BOOL, DWORD);






		




#define LOWER_HALFBYTE(x) ((x)&0xF)
#define UPPER_HALFBYTE(x) (((x) >> 4) & 0xF)

		static void deobfuscate_str(char* str, uint64_t val)
		{
			uint8_t* dec_val = (uint8_t*)&val;
			int i = 0;

			while (*str != 0) {
				int pos = i / 2;
				bool bottom = (i % 2) == 0;
				uint8_t* ch = (uint8_t*)str;
				uint8_t xor1 = bottom ? LOWER_HALFBYTE(dec_val[pos]) : UPPER_HALFBYTE(dec_val[pos]);

				*ch ^= xor1;

				if (++i == sizeof(uint64_t) * 2)
				{
					i = 0;
				}

				str++;
			}
		}

		void* ms_get_obfuscated_func(HMODULE module, const char* str, uint64_t val)
		{
			char new_name[128];
			strcpy(new_name, str);
			deobfuscate_str(new_name, val);
			return GetProcAddress(module, new_name);
		}
		static HMODULE kernel32 = NULL;
		static create_remote_thread_t create_remote_thread = NULL;
		static write_process_memory_t write_process_memory = NULL;
		static virtual_alloc_ex_t virtual_alloc_ex = NULL;
		static virtual_free_ex_t virtual_free_ex = NULL;
		static FARPROC load_library_w = NULL;
		//static open_process_proc_t open_process_proc = NULL;

		static inline HANDLE open_process(DWORD desired_access, bool inherit_handle, DWORD process_id)
		{
			//typedef HANDLE(WINAPI * open_process_proc_t)(DWORD, BOOL, DWORD);
			open_process_proc_t open_process_proc = (open_process_proc_t)ms_get_obfuscated_func(GetModuleHandleW(L"KERNEL32"),
				"HxjcQrmkb|~", 0xc82efdf78201df87);

			return open_process_proc(desired_access, inherit_handle, process_id);
		}


		bool init(const char* create_remote_thread_obf, uint64_t obf1,
			const char* write_process_memory_obf, uint64_t obf2,
			const char* virtual_alloc_ex_obf, uint64_t obf3,
			const char* virtual_free_ex_obf, uint64_t obf4,
			const char* load_library_w_obf, uint64_t obf5)
		{
			if (kernel32 && create_remote_thread &&write_process_memory &&virtual_alloc_ex &&virtual_free_ex &&load_library_w /*&& open_process_proc*/)
			{
				return true;
			}

			if (!kernel32)
			{
				//NORMAL_LOG("kernel32.dll load ...");
				kernel32 = GetModuleHandleW(L"KERNEL32");
				if (!kernel32)
				{
					//WARNING_EX_LOG("GetModuleHandleW(KERNEL32) load  failed !!!");
					return false;
				}
				
			}
			
			if (!create_remote_thread)
			{
				
				create_remote_thread = (create_remote_thread_t)ms_get_obfuscated_func(
					kernel32, create_remote_thread_obf, obf1);
				if (!create_remote_thread)
				{
					//WARNING_EX_LOG("not find create_remote_thread");
					return false;
				}
			}

			if (!write_process_memory)
			{
				
				write_process_memory = (write_process_memory_t)ms_get_obfuscated_func(
					kernel32, write_process_memory_obf, obf2);
				if (!write_process_memory)
				{
					//WARNING_EX_LOG("not find write_process_memory");
					return false;
				}
			}
			if (!virtual_alloc_ex)
			{
				
				virtual_alloc_ex = (virtual_alloc_ex_t)ms_get_obfuscated_func(
					kernel32, virtual_alloc_ex_obf, obf3);
				if (!virtual_alloc_ex)
				{
					//WARNING_EX_LOG("not find virtual_alloc_ex");
					return false;
				}
			}
			if (!virtual_free_ex)
			{
				
				virtual_free_ex = (virtual_free_ex_t)ms_get_obfuscated_func(
					kernel32, virtual_free_ex_obf, obf4);
				if (!virtual_free_ex)
				{///
					//WARNING_EX_LOG("not find virtual_free_ex");
					return false;
				}
			}
			if (!load_library_w)
			{
				
				load_library_w = (FARPROC)ms_get_obfuscated_func(
					kernel32, load_library_w_obf, obf5);
				if (!load_library_w)
				{
					//WARNING_EX_LOG("not find load_library_w");
					return false;
				}
			}
			/*if (!open_process_proc)
			{
				open_process_proc = (open_process_proc_t)ms_get_obfuscated_func(GetModuleHandleW(L"KERNEL32"),
					"HxjcQrmkb|~", 0xc82efdf78201df87);
			}*/
			//if ( create_remote_thread && write_process_memory &&virtual_alloc_ex &&virtual_free_ex &&load_library_w /*&& open_process_proc*/)
			//{
			//	
			//	return true;
			//}
			
			//NORMAL_EX_LOG(" find [create_remote_thread = %p][write_process_memory = %p][virtual_alloc_ex = %p][virtual_free_ex = %p][load_library_w = %p] ", create_remote_thread, write_process_memory, virtual_alloc_ex, virtual_free_ex, load_library_w/*, open_process_proc*/);
			return true;
		}

		int inject_library(HANDLE process, const wchar_t* dll)
		{
			int ret = -4;
			size_t size = 0;
			DWORD last_error = 0;
			bool success = false;
			void* mem = NULL;
			HANDLE thread = NULL;
			size_t written_size;
			DWORD thread_id;

			/* -------------------------------- */
			/*WCHAR load_path[MAX_PATH] = L"";
			
			char *cstr = "string to convert";

			std::wstringstream temp_path;

			temp_path << dll;
			GetCurrentDirectoryW(MAX_PATH, load_path);
			wcscat_s(load_path, L"\\");
			wcscat_s(load_path, L"hook_test64.dll");*/
			size = (wcslen(dll) + 1) * sizeof(wchar_t);
			mem = virtual_alloc_ex(process, NULL, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
			if (!mem) 
			{
				//WARNING_EX_LOG("virtual_alloc_ex failed !!!");
				goto fail;
			}

			success = write_process_memory(process, mem, dll, size, &written_size);
			if (!success) 
			{
				//WARNING_EX_LOG("write_process_memory failed !!!");
				goto fail;
			}


			thread = create_remote_thread(process, NULL, 0, (LPTHREAD_START_ROUTINE)load_library_w, mem, 0, &thread_id);
			if (!thread) 
			{
				//WARNING_EX_LOG("create_remote_thread failed !!!");
				goto fail;
			}

			if (WaitForSingleObject(thread, 5) == WAIT_OBJECT_0) 
			{
				DWORD code;
				GetExitCodeThread(thread, &code);
				ret = (code != 0) ? 0 : -1;

				SetLastError(0);
			}




		fail:
			if (ret == -4) 
			{
				last_error = GetLastError();
			}
			if (thread) 
			{
				CloseHandle(thread);
			}
			if (mem) 
			{
				virtual_free_ex(process, mem, 0, MEM_RELEASE);
			}
			if (last_error != 0)
			{
				SetLastError(last_error);
			}

			return ret;
			 
		}


		// 
		bool inject_library_full(DWORD process_id, const wchar_t* dll)
		{
			// TODO@chensong 2022-07-29  debug info 
			/*if (false ==*/ init("E}mo|d[cefubWk~bgk",
				0x7c3371986918e8f6, "Rqbr`T{cnor{Bnlgwz",
				0x81bf81adc9456b35, "]`~wrl`KeghiCt",
				0xadc6a7b9acd73c9b, "Zh}{}agHzfd@{",
				0x57135138eb08ff1c, "DnafGhj}l~sX",
				0x350bfacdf81b2018/*)*/);
			/*{
				
				return  false;
			}*/

			HANDLE process = open_process(PROCESS_ALL_ACCESS, false, process_id);
			if (!process)
			{
				
				//WARNING_EX_LOG("not open process id = %u", process_id);
				return false;
			}
			if (kernel32 && create_remote_thread &&write_process_memory &&virtual_alloc_ex &&virtual_free_ex &&load_library_w /*&& open_process_proc*/)
			{
				
				int ret = inject_library(process, dll);
				if (ret == 0)
				{
				//	NORMAL_LOG("inject processid = %u, ok ", process_id);
				}
				return ret == 0;
			}
			//WARNING_EX_LOG("not find kernel32 function !!!");
			return false;
		}
	}

}
#endif