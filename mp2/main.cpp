#include "Image.h"
#include "StickerSheet.h"

using namespace cs225;
int main() {

  Image drake; drake.readFromFile("drake.png");
  Image wade;    wade.readFromFile("wade.png");
  wade.scale(.5);
  Image segfault; segfault.readFromFile("segfault.PNG");
  segfault.scale(3);
  Image valgrind; valgrind.readFromFile("valgrind.PNG");
 	valgrind.scale(1.5);
  Image alltestspass; alltestspass.readFromFile("alltestspass.png");
	alltestspass.resize(400, alltestspass.height());
	alltestspass.scale(500, 100);

  StickerSheet mySheet(drake, 5);
  mySheet.addSticker(wade, 50, 50);
  mySheet.addSticker(segfault, 400, 25);
  mySheet.addSticker(valgrind, 400, 100);
  mySheet.addSticker(alltestspass, 400, 500);
  mySheet.addSticker(wade, 100, 375);


mySheet.render().writeToFile("myImage.png");

  return 0;
}
