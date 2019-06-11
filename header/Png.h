/**
 * @file Expression file is undefined on line 2, column 12 in file:///home/florian/git/steganoMessage/nbproject/licenseheader.txt.
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 2019.06.11
 * @brief
 */
/* 
 * File:   PNGraphics.h
 * Author: Florian Leuze
 *
 * Created on 11. Juni 2019, 13:32
 */

#ifndef PNGCLASS_H //to avoid collision with libpng include armor
#define PNGCLASS_H

#include "Image.h"
#include "png.h"
#include "ErrorHandler.h"
#include <array>

/**
 *@brief Png class to load a png image and autoatically convert it into a bitmap. Overloads readImage from Image class
 */
class Png : public Image{
public:
    //CONSTRUCTORS/DECONSTRUCTORS/************************************************************/
    /**
    * @brief Standard constructor.
    */
    Png();
    /**
    * @brief Non-Standard constructor. Stores path and ErrorHandler object for usage.
     * @param std::string p - path to file
     * @param ErrorHandler* err - pointer to ErrorHandler type object
    */
    Png(std::string p, ErrorHandler* err);
    /**
     * @brief Copy Constructor. 
     * @param orig - Reference to original Jpeg-type object
     */
    Png(const Png& orig);
    /**
     * Standard deconstructor. 
     */
    virtual ~Png();
    
    ///////////////////////////////////************************************************************/
    /**OTHER METHODS**/////////////////
    ///////////////////////////////////
    /**
     * @brief Overloaded readImage method. Reads the jpeg file using jpeglib, decompresses it and builds the BitmapArray and BitmapHeader objects to store the data there
     * @return returns integer containing error code
     */
    int readImage();
private:
    png_structp png_ptr;/**< png_structp is used internally to keep track of the current state of the png image*/
    png_infop info_ptr;/**< png_infop is used to indicate what the state of the pnc will be after user transformations are performed*/
    bool bKgdFlag; /**< backgroundcolor flag, active if background color is set in file*/
    uint32_t width;/**< temporary storage for width*/
    uint32_t height; /**< temporary storage for height*/
    int bDepth;/**< temporary storage for bitcount per color*/
    int cType;/**< temporary storage for color type compelling to png standard*/
    unsigned char *pData; /**< data storage*/
        
    /**
    * @brief initializes everything needed to read the png file
     * @param FILE *inFile- pointer to input file
     * @param uint32_t *pWidth - pointer to temporary storage for image width
     * @param uint32_t *pHeight - pointer to temporary storage for image height
     * @param int *bitDepth - pointer to temporary storage for bitcount per color
     * @param int *colorType - pointer to temporary storage for color type compelling to png standard
     * @return integer with error code
    */
    int readPng_init(FILE *inFile, uint32_t *pWidth, uint32_t *pHeight, int *bitDepth, int *colorType);
    /**
    * @brief Checks if backgroundcolor is set and writes it to argument addresses
     * @param uint8_t *red - pointer to storage for red color
     * @param uint8_t *green - pointer to storage for green color
     * @param uint8_t *blue - pointer to storage for blue color
     * @return integer with error code
    */
    int readpng_get_bgcolor(uint8_t *red, uint8_t *green, uint8_t *blue);
    /**
    * @brief Reads the image header and data
     * @param double display_exponent - gamma value
     * @param int *pChannels - pointer to storage for color channels
     * @param uint8_t *blue - pointer to storage for rowbytes
     * @return integer with error code
    */
    int readpng_get_image(double display_exponent, int *pChannels, unsigned long *pRowBytes);
    /**
    * @brief Frees all allocated memory except for image data
     * @return integer with error code
    */
    int readpng_cleanup();
    
};

#endif /* PNGCLASS_H */

