/**
 * @file Expression file is undefined on line 2, column 12 in file:///home/florian/git/steganoMessage/nbproject/licenseheader.txt.
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 2019.06.08
 * @brief
 */
/* 
 * File:   BitmapConverter.h
 * Author: Florian Leuze
 *
 * Created on 8. Juni 2019, 18:13
 */

#ifndef BITMAPCONVERTER_H
#define BITMAPCONVERTER_H


#include "./BitmapHeader.h"
#include "./BitmapArray.h"
//#include "jpeglib.h"
//#include "jerror.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <turbojpeg.h>

class BitmapConverter {
public:
    BitmapConverter();
    BitmapConverter(std::string p, BitmapHeader* bH, BitmapArray* bD);
    BitmapConverter(const BitmapConverter& orig);
    virtual ~BitmapConverter();
private:
    BitmapHeader *bHeader;
    BitmapArray *bData;
    std::string path;
    int readJpg();

};

#endif /* BITMAPCONVERTER_H */

