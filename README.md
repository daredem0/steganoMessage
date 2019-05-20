# network-analyzer
tool to automatically ping and traceroute an ip range and generate a graph from the results. 

This project is mainly to teach myself about gtk+, multithreading and some basic path finding and storing algorithms.
Nevertheless the goal is to make this a useful tool. 
Compiles on linux with:
g++ `pkg-config --cflags gtk+-3.0` -o na_001 ./src/main.cpp ./src/callbacks.cpp ./header/callbacks.h 
  ./src/Data.cpp ./header/Data.h ./src/Gui.cpp ./header/Gui.h ./src/IPAddress.cpp ./header/IPAddress.h 
  ./src/IPRange.cpp ./header/IPRange.h ./src/Network.cpp ./header/Network.h ./src/OutputStream.cpp ./header/OutputStream.h 
  /src/Ping.cpp ./header/Ping.h `pkg-config --libs gtk+-3.0` -export-dynamic -pthread -g
  
Should compile with little to no changes on MAC as well. Ping relies on OS dependend ping command for now which might needs
to be changed slightly under MAC. Should work under cygwin or mingw in windows as well if needed tools are installed. No promises though.
Btw. its really slow so far. Need to multithread the pings.
