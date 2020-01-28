/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */
#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <string>
#include <vector>
#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"

using namespace std;

namespace cs225 {
	class Image : public PNG {
		public:
			void lighten();
			void lighten(double amount);
 			void darken();
			void darken(double amount);
			void saturate(); 
			void saturate(double amount);
			void desaturate();
			void desaturate(double amount);
			void grayscale();
			void rotateColor(double degrees); 
			void illinify();
			void scale(double factor);
			void scale(unsigned w, unsigned h);
	
	};
}

#endif
 
