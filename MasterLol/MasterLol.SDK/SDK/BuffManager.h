#pragma once
#include "stdafx.h"
#include "Offsets.h"
#include "StaticEnums.h"
#include "Names.h"

class BuffVTable {
public:
	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual char charFn1();
	virtual int intFn3();
	virtual void Function8();
	virtual void Function9();
	virtual void Function10();
	virtual signed int sigIntFn1();
	virtual void Function12();
	virtual bool boolFn2();
	virtual int intFn1();
	virtual void Function15();
	virtual void Function16();
	virtual void Function17();
	virtual void Function18();
	virtual bool boolFn1();
};

class BuffInstance
{
public:
	char pad_0004[156]; //0x0004
	char** mName; //0x009C

	inline BuffVTable * GetVirtual() {
		return reinterpret_cast<BuffVTable*>(this);
	}
}; //Size: 0x0038

class BuffNode
{
public:
	char pad_0000[8]; //0x0000
	class BuffInstance* mBuffInstance; //0x0008
	float mStartTime; //0x000C
	float mEndTime; //0x0010
	char pad_0014[92]; //0x0014
	uint32_t mBuffCount; //0x0070
}; //Size: 0x0184

class BuffManager {

public:
	char pad_0000[16]; //0x0000
	class BuffNode** mBuffArray; //0x0010
	class BuffNode* mEnd; //0x0014

	inline int GetSize() {
		return ((DWORD)this->mEnd - (DWORD)this->mBuffArray) / 0x4;
	}

	inline BuffNode* GetBuffFromName(const char* name) {
		int size = this->GetSize();
		for (int i = 0; i < size; ++i)
		{
			BuffNode* currBuff = this->mBuffArray[i];
			if (!currBuff)
				continue;
			BuffInstance* currBuffInstance = currBuff->mBuffInstance;
			if ((DWORD)currBuffInstance < 0x10000000)
				continue;

			char buffName[50];
			sprintf(buffName, "%s", currBuffInstance->mName);
			if (strcmp(name, buffName) == 0) {
				return currBuff;
			}
		}
		return nullptr;
	}
};
