#include "utils.h"

std::string fileToString(const char *file_name)
{
	struct stat file_status;
	int ret;

	std::ifstream in(file_name);
	std::string s((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

	return s;
}
