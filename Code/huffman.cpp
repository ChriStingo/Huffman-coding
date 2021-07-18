#include <bits/stdc++.h>
#include <sys/stat.h>
#include "Tree.h"
using namespace std;
using namespace tree;

int Length = 256;

// Compute the Entropy value
double entropy(vector<double>probability){
    double sum = 0;
    for(int i = 0; i < Length; i++){
        sum += probability[i] == 0 ? 0 : (probability[i] * log2(1/probability[i]));
    }
    return sum;
}

// Compute the rate value
double rate(vector<double>probability, vector<string>encoding){
    double sum = 0;
    for (int i = 0; i < Length; i++)
        sum += probability[i] * encoding[i].length();
    return sum;
}

// Compute the probability value for each character
vector<double> probability(vector<int>&ascii){
    int sum = 0;
    vector<double>result(Length);
    for(int i = 0; i < Length; i++){
            sum += (ascii[i] > 0 ? ++ascii[i] : 0);
    }
    for(int i = 0; i < Length; i++){
           result[i] = (double)ascii[i] / sum;
    }
    return result;
}

int main(int argc, char **argv)
{
    //Check input
    if(argc <= 1){
        cout << "\x1B[91mPut the file in the Input folder. Insert the name of input file.\033[0m" << endl;
        return 0;
    }


    /*###############################################################################################################################
    Allocating, initialize data structures and open input file
    ###############################################################################################################################*/


    // Allocating data structures
    vector<int>ascii(Length, 0);
    vector<double>prob;
    vector<string>encoding;
    priority_queue< pair<double, int>, vector<pair<double,int>>, greater<pair<double,int>> > pq; 
    Tree g = createEmptyTree();

    // Open read file given in input
    string inString = argv[1];
    inString = "Input/" + inString;
    FILE* fdInput = freopen( &inString[0], "r", stdin);
    if(fdInput == nullptr){
        cout << "\x1B[91mInsert the name of the input file. It must be the same name of the file inside Input folder.\033[0m" << endl;
        return 0;
    }


    /*###############################################################################################################################
    Read input file, count the character frequency and compute probability
    ###############################################################################################################################*/


    // Read characters from file
    while(true){
        unsigned char character;
        cin >> noskipws >> character; // noskipws used to take space and new line
        if(cin.eof())
            break;
        ascii[(int)character]++;
    }

    // Close the input file
    fclose(fdInput);

    // Compute the probability fro each character
    prob = (probability(ascii));


    /*###############################################################################################################################
    Creating the Tree using a priority queue. The Tree header is inside Tree.h and the tree code is inside tree.cpp
    ###############################################################################################################################*/
    

    // Insert character into a priority queue order by probability
    for(int i = 0; i < Length; i++){
        pq.push(make_pair(prob[i], i));
    }
    
    // Insert values into the Tree
    int new_char = Length;  // new_char is the sum of the 2 elements chosen by the algorithm, this value must be unique inside the Tree, so it is a number > all character in the Tree
    while(!pq.empty()){
        // Take the smallest probability pair
        pair<double,int> x = pq.top();
        pq.pop();
        addVertex(x.second, g); // Insert in the Tree
        if(pq.empty())
            break;
        // If the previus is not the only elements inside the queue, take the smallest probability pair
        pair<double,int> y = pq.top();
        pq.pop();
        addVertex(y.second, g); // Insert in the Tree
        
        // Creating the father os the 2 elements and add it to the Tree
        addVertex(new_char, g);
        addEdge(new_char, x.second, "1", g);
        addEdge(new_char, y.second, "0", g);
        // Check if the algorithm ends
        if(pq.empty())
            break;
        // If there are other elements inside the queue insert in order the new father and go on
        pq.push(make_pair(x.first + y.first, new_char));
        new_char++;
    }

    // Map all the character with the encode value (use the int value of character like an index)
    for(int i = 0; i < Length; i++){
        string aux = dfs(g,i);
        encoding.push_back (aux);
    }


    /*###############################################################################################################################
    Print the Legend file and encode input writing in output file
    ###############################################################################################################################*/


    // Print Entropy, the Rate and their ratio
    cout << "\tEntropy: " << entropy(prob) << " bits/symbols\n\tRate: " << rate(prob, encoding) << " bits/symbols\n\tRedundancy: " << rate(prob, encoding) - entropy(prob) << " bits/symbols" << endl;
    cout << "\n\tLegend created in Output/Legend_" << argv[1] << ".txt\n\tFile encoded will be created in Output/" << argv[1] << ".encoded" << endl;
    // Re-open the input file for encoding and open the output file
    string outString = argv[1];
    outString = "Output/Legend_" + outString + ".txt";
    FILE* fdOutput = freopen( &outString[0], "w", stdout);
    cout << "ASCII # appears # times with symbol # --> encode bits string" << endl;

    // Print the legend and close the output file
    for(int i = 0; i < Length; i++){
        cout << "ASCII " << i << " appears " << (ascii[i] > 0 ? (ascii[i]-1) : 0) << " times";
        if(isprint((unsigned char)i))
            cout << " with symbol: " << (unsigned char)i;
        else
            cout << " with symbol: not printable";
        cout << " --> " << encoding[i] << endl;
    }
    fclose(fdOutput);
    
    // Re-open the input file for encoding and open the output file
    fdInput = freopen( &inString[0], "r", stdin);
    outString = argv[1];
    outString = "Output/" + outString + ".encoded";
    fdOutput = freopen( &outString[0], "w", stdout);

    // Clear the buffer for new read
    cin.clear();

    // Read characters from file and write the encode value in the output file
    while(true)
    {
        unsigned char aux;
        cin >> noskipws >> aux; // noskipws used to take space and new line
        if(cin.eof())
            break;
        cout << encoding[int(aux)];
    }


    /*###############################################################################################################################
    Closing files descriptor and end the program
    ###############################################################################################################################*/


    // Close input and output file
    fclose(fdInput);
    fclose(fdOutput);
    return 0;
}