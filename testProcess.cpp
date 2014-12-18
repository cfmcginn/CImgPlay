#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include "CImg.h"

void rgbToGrey(cimg_library::CImg<unsigned char>* inRGB_p, cimg_library::CImg<unsigned char>& outGrey);
float getMedianGreyScale(cimg_library::CImg<unsigned char>* inGrey_p);

int main(int argc, char* argv[])
{
  if(argc!=3){
    std::cout << "Usage: testProcess <inFileName> <nPhoto>" << std::endl;
    return 1;
  }

  cimg_library::CImg<unsigned char> img(argv[1]);
  const unsigned int imgWidth = img.width();
  const unsigned int imgHeight = img.height();
  const unsigned int imgDepth = img.depth();
  const unsigned int imgSpec = img.spectrum();
  cimg_library::CImg<unsigned char> imgMod(imgWidth, imgHeight, imgDepth, imgSpec, 255);
  rgbToGrey(&img, imgMod);

  float medianLum = 0;
  medianLum = getMedianGreyScale(&imgMod);

  const int nOutPic = std::atoi(argv[2]);
  int pixNum[nOutPic];
  cimg_library::CImg<unsigned char>* imgSamples[nOutPic];
  for(int pixIter = 0; pixIter < nOutPic; pixIter++){
    pixNum[pixIter] = pixIter*imgWidth*imgDepth/nOutPic;

    imgSamples[pixIter] = new cimg_library::CImg<unsigned char>;
  }


  std::set<int>* pixSet_p = new std::set<int>;
  while(pixSet_p->size() < imgWidth*imgDepth*(nOutPic-1)/nOutPic){
    int inNum = rand()%imgWidth*1000 + rand()%imgHeight;
    pixSet_p->insert(inNum);
  }

  /*
  for(std::set<int>::iterator it = pixSet_p->begin(); it != pixSet_p->end(); it++){
    for(int rgbIter = 0; rgbIter < 3; rgbIter++){
      imgMod((*it)/1000, (*it)%1000, 0, rgbIter) = 255;
    }
  }
  */

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

  for(int wIter = 0; wIter < imgWidth; wIter++){
    for(int hIter = 0; hIter < imgHeight; hIter++){
      float lum = 0.0;

      for(int lumIter = 0; lumIter < rgbNum; lumIter++){
	lum += (float)inRGB_p->atXYZ(wIter, hIter, 0, lumIter)*rgbWeight[lumIter];
      }

      for(int lumIter = 0; lumIter < rgbNum; lumIter++){
	outGrey(wIter, hIter, 0, lumIter) = (unsigned char)lum;
      }
    }
  }

  return;
}


float getMedianGreyScale(cimg_library::CImg<unsigned char>* inGrey_p)
{
  const unsigned int imgWidth = inGrey_p->width();
  const unsigned int imgHeight = inGrey_p->height();

  std::vector<float>* lumVect_p = new std::vector<float>;

  for(int wIter = 0; wIter < imgWidth; wIter++){
    for(int hIter = 0; hIter < imgHeight; hIter++){
      lumVect_p->push_back((float)inGrey_p->atXYZ(wIter, hIter, 0, 0));
    }
  }

  std::sort(lumVect_p->begin(), lumVect_p->end());

  const int vSize = lumVect_p->size();
  return lumVect_p->at(vSize/2);
}
