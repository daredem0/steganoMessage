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
    int buildMessage(std::string m);
    Message *getMessage();
    int buildImage(std::string path);
    Image *getImage();
    int setMode(std::string m);
    std::string getMode();
    void printValues();
    bool getPathVerified();
    
    static int checkPath(std::string path);
    static bool exists(std::string p);
    
private:
    ErrorHandler *err; /**< Pointer to ErrorHandler type object that was constructed when this was constructed.*/
    Message *mess;
    Image *img;
    std::string mode;
    bool modeSet;
    bool path;
};

#endif /* STEGANOMESSAGE_H */

