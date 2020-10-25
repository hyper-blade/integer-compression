#include <iostream>
#include <fstream>
#include <bitset>
#include <sstream>
using namespace std;

string dbits(int decimal) {
	bitset<4> bits(decimal);
	return bits.to_string();
}

string bdec(unsigned char byte) {
    stringstream decimal;
    decimal << (byte >> 4) << (byte & 0x0f);
    return decimal.str();
}

void compress(string inFilename, string outFilename) {
    ifstream inFile(inFilename);
    ofstream outFile(outFilename);

    string bits = "";
    unsigned char digit;

    while (inFile >> digit) {
        bits += dbits(digit - '0');
        if (bits.size() == 8) {
            unsigned char byte = bitset<8>(bits).to_ulong();
            outFile << byte;
            bits.clear();
        }
    }
}

void decompress(string inFilename, string outFilename) {
    ifstream inFile(inFilename);
    ofstream outFile(outFilename);

    unsigned char byte;

    while (inFile >> noskipws >> byte) {
        string decimal = bdec(byte);
        outFile << decimal;
    }
}

int main() {
    compress("pi.txt", "pi_c.txt");
    decompress("pi_c.txt", "pi_dc.txt");
    return 0;
}