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
    std::cout << "Set Filter" << std::endl;
    if(returnValue == -1)
        return terminate(steg);
    else{
        try{
            int errTemp = steg->initialize(argc, argv);
            steg->applyFilter();
            if(errTemp != 0)
                throw errTemp; 
        }
    catch (int i){ //catch errPath and send it to printError
        exit(errTerminate(steg));
    }
    catch (...){ //catch everything weird
        steg->getErrHandle()->printError(errUnknown);
        exit(errTerminate(steg));
    }
    if(steg->getErrHandle()->printError(steg->checkPath(steg->getImage()->getPath())) != 0)
        exit(errTerminate(steg));
    //debuggingStuff(steg);


    //modestuff here
    steg->modeHandler();
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
            steg->getErrHandle()->printLog("Found " + ENCRYPT + "\n");
                steg->setMode(ENCRYPT); 
        }
        else if(argv == DECRYPT){
            steg->getErrHandle()->printLog("Found " + DECRYPT + "\n");
            steg->setMode(DECRYPT);
        }
        else if(argv == FILTER){
            steg->getErrHandle()->printLog("Found " + FILTER + "\n");
            steg->setMode(FILTER);
        }
        else if(argv == CRFILTER){
            steg->getErrHandle()->printLog("Found " + CRFILTER + "\n");
            steg->setMode(CRFILTER);
        }
        else if(argv == BMPTOTXT){
            steg->getErrHandle()->printLog("Found " + BMPTOTXT + "\n");
            steg->setMode(BMPTOTXT);
        }
        else if (argv == HELP)
            returnValue = printHelp();
        else{
            steg->getErrHandle()->printLog("Found " + NOSWITCH + "\n");
            returnValue = printHelp();
        }
    }
    catch (int i){ //catch errSwitch and send it to printError
        steg->getErrHandle()->printError(i);
        returnValue = -1;
    }
    catch (...){ //catch everything weird
        steg->getErrHandle()->printError(errUnknown);
    }
    return 0;
}

int printHelp(){
    cout << HELPFILE << endl;
	return -1;
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
