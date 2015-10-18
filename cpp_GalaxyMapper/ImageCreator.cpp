#include "ImageCreator.h"
using gm::ImageCreator;

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

void ImageCreator::Start()
{
	ReadSystems();
	PopulateGrid();
	//WriteGrid();
	PopulateImageMap();
	MainWindowLoop();
}

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