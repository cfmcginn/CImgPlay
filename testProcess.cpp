#include <iostream>
#include <set>
#include <stdlib.h>
#include "CImg/CImg.h"
//#include "boost_1_56_0/multi_array.hpp"

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

  const int pixNum = 1000;
  std::set<int>* pixSet_p = new std::set<int>;

  while(pixSet_p->size() < pixNum){
    int inNum = rand()%imgWidth*1000 + rand()%imgHeight;
    pixSet_p->insert(inNum);
  }

  for(std::set<int>::iterator it = pixSet_p->begin(); it != pixSet_p->end(); it++){
    std::cout << *it << ", " << (*it)/1000 << ", " << (*it)%1000<< std::endl;

    for(int rgbIter = 0; rgbIter < 3; rgbIter++){
      imgMod((*it)/1000, (*it)%1000, 0, rgbIter) = 255;
    }
  }

  img.save("testPhoto_YOLO.jpg");
  imgMod.save("testPhoto_YOLOMOD.jpg");

  pixSet_p->clear();
  delete pixSet_p;

  return 0;
}


void rgbToGrey(cimg_library::CImg<unsigned char>* inRGB_p, cimg_library::CImg<unsigned char>& outGrey)
{
  const int rgbNum = 3;
  const float rgbWeight[rgbNum] = {0.2989, 0.5870, 0.1140};

  const unsigned int imgWidth = inRGB_p->width();
  const unsigned int imgHeight = inRGB_p->height();

  for(int widthIter = 0; widthIter < imgWidth; widthIter++){
    for(int heightIter = 0; heightIter < imgHeight; heightIter++){
      float lum = 0.0;

      for(int lumIter = 0; lumIter < rgbNum; lumIter++){
	lum += (float)inRGB_p->atXYZ(widthIter, heightIter, 0, lumIter)*rgbWeight[lumIter];
      }

      for(int lumIter = 0; lumIter < rgbNum; lumIter++){
	outGrey(widthIter, heightIter, 0, lumIter) = (unsigned char)lum;
      }
    }
  }

  return;
}
