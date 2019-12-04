#include "Trie.h"
#include <iostream>
using namespace std;
Trie::Trie(char c){
    node = c;
    first = NULL;
    right = NULL;
    ocorrencias=NULL;
}

Trie* Trie::inserir(string s){
    char c = s.front();
    s.erase(s.begin());
    Trie *anterior,*cursor;
    anterior = first;
    cursor = first;
    while(cursor){
        if (c==cursor->getNode()) {
            if (!s.size()) return cursor;
            else return cursor->inserir(s);
        } else if (c<cursor->getNode()) { //entre anterior e o cursor, ou no inicio de os dois -> pro primeiro
            Trie *t = new Trie(c);
            t->right = cursor;
            if (anterior!=cursor) anterior->right=t;
            else first = t;
            if (!s.size()) return t;
            else return t->inserir(s);
        } else {
            anterior=cursor;
            cursor=cursor->right;
        }
    }
    Trie *t = new Trie(c);
    t->right = cursor; //null
    if (anterior!=cursor) anterior->right=t; // anterior = ultimo
    else first = t; // anterior == null
    if (!s.size()) return t;
    else return t->inserir(s);
}

Trie * Trie::findChild(char c){
    Trie* cursor = first;
    while(cursor){
        if (cursor->node == c) return cursor;
        cursor = cursor->right;
    }
    return NULL;
}

string temp="";
void Trie::show()
{
    if (node) temp.push_back(node);
    if(first)
        first->show();
    else{
        cout<<temp<<endl;
        temp="";
    }
    if(right) right->show();
}

char Trie::getNode(){
    return node;
}

Ocorrencia * Trie::ordernarOcorrencias(){
    int maior;
    Ocorrencia * ordenada,*cursor,*origem,*anterior,*temp,*tempanterior;
    origem = ocorrencias;
    ordenada = NULL;
    while (origem){
        cursor = origem;
        anterior = origem;
        maior = 1;
        while (cursor){
            if (cursor->getFrequencia()>=maior) {
                tempanterior = anterior;
                temp = cursor;
                maior = cursor->getFrequencia();
            }
            anterior=cursor;
            cursor=cursor->getProximo();
        }
        if (temp==origem) origem = origem->getProximo();
        else tempanterior->setProximo(temp->getProximo());
        temp->setProximo(NULL);


        cursor = ordenada;
        if (cursor) {
            cursor = cursor->getLast();
            cursor->setProximo(temp);
            temp = origem;
        }
        else ordenada = temp;
    }
    return ordenada;
}
