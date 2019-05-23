/**
 * @file Expression file is undefined on line 2, column 12 in file:///home/florian/git/steganoMessage/nbproject/licenseheader.txt.
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 2019.05.22
 * @brief Constants
 */
/* 
 * File:   constants.h
 * Author: Florian Leuze
 *
 * Created on 22. Mai 2019, 18:23
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

const int errUnknown = 0;
const int errSwitch = 1;
const int errPath = 2;

const std::string DECRYPT = "-decrypt";
const std::string ENCRYPT = "-encrypt";
const std::string NOSWITCH = "";
const std::string NOPATH = "";

const std::string HELP = "-h";
const std::string HELPFILE = 
"steganoMessage is a command line tool to hide a message somewhere in a bitmap file.\n"
"Use either of the following as first switch to decide if you want to encrypt a message or decrypt a message. Add path of image file after the switch.\n"
"-decrypt\n"
"-encrypt \n"
"\n"
"example:\n"
"\n"
"./steganoMessage -encrypt ./example.bmp\n"
"    This will start the routine to encrypt your message into example.bmp\n"
"./steganoMessage -decrypt ./example.bmp\n"
"    This will start the routine to decrypt your message from example.bmp\n"
"\n"
"./steganoMessage -h\n"
    "This will return the information contained in this help file. \n";

#endif /* CONSTANTS_H */

