#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <cassert>
#include "cs225/lodepng/lodepng.h"
#include "cs225/PNG.h"
//#include "cs225/RGB_HSL.h"
#include "Image.h"

using namespace std;
namespace cs225{


void Image::lighten(){
	for (unsigned x = 0; x < this->width(); x++) {
    		for (unsigned y = 0; y < this->height(); y++) {
	      		HSLAPixel & pixel = (this->getPixel(x, y));
      		        pixel.l = pixel.l + 0.1;
			
			if (pixel.l > 1)
				pixel.l = 1;
	    	}
  	}

}

void Image::lighten(double amount){
	for (unsigned x = 0; x < this->width(); x++) {
    		for (unsigned y = 0; y < this->height(); y++) {
	      		HSLAPixel & pixel = (this->getPixel(x, y));
      		        pixel.l = pixel.l + amount;
			
			if (pixel.l > 1)
				pixel.l = 1;
	    	}
  	}
}

void Image::darken(){
	for (unsigned x = 0; x < this->width(); x++) {
    		for (unsigned y = 0; y < this->height(); y++) {
	      		HSLAPixel & pixel = (this->getPixel(x, y));
      		        pixel.l = pixel.l - 0.1;
			
			if (pixel.l < 0)
				pixel.l = 0;
	    	}
  	}
}

void Image::darken(double amount){
	for (unsigned x = 0; x < this->width(); x++) {
    		for (unsigned y = 0; y < this->height(); y++) {
	      		HSLAPixel & pixel = (this->getPixel(x, y));
      		        pixel.l = pixel.l - amount;
			
			if (pixel.l < 0)
				pixel.l = 0;
	    	}
  	}
}

void Image::saturate(){
	for (unsigned x = 0; x < this->width(); x++) {
    		for (unsigned y = 0; y < this->height(); y++) {
	      		HSLAPixel & pixel = (this->getPixel(x, y));
      		        pixel.s = pixel.s + 0.1;
			
			if (pixel.s > 1)
				pixel.s = 1;
	    	}
  	}
}

void Image::saturate(double amount){
	for (unsigned x = 0; x < this->width(); x++) {
    		for (unsigned y = 0; y < this->height(); y++) {
	      		HSLAPixel & pixel = (this->getPixel(x, y));
      		        pixel.s = pixel.s + amount;
			
			if (pixel.s > 1)
				pixel.s = 1;
	    	}
  	}
}

void Image::desaturate(){
	for (unsigned x = 0; x < this->width(); x++) {
    		for (unsigned y = 0; y < this->height(); y++) {
	      		HSLAPixel & pixel = (this->getPixel(x, y));
      		        pixel.s = pixel.s - 0.1;
			
			if (pixel.s < 0)
				pixel.s = 0;
	    	}
  	}
}

void Image::desaturate(double amount){
	for (unsigned x = 0; x < this->width(); x++) {
    		for (unsigned y = 0; y < this->height(); y++) {
	      		HSLAPixel & pixel = (this->getPixel(x, y));
      		        pixel.s = pixel.s - amount;
			
			if (pixel.s < 0)
				pixel.s = 0;
	    	}
  	}
}

void Image::grayscale(){
	for (unsigned x = 0; x < this->width(); x++) {
    		for (unsigned y = 0; y < this->height(); y++) {
      			HSLAPixel & pixel = (this->getPixel(x, y));

		       pixel.s = 0;
	    	}
  	}
}

void Image::rotateColor(double degrees){
	for (unsigned x = 0; x < this->width(); x++) {
    		for (unsigned y = 0; y < this->height(); y++) {
      			HSLAPixel & pixel = (this->getPixel(x, y));
			if (degrees >= 0) //positive degrees
			{
				if (((pixel.h + degrees) >= 0) && ((pixel.h + degrees) <= 360)) //If within bound.
					pixel.h = pixel.h + degrees;				
				else if ((pixel.h + degrees) > 360) //If adding degrees makes hue > 360
					pixel.h = pixel.h + degrees - 360;
				
			}
			if (degrees < 0) //negative degrees
			{
				if (((pixel.h + degrees) >= 0) && ((pixel.h + degrees) <= 360))
					pixel.h = pixel.h + degrees;		
				else if ((pixel.h + degrees) < 0) //If adding degrees makes hue < 0
						pixel.h = 360 + (pixel.h + degrees);
					
			}			
	    	}
  	}
}


 
void Image::illinify(){
	for (unsigned x = 0; x < this->width(); x++) { //Start from (first pixel in grid to last)
		for (unsigned y = 0; y < this->height(); y++) {
     			
			HSLAPixel & pixel = (this->getPixel(x, y)); //Get that pixels values
			if ( (293.5 <= pixel.h) || (pixel.h <= 113.5) ) //if closer to orange, then orange
				pixel.h = 11;
			else					//if closer to blue, then blue
				pixel.h = 216;
		}
	}

 
}

void Image::scale(double factor){
	unsigned newWidth = factor * this->width();
	unsigned newHeight = factor * this->height();
	Image* imageCopy = new Image(*this); //Copy of original image.
	this->resize(newWidth, newHeight); //Now resize the original image.
	for (unsigned x = 0; x < this->width(); x++) { //Start from (first pixel in grid to last)
		for (unsigned y = 0; y < this->height(); y++) {	//Using resized image size
     			
			HSLAPixel & pixel = (this->getPixel(x, y)); //Get that pixels values			
			HSLAPixel & origPixel = (imageCopy->getPixel(x/factor, y/factor));
			pixel = origPixel;
		}
	}
	delete imageCopy;
}

void Image::scale(unsigned w, unsigned h){
	double ratio = this->width() / this->height();	//Aspect ratio.
	double newWidth = h * ratio;	//To maintain ratio. To get w/h = ratio, w = h*ratio.
	double newHeight = h;
	double factor = newHeight/(this->height());	//factor = newHeight/original
		scale(factor);
}

}
