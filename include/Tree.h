#ifndef TREE_H
#define TREE_H
#include <string>
//#include "Ocorrencia.h"

#define bolete(p) cout<<"bolete: "<<p<<endl;
#include "Trie.h"



const float frequencia[] = {14.63, 1.04, 3.88, 4.99, 12.57, 1.02, 1.30, 1.28,
                        6.18, 0.4, 0.02, 2.78, 4.47, 5.05, 10.73, 2.52,
                        1.2, 6.53, 7.81, 4.34, 4.63, 1.67, 0.01, 0.21,
                        0.01, 0.47};


class Tree
{
    public:
        Tree();
        Tree(int i,int f);
        void show();
        Tree *findChar(char c);
        int depth();
        void adicionar(std::string s,int arq);
        Trie * procurar(std::string s);
        Trie * trie;
    protected:

    private:
        char node;
        Tree * left;
        Tree * right;
};


#endif // TREE_H
