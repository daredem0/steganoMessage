/**
 * @file Expression file is undefined on line 2, column 12 in file:///home/florian/git/steganoMessage/nbproject/licenseheader.txt.
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 2019.05.21
 * @brief ErrorHandler class cpp file
 */
/* 
 * File:   ErrorHandler.cpp
 * Author: Florian Leuze
 * 
 * Created on 21. Mai 2019, 14:16
 */

#include "../header/ErrorHandler.h"

ErrorHandler::ErrorHandler() {
    std::cout << "Creating new ErrorHandler Object" << std::endl;
    errorOut.assign(1, "Unknown Error");
    errorOut.push_back("Wrong/No switch set");
    errorOut.push_back("No path set");
}

ErrorHandler::ErrorHandler(const ErrorHandler& orig) {
}

ErrorHandler::~ErrorHandler() {
}

void ErrorHandler::printError(int err){
    std::list<std::string>::iterator it = errorOut.begin();
    std::advance(it, err);
    std::cout << *it << std::endl;
}

void ErrorHandler::printAllErrors(void){
    std::cerr << "Start to print errors" << std::endl;
    for(std::list<std::string>::iterator it = errorOut.begin(); it != errorOut.end(); ++it){
       std::cout << *it << std::endl;
    }
}

