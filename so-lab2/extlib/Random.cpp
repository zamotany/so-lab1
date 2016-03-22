#include "Random.h"

Random::Random(bool allowRepeat)
	: AllowRepeat_(allowRepeat), PrevousNum_(-1), Seeder_(), Engine_(Seeder_())
{
}

Random::~Random()
{
}


unsigned int Random::next()
{
	std::uniform_int_distribution<unsigned int> dist(0);

	unsigned int num;

	do
		num = dist(Engine_);
	while (!AllowRepeat_ && PrevousNum_ == num);

	PrevousNum_ = num;
	return num;
}

int Random::nextSigned()
{
	std::uniform_int_distribution<int> dist(std::numeric_limits<int>::min());

	int num;

	do
		num = dist(Engine_);
	while (!AllowRepeat_ && PrevousNum_ == num);

	PrevousNum_ = num;
	return num;
}

unsigned int Random::next(unsigned int min, unsigned int max)
{
	std::uniform_int_distribution<unsigned int> dist(min, max);

	unsigned int num;

	do
		num = dist(Engine_);
	while (!AllowRepeat_ && PrevousNum_ == num);

	PrevousNum_ = num;
	return num;
}

int Random::nextSigned(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max);

	int num;

	do
		num = dist(Engine_);
	while (!AllowRepeat_ && PrevousNum_ == num);

	PrevousNum_ = num;
	return num;
}