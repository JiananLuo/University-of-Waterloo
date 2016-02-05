#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

int widthFlag=0; //a flag that tells the program the first width of the image is set


struct Pixel
{
    unsigned int r;  // value for red
    unsigned int g;  // value or green
    unsigned int b;  // value for blue
};

struct PpmArray
{
    int size;      // number of pixels the array currently holds
    int capacity;  // number of pixels the array could hold, given current
                   // memory allocation to pixels
    int width;     // width of image
    int height;    // height of image
    Pixel *pixels;
};
/*********** flipHorizontal ********
     Purpose: This function consume a reference of a PpmArray struct and flip the image in the struct
     Returns: This function returns nothing but make change to the image in the struct
************************************/
void flipHorizontal(PpmArray &ppm)
{
  int size=ppm.size; //ppm size
  int width=ppm.width; //ppm width
  int height=ppm.height; //ppm height
  Pixel *newPixel=new Pixel[ppm.capacity];
  for(int k=0; k<size; k++)
  {
    int h=k/width;
    int w=k%width;
    newPixel[h * width + w] = ppm.pixels[h * width + width - w - 1];
  }
  delete [] ppm.pixels;
  ppm.pixels=newPixel;
}
/*********** rotate ****************
     Purpose: This function consume a reference of a PpmArray struct and rotate the image in the struct
     Returns: This function returns nothing but make change to the image in the struct
************************************/
void rotate(PpmArray &ppm)
{
  int size=ppm.size;
  int width=ppm.width;
  int height=ppm.height;
  Pixel *newPixel=new Pixel[ppm.capacity];
  for(int k=0; k<size; k++)
  {
    int i=k/width;
    int j=k%width;
    newPixel[j * height + i] = ppm.pixels[width * (height - i - 1) + j];
  }
  delete [] ppm.pixels;
  ppm.pixels=newPixel;
  ppm.width=height;
  ppm.height=width;
}
/*********** sepia *****************
     Purpose: This function consume a reference of a PpmArray struct and sepia the image in the struct
     Returns: This function returns nothing but make change to the image in the struct
************************************/
void sepia(PpmArray &ppm)
{
  int size=ppm.size;
  for(int k=0; k<size; k++)
  {
    int r=ppm.pixels[k].r;
    int g=ppm.pixels[k].g;
    int b=ppm.pixels[k].b;
    ppm.pixels[k].r = r *.393 + g * .769 + b * .189;
    if(ppm.pixels[k].r > 255)
      ppm.pixels[k].r=255;
    ppm.pixels[k].g = r *.349 + g * .686 + b * .168;
    if(ppm.pixels[k].g > 255)
      ppm.pixels[k].g=255;
    ppm.pixels[k].b = r *.272 + g * .534 + b * .131;
    if(ppm.pixels[k].b > 255)
      ppm.pixels[k].b=255;
  }
}
/*********** doublePixel ***********
     Purpose: This function consume a reference of a PpmArray struct and double the capacity of the pixels array in the struct
     Returns: This function returns nothing but make change to the image in the struct
************************************/
void doublePixel(PpmArray * maPPM)
{
  maPPM->capacity*=2;
  Pixel *tmpPpmArray=new Pixel[maPPM->capacity];
  for(int k=0; k<maPPM->size; k++)
  {
    tmpPpmArray[k].r=maPPM->pixels[k].r;
    tmpPpmArray[k].g=maPPM->pixels[k].g;
    tmpPpmArray[k].b=maPPM->pixels[k].b;
  }
  delete [] maPPM->pixels;
  maPPM->pixels=tmpPpmArray;
}
/*********** deleto ****************
     Purpose: This function consume a reference of a PpmArray struct and delete the pixels in it and itself
     Returns: This function returns nothing but delete the whole struct
************************************/
void deleto(PpmArray * maPPM)
{
  delete [] maPPM->pixels;
  delete maPPM;
}
/************* main ****************
     Purpose: This function is the main function basically it does everything, calls helper function whenever it need
     Returns: STATE
************************************/
int main()
{
  PpmArray *maPPM = new PpmArray;
  maPPM->size=0;
  maPPM->capacity=5;
  maPPM->width=0;
  maPPM->height=0;
  maPPM->pixels=new Pixel[maPPM->capacity];

  string s;
  while(getline(cin,s))
  {
    int someR, someG, someB, maW, maH;
    stringstream maSS(s);
    if(maSS>>someR>>someG>>someB)
    {
      if(someR<0 || someG<0 || someB<0 || someR>255 || someG>255 || someB>255)
      {
        deleto(maPPM);
        return -1;
      }//return if a pixel contains a number that less than 0 or greater than 255
      maPPM->pixels[maPPM->size].r=someR;
      maPPM->pixels[maPPM->size].g=someG;
      maPPM->pixels[maPPM->size].b=someB;
      maPPM->size++;
      int currentWidth=1;
      while(true)
      {
        if(maSS>>someR)
        {
          if(maSS>>someG)
          {
            if(maSS>>someB)
            {
              if(maPPM->size == maPPM->capacity)
              {
                doublePixel(maPPM);
              }
              maPPM->pixels[maPPM->size].r=someR;
              maPPM->pixels[maPPM->size].g=someG;
              maPPM->pixels[maPPM->size].b=someB;
              maPPM->size++;

              currentWidth++;
            }
            else
            {
              deleto(maPPM);
              return -1;
            }//return if a pixel contains only 2 number
          }
          else
          {
            deleto(maPPM);
            return -1;
          }//return if a pixel contains only 1 number
        }
        else
          break;
      }
      if(widthFlag==0)//after find the first pixel line width
      {
        maPPM->width=currentWidth;
        widthFlag=1;//set the flag to 1
        maPPM->height=1;
      }
      else if(maPPM->width == currentWidth)
        maPPM->height++;
      else
      {
        deleto(maPPM);
        return -1;
      }//return if the current width is not equal to the width find previous
    }
    else if(someR && someG)
    {
      maW=someR;
      maH=someG;
      if(maW!=maPPM->width || maH!=maPPM->height)
      {
        deleto(maPPM);
        return -1;
      }//return if the width and height are not equal to the width and heightfind previously
      string ssss;//temp string which check if cin are correct command
      while((cin >> ssss))
      {
        if(ssss == "rotate")
          rotate(*maPPM);
        else if(ssss == "sepia")
          sepia(*maPPM);
        else if(ssss == "flip")
          flipHorizontal(*maPPM);
        else
        {
          deleto(maPPM);
          return -1;
        }//return if the command is not either rotate sepia or flip
      }
    }
  }
  if(maPPM->width==0 || maPPM->height==0)//return if the width or height of the image is 0
  {
    deleto(maPPM);
    return -1;
  }
//start print
  cout << "P3" << endl;
  cout << maPPM->width << " " << maPPM->height << endl;
  cout << "255" << endl;
  for (int k=0; k<maPPM->size; k++)
  {
    cout << maPPM->pixels[k].r << " " << maPPM->pixels[k].g << " " << maPPM->pixels[k].b;
    if(((k+1)%maPPM->width) == 0)
      cout << endl;
    else
      cout << " ";
  }
  deleto(maPPM);
  return 0;
}
