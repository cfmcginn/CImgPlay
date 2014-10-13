#include <iostream>
#include "CImg/CImg.h"

int main()
{
  cimg_library::CImg<unsigned char> img("testPhoto.jpg");

  const unsigned int imgWidth = img.width();
  const unsigned int imgHeight = img.height();
  const unsigned int imgDepth = img.depth();
  const unsigned int imgSpec = img.spectrum();

  std::cout << "Image width: " << imgWidth << std::endl;
  std::cout << "Image height: " << imgHeight << std::endl;
  std::cout << "Image depth: " << imgDepth << std::endl;
  std::cout << "Image spectrum: " << imgSpec << std::endl;

  cimg_library::CImg<unsigned char> imgMod(imgWidth, imgHeight, imgDepth, imgSpec, 255);

  unsigned char purple[3] = {255, 0, 255};
  img.draw_text(100, 100, "YOLO", purple);
  imgMod.draw_text(100, 100, "YOLO", purple);

  img.save("testPhoto_YOLO.jpg");
  imgMod.save("testPhoto_YOLOMOD.jpg");

  return 0;
}
