/**
 * @file Expression file is undefined on line 2, column 12 in file:///home/florian/git/steganoMessage/nbproject/licenseheader.txt.
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 2019.06.08
 * @brief
 */
/* 
 * File:   BitmapConverter.cpp
 * Author: Florian Leuze
 * 
 * Created on 8. Juni 2019, 18:13
 */

#include "../header/BitmapConverter.h"
#include <turbojpeg.h>


#define THROW(action, message) { \
  printf("ERROR in line %d while %s:\n%s\n", __LINE__, action, message); \
  retval = -1;  goto bailout; \
}

//#define THROW_TJ(action)  THROW(action, tjGetErrorStr2(tjInstance))

#define THROW_UNIX(action)  THROW(action, strerror(errno))

#define DEFAULT_SUBSAMP  TJSAMP_444
#define DEFAULT_QUALITY  95

const char *subsampName[TJ_NUMSAMP] = {
  "4:4:4", "4:2:2", "4:2:0", "Grayscale", "4:4:0", "4:1:1"
};

const char *colorspaceName[TJ_NUMCS] = {
  "RGB", "YCbCr", "GRAY", "CMYK", "YCCK"
};

tjscalingfactor *scalingFactors = NULL;
int numScalingFactors = 0;



BitmapConverter::BitmapConverter() {
}

BitmapConverter::BitmapConverter(std::string p, BitmapHeader* bH, BitmapArray* bD):path(p), bHeader(bH), bData(bD) {
    
}
    
BitmapConverter::BitmapConverter(const BitmapConverter& orig) {
}

BitmapConverter::~BitmapConverter() {
}

int BitmapConverter::readJpg(){
    tjscalingfactor scalingfactor = {1, 1};//?
    int outSubsamp = -1, outQual = -1; //?
    tjtransform xform;//?
    int flags = 0;//?
    int width, height;
    FILE *jpegfile = NULL;
    unsigned char *imgBuf = NULL, *jpegBuf = NULL;
    int retval = 0, i, pixelFormat = TJPF_UNKNOWN;
    tjhandle tjInstance = NULL;
    
   if((scalingFactors = tjGetScalingFactors(&numScalingFactors)) == NULL)
        THROW_TJ("getting scaling factors");
    memset(&xform, 0, sizeof(tjtransform)); //setting the tjtransform struct to 0
    
    long size;
    int inSubsamp, inColorspace;
bailout:
    //if (imgBuf) tjFree(imgBuf);
    //if (tjInstance) tjDestroy(tjInstance);
    //if (jpegBuf) tjFree(jpegBuf);
   // if (jpegFile) fclose(jpegFile);
    return retval;
}
