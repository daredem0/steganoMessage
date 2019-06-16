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
#include <unistd.h>
#include "../header/BitmapHeader.h"
#include "../header/BitmapArray.h"
#include "./ErrorHandler.h"
#include <sstream>
#include <ios>
#include <sys/stat.h>
#include <dirent.h>

/*detect OS and define constants which will be evaluated. Needs to be done because get currenct wcdir depends on os*/
#if defined (__linux__)
    #define LINUX 1
    #define MAC 0
    #define PATHLINUX get_current_dir_name()
    #define OPENDIR_LINUX(log) opendir(log) 
#define MKDIR_LINUX(argA, argB) mkdir(argA, argB)
#elif defined (__APPLE__)
    #define MAC 1
    #define LINUX 0
    //#define PATHMAC /*************TOBI HIER ***************/
    #define PATHLINUX NULL;
#endif

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
     * @param ErrorHandler *errH - Errorhandler 
    */
    Image(std::string p, ErrorHandler *errH);
    /**
     * @brief Copy Constructor. 
     * @param orig - Reference to original Image-type object
     */
    Image(const Image& orig);
    /**
     * Standard deconstructor.
     */
    virtual ~Image();
    
    ///////////////////////////////////************************************************************/
    /**GETTERS**///////////////////////
    ///////////////////////////////////
    /**
     * @brief Returns the path of the image.
     * @return std::string including stored path.
     */
    std::string getPath();
    /**
     * @brief Getter for bitmapHeader
     * @return BitmapHeader type pointer to BitmapHeader
     */
    BitmapHeader *getBitmapHeader();
    /**
     * @brief Getter for bitmapArray
     * @return BitmapArray type pointer to BitmapArray
     */
    BitmapArray *getBitmapArray();
    
    ///////////////////////////////////************************************************************/
    /**SETTERS**///////////////////////
    ///////////////////////////////////
    /**
     * @brief Stores path in this.
     * @param std::string p - Path to the image file.
     */
    void setPath(std::string p);
    /**
     * @brief Sets flags for while reading/writing filters
     * @return returns integer containing error code
     */
    int setFilter(std::string gr, std::string col);
    /**
     * @brief Sets mode and path for text generation
     * @param std::string path - path to output file
     * @param std::ios mode - mode (trunc or app, dont fiddle with in/out!)
     */
    void setLogMode(std::string path, std::ios_base::openmode mode);
    
    ///////////////////////////////////************************************************************/
    /**EVALUATIONS**///////////////////
    ///////////////////////////////////
    /**
     * @brief Identifies the file format of the loaded image. Possible so far: .bmp; .jpg,; .gif; .png
     * @return std::string containing format information (JPEG/BITMAP/PNG/GIF)
     */
    static std::string identifyFileFormat(std::string path);
    
    ///////////////////////////////////************************************************************/
    /**OTHER METHODS**/////////////////
    ///////////////////////////////////
    /**
     * @brief Calls Constructors for BitMapHeader and BitMapArray and reads information from image
     * @return returns integer containing error code
     */
    virtual int readImage();
    /**
     * @brief Prints text file to terminal (just for convenience and to check if ifstream works
     * @param std::string containing path to text file
     */
    int generateBitmap();
    /**
     * @brief Generates txt file containing bitmap information as hex values
     * @return returns integer containing error code
     */
    int printTextFile(std::string p);
    /**
     * @brief Writes information to a text file !!Not debugged!! !!No Error Handling implemented!! !!Dont use!!
     * @param std::string t - contains text that is to be written
     * @param std::string p - contains path to text file
     */
    int writeTextFile(std::string t, std::string p);
    
    /**
     * @brief Generates new bitmap file
     * @return returns integer containing error code
     */
    int bmpToTxt();
    /**
     * @brief Converts a byte to hex string
     * @return std:string containing hex value
     */
    static std::string byteToHex(uint8_t v);
    /**
     * @brief Helps bmpToTxt to do the conversion. Responsible to converting x > 9 into A-F
     * @return std:string containing hex value
     */
    static std::string decToHex(uint8_t v);
protected:
    std::string path; /**< Imagepath*/
    BitmapHeader *header; /**< Pointer to BitmapHeader object containing header information*/
    BitmapArray *array; /**< Pointer to BitmapArray object containing imagedata*/
    ErrorHandler *errHandle;/**< Pointer to ErrorHandler type object that was constructed when this was constructed.*/
    std::string filterModeGrey;/**<Flag for while reading/writing filters*/
    std::string filterModeCol;/**<Flag for while reading/writing filters*/
    
    std::string logfilePath;/**<path to logfile*/
    std::ios_base::openmode logfileMode;/**<mode of logfile, either std::ios::trunc or std::ios::app, dont fiddle with in/out!*/
    
    /**
     * @brief Checks if a file already exists
     * @return boolean value - true for exists already, false for not
     */
    bool exists(const std::string& name);
};

#endif /* IMAGE_H */