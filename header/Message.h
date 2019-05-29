/**
 * @file Expression file is undefined on line 2, column 12 in file:///home/florian/git/steganoMessage/nbproject/licenseheader.txt.
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 2019.05.21
 * @brief Message Class header file
 */
/* 
 * File:   Message.h
 * Author: Florian Leuze
 *
 * Created on 21. Mai 2019, 13:58
 */

#ifndef MESSAGE_H
#define MESSAGE_H


#include <string>
#include "./ErrorHandler.h"
#include "./constants.h"

/**
 *@brief Message class is supposed to contain the message that the user enters via terminal and wants to hide in the image file.
 */
class Message {
public:
    //CONSTRUCTORS/DECONSTRUCTORS/************************************************************/
    /**
    * @brief Standard constructor.
    */
    Message();
    /**
    * @brief Non-Standard constructor. Initializes the object with a message.
    * @param std::string m - Message that is to be stored in the object.
    * @param ErrorHandler *errH - Errorhandler 
    */
    Message(std::string m, ErrorHandler *h);
    /**
     * @brief Copy Constructor. 
     * @param orig - Reference to original Message-type object
     */
    Message(const Message& orig);
    /**
     * Standard deconstructor.
     */
    virtual ~Message();
    
    /**
     * @brief setter for std::string mess
     * @param std::string m - Contains the message extracted from terminal.
     * @return value > 0 for all good, -1 for not so good.
     */
    int setMessage(std::string m); 
    /**
     * @brief getter for std::string mess
     * @return std::string mess
     */
    std::string getMessage(void);
private:
    std::string mess; /**< Stores the message extracted from terminal.*/
    ErrorHandler *errHandle;
};

#endif /* MESSAGE_H */