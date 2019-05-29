# steganoMessage
Tool to encrypt and decrypt a message withing a random graphic file (for now bitmap, propably will support jpeg and png as well)

Mainly as experiment to learn about steganography.
Compiles on linux with:
g++ -o steganoMessage ./src/main.cpp ./src/SteganoMessage.cpp ./header/SteganoMessage.h ./src/Message.cpp ./header/Message.h ./src/Image.cpp ./header/Image.h ./src/BitmapHeader.cpp ./header/BitmapHeader.h ./src/BitmapArray.cpp ./header/BitmapArray.h ./src/ErrorHandler.cpp ./header/ErrorHandler.h ./header/constants.h

for GDB debugging do :
g++ -o steganoMessage ./src/main.cpp ./src/SteganoMessage.cpp ./header/SteganoMessage.h ./src/Message.cpp ./header/Message.h ./src/Image.cpp ./header/Image.h ./src/BitmapHeader.cpp ./header/BitmapHeader.h ./src/BitmapArray.cpp ./header/BitmapArray.h ./src/ErrorHandler.cpp ./header/ErrorHandler.h ./header/constants.h -export-dynamic -g
  
Should compile with little to no changes on MAC as well for now. Should work under cygwin or mingw in windows as well if needed tools are installed. No promises though.
