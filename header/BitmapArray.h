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
    BitmapArray(std::string p, uint32_t b, uint32_t w, uint32_t h, uint32_t bit);
    /**
     * @brief Copy Constructor. 
     * @param orig - Reference to original BitmapArray-type object
     */
    BitmapArray(const BitmapArray& orig);
    /**
     * Standard deconstructor.
     */
    virtual ~BitmapArray();
    int readArray();
    void printArray();
    std::vector<std::vector<uint32_t>> getBData();
    std::ofstream getBDataStream();
    std::string infuse(std::string message);
    
private:
    std::vector<std::vector<uint32_t>> bData; 
    std::string path;
    uint32_t width;
    uint32_t height;   
    uint32_t bitOffset;
    uint32_t bitCount;
    void read(std::ifstream& f);
    uint32_t genInt(char* c, size_t s);
    void printArray(char* c, size_t s);
};

#endif /* BITMAPARRAY_H */

