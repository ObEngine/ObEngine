#!/bin/bash
apt-get install libsfml-dev
apt-get install liblua5.3-dev
apt-get install lua5.3
git clone https://github.com/Satoren/Kaguya
cd Kaguya/
cmake .
make
cd ..
mkdir ../libs/kaguya
mv Kaguya/include ../libs/kaguya/include
rm -rf Kaguya/
