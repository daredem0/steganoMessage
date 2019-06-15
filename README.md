# steganoMessage
Tool to encrypt and decrypt a message withing a random graphic file (for now bitmap, propably will support jpeg and png as well)

Mainly as experiment to learn about steganography.
~~Compiles on linux with:  
g++ -o steganoMessage ./src/main.cpp ./src/SteganoMessage.cpp ./header/SteganoMessage.h ./src/Message.cpp ./header/Message.h ./src/Image.cpp ./header/Image.h ./src/BitmapHeader.cpp ./header/BitmapHeader.h ./src/BitmapArray.cpp ./header/BitmapArray.h ./src/ErrorHandler.cpp ./header/ErrorHandler.h ./header/constants.h ./src/Jpeg.cpp ./header/Jpeg.h ./src/Filter.cpp ./header/Filter.h ./src/Png.cpp ./header/Png.h -ljpeg -lpng~~

~~for GDB debugging do:  
g++ -o steganoMessage ./src/main.cpp ./src/SteganoMessage.cpp ./header/SteganoMessage.h ./src/Message.cpp ./header/Message.h ./src/Image.cpp ./header/Image.h ./src/BitmapHeader.cpp ./header/BitmapHeader.h ./src/BitmapArray.cpp ./header/BitmapArray.h ./src/ErrorHandler.cpp ./header/ErrorHandler.h ./header/constants.h ./src/Jpeg.cpp ./header/Jpeg.h ./src/Filter.cpp ./header/Filter.h ./src/Png.cpp ./header/Png.h -export-dynamic -g -ljpeg -lpng~~
  
~~Compiles with little to no changes on MAC as well for now:  
g++-9 -o steganoMessage ./src/main.cpp ./src/SteganoMessage.cpp ./header/SteganoMessage.h ./src/Message.cpp ./header/Message.h ./src/Image.cpp ./header/Image.h ./src/BitmapHeader.cpp ./header/BitmapHeader.h ./src/BitmapArray.cpp ./header/BitmapArray.h ./src/ErrorHandler.cpp ./header/ErrorHandler.h ./header/constants.h ./src/Jpeg.cpp ./header/Jpeg.h ./src/Filter.cpp ./header/Filter.h ./src/Png.cpp ./header/Png.h -ljpeg -lpng~~

~~Should work under cygwin or mingw in windows as well if needed tools are installed. No promises though.~~

Debugging on terminal gets ugly from here on. To keep things os independet please use cmake:

Project can be built with cmake file. Do:  
$./$ cmake .  
$./$ make  
Tested on Linux, not tested on OSX/Windows

Usage:
_steganoMessage_ is a command line tool to hide a message somewhere in a bitmap file.
Use either of the following as first switch to decide if you want to encrypt a message or decrypt a message. Add path of image file after the switch.
-decrypt\n
-encrypt 

***

**example**:

`./steganoMessage -encrypt <path>`  
This will start the routine to encrypt your message into example.bmp  
`./steganoMessage -decrypt <path>`  
This will start the routine to decrypt your message from example.bmp

`./steganoMessage -h`  
This will return the information contained in this help file.  

`./steganoMessage -convert_txt <path>`  
This will convert the bitmap file into a readable text file containing all information as hex values.

`./steganoMessage -filter <path> -filter <type>`  
Applies filter, possible values: `grey/color_a/color_b` <- Filters that are going to be applied while reading/writing  
`color` <- Dummy filter 
 
`inv_n/swap_by/swap_oc/swap_by_oc/swap_by_bi/swap_by_oc_bi/swap_bg/swap_br/swap_gr/subst_bl/subst_rd/subst_gr` <- Filters that will be applied after reading before writing. 
 
`./steganoMessage -filter_cr <path> -filter <type>`  
Activates crazy mode for filters. Same filter codes, automatically shifts the color.  
Sorry, no time yet to describe the filter effects. Just try.

Filters can also be applied automatically while adding a steganoMessage. This will likely mess up everything. Do:
`./steganoMessage -decrypt/-encrypt <path> -filter <type>`




Output into a textfile is possible with the switch -log. Usage is possible with and without filters:  
example a: `./steganoMessage -encrypt <path> -filter <type> -log`  
example b: `./steganoMessage -encrypt <path> -log`  
Logfile will be generated in log folder in ./ and will be named with a timestampm  

It is furthermore possible to view the processed image starting with version 0.3  
To view the image add -show at the end (this is important) of your call. Example:  
`./steganoMessage -encrypt <path> -show`  
`./steganoMessage -encrypt <path> -filter <type> -show`  
`./steganoMessage -encrypt <path> -filter <type> -log -show`  
