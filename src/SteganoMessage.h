/**
 * @file Expression file is undefined on line 2, column 12 in file:///home/florian/git/steganoMessage/nbproject/licenseheader.txt.
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 2019.05.21
 * @brief
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

class SteganoMessage {
public:
    SteganoMessage();
    SteganoMessage(const SteganoMessage& orig);
    virtual ~SteganoMessage();
    ErrorHandler *getErrHandle();
private:
    ErrorHandler *err;
};

#endif /* STEGANOMESSAGE_H */

