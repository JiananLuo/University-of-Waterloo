#include <iostream>
using namespace std;

struct Tree
{
        int rootValue;
        int numChild;
        Tree ** child;
};

Tree * readTree()
{
        Tree * newTree = new Tree;

        int tRootValue;
        int tNumChild;
        cin >> tRootValue;
        cin >> tNumChild;

        newTree->rootValue = tRootValue;
        newTree->numChild = tNumChild;

        if(tNumChild != 0)
        {
                newTree->child = new Tree * [tNumChild];

                for(int i=0; i<tNumChild; i++)
                {
                        newTree->child[i] = readTree();
                }
        }
        return newTree;
}

void printTree(Tree *t)
{
        for(int i=0; i<t->numChild; i++)
        {
                printTree(t->child[i]);
        }
        cout << t->rootValue << " " << t->numChild << endl;
}

int main()
{
        Tree * bt = readTree();
        printTree(bt);
}