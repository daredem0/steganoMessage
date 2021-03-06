/**
 * @file Expression file is undefined on line 2, column 12 in file:///home/florian/git/steganoMessage/nbproject/licenseheader.txt.
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 2019.05.24
 * @brief BitmapHeader-Class header file
 */
/* 
 * File:   BitmapHeader.h
 * Author: Florian Leuze
 *
 * Created on 24. Mai 2019, 22:46
 */

#ifndef BITMAPHEADER_H
#define BITMAPHEADER_H

#include <fstream>
#include <iostream>
#include "./ErrorHandler.h"

/**
 *@brief Header struct contains BitmapHeader Information and leftover
 */
struct __attribute__((__packed__)) Header{ //packed to prevent compiler from implementing padding bytges. Careful, order of this struct is as per bitmap standard defined. Dont change it even for convenience
    uint16_t bfType;/**< ASCII COde, usually contains BM*/
    uint32_t bfSize;/**< size of the file*/
    uint32_t bfReserved;/**< Reserved, software dependend*/
    uint32_t bfOffBits;/**< Offset between image data and begin of file*/ //we need this one
    //information header
    uint32_t biSize;/**< size of information header*/
    uint32_t biWidth;/**< width in pixel*/
    uint32_t biHeight;/**< height in pixel*/
    uint16_t biPlanes;/**< oputdated*/
    uint16_t biBitCount;/**< Color Depth in bit*/
    uint32_t biCompression;/**< Compression, 0=not compressed; 1=8bpp rle; 1=4bpp rle; 3=uncompressed and color coded*/
    uint32_t biSizeImage;/**< biSizeImage*/
    uint32_t biXPelsPerMeter;/**< biXPelsPerMeter*/
    uint32_t biYPelsPerMeter;/**< biYPelsPerMeter*/
    uint32_t biClrUsed;/**< biClrUsed*/
    uint32_t biClrImportant;/**< biClrImportant*/
    unsigned char leftover[5000];/**< leftover of header */
    char bfTypeA;/**< bfType first hex value*/
    char bfTypeB;/**< bfType second hex value*/
    uint16_t oldBitCount;
};

 /**
 *@brief BitmapHeader Class contains header information extracted from bitmap file
 */
class BitmapHeader {
public:
    //CONSTRUCTORS/DECONSTRUCTORS/************************************************************/
    /**
    * @brief Standard constructor.
    */
    BitmapHeader();
    /**
    * @brief Non-Standard Constructor, stores p in path member and calls readHeader with p as argument
    * @param ErrorHandler *errH - Errorhandler 
    */
    BitmapHeader(std::string p, ErrorHandler *errH);
    /**
    * @brief Non-Standard Constructor, stores p in path member and calls readHeader with p as argument
    * @param ErrorHandler *errH - Errorhandler 
    */
    BitmapHeader(std::string p, ErrorHandler *errH, bool read);
    /**
    * @brief Non-Standard Constructor, takes arguments for all members and stores them. Outdated, not used
    * @param ErrorHandler *errH - Errorhandler 
    */
    BitmapHeader(const BitmapHeader& orig);
    /**
     * Standard deconstructor.
     */
    virtual ~BitmapHeader();
    
    ///////////////////////////////////************************************************************/
    /**GETTERS**///////////////////////
    ///////////////////////////////////
    /**
     * @brief Returns pointer to char array containing the complete fileheader extracted/converted from original file
     * @return char* pointer to char
     */
    char* getHeader();
    /**
     * @brief Getter for bfSize
     * @return uint32_t bfSize
     */
    uint32_t getSize();
    /**
     * @brief Getter for bfOffBits
     * @return uint32_t bfOffBits
     */
    uint32_t getOffBits();
    /**
     * @brief Getter for BiSize
     * @return uint32_t BiSize
     */
    uint32_t getBiSize();
    /**
     * @brief Getter for BiWidth
     * @return uint32_t BiWidth
     */
    uint32_t getWidth();
    /**
     * @brief Getter for BiHeight
     * @return uint32_t BiHeight
     */
    uint32_t getHeight();
    /**
     * @brief Getter for BiSizeImage
     * @return uint32_t BiSizeImage
     */
    uint32_t getSizeImage();
    /**
     * @brief Getter for BiBitCount
     * @return uint32_t BiBitCount
     */
    uint32_t getBitCount();
    /**
     * @brief Getter for OldBiBitCount
     * @return uint32_t BiBitCount
     */
    uint32_t geOldtBitCount();
    /**
     * @brief Returns Header type Pointer to header struct to access members.
     * @return Header* type pointer to struct
     */
    Header* getHeaderStruct();
    
    ///////////////////////////////////************************************************************/
    /**OTHER METHODS**/////////////////
    ///////////////////////////////////
    /**
     * @brief Overloaded readHeader, opens ifstream to path and calls read private method
     * @param std::string p - Path to bmp file
     * @return Integer containing error codes
     */
    int readHeader(std::string p);
    /**
     * @brief Opens ifstream to path and calls read private method
     * @return Integer containing error codes
     */
    int readHeader();
    /**
     * @brief Prints all stored values, attention, values not initialized, should be fixed in constructor
     */
    void printHeader();
    /**
     * @brief Takes uint16_t Header.bfType and writes lower bits to uint8_t Header.bfTypeA and upper bits to uint8_t Header.bfTypeB. Should always be done after reading of header
     * @return Integer containing error codes
     */
    int fixType();
    
private:
    Header header;/**< Struct containing 54byte header information + bitOffSet - 54 byte leftover */
    char *headerStream; /**< Pointer to char array containing the complete header */
    std::string path;/**< Imagepath*/
    ErrorHandler *errHandle;/**< Pointer to ErrorHandler type object that was constructed when this was constructed.*/
    
    /**
     * @brief reads header information from ifstream
     * @return Not yet implemented, should try catch for error handling + return error codes
     */
    int read(std::ifstream& f);
};

#endif /* BITMAPHEADER_H */