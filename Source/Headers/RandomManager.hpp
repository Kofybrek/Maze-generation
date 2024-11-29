#pragma once

class RandomManager
{
	std::mt19937_64 random_engine;
public:
	RandomManager();

	double get_random(const double& i_value_max = DBL_MAX, const double& i_value_min = DBL_MIN);
	float get_random(const float& i_value_max = FLT_MAX, const float& i_value_min = FLT_MIN);
	int get_random(const int& i_value_max = INT_MAX, const int& i_value_min = INT_MIN);
	long get_random(const long& i_value_max = LONG_MAX, const long& i_value_min = LONG_MIN);
	long double get_random(const long double& i_value_max = LDBL_MAX, const long double& i_value_min = LDBL_MIN);
	long long get_random(const long long& i_value_max = LLONG_MAX, const long long& i_value_min = LLONG_MIN);
	short get_random(const short& i_value_max = SHRT_MAX, const short& i_value_min = SHRT_MIN);
	unsigned get_random(const unsigned& i_value_max = UINT_MAX, const unsigned& i_value_min = 0);
	unsigned long get_random(const unsigned long& i_value_max = ULONG_MAX, const unsigned long& i_value_min = 0);
	unsigned long long get_random(const unsigned long long& i_value_max = ULLONG_MAX, const unsigned long long& i_value_min = 0);
	unsigned short get_random(const unsigned short& i_value_max = USHRT_MAX, const unsigned short& i_value_min = 0);
};