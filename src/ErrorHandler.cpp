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

/********PUBLIC**************PUBLIC*****************PUBLIC**************PUBLIC************/
//CONSTRUCTORS/DECONSTRUCTORS/************************************************************/
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

ErrorHandler::ErrorHandler(const ErrorHandler& orig) {
}

ErrorHandler::~ErrorHandler() {
}

//SETTERS/************************************************************/

void ErrorHandler::setLog(bool l){
    log = l;
}

//OTHER METHODS/************************************************************/
int ErrorHandler::printError(int err){
    std::list<std::string>::iterator it = errorOut.begin();
    std::advance(it, err);
    std::cout << *it << std::endl;
    return err;
}
const std::string ErrorHandler::printError(const std::string err){
    std::cout << err << std::endl;
}

void ErrorHandler::printAllErrors(void){
    std::cerr << "Start to print errors" << std::endl;
    for(std::list<std::string>::iterator it = errorOut.begin(); it != errorOut.end(); ++it){
       std::cout << *it << std::endl;
    }
}

void ErrorHandler::printErrorStdEx(const std::exception& e){
    std::cout << e.what() << std::endl;
}

void ErrorHandler::printLog(std::string log){
    std::cout << log;
}

/********PRIVATE**************PRIVATE*****************PRIVATE**************PRIVATE************/
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
//PUBLIC MEMBERS/************************************************************/
const std::string ErrorHandler::ERRRESERVED = "";

const std::string ErrorHandler::ERRNOERROR = "No Error Occured";
const std::string ErrorHandler::ERRUNKNOWN = "Error: Unknown Error";
const std::string ErrorHandler::ERRSWITCH = "Error: Wrong/No switch set";
const std::string ErrorHandler::ERRPATH = "Error: No path set";
const std::string ErrorHandler::ERRPATHWRONG = "Error: Not a valid path entered";
const std::string ErrorHandler::ERRPATHEXIST = "Error: Path does not exist";
const std::string ErrorHandler::ERRMODE = "Error: Mode Error";
const std::string ErrorHandler::ERRBITCOUNT = "Error: Bit Count Error";
const std::string ErrorHandler::ERRSTDEXCEPT = "Error: Exception";

const std::string ErrorHandler::ERRMESS = "Error: Message Error";
const std::string ErrorHandler::ERRMESSEXIST = "Error: Message exists already";

const std::string ErrorHandler::ERRMESSEMPTY = "Error: Message is empty";

const std::string ErrorHandler::ERRIMG = "Error: Image Error";
const std::string ErrorHandler::ERRIMGEXIST = "Error: Image exists already";
const std::string ErrorHandler::ERRIMGWD = "Error: Can't get working directory";
const std::string ErrorHandler::ERRIMGWRHEAD = "Error: Can't write header";
const std::string ErrorHandler::ERRIMGWRDATA = "Error: Can't write image data";

const std::string ErrorHandler::ERRBMHEAD = "Error: Bitmap Header Error";
const std::string ErrorHandler::ERRBMHEADREAD = "Error: Can't read bitmap header";

const std::string ErrorHandler::ERRBMDATA = "Error: Bitmap Data Error";
const std::string ErrorHandler::ERRBMDATAREAD = "Error: Can't read bitmap data";

const std::string ErrorHandler::ERRFILETYPE = "Error: Filetype not supported";

const std::string ErrorHandler::ERROSERR = "Error: Os not supported";
const std::string ErrorHandler::ERROSERRMAC = "Error: MAC not supported";