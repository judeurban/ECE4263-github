#include <iostream>
#include <string>
#include <algorithm>
#include "main.h"
#include <stdint.h>
#include <iterator>
#include <map>

using namespace std;

void Decode(void);

string input_string;

// empty map container
map<char, ptr> HuffmamDict;

class HuffmanCharacter
{
private:
    /* data */
public:
    char value;
    int path;
    int frequency;
    HuffmanCharacter(char c /*, int p, int f */ )
    {
        cout << "new character: " << c << endl;
        value = c;
        path = 0;
        frequency = 0;
        // path = p;
        // frequency = f;
    }

    HuffmanCharacter() 
    {
        cout << "new character" << endl;
        path = 0;
        frequency = 0;
    }

    void DispChar()
    {
        cout << "value: -------- " << value << endl;
        cout << "path: --------- " << path << endl;
        cout << "frequency: ---- " << frequency << endl << endl;
        return;
    }
};

int main()
{
    input_string = "No gains without pains.";
    if (input_string.length() >= HUFFMAN_ARRAY_LEN)
        return 0;
        
    HuffmanCharacter mynewchar;
    HuffmanCharacter mychar('+');
    HuffmanCharacter mynewestchar;

    //decode
    Decode();

    // mynewchar.DispChar();
    // mychar.DispChar();
    // mynewestchar.DispChar();

    return 0;
}

void Decode()
{
    uint8_t str_idx;
    uint8_t arr_idx = 0;
    uintptr_t addr;

	HuffmamDict.insert(pair<int, int>(2, 30));

    // if(HuffmamDict.find(2) == 30)
    // {
    // cout << "true" << endl;

    // }
    // else
    // {
    // cout << "false" << endl;
    // }
    // for(str_idx = 0 ; str_idx <= input_string ; str_idx++)
    // {

    // }

}