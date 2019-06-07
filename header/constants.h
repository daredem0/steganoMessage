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
#include <string>

/**
 *@brief Containing some globally used constants
 */
const int errNoError = 0;
const int errUnknown = 1;
const int errSwitch = 2;
const int errPath = 3;
const int errPathWrong = 4;
const int errPathExist = 5;
const int errMode = 6;
const int errBitCount = 7;
const int errStdExcept = 9;

const int errMess = 10;
const int errMessExist = 11;

const int errImg = 20;
const int errImgExist = 21;
const int errImgWD = 22;
const int errImgWrHead = 23;
const int errImgWrData = 23;

const int errBmHead = 30;
const int errBmHeadRead = 31;
const int errBmHeadReadHead = 32;

const int errBmData = 40;
const int errBmDataRead = 41;

const std::string BITMAP = "BM";
const std::string PNG = "PNG";
const std::string JPEG = "JPEG";
const std::string GIF = "GIF";

const std::string ERRRESERVED = "";

const std::string ERRNOERROR = "No Error Occured";
const std::string ERRUNKNOWN = "Error: Unknown Error";
const std::string ERRSWITCH = "Error: Wrong/No switch set";
const std::string ERRPATH = "Error: No path set";
const std::string ERRPATHWRONG = "Error: Not a valid path entered";
const std::string ERRPATHEXIST = "Error: Path does not exist";
const std::string ERRMODE = "Error: Mode Error";
const std::string ERRBITCOUNT = "Error: Bit Count Error";
const std::string ERRSTDEXCEPT = "Error: Exception";

const std::string ERRMESS = "Error: Message Error";
const std::string ERRMESSEXIST = "Error: Message exists already";

const std::string ERRIMG = "Error: Image Error";
const std::string ERRIMGEXIST = "Error: Image exists already";
const std::string ERRIMGWD = "Error: Can't get working directory";
const std::string ERRIMGWRHEAD = "Error: Can't write header";
const std::string ERRIMGWRDATA = "Error: Can't write image data";

const std::string ERRBMHEAD = "Error: Bitmap Header Error";
const std::string ERRBMHEADREAD = "Error: Can't read bitmap header";

const std::string ERRBMDATA = "Error: Bitmap Data Error";
const std::string ERRBMDATAREAD = "Error: Can't read bitmap data";



const std::string DECRYPT = "-decrypt";
const std::string ENCRYPT = "-encrypt";
const std::string BMPTOTXT = "-convert_txt";
const std::string FILTER = "-filter";
const std::string CRFILTER = "-filter_cr";
    
enum Filter {noFilter = 0, grey = 1, colorA = 2, colorB = 3, 
color = 4, invertBit = 5, swapByte = 6, swapOctet = 7, swapByteOctet = 8, 
swapByteOctetBit = 9, swapByteBit = 10, swapBtG = 11, swapBtR = 12, swapGtR = 13, substBl = 14, substRd = 15, substGr = 16};

const std::string GREY = "grey";
const std::string COLORA = "color_a";
const std::string COLORB = "color_b";
const std::string COLORDUMMY = "color";
const std::string INVERTBIT = "inv_b";
const std::string SWAPBYTE = "swap_by";
const std::string SWAPOCTET = "swap_oc";
const std::string SWAPBYOC = "swap_by_oc";
const std::string SWAPBYBI = "swap_by_bi";
const std::string SWAPBYOCBI = "swap_by_oc_bi";
const std::string SWAPBG = "swap_bg";
const std::string SWAPBR = "swap_br";
const std::string SWAPGR = "swap_gr";
const std::string SUBSTB = "subst_bl";
const std::string SUBSTR = "subst_rd";
const std::string SUBSTG = "subst_gr";
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
"./steganoMessage -encrypt <path>\n"
"    This will start the routine to encrypt your message into example.bmp\n"
"./steganoMessage -decrypt <path>\n"
"    This will start the routine to decrypt your message from example.bmp\n"
"\n"
"./steganoMessage -h\n"
"   This will return the information contained in this help file. \n"
"./steganoMessage -convert_txt <path>\n"
"   This will convert the bitmap file into a readable text file containing all information as hex values."
"./steganoMessage -filter <path> -filter <type>\n"
"   Applies filter, possible values: grey/color_a/color_b <- Filters that are going to be applied while reading/writing\n"
"color <- Dummy filter\n"
"inv_n/swap_by/swap_oc/swap_by_oc/swap_by_bi/swap_by_oc_bi/swap_bg/swap_br/swap_gr/subst_bl/subst_rd/subst_gr <- Filters that will be applied after reading before writing.\n"
"./steganoMessage -filter_cr <path> -filter <type>\n"
"   Activates crazy mode for filters. Same filter codes, automatically shifts the color."
"   Sorry, no time yet to describe the filter effects. Just try.\n"
"\n"
"Filters can also be applied automatically while adding a steganoMessage. This will likely mess up everything. Do:\n"
"./steganoMessage -decrypt/-encrypt <path> -filter <type>";

#endif /* CONSTANTS_H */