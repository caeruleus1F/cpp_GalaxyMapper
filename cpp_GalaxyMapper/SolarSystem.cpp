#include "SolarSystem.h"
using gm::SolarSystem;

#include <cstring>
#include <stdlib.h>

SolarSystem::SolarSystem(
	char* regionID, char* constellationID, char* solarsystemID, char* solarsystemName,
	char* x, char* y, char* z, char* xMin, char* xMax, char* yMin, char* yMax, char* zMin,
	char* zMax, char* luminosity, char* border, char* fringe, char* corridor, char* hub,
	char* international, char* regional, char* constellation, char* security, char* factionID,
	char* radius, char* sunTypeID, char* securityClass)
	: _regionID(nullptr), _constellationID(nullptr), _solarsystemID(nullptr), _solarsystemName(nullptr),
	_x(nullptr), _y(nullptr), _z(nullptr), _xMin(nullptr), _xMax(nullptr), _yMin(nullptr), _yMax(nullptr),
	_zMin(nullptr), _zMax(nullptr), _luminosity(nullptr), _border(nullptr), _fringe(nullptr), _corridor(nullptr),
	_hub(nullptr), _international(nullptr), _regional(nullptr), _constellation(nullptr), _security(nullptr),
	_factionID(nullptr), _radius(nullptr), _sunTypeID(nullptr), _securityClass(nullptr)
{
	int length = strlen(regionID) + 1;
	_regionID = new char[length]();
	strcpy_s(_regionID, length, regionID);

	length = strlen(constellationID) + 1;
	_constellationID = new char[length]();
	strcpy_s(_constellationID, length, constellationID);

	length = strlen(solarsystemID) + 1;
	_solarsystemID = new char[length]();
	strcpy_s(_solarsystemID, length, solarsystemID);

	length = strlen(solarsystemName) + 1;
	_solarsystemName = new char[length]();
	strcpy_s(_solarsystemName, length, solarsystemName);

	length = strlen(x) + 1;
	_x = new char[length]();
	strcpy_s(_x, length, x);

	length = strlen(y) + 1;
	_y = new char[length]();
	strcpy_s(_y, length, y);

	length = strlen(z) + 1;
	_z = new char[length]();
	strcpy_s(_z, length, z);

	length = strlen(xMin) + 1;
	_xMin = new char[length]();
	strcpy_s(_xMin, length, xMin);

	length = strlen(xMax) + 1;
	_xMax = new char[length]();
	strcpy_s(_xMax, length, xMax);

	length = strlen(yMin) + 1;
	_yMin = new char[length]();
	strcpy_s(_yMin, length, yMin);

	length = strlen(yMax) + 1;
	_yMax = new char[length]();
	strcpy_s(_yMax, length, yMax);

	length = strlen(zMin) + 1;
	_zMin = new char[length]();
	strcpy_s(_zMin, length, zMin);

	length = strlen(zMax) + 1;
	_zMax = new char[length]();
	strcpy_s(_zMax, length, zMax);

	length = strlen(luminosity) + 1;
	_luminosity = new char[length]();
	strcpy_s(_luminosity, length, luminosity);

	length = strlen(border) + 1;
	_border = new char[length]();
	strcpy_s(_border, length, border);

	length = strlen(fringe) + 1;
	_fringe = new char[length]();
	strcpy_s(_fringe, length, fringe);

	length = strlen(corridor) + 1;
	_corridor = new char[length]();
	strcpy_s(_corridor, length, corridor);

	length = strlen(hub) + 1;
	_hub = new char[length]();
	strcpy_s(_hub, length, hub);

	length = strlen(international) + 1;
	_international = new char[length]();
	strcpy_s(_international, length, international);

	length = strlen(regional) + 1;
	_regional = new char[length]();
	strcpy_s(_regional, length, regional);

	length = strlen(constellation) + 1;
	_constellation = new char[length]();
	strcpy_s(_constellation, length, constellation);

	length = strlen(security) + 1;
	_security = new char[length]();
	strcpy_s(_security, length, security);

	length = strlen(factionID) + 1;
	_factionID = new char[length]();
	strcpy_s(_factionID, length, factionID);

	length = strlen(radius) + 1;
	_radius = new char[length]();
	strcpy_s(_radius, length, radius);

	length = strlen(sunTypeID) + 1;
	_sunTypeID = new char[length]();
	strcpy_s(_sunTypeID, length, sunTypeID);

	if (securityClass) // some systems don't have a security class
	{
		length = strlen(securityClass) + 1;
		_securityClass = new char[length];
		strcpy_s(_securityClass, length, securityClass);
	}
}


SolarSystem::~SolarSystem()
{
	delete[] _regionID;
	_regionID = nullptr;
	delete[] _constellationID;
	_constellationID = nullptr;
	delete[] _solarsystemID;
	_solarsystemID = nullptr;
	delete[] _solarsystemName;
	_solarsystemName = nullptr;
	delete[] _x;
	_x = nullptr;
	delete[] _y;
	_y = nullptr;
	delete[] _z;
	_z = nullptr;
	delete[] _xMin;
	_xMin = nullptr;
	delete[] _xMax;
	_xMax = nullptr;
	delete[] _yMin;
	_yMin = nullptr;
	delete[] _yMax;
	_yMax = nullptr;
	delete[] _zMin;
	_zMin = nullptr;
	delete[] _zMax;
	_zMax = nullptr;
	delete[] _luminosity;
	_luminosity = nullptr;
	delete[] _border;
	_border = nullptr;
	delete[] _fringe;
	_fringe = nullptr;
	delete[] _corridor;
	_corridor = nullptr;
	delete[] _hub;
	_hub = nullptr;
	delete[] _international;
	_international = nullptr;
	delete[] _regional;
	_regional = nullptr;
	delete[] _constellation;
	_constellation = nullptr;
	delete[] _security;
	_security = nullptr;
	delete[] _factionID;
	_factionID = nullptr;
	delete[] _radius;
	_radius = nullptr;
	delete[] _sunTypeID;
	_sunTypeID = nullptr;
	delete[] _securityClass;
	_securityClass = nullptr;
}

__int64 SolarSystem::GetX()
{
	return _atoi64(_x);
}

__int64 SolarSystem::GetY()
{
	return _atoi64(_y);
}

__int64 SolarSystem::GetRegionID()
{
	return _atoi64(_regionID);
}