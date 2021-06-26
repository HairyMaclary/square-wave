#ifndef MapData_H
#define MapData_H

class MapData
{
	int mSourceStart;
	int mSourceEnd;
	int mTargetStart;
	int mTargetEnd;
	int mInputRange;
	int mOutputRange;

public:
	MapData(int sourceStart, int sourceEnd, int targetStart, int targetEnd);
	int convert(int sourceValue);
	void printInputRange();
};

#endif