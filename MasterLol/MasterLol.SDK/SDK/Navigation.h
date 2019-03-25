#pragma once
#include <vector>
#include "math/Vector.hpp"

class PathManager
{
public:
	int32_t mCurrentPathId; //0x0000
	char pad_0004[4]; //0x0004
	Vector3 mStartPosition; //0x0008
	Vector3 mEndPosition; //0x0014
	Vector3* mPath; //0x0020
	Vector3* mEnd; //0x0024

	inline int GetSize() {
		return ((DWORD)this->mEnd - (DWORD)this->mPath) / (sizeof(Vector3));
	}

	inline float GetPathLength() {
		float length = 0;
		for (int i = 0; i < this->GetSize(); ++i)
			length += this->mPath[i + 1].DistTo(this->mPath[i]);

		return length;
	}

	inline std::vector<Vector3> GetPathList() {
		std::vector<Vector3> result = std::vector<Vector3>();
		int size = this->GetSize();
		for (int i = this->mCurrentPathId - 1; i < size; ++i)
			result.push_back(this->mPath[i]);

		return result;
	}

	inline std::vector<Vector3> CutPath(float distance) 
	{
		std::vector<Vector3> result = std::vector<Vector3>();
		float Distance = distance;
		if (distance < 0)
		{
			this->mPath[0] = this->mPath[0] + distance * (this->mPath[1] - this->mPath[0]).Normalized();
			return this->GetPathList();
		}

		for (int i = 0; i < this->GetSize() - 1; i++)
		{
			float dist = this->mPath[i].DistTo(this->mPath[i + 1]);
			if (dist > Distance)
			{
				result.push_back(this->mPath[i] + Distance * (this->mPath[i + 1] - this->mPath[i]).Normalized());
				for (int j = i + 1; j < this->GetSize(); j++)
				{
					result.push_back(this->mPath[j]);
				}

				break;
			}
			Distance -= dist;
		}
		if (!result.size())
			result.push_back(this->mPath[this->GetSize() - 1]);

		return result;
	}
};

class Navigation
{
public:
	char pad_0004[16]; //0x0000
	Vector3 mGoingTo; //0x0010
	char pad_001C[380]; //0x001C
	bool mIsMoving; //0x0198
	char pad_0199[3]; //0x0199
	PathManager mPathManager; //0x019C
	char pad_01D0[236]; //0x01D0
	Vector3 mCurrPosition; //0x02BC
	Vector3 mVelocity; //0x02C8
	char pad_02D4[144]; //0x02D4
	Vector3 mDashEndPosition; //0x0364
	char pad_0370[52]; //0x0370
	bool mIsDashing; //0x03A4
	char pad_03A5[1243]; //0x03A5
};

/*
	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual bool IsStanding();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
	virtual void Function10();
	virtual void Function11();
	virtual DWORD* unkPtr();
	virtual void Function13();
	virtual void Function14();
	virtual int Function15();
	virtual void Function16();
	virtual void Function17();
	virtual float GetMovementSpeed();
	virtual float GetFloat();
	virtual void Function20();
	virtual void Function21();
	virtual void Function22();
	virtual void Function23();
	virtual void Function24();
	virtual void Function25();
	virtual void Function26();
	virtual void* fn27_voidPtr(bool a1);
*/
