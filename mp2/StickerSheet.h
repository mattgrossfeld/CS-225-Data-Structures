/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#ifndef STICKERSHEET_H_
#define STICKERSHEET_H_

#include "cs225/PNG.h"
#include "Image.h"

using namespace std;

namespace cs225{
class StickerSheet{
	public:
		StickerSheet(const Image &picture, unsigned max);
		~StickerSheet();
		StickerSheet(const StickerSheet &other);
	const StickerSheet& operator=(const StickerSheet &other);
	void	changeMaxStickers(unsigned max);
	int	addSticker(Image &sticker, unsigned x, unsigned y);
	bool	translate(unsigned index, unsigned x, unsigned y);
	void	removeSticker(unsigned index);
	Image*	getSticker(unsigned index) const;
	Image	render() const;
	void	deleteFunction();
	void	copyFunction(const StickerSheet & other);

	private:
		unsigned int max_;
		unsigned int * xValue;
		unsigned int * yValue;
		Image** imageArray;
		Image	basePicture;

	};

}
#endif
 
