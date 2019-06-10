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
int terminate(SteganoMessage *steg, int err);
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
    SteganoMessage *steg = new SteganoMessage(); /*Build ne SteganoMessage object first*/
    steg->getErrHandle()->printLog("argc: " + std::to_string(argc) + "\n" + "argv: " + (argv[1] == NULL ? NOSWITCH : argv[1]) + "\n");
    //cout << "argc: " << argc << endl;  //just for debugging
    //cout << "argv: " << (argv[1] == NULL ? NOSWITCH : argv[1]) << endl; //just for debugging, first switch
    int returnValue = ui(argv[1] == NULL ? NOSWITCH : (string)argv[1], steg); /*if there was no switch on terminal send NOSWITCH, otherwise send the switch from terminal*/
    steg->getErrHandle()->printLog("Startup init routine \n");
    if(returnValue == -1) /*Check for error in ui function*/
        return terminate(steg, -1);
    else{
        try{
            int errTemp = steg->initialize(argc, argv); /*initialize everything and check for error*/
            steg->applyFilter(); /*If a filter was set apply it on the image data*/
            if(errTemp != 0) 
                throw errTemp; 
        }
        catch (int i){ //catch errTemp and send it to printError
            steg->getErrHandle()->printError(i);
            exit(terminate(steg, -1));
        }
        catch (...){ //catch everything weird
            steg->getErrHandle()->printError(errUnknown);
            exit(errTerminate(steg));
        }
        if(steg->getErrHandle()->printError(steg->checkPath(steg->getImage()->getPath())) != 0) /*Check path, print error if occured and exit clean*/
            exit(terminate(steg, -1));
        //debuggingStuff(steg);

        steg->getErrHandle()->printLog("Successfully initialized bitmap steganoMessage\n");

        //modestuff here
        steg->modeHandler(); /*Load modehandler which will organise the rest of the program*/
        steg->getLogMode() == true ? steg->getImage()->bmpToTxt() : 1;

        terminate(steg, 0); //cleanup

        return 0;
    }
}

//finds the switch we got on the console, for now prints it. Needs to be stored in SteganoMessage object to decide if the encryption or decryption routine is needed
int ui(string argv, SteganoMessage *steg){
    int returnValue = 0;
    try{
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
    exit(1);
}

int terminate(SteganoMessage *steg, int err){
    if(steg != NULL)
        delete steg;
    return err;
            
}

//outdated, should not be used anymore
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
