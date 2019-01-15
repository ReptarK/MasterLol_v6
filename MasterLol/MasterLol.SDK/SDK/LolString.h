#pragma once
class LolString
{
	char        _content[0x10];
	int         _contentLength = 0;
	int         _maxContentLength = 0;

public:

	operator const char*(void) 
	{
		return Get();
	}
	operator std::string(void)
	{
		return std::string(Get());
	}
	char* Get(void)
	{
		if (DWORD(this) <= 0x1000)
			return (char*)"Unknown";

		return _maxContentLength >= 0x10
			? *reinterpret_cast< char** >(_content)
			: _content;
	}


private:
};


