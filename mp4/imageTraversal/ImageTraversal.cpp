#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 * 
 * @param rightPoint First pixel
 * @param downPoint Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & rightPoint, const HSLAPixel & downPoint) {
  double h = fabs(rightPoint.h - downPoint.h);
  double s = rightPoint.s - downPoint.s;
  double l = rightPoint.l - downPoint.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );    
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
	traversal_ = NULL; // No traversal defined.
	endOfTraversal = false;
}

//Custom constructor
ImageTraversal::Iterator::Iterator(PNG image, Point startPoint, double tolerance, ImageTraversal* traversal)
{
	for (unsigned int i = 0; i < (image.width() * image.height()); i++)
	{
		visitedPoints_.push_back(false);
	}
	endOfTraversal = false;
	image_ = image;
	startPoint_ = startPoint;
	currPoint_ = startPoint;
	tolerance_ = tolerance;
	traversal_ = traversal;
	if (visitPoint(currPoint_) == false)
		endOfTraversal = true;
	else if (visitPoint(currPoint_) == true)
	{
		visitedPoints_[currPoint_.x + currPoint_.y * image_.width()] = true;
		traversalPath_.push_back(currPoint_);
	}
		
}


bool ImageTraversal::Iterator::visitPoint(Point point)
{
	if (point.x >= image_.width() || point.y >= image_.height()) //If it's out of bounds, return 0 
		return false; //Cant visit.
	HSLAPixel nextPixel = image_.getPixel(point.x, point.y);
	HSLAPixel startPixel = image_.getPixel(startPoint_.x, startPoint_.y);
	if (calculateDelta(startPixel, nextPixel) >= tolerance_)
		return false;
	return true;
}


/*
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */

	if (visitPoint(Point(currPoint_.x + 1, currPoint_.y)) == true)  //If rightpoint can be visited, add it.
		traversal_->add(Point(currPoint_.x + 1, currPoint_.y));
	if (visitPoint(Point(currPoint_.x, currPoint_.y + 1)) == true) //If downpoint can be visited, add it.
		traversal_->add(Point(currPoint_.x, currPoint_.y + 1));
	if (visitPoint(Point(currPoint_.x-1, currPoint_.y)) == true) //If leftpoint can be visited, add it.
		traversal_->add(Point(currPoint_.x-1, currPoint_.y));
	if (visitPoint(Point(currPoint_.x, currPoint_.y - 1)) == true) //If uppoint can be visited, add it.
		traversal_->add(Point(currPoint_.x, currPoint_.y - 1));

	if (traversal_->empty())
	{
	    endOfTraversal = true;
	    return *this;
	}

	Point nextPoint = traversal_->pop();
	while (visitedPoints_[nextPoint.x + nextPoint.y * image_.width()] == true)
	{
		if (traversal_->empty()) 
		{
			endOfTraversal = true;
			return *this;
		}
		nextPoint = traversal_->pop();
	 }
	currPoint_ = nextPoint;
	visitedPoints_[currPoint_.x + currPoint_.y * image_.width()] = true;
	traversalPath_.push_back(currPoint_);	
	return *this;
}

/**
 * Iterator accessor opreator.
 * 
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return currPoint_;
}

/**
 * Iterator inequality operator.
 * 
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
	return endOfTraversal != other.endOfTraversal;
}

