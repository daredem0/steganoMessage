/**
 * @file main.cpp
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 05.02.2019
 * @brief Main Function network analyzer. Mainly ochestrates the init and gui creation
 */

#include <iostream>
#include "SteganoMessage.h"


const int errUnknown = 0;
const int errSwitch = 1;
const std::string DECRYPT = "-decrypt";
const std::string ENCRYPT = "-encrypt";
const std::string NOSWITCH = "";


using namespace std;

int ui(string argv, SteganoMessage *steg);

int main(int argc, char *argv[]) { 
    SteganoMessage *steg = new SteganoMessage();
    cout << "argc: " << argc << endl;
    cout << "argv: " << (argv[1] == NULL ? NOSWITCH : argv[1]) << endl;
    ui(argv[1] == NULL ? NOSWITCH : (string)argv[1], steg);
    if(steg != NULL)
        delete steg;
    return 0;
}

//finds the switch we got on the console, for now prints it. Needs to be stored in SteganoMessage object to decide if the encryption or decryption routine is needed
int ui(string argv, SteganoMessage *steg){
    try{
        cout << "Found switch: " << argv << endl;
        if(argv == ENCRYPT)
                cout << "Found encrypt" << endl;
        else if(argv == DECRYPT)
            cout << "Found decrypt" << endl;
        else{
            cout << "No switch" << endl;
            throw errSwitch;
        }
    }
    catch (int i){
        steg->getErrHandle()->printError(i);
    }
    catch (...){
        steg->getErrHandle()->printError(errUnknown);
    }
}


