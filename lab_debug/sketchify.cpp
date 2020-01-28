#include <cstdlib>
#include <cmath>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
using namespace cs225;

// sets up the output image
PNG* setupOutput(unsigned w, unsigned h) {
    PNG* image = new PNG(w, h);
    return image;
}

// Returns my favorite color
HSLAPixel myFavoriteColor(double saturation) {
    HSLAPixel pixel(210, saturation, 0.5);
    return pixel;
}

void sketchify(std::string inputFile, std::string outputFile) {
    // Load in.png
    PNG* original = new PNG();
	cout << "Reached line 23" << endl;
    original->readFromFile(inputFile);
    unsigned width = original->width();
    unsigned height = original->height();
	cout << "Reached line 27" << endl;
    // Create out.png
    PNG* output;
    output = setupOutput(width, height);

    // Load our favorite color to color the outline
    HSLAPixel myPixel = myFavoriteColor(0.5);

    // Go over the whole image, and if a pixel differs from that to its upper
    // left, color it my favorite color in the output
    for (unsigned y = 1; (0 < y) && (y < height); y++) {
        for (unsigned x = 1; (0 < x) && (x < width); x++) {
	 	//cout << "Inner for-loop beginning" << endl;
            // Calculate the pixel difference
            HSLAPixel & prev = original->getPixel(x - 1, y - 1);
            HSLAPixel & curr = original->getPixel(x, y);
		//cout << "previous and current pixels gotten." << endl;
            double diff = std::fabs(curr.h - prev.h);
		//cout << "difference between pixels gotten" << endl;
            // If the pixel is an edge pixel,
            // color the output pixel with my favorite color
            HSLAPixel & currOutPixel = output->getPixel(x, y);
		//cout << "Get the current output pixel" << endl;
            if (diff > 20) {
                currOutPixel.h = myPixel.h;
		currOutPixel.s = myPixel.s;
		currOutPixel.l = myPixel.l;
		currOutPixel.a = myPixel.a;
            }
		//cout << "Inner for-loop ending" << endl;
        }
    }

    // Save the output file
    output->writeToFile(outputFile);

    // Clean up memory
    //delete myPixel;
    delete output;
    delete original;
}
