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
    if(header != NULL)
        delete header;
    if(array != NULL)
        delete array;
}

std::string Image::getPath(){
    return path;
}

void Image::setPath(std::string p){
    path = p;
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

int Image::readImage(){
    if(path == "")
        return 3;
    header = new BitmapHeader(path, errHandle);
    header->printHeader();
    array = new BitmapArray(path, header->getOffBits(), header->getWidth(), header->getHeight(), header->getBitCount(), errHandle);
    return 0;
}

BitmapHeader *Image::getBitmapHeader(){return header;}

int Image::generateBitmap(){
    std::cout << "opening ofstream" << std::endl;
    std::string sWD;
    std::ofstream file;
    try{
        char* wD;
        //get current working dir and generate path
        wD = get_current_dir_name(); //gives current dir (works only on linux, maybe switch to std::filesystem once c++17 is stable), mallocs automatically 
        sWD = wD;
        free(wD);//free malloced storage from get_current_dir_name()
        sWD += "/output.bmp";
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
        std::cout << "Output-Path: " << sWD << std::endl;
        file.open(sWD, std::ios::binary | std::ios::trunc);
        std::cout << "writing header" << std::endl;
        file.write(header->getHeader(), header->getOffBits());
        std::cout << "header written and closing stream" << std::endl;
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
        std::cout << "opening ofstream" << std::endl;
        file.open(sWD, std::ios::binary | std::ios::app);
        std::cout << "reopened ofstream" << std::endl;
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
                            //file << (uint8_t)((*itInner)>>((i+(header->getBitCount()/8)-1-i)*8)); //this will make greytone output file
                            file << (uint8_t)((*itInner)>>((i*8))); //this will make colorful output file
                        }
                        break;
                    default:
                        return -1;
                }
            }
        }
        file.close();
        std::cout << "Finished writing" << std::endl;
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