/**
 * @file HSLAPixel.h
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#ifndef CS225_HSLAPIXEL_H_
#define CS225_HSLAPIXEL_H_

#include <iostream>
#include <sstream>

namespace cs225 {
	class HSLAPixel {
		public:
			//Variables
			double h; //Hue of pixel. [0,360)
			double s; //Saturation of pixel. [0,1]
			double l; //Luminance of pixel. [0,1]
			double a; //Alpha channel of pixel. [0,1]

			//Functions
			HSLAPixel(); 		       //Constructs a default pixel.

			HSLAPixel(double hue,	       //Constructs opaque pixel
				  double saturation,   //with given hue, saturation, luminance values.
				  double luminance); 

			HSLAPixel(double hue,	       //Constructs pixel with given
				  double saturation,   //hue, saturation, luminance, alpha values.
				  double luminance,
				  double alpha);

		private: //Empty
			};
}

#endif
