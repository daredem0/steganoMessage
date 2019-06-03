/**
 * @file Expression file is undefined on line 2, column 12 in file:///home/florian/git/steganoMessage/nbproject/licenseheader.txt.
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 2019.05.24
 * @brief BitmapArray-Class cpp file
 */
/* 
 * File:   BitmapArray.h
 * Author: Florian Leuze
 *
 * Created on 24. Mai 2019, 22:46
 */

#ifndef BITMAPARRAY_H
#define BITMAPARRAY_H

#include <vector>
#include <fstream>
#include <iterator>
#include <iostream>
#include "./ErrorHandler.h"

/**
 *@brief BitmapArray Class is supposed to contain image data of the bitmap file
 */
class BitmapArray {
public:
    //CONSTRUCTORS/DECONSTRUCTORS/************************************************************/
    /**
    * @brief Standard constructor.
    */
    BitmapArray();
    //CONSTRUCTORS/DECONSTRUCTORS/************************************************************/
    /**
    * @brief Non-Standard constructor.
     * @param std::string p - Path to original file
     * @param uint32_t b - Offset of fileheader
     * @param uint32_t w - width of bitmap
     * @param uint32_t h - height of bitmap
     * @param uint32_t bit - color depth of bitmap
     * @param ErrorHandler *errH - Errorhandler 
     */
    BitmapArray(std::string p, uint32_t b, uint32_t w, uint32_t h, uint32_t bit, ErrorHandler *errH, std::string fm);
    /**
     * @brief Copy Constructor. 
     * @param orig - Reference to original BitmapArray-type object
     */
    BitmapArray(const BitmapArray& orig);
    /**
     * Standard deconstructor.
     */
    virtual ~BitmapArray();
    /**
     * @brief Opens original bitmap file and calls private read function. 
     * @return Integer containing error codes
     */
    int readArray();
    /**
     * @brief Prints all image data
     */
    void printArray();
    /**
     * @brief Returns the 2D std::vector containing image information.
     * @return std::vector<std::vector<uint32_t>> containing image data
     */
    std::vector<std::vector<uint32_t>> getBData();
    std::vector<std::vector<uint32_t>> *getBDataPointer();
    /**
     * @brief ***
     * @return std::string ***
     */
    std::string infuse(std::string message);
    int setFilter(std::string fm);
    
private:
    std::vector<std::vector<uint32_t>> bData; /**< 2D std::vector that contains the image data. Careful, its upside down. Bitmap data starts from lower left to upper right. First vector member is lower left. */
    std::string path; /**< path to original file*/
    uint32_t width; /**< width of original file*/
    uint32_t height;    /**< height of original file*/
    uint32_t bitOffset; /**< Headeroffest of original file*/
    uint32_t bitCount; /**< Color Depth of original file*/
    std::string filterMode;
    
    ErrorHandler *errHandle;
    
    /**
     * @brief Loads and decrypts the image data to the 2D std::vector member 
     * @param std::ifstream& f - to inputstream of original image
     * @return Integer containing error codes
     */
    int read(std::ifstream& f);
    /**
     * @brief Generates an uint32_t value from up to 4 Bytes
     * @param char* c - pointer to array containing up to 4 bytes
     * @param size_t s - size of array
     * @return uint32_t generated value
     */
    uint32_t genInt(char* c, size_t s);
    /**
     * @brief Loads and decrypts the image data to the 2D std::vector member 
     * @param char* c - pointer to array containing up to 4 bytes
     * @param size_t s - size of array
     */
    void printArray(char* c, size_t s);
};

#endif /* BITMAPARRAY_H */