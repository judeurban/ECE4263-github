// huffman compression algorithm in c++
//jude urban
//14 september 2021

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct HuffmanFormat
{
    int path[100];
    string characters;
    int frequency[100];
};

class Node
{
private:
    /* data */
public:
    Node *leftchild;
    Node *rightchild;
    string value;
    int path;
    Node(/* args */);

    Node(Node &, Node &, string);
};

//constuctor 1
Node::Node()
{
    // place in tree, determine the path
    // left shift to lower into tree
    // don't add for left child, add one for right child
}

// constructor 2
Node::Node(Node &leftchild, Node &rightchild, string value)
{
}

int main()
{
    size_t n;
    // string filepath;
    // string fileline;
    // cout << "Copy and paste or drag and drop the path here: " ;
    // cin >> filepath;
    // filepath = "compress.txt";

    // FILE *fileptr = fopen(filepath, "r");

    // fgets(fileline, 5, fileptr)

    string input_string;
    HuffmanFormat huffman;
    uint8_t i;

    Node rootnode;
    Node leftchildnode;
    Node rightchildnode;
    Node leftchildsnodeleftchild;

    input_string = "No gains without pains.";
    if (input_string.length() >= 100)
        return 0;

    std::string s = "a_b_c";

    //for each character
    //if char is in aray,
    //else
    //store 'n' in an array. the frequency of each character

    // for(i = 0 ; input_string.length() ; i++)
    // {
    //     cout << i << endl;
    //     if(huffman.characters.find(input_string[i] != string::npos))
    //     {
    //         // true
    //         cout << "true... do not add chacter or count " << endl;
    //     }
    //     else
    //     {
    //         cout << "false... add characater " << endl;
    //         // huffman.characters.append(input_string[i]);
    //         huffman.characters.append("str");
    //         // n = count(input_string.begin(), s.end(), '_');
    //         // huffman.frequency(i)  = n
    //     }
    //     i ++;
    // }

    cout << "string length is: " << input_string.length() << endl;

    for (i = 0; i <= input_string.length(); i++)
    {
        if (huffman.characters.find(input_string[i]) != string::npos)
        {
            cout << "found!" << '\n';
        }
        else
        {
            cout << "not found!!" << endl;
        }
    }

    cout << huffman.characters << endl;

    leftchildnode.leftchild = &leftchildsnodeleftchild;
    rootnode.leftchild = &leftchildnode;
    rootnode.rightchild = &rightchildnode;

    cout << "leftchild node is at " << &leftchildnode << endl;
    cout << "rightchild node is at " << &rightchildnode << endl;
    cout << "rootnode left child is at " << rootnode.leftchild << endl;
    cout << "rootnode right child is at " << rootnode.rightchild << endl;
    cout << "rootnode left child left child is at " << rootnode.leftchild->leftchild << endl;

    return 0;
}