#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

namespace gm
{
	class SolarSystem
	{
	public:
		SolarSystem(
			char* regionID,
			char* constellationID,
			char* solarsystemID,
			char* solarsystemName,
			char* x,
			char* y,
			char* z,
			char* xMin,
			char* xMax,
			char* yMin,
			char* yMax,
			char* zMin,
			char* zMax,
			char* luminosity,
			char* border,
			char* fringe,
			char* corridor,
			char* hub,
			char* international,
			char* regional,
			char* constellation,
			char* security,
			char* factionID,
			char* radius,
			char* sunTypeID,
			char* securityClass);
		~SolarSystem();

		__int64 GetX();
		__int64 GetY();
		__int64 GetRegionID();

	private:
		char* _regionID;
		char* _constellationID;
		char* _solarsystemID;
		char* _solarsystemName;
		char* _x;
		char* _y;
		char* _z;
		char* _xMin;
		char* _xMax;
		char* _yMin;
		char* _yMax;
		char* _zMin;
		char* _zMax;
		char* _luminosity;
		char* _border;
		char* _fringe;
		char* _corridor;
		char* _hub;
		char* _international;
		char* _regional;
		char* _constellation;
		char* _security;
		char* _factionID;
		char* _radius;
		char* _sunTypeID;
		char* _securityClass;
	};
}
#endif