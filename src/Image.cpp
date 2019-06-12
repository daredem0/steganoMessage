/**
 * @file Expression file is undefined on line 2, column 12 in file:///home/florian/git/steganoMessage/nbproject/licenseheader.txt.
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 2019.05.22
 * @brief Image-Class cpp file
 */
/* 
 * File:   Image.cpp
 * Author: Florian Leuze
 * 
 * Created on 22. Mai 2019, 19:57
 */

#include "../header/Image.h"

/********PUBLIC**************PUBLIC*****************PUBLIC**************PUBLIC************/
//CONSTRUCTORS/DECONSTRUCTORS/************************************************************/
Image::Image() {
    path == "";
    header = NULL;
    array = NULL;
}

Image::Image(std::string p, ErrorHandler *errH):path(p), errHandle(errH){
    header = NULL;
    array = NULL;
}

Image::Image(const Image& orig) {
}

Image::~Image() {
    if(header != NULL){
        delete header;
    }
    if(array != NULL)
        delete array;
}

//GETTERS/************************************************************/
std::string Image::getPath(){return path;}
BitmapHeader *Image::getBitmapHeader(){return header;}
BitmapArray *Image::getBitmapArray(){return array;}


//SETTERS/************************************************************/
void Image::setPath(std::string p){
    path = p;
}

int Image::setFilter(std::string gr, std::string col){
    filterModeGrey = gr;
    filterModeCol = col;
    return 0;
}

void Image::setLogMode(std::string path, std::ios_base::openmode mode){
    logfilePath = path;
    logfileMode = mode;
}

//EVALUATIONS/************************************************************/
std::string Image::identifyFileFormat(std::string p){
    std::ifstream file(p);
    std::stringstream ss;
    std::string returnValue;
    if(!file.good()){
        return ERRUNKNOWN;
    }
    file.seekg(0, std::ios::beg);
    unsigned char type[10];
    std::fill(type, type + sizeof(type), 0);
    file.read((char*)type, sizeof(type));
    //check for bitmap
    if(type[0] == 0x42 && type[1] == 0x4D)
         ss << type[0] << type[1];
    
    //check for jpeg
    if(type[0] == 0xFF && type[1] == 0xD8)
        ss << JPEG;
    //check for gif
    if(type[0] == 0x47 && type[1] == 0x49 && type[2] == 0x46)
        ss << type[0] << type[1] << type[2];
    //check for png
    if(type[0] == 0x89 && type[1] == 0x50 && type[2] == 0x4E && type[3] == 0x47 && type[4] == 0x0D && type[5] == 0x0A && type[6] == 0x1A && type[7] == 0x0A)
        ss << PNG;
    ss >> returnValue;
    file.close();
    return returnValue;
}

//OTHER METHODS/************************************************************/
int Image::readImage(){
    std::cout << "In bitmap read image" << std::endl;
    if(path == "")
        return ErrorHandler::errPath;
    header = new BitmapHeader(path, errHandle);
    header->printHeader();
    array = new BitmapArray(path, header->getOffBits(), header->getWidth(), header->getHeight(), header->geOldtBitCount(), errHandle, filterModeCol);
    return ErrorHandler::errNoError;
}

int Image::generateBitmap(){
    errHandle->printLog("Loading bitmap builder\n");
    errHandle->printLog("Opening ofstream\n");
    std::string sWD;
    std::ofstream file;
    try{
        if(LINUX == 1 && MAC == 0)
        {
            char* wD;
            //get current working dir and generate path
            wD = PATHLINUX; //gives current dir (works only on linux, maybe switch to std::filesystem once c++17 is stable), mallocs automatically 
            sWD = wD;
            free(wD);//free malloced storage from get_current_dir_name()
            int i = 0;
            while(exists(sWD + "/output" + std::to_string(i) + ".bmp")){
                ++i;
            }
            sWD = "./";
            sWD += "output" + std::to_string(i) + ".bmp";
        }
        else
        {
            throw ErrorHandler::errOsErrMac;
        }
    }
    catch(int i){
        return i;
    }
    catch(const std::exception& e){
        errHandle->printErrorStdEx(e);
        errHandle->printError(errImgWD);
        return errImgWD;
    }
    catch(...){
        errHandle->printError(errUnknown);
        errHandle->printError(errImgWD);
        return errImgWD;
    }
    try{
        errHandle->printLog("Output-path: " + sWD + "\n");
        file.open(sWD, std::ios::binary | std::ios::trunc);
        errHandle->printLog("Writing header\n");
        file.write(header->getHeader(), header->getOffBits());
        errHandle->printLog("Header written - closing stream\n");
        file.close();
    }
    catch(const std::exception& e){
        errHandle->printErrorStdEx(e);
        errHandle->printError(errImgWrHead);
        return errImgWrHead;
    }
    catch(...){
        errHandle->printError(errUnknown);
        errHandle->printError(errImgWrHead);
        return errImgWrHead;
    }
    try{
        errHandle->printLog("Reopening ofstream\n");
        file.open(sWD, std::ios::binary | std::ios::app);
        long i = 0;
        std::vector<std::vector<uint32_t>> temp = array->getBData();
        for(auto itOuter = temp.begin(); itOuter != temp.end(); ++itOuter){
            for(auto itInner = itOuter->begin(); itInner != itOuter->end(); ++itInner){
                switch(header->getBitCount()){
                    case 8:
                        file  << (uint8_t) *itInner;
                        break;
                    case 16:
                        file  << (uint16_t) *itInner;
                        break;
                    case 24:
                    case 32:
                        for(int i = 0; i < (header->getBitCount()/8); ++i){
                            if(filterModeGrey == GREY)
                                file << (uint8_t)((*itInner)>>((i+(header->getBitCount()/8)-1-i)*8)); //this will make greytone output file
                            else
                                file << (uint8_t)((*itInner)>>((i*8))); //this will make colorful output file
                        }
                        break;
                    default:
                        return -1;
                }
            }
        }
        file.close();
        errHandle->printLog("Finished writing\n");
        return 0;
    }
    catch(const std::exception& e){
        errHandle->printErrorStdEx(e);
        errHandle->printError(errImgWrData);
        return errImgWrData;
    }
    catch(...){
        errHandle->printError(errUnknown);
        errHandle->printError(errImgWrData);
        return errImgWrData;
    }
    return errNoError;
}

int Image::printTextFile(std::string p){
    try{
        std::ifstream file(p.c_str());
        std::string out;
        while (getline(file,out)) {
            std::cout << out << std::endl ;
        }
        file.close();
        return errNoError;
    }
    catch(const std::exception& e){
        errHandle->printErrorStdEx(e);
        return errStdExcept;
    }
    catch(...){
        errHandle->printError(errUnknown);
        return errUnknown;
    }
    return errUnknown;
}

int Image::writeTextFile(std::string t, std::string n){
    try{
        std::string path = "./"+n;
        std::ofstream file(path.c_str());
        file << t << std::endl;
        file.close();
    }
    catch(const std::exception& e){
        errHandle->printErrorStdEx(e);
        return errStdExcept;
    }
    catch(...){
        errHandle->printError(errUnknown);
        return errUnknown;
    }
    return errUnknown;
}

int Image::bmpToTxt(){
    try{
        if(this->logfileMode == std::ios::app){
            if(OPENDIR_LINUX("./log") == NULL){
                MKDIR_LINUX("./log", S_IRWXU);
            }
        }
        errHandle->printLog("Generate textfile\n");

        //buffer header
        char *head = header->getHeader();
        //buffer data
        char *data = array->getBDataStream();
        std::string path = logfilePath;
        if(MAC == 1 && logfilePath[2] == 'l'){
            logfilePath = logfilePath.erase(2,5);
        }
        std::ofstream outFile(path.c_str(), logfileMode);

        //write header
        int count;
        outFile << "Header Information:\n";
        //std::cout << (header->getHeight()*header->getWidth())*header->getBitCount()/8 << std::endl;
        for(count = 0; count<= header->getOffBits()-1; ++count){
            //std::cout << byteToHex(*(head+count)) << " ";
            outFile << byteToHex(*(head+count));
                if(count != 0 && (count+1)%16 == 0){
                    outFile << std::endl;
                    //std::cout << std::endl;
                }
                else 
                    outFile << " ";
        }

        //write data
        outFile << "\nImage Data:\n";
        count = 0;
        for(int i = 0; i <= ((header->getHeight()*header->getWidth())*header->getBitCount()/8)-1; ++i){
            //std::cout << byteToHex(*(data+i)) << " ";
            outFile << byteToHex(*(data + i));
            if(count != 0 && (count+1)%16 == 0){
                outFile << std::endl;
                //std::cout << std::endl;
            }
            else
                outFile << " ";
            ++count;
        }

        //clean up
        delete(data);
        //delete(head);
        //delete(data);
        //inFile.close();
        outFile.close();
        errHandle->printLog("Generation successfull to " + logfilePath + "\n");
        return errNoError;
    }
    catch(const std::exception& e){
        errHandle->printErrorStdEx(e);
        return errStdExcept;
    }
    catch(...){
        errHandle->printError(errUnknown);
        return errUnknown;
    }
    return errUnknown;
}

std::string Image::byteToHex(uint8_t v){
    std::string hex;
    for(int i = 0; i <= sizeof(v); ++i){
        if(i == 0)
            hex += "0x";
        hex += decToHex(v >> ((sizeof(v)-i)*4));
    }
   return hex;    
}

std::string Image::decToHex(uint8_t v){
    switch(+(v & 0x0F)){
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5: 
        case 6:
        case 7:
        case 8:
        case 9:
            return std::to_string(+(v & 0x0F));
        case 10:
            return "A";
        case 11:
            return "B";
        case 12:
            return "C";
        case 13:
            return "D";
        case 14:
            return "E";
        case 15:
            return "F";
        default:
            return std::to_string(errUnknown);
    }
}

/********PRIVATE**************PRIVATE*****************PRIVATE**************PRIVATE************/
bool Image::exists(const std::string& name){
    std::ifstream f(name.c_str()); 
    return f.good();
}