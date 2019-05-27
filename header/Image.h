/**
 * @file Expression file is undefined on line 2, column 12 in file:///home/florian/git/steganoMessage/nbproject/licenseheader.txt.
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 2019.05.22
 * @brief Image-Class header file
 */
/* 
 * File:   Image.h
 * Author: Florian Leuze
 *
 * Created on 22. Mai 2019, 19:57
 */

#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
#include "../header/BitmapHeader.h"
#include "../header/BitmapArray.h"

/**
 *@brief Image Class is implemented to store the bitstream of the image file as well as the filepath and to offer easy to use methods to extract information from the image file
 */
class Image {
public:
    //CONSTRUCTORS/DECONSTRUCTORS/************************************************************/
    /**
    * @brief Standard constructor.
    */
    Image();
    /**
    * @brief Non-Standard constructor. Initializes the object with a path.
    * @param std::string p - path that is to be stored in the object.
    */
    Image(std::string p);
    /**
     * @brief Copy Constructor. 
     * @param orig - Reference to original Image-type object
     */
    Image(const Image& orig);
    /**
     * Standard deconstructor.
     */
    virtual ~Image();
    /**
     * @brief Returns the path of the image.
     * @return std::string including stored path.
     */
    std::string getPath();
    /**
     * @brief Stores path in this.
     * @param std::string p - Path to the image file.
     */
    void setPath(std::string p);
    /**
     * @brief Calls Constructors for BitMapHeader and BitMapArray and reads information from image
     * @return returns integer containing error code
     */
    int readImage();
    /**
     * @brief Prints text file to terminal (just for convenience and to check if ifstream works
     * @param std::string containing path to text file
     */
    void printTextFile(std::string p);
    /**
     * @brief Writes information to a text file !!Not debugged!! !!No Error Handling implemented!! !!Dont use!!
     * @param std::string t - contains text that is to be written
     * @param std::string p - contains path to text file
     */
    void writeTextFile(std::string t, std::string p);
    /**
     * @brief Getter for bitmapHeader
     * @return BitmapHeader type pointer to BitmapHeader
     */
    BitmapHeader *getBitmapHeader();
    
    int generateBitmap();
private:
    std::string path; /**< Imagepath*/
    BitmapHeader *header; /**< Pointer to BitmapHeader object containing header information*/
    BitmapArray *array;
};

#endif /* IMAGE_H */

