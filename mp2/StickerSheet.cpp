#include "cs225/PNG.h"
#include "Image.h"
#include "StickerSheet.h"
using namespace std;
namespace cs225{

StickerSheet::StickerSheet(const Image &picture, unsigned max){
	this->max_ = max;
	this->imageArray = new Image*[max];
	this->xValue = new unsigned int[max];
	this->yValue = new unsigned int[max];
	for (unsigned i = 0; i < this->max_; i++)
	{
		this->imageArray[i] = NULL;
		this->xValue[i] = 0;
		this->yValue[i] = 0;
	}
	
	this->basePicture = picture;	
}

StickerSheet::~StickerSheet(){
	deleteFunction();
}

StickerSheet::StickerSheet(const StickerSheet &other){
	copyFunction(other);
}

const StickerSheet& StickerSheet::operator=(const StickerSheet &other){
	deleteFunction();
	copyFunction(other);
return *this;

}

void StickerSheet::changeMaxStickers(unsigned max){	
	if (this->max_ < max){		//If original array is SMALLER, make the bigger spots NULL.
		StickerSheet tempSheet = *this;	//tempSheet = copy of this
		deleteFunction();	//Deallocate the memory
		this->imageArray = new Image*[max]; 	//Reallocate with new max size
		this->xValue = new unsigned int[max];//Reallocate with new max size
		this->yValue = new unsigned int[max];//Reallocate with new max size
		for (unsigned i = 0; i < this->max_; i++) //indices from 0 to oldMax-1 restored.
		{
			this->imageArray[i] = tempSheet.imageArray[i];
			this->xValue[i] = tempSheet.xValue[i];
			this->yValue[i] = tempSheet.yValue[i];
		}
		for (unsigned i = this->max_; i < max; i++)	//Indices from oldMax to newMax set to NULL
		{
			this->imageArray[i] = NULL;
			this->xValue[i] = 0;
			this->yValue[i] = 0;
		}
		this->max_ = max;
	}
//Below code works for this function.
	else if (this->max_ > max) //If original array is BIGGER, make the values NULL.
	{
		for(unsigned i = max; i < this->max_; i++)
		{
			this->imageArray[i] = NULL;
			this->xValue[i] = 0;
			this->yValue[i] = 0;
		}
			
	}
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y){
	//StickerSheet tempSheet = *this;	//tempSheet = copy of this
	{
		for(unsigned i = 0; i < this->max_; i++) //Go through the list.
		{
			if (this->imageArray[i] == NULL) //Check for a null spot in the sheet.
			{
				(this->imageArray[i]) = &sticker;
				(this->xValue[i]) = x;
				(this->yValue[i]) = y;
				return i;
			}
				

		}
		return -1;
	}

}


bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
	if (index >= this->max_) //outside of bounds
		return false;
	if (this->imageArray[index] == NULL) //Check if the picture is null.
		return false;
	this->xValue[index] = x;
	this->yValue[index] = y;
	return true;
	
}


void StickerSheet::removeSticker(unsigned index){
	if (this->imageArray[index] != NULL)
	{
		this->imageArray[index] = NULL;
		this->xValue[index] = 0;
		this->yValue[index] = 0;
	}
}

Image* StickerSheet::getSticker(unsigned index) const{
	if (index >= this->max_)
		return NULL;
	if (this->imageArray[index] == NULL)
		return NULL;
	return this->imageArray[index];
	
}

Image StickerSheet::render() const{
	Image imageRender = this->basePicture; //Copy the base picture.
	unsigned maxWidth = imageRender.width();
	unsigned maxHeight = imageRender.height();	

	for (unsigned i = 0; i < this->max_; i++)
	{
		if (imageArray[i] != NULL)
		{
		/*cout << "Layer:" << i<< endl;
		cout << imageArray[i]->width() << "<-w  h->"<< imageArray[i]->height() << endl;
		cout << xValue[i] << "<-xVal  yVal->"<< yValue[i] << endl;
		cout << endl;*/
			if(maxWidth < (imageArray[i]->width() + xValue[i]))
				maxWidth = imageArray[i]->width() + xValue[i];
			if(maxHeight < (imageArray[i]->height() + yValue[i]))
				maxHeight = imageArray[i]->height() + yValue[i];
		}
	}

	

	if ( (maxWidth > imageRender.width()) || (maxHeight > imageRender.height()) )
		imageRender.resize(maxWidth, maxHeight);
	for (unsigned i = 0; i < this->max_; i++)//For every sticker in the array.
	{	
		if (imageArray[i] != NULL)
		{
			for (unsigned x = 0; x < imageArray[i]->width(); x++) {
				for (unsigned y = 0; y < imageArray[i]->height(); y++) {	     	
					HSLAPixel & basePixel = (imageRender.getPixel(x+xValue[i], y+yValue[i])); 
					HSLAPixel & stickerPixel = (imageArray[i]->getPixel(x, y));
					if (stickerPixel.a != 0) //Sticker's pixel is not invisible.
						basePixel = stickerPixel; //pixel of sticker we're on.
				}
			}
		}
	
	}
	
	return imageRender;
	
}



void StickerSheet::deleteFunction(){
	delete[] imageArray;
	delete[] xValue;
	delete[] yValue;
}

void StickerSheet::copyFunction(const StickerSheet & other){
	this->max_ = other.max_;
	this->basePicture = other.basePicture;
	this->imageArray = new Image*[this->max_];
	this->xValue = new unsigned int[this->max_];
	this->yValue = new unsigned int[this->max_];
	for (unsigned i = 0; i < this->max_; i++)
	{
		this->imageArray[i] = other.imageArray[i];
		this->xValue[i] = other.xValue[i];
		this->yValue[i] = other.yValue[i];
	}
	
}

}
