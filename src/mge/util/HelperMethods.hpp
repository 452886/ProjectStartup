#ifndef HELPERMETHODS_HPP
#define HELPERMETHODS_HPP

#include <vector>
#include <string>
#include <sstream>


class HelperMethods {
public:
	static std::vector<std::string> split(const std::string& s, char delimiter);
};

#endif // HELPERMETHODS_HPP