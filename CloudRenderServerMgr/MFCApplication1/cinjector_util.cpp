/***********************************************************************************************
created: 		2022-07-27

author:			chensong

purpose:		 cinjector_util
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