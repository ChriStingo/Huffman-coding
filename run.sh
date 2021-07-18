#!/bin/bash
var="";
while [ "$var" = "" ];
do
	echo -e "Insert the input file inside Input folder and insert the name here: ";
	read var;
done
echo -e "\nCompiling..";
eval "g++ Code/*.cpp -o Code/Huffman";
echo -e "Executing..\n";
eval "./Code/Huffman $var";
echo -e "\nDone!";