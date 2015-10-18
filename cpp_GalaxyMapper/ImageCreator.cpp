#include "ImageCreator.h"
using gm::ImageCreator;

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <string>
using std::string;

using sf::VideoMode;
using sf::Event;
using sf::Vector2f;
using sf::Points;
using sf::Color;
using sf::Keyboard;
using sf::Image;

ImageCreator::ImageCreator()
	: _systems(nullptr), _number_of_systems(0), _image_map(nullptr), _grid(nullptr), _window(nullptr), _window_x(1000), 
	_window_y(1000), _padding(5)
{
	_image_map = new VertexArray[_window_y]();
	_systems = new SolarSystem*[8035];
	

	_grid = new bool*[_window_y];
	for (int i = 0; i < _window_y; ++i)
	{
		_grid[i] = new bool[_window_x];

		for (int j = 0; j < _window_x; ++j)
		{
			_grid[i][j] = false;
		}
	}
}

ImageCreator::~ImageCreator()
{
	delete[] _image_map;
	_image_map = nullptr;

	for (int i = 0; i < _number_of_systems; ++i)
	{
		delete _systems[i];
		_systems[i] = nullptr;
	}

	delete[] _systems;
	_systems = nullptr;

	for (int i = 0; i < _window_y; ++i)
	{
		delete[] _grid[i];
		_grid[i] = nullptr;
	}
	delete[] _grid;
}

/*******************************************************************************
*	Driver function
*******************************************************************************/
void ImageCreator::Start()
{
	ReadSystems();
	PopulateGrid();
	//WriteGrid();
	PopulateImageMap();
	MainWindowLoop();
}

/*******************************************************************************
*	Reads each system from a local solarsystems.csv file and stores the
*	relevant data into a SolarSystem class and placed on the heap.
*******************************************************************************/
void ImageCreator::ReadSystems()
{
	// read in solar system coords
	char buffer[300];
	ifstream reader("solarsystems.csv");
	char* next_token;

	char* regionID;
	char* constellationID;
	char* solarsystemID;
	char* solarsystemName;
	char* x;
	char* y;
	char* z;
	char* xMin;
	char* xMax;
	char* yMin;
	char* yMax;
	char* zMin;
	char* zMax;
	char* luminosity;
	char* border;
	char* fringe;
	char* corridor;
	char* hub;
	char* international;
	char* regional;
	char* constellation;
	char* security;
	char* factionID;
	char* radius;
	char* sunTypeID;
	char* securityClass;

	if (reader.is_open())
	{
		while (!reader.eof())
		{
			reader >> buffer;

			// ifstream.>> delimits at whitespace, so I call it again and
			// rejoin the strings, otherwise the whole thing blows up.
			while (strlen(buffer) < 40)
			{
				char temp[300];
				reader >> temp;
				strcat_s(buffer, " ");
				strcat_s(buffer, temp);
			}

			regionID = strtok_s(buffer, ",", &next_token);
			constellationID = strtok_s(next_token, ",", &next_token);
			solarsystemID = strtok_s(next_token, ",", &next_token);
			solarsystemName = strtok_s(next_token, ",", &next_token);
			x = strtok_s(next_token, ",", &next_token);
			y = strtok_s(next_token, ",", &next_token);
			z = strtok_s(next_token, ",", &next_token);
			xMin = strtok_s(next_token, ",", &next_token);
			xMax = strtok_s(next_token, ",", &next_token);
			yMin = strtok_s(next_token, ",", &next_token);
			yMax = strtok_s(next_token, ",", &next_token);
			zMin = strtok_s(next_token, ",", &next_token);
			zMax = strtok_s(next_token, ",", &next_token);
			luminosity = strtok_s(next_token, ",", &next_token);
			border = strtok_s(next_token, ",", &next_token);
			fringe = strtok_s(next_token, ",", &next_token);
			corridor = strtok_s(next_token, ",", &next_token);
			hub = strtok_s(next_token, ",", &next_token);
			international = strtok_s(next_token, ",", &next_token);
			regional = strtok_s(next_token, ",", &next_token);
			constellation = strtok_s(next_token, ",", &next_token);
			security = strtok_s(next_token, ",", &next_token);
			factionID = strtok_s(next_token, ",", &next_token);
			radius = strtok_s(next_token, ",", &next_token);
			sunTypeID = strtok_s(next_token, ",", &next_token);
			securityClass = strtok_s(next_token, ",", &next_token);

			_systems[_number_of_systems] = new SolarSystem(
				regionID, constellationID, solarsystemID, solarsystemName,
				x, y, z, xMin, xMax, yMin, yMax, zMin,
				zMax, luminosity, border, fringe, corridor, hub,
				international, regional, constellation, security, factionID,
				radius, sunTypeID, securityClass);
			++_number_of_systems;
		}

		reader.close();
	}
}

/*******************************************************************************
*	This is where most of the magic happens. The X and Y coordinates are
*	large enough that they can only be processed as either strings, or
*	if converted to numbers, or as 64-bit integers. Because 64-bit ints
*	are too large to work with in floating-point division, they have to
*	be divided by 1 billion. Anyway, because the range of the coords is
*	too large to be represented 1:1 in an image, they have to be
*	normalized, with room for padding. Each solar system's normalized
*	X and Y position flips a cell in **_grid from false to true. This
*	true or false value determines whether a pixel in the image is white
*	or black.
*******************************************************************************/
void ImageCreator::PopulateGrid()
{
	__int64 lowest_x = 0;
	__int64 lowest_y = 0;
	__int64 highest_x = 0;
	__int64 highest_y = 0;
	__int64 x_range = 0;
	__int64 y_range = 0;

	__int64 temp_x;
	__int64 temp_y;

	// finding the lowest and highest X and Y values
	for (int i = 0; i < _number_of_systems; ++i)
	{
		if (_systems[i]->GetRegionID() < 11000000)
		{
			temp_x = _systems[i]->GetX();
			temp_y = _systems[i]->GetY();

			if (temp_x < lowest_x) lowest_x = temp_x;
			else if (temp_x > highest_x) highest_x = temp_x;

			if (temp_y < lowest_y) lowest_y = temp_y;
			else if (temp_y > highest_y) highest_y = temp_y;
		}
	}

	x_range = highest_x - lowest_x;
	y_range = highest_y - lowest_y;

	int normalized_x = 0;
	int normalized_y = 0;
	__int64 sub_result_x = 0;
	__int64 sub_result_y = 0;
	double proportional_x = 0;
	double proportional_y = 0;

	for (int i = 0; i < _number_of_systems; ++i)
	{
		if (_systems[i]->GetRegionID() < 11000000) // filtering out J-space systems (wormholes)
		{
			temp_x = _systems[i]->GetX();
			temp_y = _systems[i]->GetY();
			sub_result_x = temp_x - lowest_x;
			sub_result_y = temp_y - lowest_y;
			proportional_x = (sub_result_x / 1E9) / (x_range / 1E9);
			proportional_y = (sub_result_y / 1E9) / (y_range / 1E9);
			normalized_x = (int)((_window_x - _padding * 2) * proportional_x) + _padding;
			normalized_y = (int)((_window_y - _padding * 2) * proportional_y) + _padding;
			_grid[normalized_x][normalized_y] = true;
		}
	}
}

/*******************************************************************************
*	Writes **_grid to a text file whose dimensions are determined by the
*	size of the window. Default is 1000 by 1000.
*******************************************************************************/
void ImageCreator::WriteGrid()
{
	ofstream writer("test.csv");

	if (writer.is_open())
	{
		for (int i = 0; i < _window_y; ++i)
		{
			for (int j = 0; j < _window_x; ++j)
			{
				writer << _grid[i][j];
			}

			if (i + 1 < _window_y)
			{
				writer << "\n";
			}
		}
	}

	writer.close();
}

/*******************************************************************************
*	Translates the TRUE/FALSE values in **_grid to white or black dots,
*	respectively. Vector2f(j, _window_x - i) flips the image around
*	so that the position of the solar systems somewhat resemble how
*	they're arranged in-game. Actually, no combination of flipping makes
*	the image look close to the way they're positioned in game. Either
*	something with my processing is off, or the game itself ignores
*	coordinate data in the SDE.
*******************************************************************************/
void ImageCreator::PopulateImageMap()
{
	for (int i = 0; i < _window_y; ++i)
	{
		_image_map[i].resize(_window_x);

		for (int j = 0; j < _window_x; ++j)
		{
			//_image_map[i][j].position = Vector2f((float)(i), (float)(j)); // untampered
			_image_map[i][j].position = Vector2f((float)(j), (float)(_window_x - i));

			if (_grid[i][j])
			{
				_image_map[i][j].color = Color::White;
			}
			else
			{
				_image_map[i][j].color = Color::Black;
			}
		}
	}
}

/*******************************************************************************
*	Handles window events. The user can press ESC to close the window or
*	F1 to take a screenshot which is automatically named "GalaxyMap.jpg".
*******************************************************************************/
void ImageCreator::MainWindowLoop()
{
	try
	{
		Image* img;
		_window = new RenderWindow(VideoMode(_window_x, _window_y), "GalaxyMapper");
		_window->setVerticalSyncEnabled(false);
		_window->setFramerateLimit(10);

		while (_window->isOpen())
		{
			Event e;

			// If user closes window.
			while (_window->pollEvent(e))
			{
				if (e.type == Event::Closed)
				{
					_window->close();
				}
			}

			_window->clear(Color::Black);

			for (int i = 0; i < _window_y; ++i)
			{
				_window->draw(_image_map[i]);
			}

			_window->display();

			if (e.key.code == Keyboard::F1)
			{
				img = new Image();
				img->create(_window_x, _window_y);
				*img = _window->capture();
				string file_name = "Galaxy_Map.jpg";
				img->saveToFile(file_name.c_str());
				delete img;
			}

			if (e.key.code == Keyboard::Escape)
			{
				_window->close();
			}
		}

		delete _window;
	}
	catch (...)
	{

	}
}