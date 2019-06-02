/**
 * @file Expression file is undefined on line 2, column 12 in file:///home/florian/git/steganoMessage/nbproject/licenseheader.txt.
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 2019.05.21
 * @brief
 */
/* 
 * File:   ErrorHandler.h
 * Author: Florian Leuze
 *
 * Created on 21. Mai 2019, 14:16
 */

#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include <list> 
#include <iterator> 
#include <iostream>
#include <string>
#include <exception>
#include "constants.h"

/**
 *@brief ErrorHandler Class is implemented to store a list of standard errors and offer a interface between standard errors and stderr
 */
class ErrorHandler {
public:
    //CONSTRUCTORS/DECONSTRUCTORS/************************************************************/
    /**
    * @brief Standard constructor. Also fills std::list<std::string> with standard error values
    */
    ErrorHandler();
    /**
     * @brief Copy Constructor. 
     * @param orig - Reference to original ErrorHandler-type object
     */
    ErrorHandler(const ErrorHandler& orig);
    /**
     * Standard deconstructor. Deletes the generated list !!not yet implementede!!
     */
    virtual ~ErrorHandler(); //free list, implement!
    
    /**
     * @brief Prints a single Error corresponding to the 
     * @param int err - expects a integer value between 0 and x that specifies the error received
     */
    int printError(int err);
    /**
     * @brief Prints all available errors (mainly for debugging)
     */
    void printAllErrors(void);
     /**
     * @brief Prints error from a std::exception
     * @param const std::exception& e- reference to the std::exception
     */
    void printErrorStdEx(const std::exception& e);
     /**
     * @brief Prints param to stdout or logfile
     * @param std::string log - logmessage
     */
    static void printLog(std::string log);
private:
    std::list<std::string> errorOut; /**< std::list that stores every standard error message as a std::string.*/
    
     /**
     * @brief Fills list with a specified amount of a specified message. Uses push_back, no push_front version implemented
     * @param std::string s - Specified message
     * @param int am - Amount of positions to be filled 
     */
    void fillList(std::string s, int am);
     /**
     * @brief Fills list with RESERVED constant std::string for a specified amount of slots
     * @param int am - Amount of positions to be filled 
     */
    void fillList(int am);
};

#endif /* ERRORHANDLER_H */