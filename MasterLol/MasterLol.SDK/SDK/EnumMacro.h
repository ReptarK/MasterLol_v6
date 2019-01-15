#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

// Search and remove whitespace from both ends of the string
static std::string TrimEnumString(const std::string &s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && isspace(*it)) { it++; }
	std::string::const_reverse_iterator rit = s.rbegin();
	while (rit.base() != it && isspace(*rit)) { rit++; }
	return std::string(it, rit.base());
}

static void SplitEnumArgs(const char* szArgs, std::string Array[], int nMax)
{
	std::stringstream ss(szArgs);
	std::string strSub;
	int nIdx = 0;
	while (ss.good() && (nIdx < nMax)) {
		getline(ss, strSub, ',');
		Array[nIdx] = TrimEnumString(strSub);
		nIdx++;
	}
};
// This will to define an enum that is wrapped in a namespace of the same name along with ToString(), FromString(), and COUNT
#define DECLARE_ENUM(ename, ...) \
    namespace ename { \
        enum ename { __VA_ARGS__, COUNT }; \
        static std::string _Strings[COUNT]; \
        static const char* ToString(ename e) { \
            if (_Strings[0].empty()) { SplitEnumArgs(#__VA_ARGS__, _Strings, COUNT); } \
            return _Strings[e].c_str(); \
        } \
        static ename FromString(const std::string& strEnum) { \
            if (_Strings[0].empty()) { SplitEnumArgs(#__VA_ARGS__, _Strings, COUNT); } \
            for (int i = 0; i < COUNT; i++) { if (_Strings[i] == strEnum) { return (ename)i; } } \
            return COUNT; \
        } \
    }
