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
    
    //General Errors
    errorOut.assign(1, ERRNOERROR);
    errorOut.push_back(ERRUNKNOWN);
    errorOut.push_back(ERRSWITCH);
    errorOut.push_back(ERRPATH);
    errorOut.push_back(ERRPATHWRONG);
    errorOut.push_back(ERRPATHEXIST);
    errorOut.push_back(ERRMODE);
    errorOut.push_back(ERRBITCOUNT);
    fillList(1);
    errorOut.push_back(ERRSTDEXCEPT);
    
    //Message Errors
    errorOut.push_back(ERRMESS);
    errorOut.push_back(ERRMESSEXIST);
    fillList(8);
    
    //Image Errors
    errorOut.push_back(ERRIMG);
    errorOut.push_back(ERRIMGEXIST);
    errorOut.push_back(ERRIMGWRHEAD);
    errorOut.push_back(ERRIMGWRDATA);
    fillList(6);
    
    //Header Errors
    errorOut.push_back(ERRBMHEAD);
    errorOut.push_back(ERRBMHEADREAD);
    errorOut.push_back(ERRBMHEADREAD);
    
    //Data Errors
}

void ErrorHandler::fillList(std::string s, int am){
    for(int i = 0; i < am; ++i){
        errorOut.push_back(s);
    }
}

void ErrorHandler::fillList(int am){
    for(int i = 0; i < am; ++i){
        errorOut.push_back(ERRRESERVED);
    }
}

ErrorHandler::ErrorHandler(const ErrorHandler& orig) {
}

ErrorHandler::~ErrorHandler() {
}

int ErrorHandler::printError(int err){
    std::list<std::string>::iterator it = errorOut.begin();
    std::advance(it, err);
    std::cout << *it << std::endl;
    return err;
}

void ErrorHandler::printErrorStdEx(const std::exception& e){
    std::cout << e.what() << std::endl;
}

void ErrorHandler::printAllErrors(void){
    std::cerr << "Start to print errors" << std::endl;
    for(std::list<std::string>::iterator it = errorOut.begin(); it != errorOut.end(); ++it){
       std::cout << *it << std::endl;
    }
}

void ErrorHandler::printLog(std::string log){
    std::cout << log;
}