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
#include "Filter.h"

/**
 *@brief Jpeg class to load a jpeg image and autoatically convert it into a bitmap. Overloads readImage from Image class
 */
class Jpeg : public Image{
public:
    //CONSTRUCTORS/DECONSTRUCTORS/************************************************************/
    /**
    * @brief Standard constructor.
    */
    Jpeg();
    /**
    * @brief Non-Standard constructor. Stores path and ErrorHandler object for usage.
     * @param std::string p - path to file
     * @param ErrorHandler* err - pointer to ErrorHandler type object
    */
    Jpeg(std::string p, ErrorHandler* err);
    /**
     * @brief Copy Constructor. 
     * @param orig - Reference to original Jpeg-type object
     */
    Jpeg(const Jpeg& orig);
    /**
     * Standard deconstructor. 
     */
    virtual ~Jpeg();
    
    ///////////////////////////////////************************************************************/
    /**OTHER METHODS**/////////////////
    ///////////////////////////////////
    /**
     * @brief Overloaded readImage method. Reads the jpeg file using jpeglib, decompresses it and builds the BitmapArray and BitmapHeader objects to store the data there
     * @return returns integer containing error code
     */
    int readImage();
private:

};

#endif /* JPEG_H */

