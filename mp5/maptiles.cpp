/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

Point<3> convertToLAB(HSLAPixel pixel) {
    Point<3> result(pixel.h/360, pixel.s, pixel.l);
    return result;
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
	if (theTiles.empty())
		return NULL;

	MosaicCanvas* canvasMosaic = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
	vector<Point<3>> tilePoints;
	map<Point<3>, int> tileMap;	
	tilePoints.resize(theTiles.size());

	for (size_t i = 0; i < theTiles.size(); i++)
	{
		HSLAPixel pixel = theTiles[i].getAverageColor();
		Point<3> mapPoint(pixel.h / 360, pixel.s, pixel.l);
		tilePoints.push_back(mapPoint);
		tileMap[mapPoint] = i;
	}

	KDTree<3> tileTree(tilePoints);

	for (int x = 0; x < canvasMosaic->getRows(); x++)
	{
		for (int y = 0; y < canvasMosaic->getColumns(); y++)
		{
			HSLAPixel canvasPixel = theSource.getRegionColor(x,y);
			canvasMosaic->setTile(x, y, get_match_at_idx(tileTree, tileMap, theTiles, theSource, x, y));
		}
	}
	
	return canvasMosaic;
}

TileImage* get_match_at_idx(const KDTree<3>& tree,
                                  map<Point<3>, int> tile_avg_map,
                                  vector<TileImage>& theTiles,
                                  const SourceImage& theSource, int row,
                                  int col)
{
    // Create a tile which accurately represents the source region we'll be
    // using
    HSLAPixel avg = theSource.getRegionColor(row, col);
    Point<3> avgPoint = convertToLAB(avg);
    Point<3> nearestPoint = tree.findNearestNeighbor(avgPoint);

    // Check to ensure the point exists in the map
    map< Point<3>, int >::iterator it = tile_avg_map.find(nearestPoint);
    if (it == tile_avg_map.end())
        cerr << "Didn't find " << avgPoint << " / " << nearestPoint << endl;

    // Find the index
    int index = tile_avg_map[nearestPoint];
    return &theTiles[index];

}
