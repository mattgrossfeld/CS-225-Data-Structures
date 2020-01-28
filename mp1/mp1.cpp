#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "mp1.h"
#include <string>
#include <cmath>

using namespace cs225;


void rotate(std::string inputFile, std::string outputFile) {
  // Part 2
//When rotating, the newX = Width - originalX - 1 since its an array
//When rotating, the newY = Height - originalY - 1 since its an array
	PNG inputImage = PNG();
	inputImage.readFromFile(inputFile);
	PNG outputImage = PNG(inputImage.width(),inputImage.height());
	
	for (size_t x = 0; x < inputImage.width(); x++){
		for (size_t y = 0; y < inputImage.height(); y++){
			HSLAPixel * inputPixel = inputImage.getPixel(x,y);
			HSLAPixel * outputPixel = outputImage.getPixel(inputImage.width()-x-1, inputImage.height()-y-1);
			*outputPixel = *inputPixel;
		}
	}
	
	outputImage.writeToFile(outputFile);
}

PNG myArt(unsigned int width, unsigned int height) { //Each corner is a diff color.
  PNG png(width, height);				//Each color represents fire, water, earth, air.
  // Part 3						//Make dead center a circle
	int centerX = width/2;
	int centerY = height/2;
	double distance, circleSize;	
	for (int x = 0; x < png.width(); x++) {
		for (int y = 0; y < png.height(); y++) {
			      HSLAPixel * pixel = png.getPixel(x, y);
			distance = sqrt( pow(centerX - x, 2) + pow(centerY - y, 2) );
			circleSize = sqrt( pow(centerX - (width/2.5), 2) + pow(centerY - (height/2.5),2) );
			
			
			if ( (x < (width/2)) && (y < (height/2)) ) //Top left quadrant, make it red.
			{
				pixel->h = 0; //Red.
				pixel->s = 1; //Fully saturated.
				pixel->l = 0.5;
				pixel->a = 1;
			}
			
			if ( (x >= (width/2)) && (y < (height/2)) ) //top right
			{
				pixel->h = 220; //Blue.
				pixel->s = 1; //Fully saturated.
				pixel->l = 0.5;
				pixel->a = 1;
			}

			if ( (x < (width/2)) && (y >= (height/2)) ) //bottom left
			{
				pixel->h = 115; //Green.
				pixel->s = 1; //Fully saturated.
				pixel->l = 0.5;
				pixel->a = 1;
			}
			
			if ( (x >= (width/2)) && (y >= (height/2)) ) //bottom right
			{
				pixel->h = 30; //brown.
				pixel->s = 1; //Fully saturated.
				pixel->l = 0.3;
				pixel->a = 1;
			}

			if (distance <= circleSize) //white circle in the middle
			{
				pixel->h = 0;
				pixel->s = 0;
				pixel->l = 1; //white
				pixel->a = 1;
			}
		}
	}

  return png;
}
