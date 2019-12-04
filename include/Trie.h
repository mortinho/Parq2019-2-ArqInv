#ifndef TRIE_H
#define TRIE_H
#include <string>
#include "Ocorrencia.h"

#define bolete(p) cout<<"bolete: "<<p<<endl;


class Trie
{
    public:
        Trie(char c=0);
        Trie* inserir(std::string s);
        Ocorrencia *ocorrencias;
        void show();
        Trie * findChild(char c);
        char getNode();
        Ocorrencia * ordernarOcorrencias();
    private:
        char node;
        Trie * first;
        Trie * right;
};

#endif // TRIE_H
