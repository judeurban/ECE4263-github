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
uint8_t huffman_idx;

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
        // cout << &HuffmanCharacter << endl;
    }

    HuffmanCharacter() 
    {
        cout << " new blank character" << endl;
        value = ' ';
        path = 0;
        frequency = 0;
    }

    void DispChar()
    {
        cout << "value: -------- " << this->value << endl;
        cout << "path: --------- " << this->path << endl;
        cout << "frequency: ---- " << this->frequency << endl << endl;
        return;
    }
};

class HuffmanStructure
{
private:
public:
    string characters[HUFFMAN_ARRAY_LEN];
    uintptr_t locations[HUFFMAN_ARRAY_LEN];


    void Append(char c, uintptr_t h)
    {
        characters[huffman_idx] = c;
        locations[huffman_idx] = h;
        huffman_idx++;
        return;
    }
};

int main()
{
    input_string = "No gains without pains.";
    if (input_string.length() >= HUFFMAN_ARRAY_LEN)
        return 0;
        
    // HuffmanCharacter mynewchar;
    // HuffmanCharacter mychar('+');
    // HuffmanCharacter mynewestchar;

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


    // creating the object 'steve' which is an instance of the class HuffmanCharacter
    HuffmanCharacter steve;

    //create an object with default values by running the contructor function.
    addr -> &HuffmanCharacter('h');

    cout << "steve's value is: '" << steve.value << "' " << endl; 

    // HuffmanStructure::Append('c', new HuffmanCharacter('a'));
    // HuffmanStructure::Append('h', addr);

    // HuffmamDict.insert(pair<'a', new HuffmanCharacter('a')>);

	// HuffmamDict.insert(pair<int, int >('a', new HuffmanCharacter('a')));
    // HuffmamDict.insert(pair<int, int>('a', 69));
	// gquiz1.insert(pair<int, int>(1, 40));


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