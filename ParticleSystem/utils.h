#ifndef UTILS_H
#define UTILS_H

#include <cstddef>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

std::string fileToString(const char *file_name);

#endif // UTILS_H
