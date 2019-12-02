#include <iostream>
#include <fstream>
#include <string>

#include "Tree.h"
#define LC ('a'-'A')

using namespace std;


int doc = 0;
string arqPrefix = "../arqinv/doc";
string arqSuffix = ".txt";
string arq = "";
string lendo="";
char c;

int main()
{
    Tree *t = new Tree(0,25);
    while (doc<20){
        doc++;

        arq = arqPrefix + to_string(doc) + arqSuffix;
        fstream file (arq,fstream::in);
        if (!file) cout << "fail: ";
//        file.get(in,50,' ');
        while(file.get(c)){
            if (c>='A' && c<='Z') c+=LC;
            if (c>='a' && c<='z') lendo.push_back(c);
            else if (//characteres que reṕresentam continuacao
            c!='-'&&
            //c!='\n'&&
            c!='\r'){
                if (lendo.size()>=3)
                    t->adicionar(lendo,doc);
                lendo = "";
            }
        }
        file.close();
    }
    Trie *a = t->procurar("");
    Ocorrencia *o = a->ordernarOcorrencias();
    while (o){
    bolete(o->getFrequencia()<<","<<o->getNumArquivo())
    o = o->getProximo();}
    return 0;
}
