#ifndef IMAGECREATOR_H
#define IMAGECREATOR_H

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
using sf::RenderWindow;
using sf::VertexArray;

#include "SolarSystem.h"
using gm::SolarSystem;

namespace gm
{
	class ImageCreator
	{
	public:
		ImageCreator();
		~ImageCreator();

		void Start();

	private:
		SolarSystem** _systems;
		int _number_of_systems;
		VertexArray* _image_map;
		bool** _grid;
		RenderWindow* _window;
		const int _window_x;
		const int _window_y;
		const int _padding;

		void ReadSystems();
		void PopulateGrid();
		void WriteGrid();
		void PopulateImageMap();
		void MainWindowLoop();
	};
}

#endif