# steganoMessage
Tool to encrypt and decrypt a message withing a random graphic file (for now bitmap, propably will support jpeg and png as well)

Mainly as experiment to learn about steganography.
Compiles on linux with:
g++ -o steganoMessage ./src/main.cpp [... all the other files located in ./src and ./header]

for GDB debugging do :
g++ -o steganoMessage ./src/main.cpp [... all the other files located in ./src and ./header]-export-dynamic -g
  
Should compile with little to no changes on MAC as well for now. Should work under cygwin or mingw in windows as well if needed tools are installed. No promises though.
