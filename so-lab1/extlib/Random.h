#pragma once

#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

#include <random>

namespace sfe
{
	class Random;
}

// \brief Class for generating random number.
// \author Pawe³ Trys³a aka zamotany.
class sfe::Random
{
public:
	// \breif Default constructor.
	// \param allowRepeat Allow to generate the same number as previusly generated one.
	Random(bool allowRepeat = false);

	// \brief Default destructor.
	~Random();

	// \brief Get next unsigned random number.
	// \note If allow repeat is set to false, method will not return the same number as the prevous one.
	// \return Generated random number.
	unsigned int next();

	// \brief Get next unsigned random number between minimum and maximum values.
	// \param min Minimal value.
	// \param max Maximal value.
	// \note If allow repeat is set to false, method will not return the same number as the prevous one.
	unsigned int next(unsigned int min, unsigned int max);

	// \brief Get next signed random number.
	// \note If allow repeat is set to false, method will not return the same number as the prevous one.
	// \return Generated random number.
	//as the prevous one.
	int nextSigned();

	// \brief Get next signed random number between minimum and maximum values.
	// \param min Minimal value.
	// \param max Maximal value.
	// \note If allow repeat is set to false, method will not return the same number as the prevous one.
	int nextSigned(int min, int max);
private:
	bool AllowRepeat_;
	long PrevousNum_;
	std::random_device Seeder_;
	std::mt19937 Engine_;
};