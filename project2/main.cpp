// huffman compression algorithm in c++
//jude urban
//14 september 2021

#include <iostream>

using namespace std;

class Node
{
private:
    /* data */
public:
    Node * leftchild;
    Node * rightchild;
    string value;
    Node(/* args */);

    // ~Node();
};

//constuctor 1
Node::Node(/* args */)
{
}


//constructor 2
// Node::~Node()
// {
// }


int main() {
    Node rootnode;
    Node leftchildnode;
    Node rightchildnode;
    rootnode.leftchild = &leftchildnode;
    rootnode.rightchild = &rightchildnode;

    cout << "leftchild node is at" << &leftchildnode << endl;
    cout << "rightchild node is at" << &rightchildnode << endl;
    cout << "rootnode left child is at" << rootnode.leftchild << endl;
    cout << "rootnode right child is at" << rootnode.rightchild << endl;

    return 0;
}