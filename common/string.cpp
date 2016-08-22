#include <cctype>
#include <string>
#include <algorithm>
#include "string.hpp"

namespace game{

	std::string StringUtil::Trim(const std::string &s)
	{
	   auto wsfront=std::find_if_not(s.begin(),s.end(),[](int c){return std::isspace(c);});
	   auto wsback=std::find_if_not(s.rbegin(),s.rend(),[](int c){return std::isspace(c);}).base();
	   return (wsback<=wsfront ? std::string() : std::string(wsfront,wsback));
	}
}
