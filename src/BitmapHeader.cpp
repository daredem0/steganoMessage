/**
 * @file Expression file is undefined on line 2, column 12 in file:///home/florian/git/steganoMessage/nbproject/licenseheader.txt.
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 2019.05.24
 * @brief BitmapHeader Class cpp file
 */
/* 
 * File:   BitmapHeader.cpp
 * Author: Florian Leuze
 * 
 * Created on 24. Mai 2019, 22:46
 */

#include "../header/BitmapHeader.h"

/********PUBLIC**************PUBLIC*****************PUBLIC**************PUBLIC************/
//CONSTRUCTORS/DECONSTRUCTORS/************************************************************/
BitmapHeader::BitmapHeader() {
}

BitmapHeader::BitmapHeader(std::string p, ErrorHandler *errH):path(p), errHandle(errH){
    readHeader(p);
}

BitmapHeader::BitmapHeader(std::string p, ErrorHandler *errH, bool read):path(p), errHandle(errH){
}

BitmapHeader::BitmapHeader(const BitmapHeader& orig) {
}

BitmapHeader::~BitmapHeader() {
}

//GETTERS/************************************************************/
char* BitmapHeader::getHeader(){
    try{
        return (char*)&header;
    }
    catch(const std::exception& e){
        errHandle->printErrorStdEx(e);
        errHandle->printError(errBmHeadRead);
        return (char*)'\0';
    }
    catch(...){
        errHandle->printError(errUnknown);
        errHandle->printError(errBmHeadRead);
        return (char*)'\0';
    }
}

uint32_t BitmapHeader::getSize(){return header.bfSize;}
uint32_t BitmapHeader::getOffBits(){return header.bfOffBits;}
uint32_t BitmapHeader::getBiSize(){return header.biSize;}
uint32_t BitmapHeader::getWidth(){return header.biWidth;}
uint32_t BitmapHeader::getHeight(){return header.biHeight;}
uint32_t BitmapHeader::getSizeImage(){return header.biSizeImage;}
uint32_t BitmapHeader::getBitCount(){return header.biBitCount;}
Header* BitmapHeader::getHeaderStruct(){return &header;}

//OTHER METHODS/************************************************************/
int BitmapHeader::readHeader(std::string p){
    try{
        std::ifstream file(p);
        if(!file.good())
            return 3;
        int returnValue = read(file);
        file.close();
        return returnValue;
    }
    catch(const std::exception& e){
        errHandle->printErrorStdEx(e);
        errHandle->printError(errBmHeadRead);
        return errBmHeadRead;
    }
    catch(...){
        errHandle->printError(errUnknown);
        errHandle->printError(errBmHeadRead);
        return errBmHeadRead;
    }
    return errBmHeadRead;
}

int BitmapHeader::readHeader(){
    try{
        std::ifstream file(path);
        if(!file.good())
            return 3;
        int returnValue = read(file);
        file.close();
        return returnValue;
    }
    catch(const std::exception& e){
        errHandle->printErrorStdEx(e);
        errHandle->printError(errBmHeadRead);
        return errBmHeadRead;
    }
    catch(...){
        errHandle->printError(errUnknown);
        errHandle->printError(errBmHeadRead);
        return errBmHeadRead;
    }
    return errBmHeadRead;
}

void BitmapHeader::printHeader(){
    std::cout << "Type: " << header.bfTypeA << header.bfTypeB << std::endl;
    std::cout << "File-Size in byte kb: " << header.bfSize/1000 << std::endl;
    std::cout << "Reserved: " << header.bfReserved << std::endl;
    std::cout << "OffBits: " << header.bfOffBits << std::endl;
    std::cout << "Info-Header-Size in byte kb: " << header.biSize<< std::endl;
    std::cout << "Width in pixel: " << header.biWidth << std::endl;
    std::cout << "Height in pixel: " << header.biHeight << std::endl;
    std::cout << "Planes (outdated): " << header.biPlanes << std::endl;
    std::cout << "Color Depth (bit count): " << header.biBitCount << std::endl;
    std::cout << "Compression: " << header.biCompression << std::endl;
    std::cout << "Size of image data: " << header.biSizeImage << std::endl;
    std::cout << "biXPelsPerMeter: " << header.biXPelsPerMeter << std::endl;
    std::cout << "biYPelsPerMeter: " << header.biYPelsPerMeter << std::endl;
    std::cout << "biClrUsed: " << header.biClrUsed << std::endl;
    std::cout << "biClrImportant: " << header.biClrImportant << std::endl;
}

int BitmapHeader::fixType(){
    header.bfTypeA = header.bfType & 0x00FF;
    header.bfTypeB = header.bfType >> 8;
    return 0;
}

/********PRIVATE**************PRIVATE*****************PRIVATE**************PRIVATE************/
int BitmapHeader::read(std::ifstream& f){
    try{
        f.seekg(0, std::ios::beg);
        //File Header
        f.read((char*) &header.bfType, sizeof(header.bfType));
        fixType();
        f.read((char*) &header.bfSize, sizeof(header.bfSize));
        f.read((char*) &header.bfReserved, sizeof(header.bfReserved));
        f.read((char*) &header.bfOffBits, sizeof(header.bfOffBits));
        //Information Header
        f.read((char*) &header.biSize, sizeof(header.biSize));
        f.read((char*) &header.biWidth, sizeof(header.biWidth));
        f.read((char*) &header.biHeight, sizeof(header.biHeight));
        f.read((char*) &header.biPlanes, sizeof(header.biPlanes));
        f.read((char*) &header.biBitCount, sizeof(header.biBitCount));
        f.read((char*) &header.biCompression, sizeof(header.biCompression));
        f.read((char*) &header.biSizeImage, sizeof(header.biSizeImage));
        f.read((char*) &header.biXPelsPerMeter, sizeof(header.biXPelsPerMeter));
        f.read((char*) &header.biYPelsPerMeter, sizeof(header.biYPelsPerMeter));
        f.read((char*) &header.biClrUsed, sizeof(header.biClrUsed));
        f.read((char*) &header.biClrImportant, sizeof(header.biClrImportant));
        
        if(header.bfOffBits > f.tellg()){
            std::cout << "Building header leftover size: " << header.bfOffBits - f.tellg() << std::endl;
            f.read((char*)&header.leftover, header.bfOffBits - f.tellg());
        }
        return errNoError;
    }
    catch(const std::exception& e){
        errHandle->printErrorStdEx(e);
        errHandle->printError(errBmHeadRead);
        return errBmHeadRead;
    }
    catch(...){
        errHandle->printError(errUnknown);
        errHandle->printError(errBmHeadRead);
        return errBmHeadRead;
    }
    return errBmHeadRead;
}