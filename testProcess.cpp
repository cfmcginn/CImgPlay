#include <iostream>
#include "CImg/CImg.h"

int main()
{
  const float redWeight = 0.2989;
  const float greenWeight = 0.5870;
  const float blueWeight = 0.1140;

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

  for(int widthIter = 0; widthIter < imgWidth; widthIter++){
    for(int heightIter = 0; heightIter < imgHeight; heightIter++){

      float lum = (float)img(widthIter, heightIter, 0, 0)*redWeight + (float)img(widthIter, heightIter, 0, 1)*greenWeight + (float)img(widthIter, heightIter, 0, 2)*blueWeight;

      imgMod(widthIter, heightIter, 0, 0) = (unsigned char)lum;
      imgMod(widthIter, heightIter, 0, 1) = (unsigned char)lum;
      imgMod(widthIter, heightIter, 0, 2) = (unsigned char)lum;

    }
  }

  unsigned char purple[3] = {255, 0, 255};
  img.draw_text(100, 100, "YOLO", purple);
  imgMod.draw_text(100, 100, "YOLO", purple);

  imgMod.blur(2.5);

  img.save("testPhoto_YOLO.jpg");
  imgMod.save("testPhoto_YOLOMOD.jpg");

  return 0;
}
