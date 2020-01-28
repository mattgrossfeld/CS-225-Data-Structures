#include "cs225/PNG.h"
#include <list>
#include <iostream>


#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 * 
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png) {
  /** @todo [Part 2] */
	image_ = new PNG(png);
}

/**
 * Adds a flood fill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 * 
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker) {
  /** @todo [Part 2] */
	ColorPicker* picker = &colorPicker;
	ImageTraversal* imageTrav = &traversal; 
	colorPicker_.push_back(picker);
	traversal_.push_back(imageTrav);
}

/**
 * Creates an Animation of frames from the FloodFill operations added to this object.
 * 
 * Each FloodFill operation added by `addFloodFill` is executed based on the order
 * the operation was added.  This is done by:
 * 1. Visiting pixels within the image based on the order provided by the ImageTraversal iterator and
 * 2. Updating each pickedPixel to a new color based on the ColorPicker
 * 
 * While applying the FloodFill to the image, an Animation is created by saving the image
 * after every `frameInterval` pixels are filled.  To ensure a smooth Animation, the first
 * frame is always the starting image and the final frame is always the finished image.
 * 
 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pickedPixel has been filled
 *   - Then after the 8th pickedPixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 */ 
Animation FloodFilledImage::animate(unsigned frameInterval) const {
  Animation animation;
  /** @todo [Part 2] */
	
	animation.addFrame(*image_); //Add the image to the frame.
	for (unsigned int traverseCounter = 0; traverseCounter < traversal_.size(); traverseCounter++) //Until traversal is done, keep modifying frames.
	{
		ImageTraversal::Iterator iotEnd = traversal_[traverseCounter]->end();
		ImageTraversal::Iterator iotBegin = traversal_[traverseCounter]->begin();
		unsigned int intervalCounter = 0;
		for (ImageTraversal::Iterator iot = iotBegin; iot != iotEnd; ++iot) 
		{
			if (intervalCounter == frameInterval) 
			{
				animation.addFrame(*image_);
				intervalCounter = 0;
			}

			HSLAPixel pickedPixel = colorPicker_[traverseCounter]->getColor((*iot).x, (*iot).y);
			HSLAPixel & imagePixel = image_->getPixel((*iot).x, (*iot).y);
			imagePixel.a = pickedPixel.a;
			imagePixel.l = pickedPixel.l;
			imagePixel.s = pickedPixel.s;
			imagePixel.h = pickedPixel.h;
			intervalCounter++;
    		}
		animation.addFrame(*image_);
	}
	
  return animation;
}
