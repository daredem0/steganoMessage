/**
 * @file main.cpp
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 05.02.2019
 * @brief Main Function of steganoMessage. Mainly ochestrates the init and gui creation
 */

#include <iostream>
#include <fstream>
#include "../header/SteganoMessage.h"

using namespace std;

/**
* @brief Evaluates the terminal input
* @param std::string argv - give the argument from command line
* @param SteganoMessage *steg - give SteganoMessage object
* @return value > 0 for all good, -1 for not so good.
*/
int ui(string argv, SteganoMessage *steg);
/**
* @brief Prints help file stored in const string
* @return always returns -1 to surely execute the program
*/
int printHelp();
/**
* @brief Terminates the program without an error
* @return always returns 0
*/
int terminate(SteganoMessage *steg);
/**
* @brief Terminates the program with an error
* @return always returns 1
*/
int errTerminate(SteganoMessage *steg);
void debuggingStuff(SteganoMessage *steg);
/**
* @brief Main Function orchestrating the program
* @param int argc - Number of parameters we got from the terminal
* @param char *argv[] - Array containing the arguments
* @return int standard linux error codes
*/


int main(int argc, char *argv[]) { 
    //For debugging
    //argc = 3;
    //argv[0] = (char*)'3';
    //argv[1] = (char*)"-encrypt";
    //argv[1] = (char*)"-decrypt";
    //argv[2] = (char*)"./misc/examples/swirl_effect.bmp";
    int returnValue = 0;
    SteganoMessage *steg = new SteganoMessage();
    cout << "argc: " << argc << endl;  //just for debugging
    cout << "argv: " << (argv[1] == NULL ? NOSWITCH : argv[1]) << endl; //just for debugging, first switch
    returnValue = ui(argv[1] == NULL ? NOSWITCH : (string)argv[1], steg); //if there was no switch on terminal send NOSWITCH, otherwise send the switch from terminal
    if(returnValue == -1)
        return terminate(steg);
    else{
        try{
            cout << "Trying to get path" << endl;
            string tempPath;
            argv[2] == NULL ? tempPath = NOPATH : tempPath = (string)argv[2];
            if(tempPath == NOPATH)
                throw errPath;
            cout << "Found Path: " << tempPath << endl;
            steg->buildImage(tempPath);
            cout << "Built path: " << steg->getImage()->getPath() << endl;
            steg->getImage()->readImage();
            //steg->getImage()->getBitmapHeader()->printHeader();
        }
    catch (int i){ //catch errPath and send it to printError
        steg->getErrHandle()->printError(i);
        exit(errTerminate(steg));
    }
    catch (...){ //catch everything weird
        steg->getErrHandle()->printError(errUnknown);
        exit(errTerminate(steg));
    }
        if(steg->getErrHandle()->printError(steg->checkPath(steg->getImage()->getPath())) != 0)
            exit(errTerminate(steg));
        //debuggingStuff(steg);
        steg->getImage()->generateBitmap();
    if(steg != NULL)
        delete steg;
    return 0;
    }
}

//finds the switch we got on the console, for now prints it. Needs to be stored in SteganoMessage object to decide if the encryption or decryption routine is needed
int ui(string argv, SteganoMessage *steg){
    int returnValue = 0;
    try{
        cout << "Found switch: " << argv << endl;
        if(argv == ENCRYPT){
                cout << "Found encrypt" << endl;
                steg->setMode(ENCRYPT); 
        }
        else if(argv == DECRYPT){
            cout << "Found decrypt" << endl;
            steg->setMode(DECRYPT);
        }
        else if (argv == HELP)
            returnValue = printHelp();
        else{
            cout << "No switch" << endl;
            throw errSwitch;
        }
    }
    catch (int i){ //catch errSwitch and send it to printError
        steg->getErrHandle()->printError(i);
        returnValue = -1;
    }
    catch (...){ //catch everything weird
        steg->getErrHandle()->printError(errUnknown);
    }
    return returnValue;
}

int printHelp(){
    cout << HELPFILE << endl;
}

int terminate(SteganoMessage *steg){
    if(steg != NULL)
        delete steg;
    return 0;
}

int errTerminate(SteganoMessage *steg){
    if(steg != NULL)
        delete steg;
    return 1;
}

void debuggingStuff(SteganoMessage *steg){
    steg->getErrHandle()->printError(steg->checkPath(steg->getImage()->getPath()));
    steg->printValues();
    //steg->getImage()->printTextFile(steg->getImage()->getPath());
}


