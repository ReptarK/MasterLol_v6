#pragma once
#include "stdafx.h"
#include "singleton.hpp"
#include "math/Vector.hpp"
#include "detours/detours.h"

#pragma region CONVENTION_TYPES
enum class convention_type
{
	stdcall_t,
	cdecl_t,
	fastcall_t,
	winapi_t,
	thiscall_r
};

template <convention_type tp, typename retn, typename convention, typename ...args>
struct convention;

template <typename retn, typename ...args>
struct convention<convention_type::stdcall_t, retn, args...>
{
	typedef retn(__stdcall *type)(args ...);
};

template <typename retn, typename ...args>
struct convention<convention_type::cdecl_t, retn, args...>
{
	typedef retn(__cdecl *type)(args ...);
};

template <typename retn, typename ...args>
struct convention<convention_type::fastcall_t, retn, args...>
{
	typedef retn(__fastcall *type)(args ...);
};

template <typename retn, typename ...args>
struct convention<convention_type::winapi_t, retn, args...>
{
	typedef retn(WINAPI *type)(args ...);
};

template <typename retn, typename ...args>
struct convention<convention_type::thiscall_r, retn, args...>
{
	typedef retn(__thiscall *type)(args ...);
};
#pragma endregion

typedef struct DetourEntry
{
	void* orig;
	void* detour;

	DetourEntry(void* o, void* d) : orig(o), detour(d) {}
} DetourEntry;

class HooksManager
	: public Singleton<HooksManager>
{
	friend class Singleton<HooksManager>;
	HooksManager(){}
	~HooksManager(){}

public:
	void AddHook(DetourEntry detourEntry)
	{
		detourList.push_back(detourEntry);
	}

	bool RemoveHooks() const 
	{
		for (auto hookEntry : detourList)
		{
			if (!DetourRemove((PBYTE)hookEntry.orig, (PBYTE)hookEntry.detour))
			{
				std::cout << "Error : Failed to detatch hook" << std::endl;
			}
		}
		return true;
	}
private:
	std::vector<DetourEntry> detourList;
};

template <convention_type tp, typename retn, typename ...args >
class MAKE_HOOK
{
	typedef typename convention<tp, retn, args...>::type type;
	bool _isApplied;

public:
	type _orig;
	void* _detour;

	MAKE_HOOK() : _isApplied(false), _orig(0), _detour(0) {}

	template <typename T>
	MAKE_HOOK(DWORD pFunc, type detour)
	{
		//Apply(pFunc, detour);
	}

	~MAKE_HOOK()
	{
		Remove();
	}

	void Apply(DWORD pFunc, void* detourFunc)
	{
		_detour = detourFunc;
		_orig = (type)DetourFunction((PBYTE)pFunc, (PBYTE)detourFunc);
		_isApplied = _orig != nullptr;
		// Add detour to detour list
		HooksManager::Get().AddHook(DetourEntry((void*)_orig, detourFunc));
	}


	bool Remove()
	{
		if (!_isApplied)
			return false;

		_isApplied = false;
		DetourRemove((PBYTE)_orig, (PBYTE)_detour);
		return true;
	}

	retn CallOriginal(args ... p)
	{
		return _orig(p...);
	}

	retn CallDetour(args ... p)
	{
		return _detour(p...);
	}

	bool IsApplied() const
	{
		return _isApplied;
	}
};


