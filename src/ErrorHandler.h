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

class ErrorHandler {
public:
    ErrorHandler();
    ErrorHandler(const ErrorHandler& orig);
    virtual ~ErrorHandler();
    
    void printError(int err);
    void printAllErrors(void);
private:
    std::list<std::string> errorOut;
};

#endif /* ERRORHANDLER_H */

