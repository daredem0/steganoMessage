/*
 * @file Expression file is undefined on line 2, column 12 in file:///home/florian/git/steganoMessage/nbproject/licenseheader.txt.
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 2019.06.11
 * @brief
 */
/* 
 * File:   Png.cpp
 * Author: Florian Leuze
 * 
 * Created on 11. Juni 2019, 13:32
 */

#include "../header/Png.h"

Png::Png() {
}

Png::Png(std::string p, ErrorHandler* err):Image(p, err){
}
    
Png::Png(const Png& orig) {
}

Png::~Png() {
    free(pData);
}

int Png::readImage(){
    int error;
    const uint32_t bitmapHeaderLength = 54;
    const uint32_t infoHeaderLength = 40;
    unsigned char alphaChannel;
    errHandle->printLog("Reading png image\n");
     if(path == "")
        return 3;
    header = new BitmapHeader(path, errHandle, false);

    //initializing
    errHandle->printLog("Filepath: " + path + "\n");
    FILE *inFile = fopen(path.c_str(), "rb");
    
    //call our own init method
    errHandle->printLog("Startng png init\n");
    error = readPng_init(inFile, &width, &height, &bDepth, &cType);
    
    //check for background color of png file
    errHandle->printLog("Check background color\n");
    //uint8_t red, green, blue;
    //readpng_get_bgcolor(&red, &green, &blue);
    
    //no gamma correction
    double gamma = 1;
    
    //call our read method
    errHandle->printLog("Call read method\n");
    int pChannels;
    unsigned long pRowBytes;
    //png_bytep row_pointers[height];
    readpng_get_image(gamma, &pChannels, &pRowBytes);
    
    //start to fill up the header
    errHandle->printLog("Fill header\n");
    header->getHeaderStruct()->bfOffBits = bitmapHeaderLength;
    header->getHeaderStruct()->bfReserved = 0;
    header->getHeaderStruct()->bfSize = 32/8 * height * width  + bitmapHeaderLength;
    header->getHeaderStruct()->bfType = 0x4D42;
    header->fixType();
    header->getHeaderStruct()->biBitCount = 32;
    header->getHeaderStruct()->biClrImportant = 0;
    header->getHeaderStruct()->biClrUsed = 0;
    header->getHeaderStruct()->biCompression = 0;
    header->getHeaderStruct()->biHeight = height;
    header->getHeaderStruct()->biPlanes = 1;
    header->getHeaderStruct()->biSize = infoHeaderLength;
    header->getHeaderStruct()->biSizeImage = 0;//32 * cinfo.image_height * cinfo.image_width;
    header->getHeaderStruct()->biWidth = width;
    header->getHeaderStruct()->biXPelsPerMeter = 0;
    header->getHeaderStruct()->biYPelsPerMeter = 0;
    header->printHeader();
        //bDepth = png_get_bit_depth(png_ptr, info_ptr);
    std::cout << "BitDepth: " << bDepth << std::endl;
    errHandle->printLog("Parsing data\n");
    std::vector<std::vector<uint32_t>> data;
    std::vector<uint32_t> innerData;
    uint32_t temp = 0;
    switch(cType){
        case 2:{
            uint32_t temp = 0, k = 1;
            uint32_t limit = width * height * 3;
            for(int i = 0; i < width * height * 3 ; i = i+3){
                temp = ((uint32_t)(*(pData+limit-k*width*3 + i+2)) | (((uint32_t)(*(pData+limit-k*width*3+i+1)))<<8) 
                        | (((uint32_t)(*(pData+limit-k*width*3+i)))<<16) | (((uint32_t)(0x00))<<24));
                innerData.push_back(temp);
                if(i != 0 && i%(3*width) == 0)
                    k+=2;
                if(innerData.size() == header->getWidth()){
                    temp = 0;
                    data.push_back(innerData);
                    innerData.clear();
                }
            }
        }
            break;
        case 6: {
            uint32_t temp = 0, k = 1;
            uint32_t limit = width * height * 4;
            for(int i = 0; i < width * height * 4 ; i = i+4){
                temp = ((uint32_t)(*(pData+limit-k*width*4 + i+2)) | (((uint32_t)(*(pData+limit-k*width*4+i+1)))<<8) 
                        | (((uint32_t)(*(pData+limit-k*width*4+i)))<<16) | (((uint32_t)(*(pData+limit-k*width*4+i+3)))<<24));
                innerData.push_back(temp);
                if(i != 0 && i%(4*width) == 0)
                    k+=2;
                if(innerData.size() == header->getWidth()){
                    temp = 0;
                    data.push_back(innerData);
                    innerData.clear();
                }
            }
        }
            break;
        default:
            return ErrorHandler::errPng;
    }
    
    array = new BitmapArray(path, header->getOffBits(), header->getWidth(), header->getHeight(), header->getBitCount(), errHandle, filterModeCol, data);
       
    readpng_cleanup();
    fclose(inFile);
    return ErrorHandler::errNoError;
}

int Png::readPng_init(FILE *inFile, uint32_t *pWidth, uint32_t *pHeight, int *bitDepth, int *colorType){
    //check again if the file really is a png file
    unsigned char signature[8]; //8 bits are identical for every png file
    fread(signature, 1, 8, inFile);
    if(!png_check_sig(signature, 8))
        return ErrorHandler::errPngSig;
    
    /*Build image information structs and check for out of memory errors*/
    /*png_structp is used internally to keep track of the current state of the png image*/
    errHandle->printLog("Create read struct\n");
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if(!png_ptr)
        return ErrorHandler::errPngMem;
    
    /*png_infop is used to indicate what the state of the pnc will be after user transformations are performed*/
    errHandle->printLog("create info struct\n");
    info_ptr = png_create_info_struct(png_ptr);
    if(!info_ptr){
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        return ErrorHandler::errPngMem;
    }
    
    //libpng specific error handling
    if(setjmp(png_jmpbuf(png_ptr))){
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        return ErrorHandler::errPngInt;
    }
    
    //do some init stuff
    errHandle->printLog("initio and set sig bytes\n");
    png_init_io(png_ptr, inFile);
    png_set_sig_bytes(png_ptr, 8);
    
    //now we read basically everything until the image data
    errHandle->printLog("read info\n");
    png_read_info(png_ptr, info_ptr); 
    /*Lastly we write the important information from the header to the addresses where the pointer arguments point*/
    errHandle->printLog("get IHDR\n");
    png_uint_32 w, h;
    png_get_IHDR(png_ptr, info_ptr, (png_uint_32*)pWidth, (png_uint_32*)pHeight, bitDepth, colorType, NULL, NULL, NULL);
    //exit(1);
    return ErrorHandler::errNoError;
}

int Png::readpng_get_bgcolor(uint8_t *red, uint8_t *green, uint8_t *blue){
    errHandle->printLog("In backgroundoclor method\n");
    //libpng specific error handling
    if(setjmp(png_jmpbuf(png_ptr))){
    errHandle->printLog("internal error\n");
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        return ErrorHandler::errPngInt;
    }
    
    errHandle->printLog("Check if color is set\n");
    //check if png file has backgroundcolor set
    if(!png_get_valid(png_ptr, info_ptr, PNG_INFO_bKGD)){
        bKgdFlag = false;
        //return ErrorHandler::errPngBkgd; //careful not 1 as in example
    }
    
    //do this only if the backgroundcolor is set
    if(bKgdFlag == true){
    errHandle->printLog("Color = true\n");
        //finally get the backgroundcolor from libpng
        png_color_16p pBackground;
    errHandle->printLog("Get the background color\n");
        png_get_bKGD(png_ptr, info_ptr, &pBackground);

        //convert to 8bit values
        if(bDepth == 16){
            *red   = pBackground->red   >> 8;
            *green = pBackground->green >> 8;
            *blue  = pBackground->blue  >> 8;
        }
        else if(cType == PNG_COLOR_TYPE_GRAY && bDepth < 8){
            switch(bDepth){
                case 1:
                    *red = *green = *blue = pBackground->gray? 255 : 0;
                    break;
                case 2:
                    *red = *green = *blue = (255/3) * pBackground->gray;
                    break;
                default: /* means bDepth = 4*/
                    *red = *green = *blue = (255/15) * pBackground->gray;
            }
        }
        else{
            *red   = pBackground->red;
            *green = pBackground->green;
            *blue  = pBackground->blue;
        }
    }
    else{ /*if no background color is set in the image make it white*/
    errHandle->printLog("No color is set\n");
        *red = *green = *blue = 255;
    }
    
    return ErrorHandler::errNoError;
}

int Png::readpng_get_image(double display_exponent, int *pChannels, unsigned long *pRowBytes){
    errHandle->printLog("In read method\n");
    //libpng specific error handling
    if(setjmp(png_jmpbuf(png_ptr))){
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        return ErrorHandler::errPngInt;
    }
    //set up png to give us 8 bit per channel + alpha if available. 
    /*png_set_expand() shall set transformation in png_ptr such that paletted 
     * images are expanded to RGB, grayscale images of bit-depth less than 8 are expanded to 
     * 8-bit images and tRNS chunks are expanded to alpha channels.*/
    std::cout << "cType: " << cType << " | " << "bDepth: " << bDepth << std::endl;
    if (cType == PNG_COLOR_TYPE_PALETTE)
        png_set_expand(png_ptr);
    if (cType == PNG_COLOR_TYPE_GRAY && bDepth < 8)
        png_set_expand(png_ptr);
    if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
        png_set_expand(png_ptr);
    if (bDepth == 16)
        png_set_strip_16(png_ptr);
    if (bDepth == PNG_COLOR_TYPE_GRAY ||
        bDepth == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(png_ptr);
    
    std::cout << "cType: " << cType << " | " << "bDepth: " << bDepth << std::endl;
    //apply not existing gamma correction
    double  gamma;
    if (png_get_gAMA(png_ptr, info_ptr, &gamma))
        png_set_gamma(png_ptr, display_exponent, gamma);
    
    //update information struct after transformations are done and get values for the pointers
    png_uint_32 rowbytes;
    png_bytep row_pointers[height];
    //row_pointers = (png_bytep*)malloc(sizeof(png_bytep)*height);
    
    errHandle->printLog("Update info\n");
    png_read_update_info(png_ptr, info_ptr);
    
    errHandle->printLog("Get rowbytes and channels\n");
    *pRowBytes = rowbytes = png_get_rowbytes(png_ptr, info_ptr);
    std::cout << "Rowbytes " << rowbytes << std::endl;
    *pChannels = (int)png_get_channels(png_ptr, info_ptr);
    std::cout << "Amount of bytes in row: " << rowbytes << std::endl;
    //allocate memory, if we cant allocate it return memory error
    pData = NULL;
    errHandle->printLog("Allocate memory\n");
    if((pData  = (unsigned char*)malloc(rowbytes*height)) == NULL){
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        return ErrorHandler::errPngMem; 
    }
    
    //store the addresses in the row_pointers array
    for(png_uint_32 i = 0; i < height; ++i){
        row_pointers[i] = pData + i * rowbytes;
        //row_pointers[i] = (png_byte*)malloc(rowbytes);
    }
    
    //finally store the image data in the created array
    png_read_image(png_ptr, row_pointers);
    //png_read_end(png_ptr, NULL); //not sure if we need that one
    
    return ErrorHandler::errNoError;
}

int Png::readpng_cleanup(){
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    return ErrorHandler::errNoError;
}