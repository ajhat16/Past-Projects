#ifndef UTIL_H
#define UTIL_H

#include <functional>
#include <iostream>
#include <initializer_list>
#include <string>
#include <utility>
#include <type_traits>

/*
 * CODE ADAPTED FROM https://stackoverflow.com/questions/216823/how-to-trim-an-stdstring
 */

const char* const ws = " \t\n\r\f\v\"";

// trim from end of string (right)
inline std::string& rtrim(std::string& s, const char* t = ws)
{
	s.erase(s.find_last_not_of(t) + 1);
	return s;
}

// trim from beginning of string (left)
inline std::string& ltrim(std::string& s, const char* t = ws)
{
	s.erase(0, s.find_first_not_of(t));
	return s;
}

// trim from both ends of string (right then left)
inline std::string& trim(std::string& s, const char* t = ws)
{
	return ltrim(rtrim(s, t), t);
}

/**
 * @brief Casts the value to the specified type.
 * @author Read S
 */
template<typename T>
T str_cast(std::string s)
{
	T value = *reinterpret_cast<T*>(&s);

	std::function < T(const char*)> f = NULL;

	if (std::is_integral_v < T >) {
		// value = std::atoi(s.c_str());
		f = std::atoi;
	}
	else if (std::is_floating_point_v < T >) {
		// value = std::atof(s.c_str());
		f = std::atof;
	}

	if (f) {
		value = f(s.c_str());
	}


	return value;
}

#endif // UTIL_H