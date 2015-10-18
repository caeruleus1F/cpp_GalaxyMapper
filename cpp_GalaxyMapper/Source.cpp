/*******************************************************************************
*	Author: Garrett Bates
*	IGN: Thirtyone Organism
*	Date: October 17, 2015
*	Program: EVE New Eden Galaxy Mapper
*******************************************************************************/

#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "ImageCreator.h"
using gm::ImageCreator;

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	ImageCreator ic;
	ic.Start();
}