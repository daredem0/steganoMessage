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
#include "Image.h"
#include <fstream>

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
     * @brief Gives pointer to the ErrorHandler object stored in the SteganoMessage type object.
     * @return pointer to ErrorHandler
     */
    ErrorHandler *getErrHandle();
    /**
     * @brief Builds new Message type object
     * @param std::sring containing message
     * @return integer with error code
     */
    int buildMessage(std::string m);
    /**
     * @brief Getter for pointer to message object
     * @return Pointer to Message
     */
    Message *getMessage();
    /**
     * @brief Builds new Image type object
     * @param std::string containing path to image
     * @return integer with error code
     */
    int buildImage(std::string path);
    /**
     * @brief Getter for image object
     * @return Pointer to Image
     */
    Image *getImage();
    /**
     * @brief Stores mode command in member, sets flag for modeset
     * @param std::string containing mode command
     * @return integer with error code
     */
    int setMode(std::string m);
    /**
     * @brief Getter for stored mode
     * @return std::string containing mode command or ""
     */
    std::string getMode();
    /**
     * @brief Prints values stored for mode and path
     */
    void printValues();
    /**
     * @brief Getter for path verified flag
     * @return bool - true for verified, false for not verified. 
     */
    bool getPathVerified();
    
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
    /**
     * @brief Fully initializes the SteganoMessage type object into a operatable state to ensure that other methods can be called safely. This NEEDS to be called before everything else
     * @param argc - argc from terminal (amount of sent arguments including argc)
     * @param *argv[] - *argv[] from terminal (sent arguments including argc in [0]
     * @return integer with error code
     */
    int initialize(int argc, char *argv[]);
    /**
     * @brief Handles the calling of following methods depending on the set mode. initialize needs to be called before this, else the sun will explode
     * @return integer with error code
     */
    int modeHandler();
    
private:
    ErrorHandler *err; /**< Pointer to ErrorHandler type object that was constructed when this was constructed.*/
    Message *mess; /**<Message type objec to store message */
    Image *img; /**<Image type object containing path, header and image data*/
    std::string mode; /**< -encrypt or -decryptl, if not set ""*/
    bool modeSet; /**< flag to check if mode is set*/
    bool path; /**< flag to check if path is verified*/
};

#endif /* STEGANOMESSAGE_H */