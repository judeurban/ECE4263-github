// huffman compression algorithm in c++
//jude urban
//14 september 2021

#include <iostream>

using namespace std;

struct huffman
{
    int path[100];
    char character[];
};


class Node
{
private:
    /* data */
public:
    Node * leftchild;
    Node * rightchild;
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


int main() {
    string filepath;
    string fileline;
    // cout << "Copy and paste or drag and drop the path here: " ;
    // cin >> filepath;
    filepath = "compress.txt";
    
    FILE *fileptr = fopen(filepath, "r");

    fgets(fileline, 5, fileptr) 
    
    Node rootnode;
    Node leftchildnode;
    Node rightchildnode;
    Node leftchildsnodeleftchild;
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