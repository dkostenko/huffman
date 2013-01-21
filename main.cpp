#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Node
{
public:
    double a;
    char c;
    Node *left, *right;


    Node(){}

    Node(Node *Left, Node *Right)
    {
        left = Left;
        right = Right;
        a = Left->a + Right->a;
    }
};

struct MyCompare
{
    bool operator()(Node* left, Node* right) const
    {
        return left->a < right->a;
    }
};


vector<bool> code;
map<char, vector<bool> > table;

void BuildTable(Node *root)
{
    if(root->left!=NULL)
    {
        code.push_back(0);
        BuildTable(root->left);
    }

    if(root->right!=NULL)
    {
        code.push_back(1);
        BuildTable(root->right);
    }

    if(root->c) table[root->c] = code;

    code.pop_back();
}


int main()
{
    int n;
    char c;
    map<char, double>::iterator i;
    list<Node*> tree;
    string line, strChance;
    map<char, double> m;


    ifstream myfile("input.txt");

    if(myfile.is_open())
    {
        myfile >> n;    //количество символов в алфавите

        while(myfile >> line)
        {
            c = line[0];
            strChance = line.substr(1, line.length());
            istringstream ( strChance ) >> m[c];
        }

        myfile.close();
    }

    cout << endl;

    string s = "it is my striiiiiiiiing!!!!";



    /*for(int i=0; i<s.length(); ++i)
    {
        char c = s[i];
        m[c]++;
    }*/


    for(i=m.begin(); i!=m.end(); ++i)
        cout << i->first << ":" << i->second << endl;





    for(i=m.begin(); i != m.end(); ++i)
    {
        Node *p = new Node();
        p->c = i->first;
        p->a = i->second;
        tree.push_back(p);
    }


    cout << "tree.size()=" << tree.size() << endl;

    while(tree.size()!=1)
    {
        tree.sort(MyCompare());

        Node *SonL = tree.front();
        tree.pop_front();
        Node *SonR = tree.front();
        tree.pop_front();

        Node *parent = new Node(SonL, SonR);
        tree.push_back(parent);
    }

    cout << "tree.size()=" << tree.size() << endl;

    Node *root = tree.front();

    BuildTable(root);


    cout << "s.length()=" << s.length() << endl;

    for(int i=0; i<s.length(); ++i)
    {
        char c=s[i];
        vector<bool> x = table[c];

        for(n=0; n<x.size(); ++n)
            cout << x[n];
    }
    cout << endl;


    return 0;
}

