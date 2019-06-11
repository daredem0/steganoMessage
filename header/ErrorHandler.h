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
#include <string>
#include <fstream>
#include <iostream>
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
    
    ///////////////////////////////////************************************************************/
    /**SETTERS**///////////////////////
    ///////////////////////////////////
    /**
     * Sets flag for logfile output
     */
    void setLog(bool l, std::string p);
    
      ///////////////////////////////////************************************************************/
    /**OTHER METHODS**/////////////////
    ///////////////////////////////////
    /**
     * @brief Prints a single Error corresponding to the 
     * @param int err - expects a integer value between 0 and x that specifies the error received
     */
    int printError(int err);
    /**
     * @brief Prints a single Error message
     * @param static std::string err - error message
     */
    const std::string printError(const std::string err);
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
    void printLog(std::string l);
    
    ///////////////////////////////////************************************************************/
    /**ERROR CONSTANTS**///////////////
    ///////////////////////////////////
    static int const errNoError = 0;
    static int const errUnknown = 1;
    static int const errSwitch = 2;
    static int const errPath = 3;
    static int const errPathWrong = 4;
    static int const errPathExist = 5;
    static int const errMode = 6;
    static int const errBitCount = 7;
    static int const errStdExcept = 9;

    static int const errMess = 10;
    static int const errMessExist = 11;
    static int const errInfused = 12;
    static int const errMessEmpty = 13;

    static int const errImg = 20;
    static int const errImgExist = 21;
    static int const errImgWD = 22;
    static int const errImgWrHead = 23;
    static int const errImgWrData = 23;

    static int const errBmHead = 30;
    static int const errBmHeadRead = 31;
    static int const errBmHeadReadHead = 32;

    static int const errBmData = 40;
    static int const errBmDataRead = 41;
    
    static int const errFiletype = 50;
    static int const errOsErr = 60;
    static int const errOsErrMac = 61;
	
    static int const errJpeg = 70;

    static int const errPng = 80;
    static int const errPngMem = 81;
    static int const errPngSig = 82;
    static int const errPngInt = 83;
    static int const errPngBkgd = 84;

    const static std::string ERRRESERVED;

    const static std::string ERRNOERROR;
    const static std::string ERRUNKNOWN;
    const static std::string ERRSWITCH;
    const static std::string ERRPATH;
    const static std::string ERRPATHWRONG;
    const static std::string ERRPATHEXIST;
    const static std::string ERRMODE;
    const static std::string ERRBITCOUNT;
    const static std::string ERRSTDEXCEPT;

    const static std::string ERRMESS;
    const static std::string ERRMESSEXIST;
    const static std::string ERRINFUSED;
    const static std::string ERRMESSEMPTY;

    const static std::string ERRIMG;
    const static std::string ERRIMGEXIST;
    const static std::string ERRIMGWD;
    const static std::string ERRIMGWRHEAD;
    const static std::string ERRIMGWRDATA;

    const static std::string ERRBMHEAD;
    const static std::string ERRBMHEADREAD;

    const static std::string ERRBMDATA;
    const static std::string ERRBMDATAREAD;
    
    const static std::string ERRFILETYPE;
    
    const static std::string ERROSERR;
    const static std::string ERROSERRMAC;

    const static std::string ERRJPEG;

    const static std::string ERRPNG;
    const static std::string ERRPNGMEM;
    const static std::string ERRPNGSIG;
    const static std::string ERRPNGINT;
    const static std::string ERRPNGKKGD;
private:
    bool log;/**< flag for logfile*/
    std::string path;
    
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
