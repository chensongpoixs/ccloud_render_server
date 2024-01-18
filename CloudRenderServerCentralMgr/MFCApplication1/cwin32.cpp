﻿/***********************************************************************************************
created: 		2022-12-27

author:			chensong

purpose:		win32

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
#include "cwin32.h"
#include "carraysize.h"
#include "cbyte_order.h"
#include "cdigit2str.h"
#if defined(_WIN32)


#include <winsock2.h>
#include <ws2tcpip.h>
#include <algorithm>

namespace chen {

	// Helper function declarations for inet_ntop/inet_pton.
	static const char* inet_ntop_v4(const void* src, char* dst, socklen_t size);
	static const char* inet_ntop_v6(const void* src, char* dst, socklen_t size);
	static int inet_pton_v4(const char* src, void* dst);
	static int inet_pton_v6(const char* src, void* dst);

	// Implementation of inet_ntop (create a printable representation of an
	// ip address). XP doesn't have its own inet_ntop, and
	// WSAAddressToString requires both IPv6 to be  installed and for Winsock
	// to be initialized.
	const char* win32_inet_ntop(int af,
		const void* src,
		char* dst,
		socklen_t size) {
		if (!src || !dst) {
			return nullptr;
		}
		switch (af) {
		case AF_INET: {
			return inet_ntop_v4(src, dst, size);
		}
		case AF_INET6: {
			return inet_ntop_v6(src, dst, size);
		}
		}
		return nullptr;
	}

	// As above, but for inet_pton. Implements inet_pton for v4 and v6.
	// Note that our inet_ntop will output normal 'dotted' v4 addresses only.
	int win32_inet_pton(int af, const char* src, void* dst) {
		if (!src || !dst) {
			return 0;
		}
		if (af == AF_INET) {
			return inet_pton_v4(src, dst);
		}
		else if (af == AF_INET6) {
			return inet_pton_v6(src, dst);
		}
		return -1;
	}

	// Helper function for inet_ntop for IPv4 addresses.
	// Outputs "dotted-quad" decimal notation.
	const char* inet_ntop_v4(const void* src, char* dst, socklen_t size) {
		if (size < INET_ADDRSTRLEN) {
			return nullptr;
		}
		const struct in_addr* as_in_addr =
			reinterpret_cast<const struct in_addr*>(src);
		snprintf(dst, size, "%d.%d.%d.%d", as_in_addr->S_un.S_un_b.s_b1,
			as_in_addr->S_un.S_un_b.s_b2, as_in_addr->S_un.S_un_b.s_b3,
			as_in_addr->S_un.S_un_b.s_b4);
		return dst;
	}

	// Helper function for inet_ntop for IPv6 addresses.
	const char* inet_ntop_v6(const void* src, char* dst, socklen_t size) {
		if (size < INET6_ADDRSTRLEN) {
			return nullptr;
		}
		const uint16_t* as_shorts = reinterpret_cast<const uint16_t*>(src);
		int runpos[8];
		int current = 1;
		int max = 0;
		int maxpos = -1;
		int run_array_size = arraysize(runpos);
		// Run over the address marking runs of 0s.
		for (int i = 0; i < run_array_size; ++i) {
			if (as_shorts[i] == 0) {
				runpos[i] = current;
				if (current > max) {
					maxpos = i;
					max = current;
				}
				++current;
			}
			else {
				runpos[i] = -1;
				current = 1;
			}
		}

		if (max > 0) {
			int tmpmax = maxpos;
			// Run back through, setting -1 for all but the longest run.
			for (int i = run_array_size - 1; i >= 0; i--) {
				if (i > tmpmax) {
					runpos[i] = -1;
				}
				else if (runpos[i] == -1) {
					// We're less than maxpos, we hit a -1, so the 'good' run is done.
					// Setting tmpmax -1 means all remaining positions get set to -1.
					tmpmax = -1;
				}
			}
		}

		char* cursor = dst;
		// Print IPv4 compatible and IPv4 mapped addresses using the IPv4 helper.
		// These addresses have an initial run of either eight zero-bytes followed
		// by 0xFFFF, or an initial run of ten zero-bytes.
		if (runpos[0] == 1 &&
			(maxpos == 5 || (maxpos == 4 && as_shorts[5] == 0xFFFF))) {
			*cursor++ = ':';
			*cursor++ = ':';
			if (maxpos == 4) {
				cursor += snprintf(cursor, INET6_ADDRSTRLEN - 2, "ffff:");
			}
			const struct in_addr* as_v4 =
				reinterpret_cast<const struct in_addr*>(&(as_shorts[6]));
			inet_ntop_v4(as_v4, cursor,
				static_cast<socklen_t>(INET6_ADDRSTRLEN - (cursor - dst)));
		}
		else {
			for (int i = 0; i < run_array_size; ++i) {
				if (runpos[i] == -1) {
					cursor += snprintf(cursor, INET6_ADDRSTRLEN - (cursor - dst), "%x",
						NetworkToHost16(as_shorts[i]));
					if (i != 7 && runpos[i + 1] != 1) {
						*cursor++ = ':';
					}
				}
				else if (runpos[i] == 1) {
					// Entered the run; print the colons and skip the run.
					*cursor++ = ':';
					*cursor++ = ':';
					i += (max - 1);
				}
			}
		}
		return dst;
	}

	// Helper function for inet_pton for IPv4 addresses.
	// |src| points to a character string containing an IPv4 network address in
	// dotted-decimal format, "ddd.ddd.ddd.ddd", where ddd is a decimal number
	// of up to three digits in the range 0 to 255.
	// The address is converted and copied to dst,
	// which must be sizeof(struct in_addr) (4) bytes (32 bits) long.
	int inet_pton_v4(const char* src, void* dst) {
		const int kIpv4AddressSize = 4;
		int found = 0;
		const char* src_pos = src;
		unsigned char result[kIpv4AddressSize] = { 0 };

		while (*src_pos != '\0') {
			// strtol won't treat whitespace characters in the begining as an error,
			// so check to ensure this is started with digit before passing to strtol.
			if (!isdigit(*src_pos)) {
				return 0;
			}
			char* end_pos;
			long value = strtol(src_pos, &end_pos, 10);
			if (value < 0 || value > 255 || src_pos == end_pos) {
				return 0;
			}
			++found;
			if (found > kIpv4AddressSize) {
				return 0;
			}
			result[found - 1] = static_cast<unsigned char>(value);
			src_pos = end_pos;
			if (*src_pos == '.') {
				// There's more.
				++src_pos;
			}
			else if (*src_pos != '\0') {
				// If it's neither '.' nor '\0' then return fail.
				return 0;
			}
		}
		if (found != kIpv4AddressSize) {
			return 0;
		}
		memcpy(dst, result, sizeof(result));
		return 1;
	}

	// Helper function for inet_pton for IPv6 addresses.
	int inet_pton_v6(const char* src, void* dst) {
		// sscanf will pick any other invalid chars up, but it parses 0xnnnn as hex.
		// Check for literal x in the input string.
		const char* readcursor = src;
		char c = *readcursor++;
		while (c) {
			if (c == 'x') {
				return 0;
			}
			c = *readcursor++;
		}
		readcursor = src;

		struct in6_addr an_addr;
		memset(&an_addr, 0, sizeof(an_addr));

		uint16_t* addr_cursor = reinterpret_cast<uint16_t*>(&an_addr.s6_addr[0]);
		uint16_t* addr_end = reinterpret_cast<uint16_t*>(&an_addr.s6_addr[16]);
		bool seencompressed = false;

		// Addresses that start with "::" (i.e., a run of initial zeros) or
		// "::ffff:" can potentially be IPv4 mapped or compatibility addresses.
		// These have dotted-style IPv4 addresses on the end (e.g. "::192.168.7.1").
		if (*readcursor == ':' && *(readcursor + 1) == ':' &&
			*(readcursor + 2) != 0) {
			// Check for periods, which we'll take as a sign of v4 addresses.
			const char* addrstart = readcursor + 2;
			if (strchr(addrstart, '.')) {
				const char* colon = strchr(addrstart, ':');
				if (colon) {
					uint16_t a_short;
					int bytesread = 0;
					if (sscanf(addrstart, "%hx%n", &a_short, &bytesread) != 1 ||
						a_short != 0xFFFF || bytesread != 4) {
						// Colons + periods means has to be ::ffff:a.b.c.d. But it wasn't.
						return 0;
					}
					else {
						an_addr.s6_addr[10] = 0xFF;
						an_addr.s6_addr[11] = 0xFF;
						addrstart = colon + 1;
					}
				}
				struct in_addr v4;
				if (inet_pton_v4(addrstart, &v4.s_addr)) {
					memcpy(&an_addr.s6_addr[12], &v4, sizeof(v4));
					memcpy(dst, &an_addr, sizeof(an_addr));
					return 1;
				}
				else {
					// Invalid v4 address.
					return 0;
				}
			}
		}

		// For addresses without a trailing IPv4 component ('normal' IPv6 addresses).
		while (*readcursor != 0 && addr_cursor < addr_end) {
			if (*readcursor == ':') {
				if (*(readcursor + 1) == ':') {
					if (seencompressed) {
						// Can only have one compressed run of zeroes ("::") per address.
						return 0;
					}
					// Hit a compressed run. Count colons to figure out how much of the
					// address is skipped.
					readcursor += 2;
					const char* coloncounter = readcursor;
					int coloncount = 0;
					if (*coloncounter == 0) {
						// Special case - trailing ::.
						addr_cursor = addr_end;
					}
					else {
						while (*coloncounter) {
							if (*coloncounter == ':') {
								++coloncount;
							}
							++coloncounter;
						}
						// (coloncount + 1) is the number of shorts left in the address.
						// If this number is greater than the number of available shorts, the
						// address is malformed.
						if (coloncount + 1 > addr_end - addr_cursor) {
							return 0;
						}
						addr_cursor = addr_end - (coloncount + 1);
						seencompressed = true;
					}
				}
				else {
					++readcursor;
				}
			}
			else {
				uint16_t word;
				int bytesread = 0;
				if (sscanf(readcursor, "%4hx%n", &word, &bytesread) != 1) {
					return 0;
				}
				else {
					*addr_cursor = HostToNetwork16(word);
					++addr_cursor;
					readcursor += bytesread;
					if (*readcursor != ':' && *readcursor != '\0') {
						return 0;
					}
				}
			}
		}

		if (*readcursor != '\0' || addr_cursor < addr_end) {
			// Catches addresses too short or too long.
			return 0;
		}
		memcpy(dst, &an_addr, sizeof(an_addr));
		return 1;
	}

	bool Utf8ToWindowsFilename(const std::string& utf8, std::wstring* filename) {
		// TODO: Integrate into fileutils.h
		// TODO: Handle wide and non-wide cases via TCHAR?
		// TODO: Skip \\?\ processing if the length is not > MAX_PATH?
		// TODO: Write unittests

		// Convert to Utf16
		int wlen =
			::MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(),
				static_cast<int>(utf8.length() + 1), nullptr, 0);
		if (0 == wlen) {
			return false;
		}
		wchar_t* wfilename = STACK_ARRAY(wchar_t, wlen);
		if (0 == ::MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(),
			static_cast<int>(utf8.length() + 1), wfilename,
			wlen)) {
			return false;
		}
		// Replace forward slashes with backslashes
		std::replace(wfilename, wfilename + wlen, L'/', L'\\');
#if defined(WINUWP)
		// WinUWP sandboxed store applications require the paths to remain as
		// relative paths.
		filename->assign(wfilename);
#else
		// Convert to complete filename
		DWORD full_len = ::GetFullPathNameW(wfilename, 0, nullptr, nullptr);
		if (0 == full_len) {
			return false;
		}
		wchar_t* filepart = nullptr;
		wchar_t* full_filename = STACK_ARRAY(wchar_t, full_len + 6);
		wchar_t* start = full_filename + 6;
		if (0 == ::GetFullPathNameW(wfilename, full_len, start, &filepart)) {
			return false;
		}
		// Add long-path prefix
		const wchar_t kLongPathPrefix[] = L"\\\\?\\UNC";
		if ((start[0] != L'\\') || (start[1] != L'\\')) {
			// Non-unc path:     <pathname>
			//      Becomes: \\?\<pathname>
			start -= 4;
			//RTC_DCHECK(start >= full_filename);
			memcpy(start, kLongPathPrefix, 4 * sizeof(wchar_t));
		}
		else if (start[2] != L'?') {
			// Unc path:       \\<server>\<pathname>
			//  Becomes: \\?\UNC\<server>\<pathname>
			start -= 6;
			//RTC_DCHECK(start >= full_filename);
			memcpy(start, kLongPathPrefix, 7 * sizeof(wchar_t));
		}
		else {
			// Already in long-path form.
		}
		filename->assign(start);
#endif  // defined(WINUWP)

		return true;
	}

	// Windows UWP applications cannot obtain versioning information from
	// the sandbox with intention (as behehaviour based on OS versioning rather
	// than feature discovery / compilation flags is discoraged and Windows
	// 10 is living continously updated version unlike previous versions
	// of Windows).
#if !defined(WINUWP)

	bool GetOsVersion(int* major, int* minor, int* build) {
		OSVERSIONINFO info = { 0 };
		info.dwOSVersionInfoSize = sizeof(info);
		if (GetVersionEx(&info)) {
			if (major)
				*major = info.dwMajorVersion;
			if (minor)
				*minor = info.dwMinorVersion;
			if (build)
				*build = info.dwBuildNumber;
			return true;
		}
		return false;
	}

	bool GetCurrentProcessIntegrityLevel(int* level) {
		bool ret = false;
		HANDLE process = ::GetCurrentProcess(), token;
		if (OpenProcessToken(process, TOKEN_QUERY | TOKEN_QUERY_SOURCE, &token)) {
			DWORD size;
			if (!GetTokenInformation(token, TokenIntegrityLevel, nullptr, 0, &size) &&
				GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
				char* buf = STACK_ARRAY(char, size);
				TOKEN_MANDATORY_LABEL* til =
					reinterpret_cast<TOKEN_MANDATORY_LABEL*>(buf);
				if (GetTokenInformation(token, TokenIntegrityLevel, til, size, &size)) {
					DWORD count = *GetSidSubAuthorityCount(til->Label.Sid);
					*level = *GetSidSubAuthority(til->Label.Sid, count - 1);
					ret = true;
				}
			}
			CloseHandle(token);
		}
		return ret;
	}

#endif  // !defined(WINUWP)

}

#endif // #if defined(_WIN32)