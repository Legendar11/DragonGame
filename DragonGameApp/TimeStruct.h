#ifndef TIMESTRUCT_H_INCLUDED
#define TIMESTRUCT_H_INCLUDED

struct TimeStruct
{
	Uint32 timeStart;
	Uint32 timeEnd;
	Uint32 Iter;
	TimeStruct(Uint32 start, Uint32 end, Uint32 iter = 0)
		: timeStart(start), timeEnd(end), Iter(iter)
	{

	}
};

#endif // TIMESTRUCT_H_INCLUDED
