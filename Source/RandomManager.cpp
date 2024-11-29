#include <chrono>
#include <random>

#include "Headers/RandomManager.hpp"

RandomManager::RandomManager() :
	random_engine(std::chrono::system_clock::now().time_since_epoch().count())
{

}

double RandomManager::get_random(const double& i_value_max, const double& i_value_min)
{
	std::uniform_real_distribution<double> distribution(i_value_min, std::nextafter(i_value_max, DBL_MAX));

	return distribution(random_engine);
}

float RandomManager::get_random(const float& i_value_max, const float& i_value_min)
{
	std::uniform_real_distribution<float> distribution(i_value_min, std::nextafter(i_value_max, FLT_MAX));

	return distribution(random_engine);
}

int RandomManager::get_random(const int& i_value_max, const int& i_value_min)
{
	std::uniform_int_distribution<int> distribution(i_value_min, i_value_max);

	return distribution(random_engine);
}

long RandomManager::get_random(const long& i_value_max, const long& i_value_min)
{
	std::uniform_int_distribution<long> distribution(i_value_min, i_value_max);

	return distribution(random_engine);
}

long double RandomManager::get_random(const long double& i_value_max, const long double& i_value_min)
{
	std::uniform_real_distribution<long double> distribution(i_value_min, std::nextafter(i_value_max, LDBL_MAX));

	return distribution(random_engine);
}

long long RandomManager::get_random(const long long& i_value_max, const long long& i_value_min)
{
	std::uniform_int_distribution<long long> distribution(i_value_min, i_value_max);

	return distribution(random_engine);
}

short RandomManager::get_random(const short& i_value_max, const short& i_value_min)
{
	std::uniform_int_distribution<short> distribution(i_value_min, i_value_max);

	return distribution(random_engine);
}

unsigned RandomManager::get_random(const unsigned& i_value_max, const unsigned& i_value_min)
{
	std::uniform_int_distribution<unsigned> distribution(i_value_min, i_value_max);

	return distribution(random_engine);
}

unsigned long RandomManager::get_random(const unsigned long& i_value_max, const unsigned long& i_value_min)
{
	std::uniform_int_distribution<unsigned long> distribution(i_value_min, i_value_max);

	return distribution(random_engine);
}

unsigned long long RandomManager::get_random(const unsigned long long& i_value_max, const unsigned long long& i_value_min)
{
	std::uniform_int_distribution<unsigned long long> distribution(i_value_min, i_value_max);

	return distribution(random_engine);
}

unsigned short RandomManager::get_random(const unsigned short& i_value_max, const unsigned short& i_value_min)
{
	std::uniform_int_distribution<unsigned short> distribution(i_value_min, i_value_max);

	return distribution(random_engine);
}