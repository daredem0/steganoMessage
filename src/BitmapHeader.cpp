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

BitmapHeader::BitmapHeader() {
}

BitmapHeader::BitmapHeader(const BitmapHeader& orig) {
}

BitmapHeader::~BitmapHeader() {
}

BitmapHeader::BitmapHeader(std::string p):path(p){
    readHeader(p);
}

BitmapHeader::BitmapHeader(uint16_t fType, uint32_t fSize, uint32_t fReserved, 
        uint32_t fOffBits, uint32_t size, uint32_t width, uint32_t height,
            uint16_t planes, uint16_t bitCount, uint32_t compression, uint32_t sizeImage, 
        uint32_t xPelsPerMeter, uint32_t yPelsPerMeter, uint32_t clrUsed, uint32_t clrImportant) : bfType(fType), bfSize(fSize), bfReserved(fReserved), bfOffBits(fOffBits), biSize(size),
                                                                                                   biWidth(width), biHeight(height), biPlanes(planes), biBitCount(bitCount), biCompression(compression),
                                                                                                   biSizeImage(sizeImage), biXPelsPerMeter(xPelsPerMeter), biYPelsPerMeter(yPelsPerMeter), 
                                                                                                   biClrUsed(clrUsed), biClrImportant(clrImportant){
    
}

int BitmapHeader::readHeader(std::string p){
    std::ifstream file(p);
    if(!file.good())
        return 3;
    read(file);
    file.close();
    return 0;
}

int BitmapHeader::readHeader(){
    std::ifstream file(path);
    if(!file.good())
        return 3;
    read(file);
    file.close();
    return 0;
}

int BitmapHeader::fixType(){
    bfTypeA = bfType & 0x00FF;
    bfTypeB = bfType >> 8;
    return 0;
}

void BitmapHeader::read(std::ifstream& f){
    f.seekg(0, std::ios::beg);
    //File Header
    f.read((char*) &bfType, sizeof(bfType));
    fixType();
    f.read((char*) &bfSize, sizeof(bfSize));
    f.read((char*) &bfReserved, sizeof(bfReserved));
    f.read((char*) &bfOffBits, sizeof(bfOffBits));
    //Information Header
    f.read((char*) &biSize, sizeof(biSize));
    f.read((char*) &biWidth, sizeof(biWidth));
    f.read((char*) &biHeight, sizeof(biHeight));
    f.read((char*) &biPlanes, sizeof(biPlanes));
    f.read((char*) &biBitCount, sizeof(biBitCount));
    f.read((char*) &biCompression, sizeof(biCompression));
    f.read((char*) &biSizeImage, sizeof(biSizeImage));
    f.read((char*) &biXPelsPerMeter, sizeof(biXPelsPerMeter));
    f.read((char*) &biYPelsPerMeter, sizeof(biYPelsPerMeter));
    f.read((char*) &biClrUsed, sizeof(biClrUsed));
    f.read((char*) &biClrImportant, sizeof(biClrImportant));
}

void BitmapHeader::printHeader(){
    std::cout << "Type: " << bfTypeA << bfTypeB << std::endl;
    std::cout << "File-Size in byte kb: " << bfSize/1000 << std::endl;
    std::cout << "Reserved: " << bfReserved << std::endl;
    std::cout << "OffBits: " << bfOffBits << std::endl;
    std::cout << "Info-Header-Size in byte kb: " << biSize/1000 << std::endl;
    std::cout << "Width in pixel: " << biWidth << std::endl;
    std::cout << "Height in pixel: " << biHeight << std::endl;
    std::cout << "Planes (outdated): " << biPlanes << std::endl;
    std::cout << "Color Depth (bit count): " << biBitCount << std::endl;
    std::cout << "Compression: " << biCompression << std::endl;
    std::cout << "Size of image data: " << biSizeImage << std::endl;
    std::cout << "biXPelsPerMeter: " << biXPelsPerMeter << std::endl;
    std::cout << "biYPelsPerMeter: " << biYPelsPerMeter << std::endl;
    std::cout << "biClrUsed: " << biClrUsed << std::endl;
    std::cout << "biClrImportant: " << biClrImportant << std::endl;
}