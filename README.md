<P align="center">
  <img src="https://pouch.jumpshare.com/preview/yC6KnqffZIhkygf2DwZTRBwf85vQn5KD2N8CrQ-fI80n6cVHrJKzoFJEan_g2Db9cu-lRxeHz5sW_xn-3AM-LlYccHBbRpEsQCG805RA_m8">
  <img alt="Static Badge" src="https://img.shields.io/badge/authors-lzkamods-white">
  <img alt="Github All Releases" src="https://img.shields.io/github/downloads/lzkamods/PCCT2/total">
</P>

<h1>PC CONTROL TOOL C++</h1>

## all the necessary functions to control your PC directly from your browser!
· TURN OFF/RESTART/LOG OUT PC

· OPEN APPS (CHANGE PATH TO APP IN THE main.cpp)

· CHANGE VOLUME

# HOW TO INSTALL
## Way 1
### install the code and open folder builds
### then open build.exe app
## Way 2
### install the code and open build.bat
### then open builds folder and run build.exe
## Way 3 (requied g++ and MinGW)
### open command prompt with source code folder directory and run this command
```
g++ main.cpp -lole32 -loleaut32 -lws2_32 -std=c++20 -o build/build.exe
```
### then open build folder and run build.exe
