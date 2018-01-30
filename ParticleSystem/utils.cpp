#include "utils.h"


float		*hit_plane(QVector3D origin, float d)
{
    QVector3D direction(origin.x(), origin.y(), -1);
	QVector3D planeOrigin(0, 0, -2);
	QVector3D planeNormal(0, 0, 1);
	QVector3D ret;
	float t;
	float p[3];

    t = QVector3D::dotProduct(planeOrigin - origin, planeNormal) / QVector3D::dotProduct(planeNormal, direction);
	if (t >= 0.0001)
	{
		ret = origin + t * direction;
		p[0] = ret.x();
		p[1] = ret.y();
		p[2] = ret.z();
		return (p);
	}
	return (0);
}

std::string fileToString(const char *file_name)
{
	struct stat file_status;
	int ret;

	std::ifstream in(file_name);
	std::string s((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

	return s;
}
