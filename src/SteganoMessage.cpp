/**
 * @file Expression file is undefined on line 2, column 12 in file:///home/florian/git/steganoMessage/nbproject/licenseheader.txt.
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 2019.05.21
 * @brief
 */
/* 
 * File:   SteganoMessage.cpp
 * Author: Florian Leuze
 * 
 * Created on 21. Mai 2019, 14:42
 */

#include "SteganoMessage.h"

SteganoMessage::SteganoMessage() {
    std::cout << "Creating new SteganoMessage object" << std::endl;
    err = new ErrorHandler();}

SteganoMessage::SteganoMessage(const SteganoMessage& orig) {
}

SteganoMessage::~SteganoMessage() {
    //if(err != NULL)
        //delete err;
}


ErrorHandler* SteganoMessage::getErrHandle(){
    return err;
}