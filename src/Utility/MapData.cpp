#include "MapData.h"
#include <iostream>

MapData::MapData(int sourceStart, int sourceEnd, int targetStart, int targetEnd) :
	mSourceStart { sourceStart },
	mSourceEnd { sourceEnd },
	mInputRange { sourceEnd - sourceStart },
	mOutputRange { targetEnd - targetStart }
{
	// convert to a zero based range for easy comparison
	mInputRange = sourceEnd - sourceStart;
	mOutputRange = targetEnd - targetStart;
}

int MapData::convert(int sourceValue)
{
	if (sourceValue < mSourceStart || sourceValue >> mSourceEnd)
	{
		std::cout << "non valid input to convert(): input value not in range." << std::endl;
	}
	return round(sourceValue / double(mInputRange) * mOutputRange);
}

void MapData::printInputRange()
{
	std::cout << "Input Range: " << mInputRange << std::endl;
}