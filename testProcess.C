#include "CImg/CImg.h"

int main()
{
  cimg_library::CImg<unsigned char> image("testPhoto.jpg");
  //  const unsigned char red[] = {255,0,0}, green[] = {0,255,0}, blue[] = {0,0,255};
  image.blur(2.5);

  return 0;
}
