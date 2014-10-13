#include <iostream>
#include "CImg/CImg.h"

void rgbToGrey(cimg_library::CImg<unsigned char>* inRGB_p, cimg_library::CImg<unsigned char>& outGrey);

int main(int argc, char* argv[])
{
  if(argc!=2){
    std::cout << "Usage: testProcess <inFileName>" << std::endl;
    return 1;
  }

  cimg_library::CImg<unsigned char> img(argv[1]);

  const unsigned int imgWidth = img.width();
  const unsigned int imgHeight = img.height();
  const unsigned int imgDepth = img.depth();
  const unsigned int imgSpec = img.spectrum();

  std::cout << "Image width: " << imgWidth << std::endl;
  std::cout << "Image height: " << imgHeight << std::endl;
  std::cout << "Image depth: " << imgDepth << std::endl;
  std::cout << "Image spectrum: " << imgSpec << std::endl;

  cimg_library::CImg<unsigned char> imgMod(imgWidth, imgHeight, imgDepth, imgSpec, 255);

  rgbToGrey(&img, imgMod);

  unsigned char purple[3] = {255, 0, 255};
  img.draw_text(100, 100, "YOLO", purple);
  imgMod.draw_text(100, 100, "YOLO", purple);

  img.save("testPhoto_YOLO.jpg");
  imgMod.save("testPhoto_YOLOMOD.jpg");

  return 0;
}


void rgbToGrey(cimg_library::CImg<unsigned char>* inRGB_p, cimg_library::CImg<unsigned char>& outGrey)
{
  const float redWeight = 0.2989;
  const float greenWeight = 0.5870;
  const float blueWeight = 0.1140;

  const unsigned int imgWidth = inRGB_p->width();
  const unsigned int imgHeight = inRGB_p->height();

  for(int widthIter = 0; widthIter < imgWidth; widthIter++){
    for(int heightIter = 0; heightIter < imgHeight; heightIter++){
      float lum = (float)inRGB_p->atXYZ(widthIter, heightIter, 0, 0)*redWeight + (float)inRGB_p->atXYZ(widthIter, heightIter, 0, 1)*greenWeight + (float)inRGB_p->atXYZ(widthIter, heightIter, 0, 2)*blueWeight;

      outGrey(widthIter, heightIter, 0, 0) = (unsigned char)lum;
      outGrey(widthIter, heightIter, 0, 1) = (unsigned char)lum;
      outGrey(widthIter, heightIter, 0, 2) = (unsigned char)lum;
    }
  }

  return;
}
