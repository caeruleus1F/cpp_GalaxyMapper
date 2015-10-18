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

// All the galaxies in New Eden have been read and stored.
// Now we convert their X and Y coords into something that can
// be plotted onto an image. We will do this by normalizing the
// coords. Off the top of my head, the char* will be recast into
// long integers, or bigger if necessary, dividing by a sufficiently
// large number, finding the lowest and highest values, subtracting
// by the lowest value (which is likely to be negative), then
// multiplying each resulting X and Y value by the height or width
// of the image and dividing it by the range of X or Y values.
// How'd I do, Chief? Was that good? Will that work out?

// Each value will be stored into a relevant grid cell as a Point,
// probably with a white color. I'm also entertaining the idea of adding
// circles with a size that's dependent on the number of jumps in/out
// of that system within a given time period. That will require exporting
// the jumps data I've been collecting in my MySQL DB for the last several
// days. If passion moves me, this tool will help me chose a home system
// for easy farming in my alt's capital ship.