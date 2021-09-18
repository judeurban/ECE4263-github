#include <iostream>

using namespace std;

void UniqueCharacters(string);
void CreateObjects(void);
string unique_characters;



class HuffmannCharacter
{
private:
    /* data */
public:
    char value;
    uint16_t freqeuncy;
    HuffmannCharacter()
    {
        this->value = 'a';
        this->freqeuncy = 0;
    }
    HuffmannCharacter(char c)
    {
        this->value = c;
        this->freqeuncy = 0;
    }
    void DispCharacters()
    {
        for(int i = 0; i <= unique_characters.length(); i++)
        {
            cout << "value is: " << this[i].value << endl;
        }
    }
};

int main()
{
    string console_input;

    //determine unique characters, store into array

    console_input = "No gains without pains.";
    if (console_input.length() >= 100)
        return 0;

    UniqueCharacters(console_input);

    cout << "Unique characters are: " << unique_characters << endl;

    //create an object for each character, containing the frequency
    CreateObjects();

    return 0;
}

void UniqueCharacters(string input_string)
{
    for (int i = 0; i <= input_string.length(); i++)
    {
        if (unique_characters.find(input_string[i]) != string::npos)
        {
            cout << "found!" << '\n';
                
        }
        else
        {
            cout << "not found!!" << endl;
            unique_characters.push_back(input_string[i]);
        }
    }
    return;
}

void CreateObjects()
{
    HuffmannCharacter Character[unique_characters.length()];
    // HuffmannCharacter character[unique_characters.length()];
    for(int i = 0; i <= unique_characters.length(); i++)
    {
        Character[i].value = (char) unique_characters[i];
    }
   Character[0].DispCharacters();
    return;
}