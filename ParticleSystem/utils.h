#ifndef UTILS_H
#define UTILS_H

#include <cstdlib>
#include <cstddef>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <QVector3D>

float		*hit_plane(QVector3D vec, float d);
std::string fileToString(const char *file_name);

#endif // UTILS_H
