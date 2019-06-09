/**
 * @file Expression file is undefined on line 2, column 12 in file:///home/florian/git/steganoMessage/nbproject/licenseheader.txt.
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 2019.05.21
 * @brief SteganoMessage Class header file
 */
/* 
 * File:   SteganoMessage.h
 * Author: Florian Leuze
 *
 * Created on 21. Mai 2019, 14:42
 */

#ifndef STEGANOMESSAGE_H
#define STEGANOMESSAGE_H

#include "ErrorHandler.h"
#include "constants.h"
#include "Message.h"
//#include "Image.h"
#include <fstream>
#include <cmath>
#include <iomanip>
#include "Jpeg.h"

/**
 *@brief SteganoMessage class ist implemented to store values that are needed to be shared between all classes (for example errorHandler). 
 * It shall be constructed in the beginning and terminated in the very end of the runtime
 */
class SteganoMessage {
public:
    //CONSTRUCTORS/DECONSTRUCTORS/************************************************************/
    /**
    * @brief Standard constructor. Also creates new ErrorHandler object.
    */
    SteganoMessage();
    /**
     * @brief Copy Constructor. 
     * @param orig - Reference to original SteganoMessage-type object
     */
    SteganoMessage(const SteganoMessage& orig);
    /**
     * Standard deconstructor. Frees space allocated for int *err
     */
    virtual ~SteganoMessage();
    /**
     * @brief Fully initializes the SteganoMessage type object into a operatable state to ensure that other methods can be called safely. This NEEDS to be called before everything else
     * @param argc - argc from terminal (amount of sent arguments including argc)
     * @param *argv[] - *argv[] from terminal (sent arguments including argc in [0]
     * @return integer with error code
     */
    
    ///////////////////////////////////************************************************************/
    /**INIT**//////////////////////////
    ///////////////////////////////////
    int initialize(int argc, char *argv[]);
    
    ///////////////////////////////////************************************************************/
    /**Builders**//////////////////////
    ///////////////////////////////////
    /**
     * @brief Builds new Message type object
     * @param std::sring containing message
     * @return integer with error code
     */
    int buildMessage(std::string m);
    /**
     * @brief Builds new Image type object
     * @param std::string containing path to image
     * @return integer with error code
     */
    int buildImage(std::string path);
    
    ///////////////////////////////////************************************************************/
    /**GETTERS**///////////////////////
    ///////////////////////////////////
    /**
     * @brief Gives pointer to the ErrorHandler object stored in the SteganoMessage type object.
     * @return pointer to ErrorHandler
     */
    ErrorHandler *getErrHandle();
    /**
     * @brief Getter for pointer to message object
     * @return Pointer to Message
     */
    Message *getMessage();
    /**
     * @brief Getter for image object
     * @return Pointer to Image
     */
    Image *getImage();
    /**
     * @brief Getter for stored mode
     * @return std::string containing mode command or ""
     */
    std::string getMode();
    /**
     * @brief Getter for path verified flag
     * @return bool - true for verified, false for not verified. 
     */
    bool getPathVerified();
    
    ///////////////////////////////////************************************************************/
    /**SETTERS**///////////////////////
    ///////////////////////////////////
    /**
     * @brief Stores mode command in member, sets flag for modeset
     * @param std::string containing mode command
     * @return integer with error code
     */
    int setMode(std::string m);
    /**
     * @brief Prints values stored for mode and path
     */
    int setFilterMode(std::string mode);
    
    ///////////////////////////////////************************************************************/
    /**EVALUATIONS**///////////////////
    ///////////////////////////////////
    /**
     * @brief static method to quickly check if a path possibly makes sense
     * @param std::string containing the path that shall be checked
     * @return integer with error code
     */
    int checkPath(std::string p);
    /**
     * @brief Checks if a path exists
     * @param std::string containing the path that shall be checked
     * @return integer with error code
     */
    bool exists(std::string p);
    
    ///////////////////////////////////************************************************************/
    /**OTHER METHODS**/////////////////
    ///////////////////////////////////
    /**
     * @brief Handles the calling of following methods depending on the set mode. initialize needs to be called before this, else the sun will explode
     * @return integer with error code
     */
    int modeHandler();
    /**
     * @brief Sets the mode for the after reading filter
     * @return integer with error code
     */
    int applyFilter();
    /**
     * @brief Applies the filter stored in stegFilter
     * @return integer with error code
     */
    void printValues();
private:
    ErrorHandler *err; /**< Pointer to ErrorHandler type object that was constructed when this was constructed.*/
    Message *mess; /**<Message type objec to store message */
    Image *img; /**<Image type object containing path, header and image data*/
    std::string mode; /**< -encrypt or -decryptl, if not set ""*/
    bool modeSet; /**< flag to check if mode is set*/
    bool path; /**< flag to check if path is verified*/
    bool crazy;/**< Crazy filter flag*/
    Filter stegFilter; /**< enumeration to store set filter */
    
    ///////////////////////////////////************************************************************/
    /**Progress**///////////////////////
    ///////////////////////////////////
    /**
     * @brief Displays progress in % in stdout when c is a value between 0 and p
     */
    void displayProgress(int& c, int p);
     /**
     * @brief Displays 100% progress for p = 0 or -1 for wrong value in p
     */
    void displayProgress(int p);
    
    ///////////////////////////////////************************************************************/
    /**GETTERS**///////////////////////
    ///////////////////////////////////
    /**
     * @brief Method to provide the amount of pixels in the data part of the image file
     * @return integer value containing amount of pixels
     */
    int getPixel();
    
    ///////////////////////////////////************************************************************/
    /**FILTERS**///////////////////////
    ///////////////////////////////////
    /*following functions are pretty performant. Mostly bit operations, rarely loops or anything. You can use them without too many worries even in big loops*/
    /**
     * @brief Turns the whole bit-pattern around
     * @param uint32_t d - bit pattern
     * @param size_t s - size of the part of the pattern that needs to be changed
     * @return uint32_t generated new bit pattern
     */
    static uint32_t revertUint(uint32_t d, size_t s);
    /**
     * @brief Turns the bit pattern of a single byte around. Slight noise and color shift into magenta in normal mode/yellow in crazy mode.
     * @param uint32_t d - bit pattern
     * @param size_t s - size of the part of the pattern that needs to be changed
     * @return uint32_t generated new bit pattern stored in first 2 bytes of the integer
     */
    static uint32_t invert(uint8_t w);
    /**
     * @brief Swaps the bytes as good as possible depending on value in s
     * @param uint32_t d - bit pattern
     * @param size_t s - size of the part of the pattern that needs to be changed
     * @return uint32_t generated new bit pattern
     */
    static uint32_t swapBytes(uint32_t d, size_t s);
    /**
     * @brief Swaps each octet pairs as good as possible depending on value in s. Strong color shift into magenta in normal mode/yellow in crazy mode.
     * @param uint32_t d - bit pattern
     * @param size_t s - size of the part of the pattern that needs to be changed
     * @return uint32_t generated new bit pattern
     */
    static uint32_t swapOctets(uint32_t d, size_t s);
    /**
     * @brief Swaps the bytes first and then each octets as good as possible depending on value in s. Very noisy filter. In normal mode shift into magenta, in crazy mode shift into yellow.
     * @param uint32_t d - bit pattern
     * @param size_t s - size of the part of the pattern that needs to be changed
     * @return uint32_t generated new bit pattern
     */
    static uint32_t swapBytesOctets(uint32_t d, size_t s);
    /**
     * @brief Swaps the bytes first and then the bits as good as possible depending on value in s. Strong noise and psychodelig color effect.
     * @param uint32_t d - bit pattern
     * @param size_t s - size of the part of the pattern that needs to be changed
     * @return uint32_t generated new bit pattern
     */
    static uint32_t swapBytesBits(uint32_t d, size_t s);
    /**
     * @brief Swaps the bytes first followed by the octets and bits as good as possible depending on value in s. Fluid like filter.  In normal mode shift into magenta, in crazy mode shift into yellow.
     * @param uint32_t d - bit pattern
     * @param size_t s - size of the part of the pattern that needs to be changed
     * @return uint32_t generated new bit pattern
     */
    static uint32_t swapBytesOctetsBits(uint32_t d, size_t s);
    /**
     * @brief Swaps Blue with Red value if size >= 24bit
     * @param uint32_t d - bit pattern
     * @param size_t s - size of the part of the pattern that needs to be changed
     * @return uint32_t generated new bit pattern
     */
    static uint32_t swapBR(uint32_t d, size_t s);
    /**
     * @brief Swaps Blue with Green value if size >= 24bit
     * @param uint32_t d - bit pattern
     * @param size_t s - size of the part of the pattern that needs to be changed
     * @return uint32_t generated new bit pattern
     */
    static uint32_t swapBG(uint32_t d, size_t s);
    /**
     * @brief Swaps Green with Red value if size >= 24bit
     * @param uint32_t d - bit pattern
     * @param size_t s - size of the part of the pattern that needs to be changed
     * @return uint32_t generated new bit pattern
     */
    static uint32_t swapGR(uint32_t d, size_t s);
    /**
     * @brief Substracts blue value from each channel if size >= 24bit
     * @param uint32_t d - bit pattern
     * @param size_t s - size of the part of the pattern that needs to be changed
     * @return uint32_t generated new bit pattern
     */
    static uint32_t substB(uint32_t d, size_t s);
    /**
     * @brief Substracts green value from each channel if size >= 24bit
     * @param uint32_t d - bit pattern
     * @param size_t s - size of the part of the pattern that needs to be changed
     * @return uint32_t generated new bit pattern
     */
    static uint32_t substG(uint32_t d, size_t s);
    /**
     * @brief Substracts red value from each channel if size >= 24bit. 
     * @param uint32_t d - bit pattern
     * @param size_t s - size of the part of the pattern that needs to be changed
     * @return uint32_t generated new bit pattern
     */
    static uint32_t substR(uint32_t d, size_t s);
    
    /**
     * @brief Generaically calls the previously defined filter functions. They are designed to fit second parameter and following filters should be designed accordingly.
     * @param std::vector<std::vector<uint32_t>> *d - Pointer to array containing image information.
     * @param uint32_t (*f)(uint32_t, size_t) - pointer to uint32_t type function with parameter list (uint32_t, size_t); Use this to apply filters easily.
     */
    void genFilter(std::vector<std::vector<uint32_t>> *d, uint32_t (*f)(uint32_t, size_t));/**
     * @brief For debugging to call new implemented filters not ready for release
     * @param std::vector<std::vector<uint32_t>> *d - Pointer to array containing image information.
     */
    void dummyFilter(std::vector<std::vector<uint32_t>> *d);
};

#endif /* STEGANOMESSAGE_H */