/**
 * @file Expression file is undefined on line 2, column 12 in file:///home/florian/git/steganoMessage/nbproject/licenseheader.txt.
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 2019.06.08
 * @brief
 */
/* 
 * File:   Jpeg.cpp
 * Author: Florian Leuze
 * 
 * Created on 8. Juni 2019, 18:13
 */

#include "../header/Jpeg.h"

Jpeg::Jpeg() {
}

Jpeg::Jpeg(std::string p, ErrorHandler* err):Image(p, err){
    
}
    
Jpeg::Jpeg(const Jpeg& orig) {
}

Jpeg::~Jpeg() {
}

int Jpeg::readImage(){
    const uint32_t bitmapHeaderLength = 54;
    const uint32_t infoHeaderLength = 40;
    unsigned char alphaChannel;
    std::cout << "In jpeg read image" << std::endl;
     if(path == "")
        return 3;
    header = new BitmapHeader(path, errHandle, false);
    
    jpeg_decompress_struct cinfo;
    jpeg_error_mgr errMan;
    
    FILE* inFile = fopen(path.c_str(), "rb");
    cinfo.err = jpeg_std_error(&errMan);
        
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, inFile);
    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);
    header->getHeaderStruct()->bfOffBits = bitmapHeaderLength;
    header->getHeaderStruct()->bfReserved = 0;
    header->getHeaderStruct()->bfSize = 32 * cinfo.image_height * cinfo.image_width + bitmapHeaderLength;
    header->getHeaderStruct()->bfType = 0x4D42;
    uint16_t test = 0x4D42;
    header->fixType();
    if(cinfo.data_precision * cinfo.num_components == 24){
        header->getHeaderStruct()->biBitCount = 32;
        alphaChannel = cinfo.output_gamma;
    }
    header->getHeaderStruct()->biClrImportant = 0;
    header->getHeaderStruct()->biClrUsed = 0;
    header->getHeaderStruct()->biCompression = 0;
    header->getHeaderStruct()->biHeight = cinfo.image_height;
    header->getHeaderStruct()->biPlanes = 1;
    header->getHeaderStruct()->biSize = infoHeaderLength;
    header->getHeaderStruct()->biSizeImage = 0;//32 * cinfo.image_height * cinfo.image_width;
    header->getHeaderStruct()->biWidth = cinfo.image_width;
    header->getHeaderStruct()->biXPelsPerMeter = 0;
    header->getHeaderStruct()->biYPelsPerMeter = 0;
    header->printHeader();
    std::cout << "Generating array with " << (cinfo.num_components+1) * cinfo.image_height * cinfo.image_width << " Bytes storage" << std::endl;
    uint32_t bufferLength = (cinfo.num_components+1) * cinfo.image_height * cinfo.image_width;
    uint32_t bufferLength_a = cinfo.num_components * cinfo.image_height * cinfo.image_width;
    unsigned char* buffer_a = new unsigned char[bufferLength_a];
    unsigned char* buffer_b = new unsigned char[bufferLength];
    
    for(int i = 0; cinfo.output_scanline < cinfo.image_height; ++i){
        uint8_t* p = buffer_a + cinfo.output_scanline*cinfo.image_width*cinfo.num_components;
	jpeg_read_scanlines(&cinfo, &p, 1);
    }
    std::cout << "Finished reading" << std::endl;
    int k = 1;
    try{ 
        for(int i = 0; i < bufferLength; ++i){
            if(i < 3)
                *(buffer_b + k * (cinfo.num_components+1)*header->getWidth() - i) = *(buffer_a + bufferLength_a - i - 1);
            else if((i+3)%4 == 0)
                *(buffer_b + k * (cinfo.num_components+1)*header->getWidth() - i) = cinfo.output_gamma;
            else
                *(buffer_b + k * (cinfo.num_components+1)*header->getWidth() - i) = *(buffer_a + bufferLength_a - i - 1 + (i+3)/4);
           
            if(i != 0 && i%((cinfo.num_components+1)*header->getWidth()) == 0)
                k+=2;
        }
    }
    catch(const std::exception& e){
        std::cout << e.what() << std::endl;
    }
    std::cout << "Finished storing values" << std::endl;
    std::vector<std::vector<uint32_t>> data;
    std::vector<uint32_t> innerData;
    uint32_t temp = 0;
    for(int i = 0; i < bufferLength; i=i+4){ //wrong direction because bitmap image data goes from bottom to top
        temp = ((uint32_t)(*(buffer_b + i)) | (((uint32_t)(*(buffer_b+i+1)))<<8) | (((uint32_t)(*(buffer_b+i+2)))<<16) | (((uint32_t)(*(buffer_b+i+3)))<<24));
        temp = Filter::swapGR(temp, sizeof(temp)); //fix inversed byte order 
        /*std::cout << "Generated bits: " << +((uint8_t)((temp & 0xFF000000)>> 24)) << "|" << +((uint8_t)((temp & 0xFF0000) >>16)) << "|" 
                    << +((uint8_t)((temp & 0xFF00) >>8)) << "|" << +((uint8_t)(temp)) << std::endl;*/
        innerData.push_back(temp);
        if(innerData.size() == header->getWidth()){
            temp = 0;
            data.push_back(innerData);
            innerData.clear();
        }
    }
    array = new BitmapArray(path, header->getOffBits(), header->getWidth(), header->getHeight(), header->getBitCount(), errHandle, filterModeCol, data);

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(inFile);
    return 0;
}
