/**
 * @file Expression file is undefined on line 2, column 12 in file:///home/florian/git/steganoMessage/nbproject/licenseheader.txt.
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 2019.05.21
 * @brief
 */
/* 
 * File:   message.cpp
 * Author: Florian Leuze
 * 
 * Created on 21. Mai 2019, 13:58
 */

#include "Message.h"

Message::Message() {
    mess = "";
}

Message::Message(const Message& orig) {
}

Message::~Message() {
}

int Message::setMessage(std::string m){
    mess = m;
}

std::string Message::getMessage(void){
    return mess;
}

