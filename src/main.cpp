#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;
#define MEM_SIZE 0x10000
#define HEADER_SIZE 0x20

uint8_t* text  = new uint8_t[MEM_SIZE];
uint8_t* data = new uint8_t[MEM_SIZE];
uint32_t textSize = 0;

void loadFile(char filename[]) {
    ifstream ifs(filename, ios::in | ios::binary);
    if (!ifs) {

        std::cerr << "open failed ";
        exit(1);
    }
    uint8_t* header = new uint8_t[HEADER_SIZE];
    ifs.read((char *)header, HEADER_SIZE);
    memcpy(&textSize,header+8,sizeof(textSize));//little endian
    ifs.read((char *)text, textSize);
    ifs.close();
}


int main(int argc,char *argv[]) {
    loadFile(argv[1]);
    unsigned short  IP = 0;
    while(IP < textSize){
        printf("%04x: ", IP);
        switch(text[IP]){
            case 0x83:
                printf("sub ");
                ++IP;
                printf("[%02x%02x], %02x",text[++IP],text[++IP],text[++IP]);
                break;
            case 0xbb:
                printf("mov bx, ");
                printf("%02x%02x",text[++IP],text[++IP]);
                break;
            case 0xcd:
                printf("int ");
                printf("%02x",text[++IP]);
                break;
            default:
                printf("not implemented");
                exit(1);
        }
        printf("\n");
        ++IP;
    }
    return 0;
}
