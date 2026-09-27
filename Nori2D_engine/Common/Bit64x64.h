#pragma once
#include <Windows.h>
#include <vector>
#include <limits>

class Bit64x64
{
	UINT64 mBits[64];

	static const UINT64	__FULLBITS = MAXUINT64;
public:
	Bit64x64() { Clear(); }

	void SetAll() { for (int i = 0; i < 64; ++i) mBits[i] = __FULLBITS; }
	void Clear()  { for (int i = 0; i < 64; ++i) mBits[i] = 0; }

	void Set(int x, int y, bool flags)
	{
		UINT64 maskBit = (UINT64)1 << x;
		if (flags) {
			mBits[y] |= maskBit;
		}
		else {
			mBits[y] &= ~maskBit;
		}
	}

	bool Get(int x, int y)
	{
		UINT64 maskBit = (UINT64)1 << x;
		UINT64 flag = mBits[y] & maskBit;
		return (flag) ? true : false;
	}

};


class BitGroup1024x1024
{
	std::vector<Bit64x64*> mBitList;
	BYTE mIndex[16][16];
	struct { short x, y; } mLast;

	Bit64x64* GetBit64(int x, int y) {
		int fx = x / 64;
		int fy = y / 64;
		BYTE idx = mIndex[fy][fx];

		if (idx == 0xFF) {
			if(mLast.x != fx || mLast.y != fy)
				return nullptr;
		}

		return mBitList[idx];
	}

	Bit64x64* CreateBit64(int x, int y) {
		Bit64x64* bit = new Bit64x64;
		mBitList.push_back(bit);
		BYTE idx = mBitList.size() - 1;
		int fx = x / 64;
		int fy = y / 64;

		if (idx == 0xFF) {
			mLast.x = fx;
			mLast.y = fy;
		}

		mIndex[fy][fx] = idx;
		return bit;
	}

public:
	BitGroup1024x1024() { Clear(); }

	void Clear() { 
		for (Bit64x64 * bitf : mBitList) {
			delete bitf;
		}
		mBitList.clear();

		for(int y=0; y<16; ++y)
			for (int x = 0; x < 16; ++x) {
				mIndex[y][x] = 0xFF;
			}

		mLast.x = -1;
		mLast.y = -1;
	}

	void Set(int x, int y, bool flag)
	{
		Bit64x64* bits = GetBit64(x, y);
		if (bits == nullptr) {
			if (flag == false) return;

			bits = CreateBit64(x, y);
		}

		x = (x % 64);
		y = (y % 64);
		bits->Set(x, y, flag);
	}

	bool Get(int x, int y)
	{
		Bit64x64* bits = GetBit64(x, y);
		if (bits == nullptr) return false;

		x = (x % 64);
		y = (y % 64);
		return bits->Get(x, y);
	}

	/*
	void Print(std::ostream& ot)
	{
		int ii = 0;
		for (int y = 0; y < 15; ++y) {
			for (int x = 0; x < 15; ++x) {
				if (mIndex[y][x]) ot << "бс ";
				else ot << " .";

			}
			ot << std::endl;
		}
	}
	*/

};







