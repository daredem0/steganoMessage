/**
 * @file Expression file is undefined on line 2, column 12 in file:///home/florian/git/steganoMessage/nbproject/licenseheader.txt.
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 2019.05.21
 * @brief
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

class Message {
public:
    Message();
    Message(const Message& orig);
    virtual ~Message();
    
    int setMessage(std::string m);
    std::string getMessage(void);
private:
    std::string mess;

};

#endif /* MESSAGE_H */

