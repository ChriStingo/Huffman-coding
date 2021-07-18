June 2020

Huffman coding made by:
- Christian Stingone: https://github.com/ChriStingo
- Paolo Patrone: https://github.com/patpa99
- Matteo Raffo: https://github.com/Buffless24

How to execute the program:
- Before:
	Insert the file to encode into Input folder
- Run the program:
	Execute the command ./run.sh
	This file compile and execute the program.
	Once launched, you will be prompted to enter the name of the file previously entered in the Input folder (only the file name, do not enter information relating to the path)
This executable will insert the encoded file and a Legend in the Output folder, to allow a simple translation. It will also print on the terminal some information to check how good the encode was.

The file is encoded and placed in the Output folder together with a file containing the Legend corresponding to the translation of the characters.
I decided to write the encoded values ​​inside the file as characters themselves.
In this way the file is not actually compressed, since every 0 and 1 inserted are encoded with 8 bits.
This choice is deliberate, since I think it is easier to carry out a check. (useful website to check: https://www.dcode.fr/huffman-tree-compression)