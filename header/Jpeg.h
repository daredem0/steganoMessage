/**
 * @file Expression file is undefined on line 2, column 12 in file:///home/florian/git/steganoMessage/nbproject/licenseheader.txt.
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 2019.06.08
 * @brief
 */
/* 
 * File:   Jpeg.h
 * Author: Florian Leuze
 *
 * Created on 8. Juni 2019, 18:13
 */

#ifndef JPEG_H
#define JPEG_H


#include <stdio.h>
#if defined (__linux__)
#include "jpeglib.h"
#elif defined (__APPLE__)
#include "/usr/local/Cellar/jpeg/9c/include/jpeglib.h"
#endif
#include <setjmp.h>
#include <stdint.h>
#include "Image.h"

class Jpeg : public Image{
public:
    Jpeg();
    Jpeg(std::string p, ErrorHandler* err);
    Jpeg(const Jpeg& orig);
    virtual ~Jpeg();
    int readImage();
private:
    BitmapHeader *bHeader;
    BitmapArray *bData;
    //std::string path;

};

#endif /* JPEG_H */

