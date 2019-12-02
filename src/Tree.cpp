#include <iostream>
#include "Tree.h"

using namespace std;

Tree::Tree()
{
    node = 0;
    left = right = NULL;
    trie = NULL;

    //ctor
}
Tree::Tree(int i,int f){
    int n1 = i,n2 = f,n = i;
    float sum1=0,sum2=0;
    while (n1!=n2){
        if (sum1<sum2){
            n=n1;
            sum1+=frequencia[n1++];
        } else {
            n=n2;
            sum2+=frequencia[n2--];
        }
    }
    if (n==i) left = NULL;
    else left = new Tree(i,n-1);
    if (n==f) right = NULL;
    else right = new Tree(n+1,f);
    node = (char)(n+'a');
}

void Tree::show(){
    if (left!=NULL) {
        left->show();
        cout<<"/";
    }
    cout<<node;
    if (right!=NULL){
         cout<<"\\";
        right->show();
    }

}

Tree * Tree::findChar(char c){
    if (c==node) return this;
    else if (c<node) return left->findChar(c);
    else if (c>node) return right->findChar(c);
}

int Tree::depth(){
    int l=0, r=0;
    if(left!=NULL) l = left->depth();
    if (right!=NULL) r = right->depth();
    return max(l,r) + 1;
}

void Tree::adicionar(string s,int arq){
    Tree* subtree = findChar(s.front());
    if (!subtree->trie) subtree->trie = new Trie();
    s.erase(s.begin());
    Trie *subtrie = subtree->trie->inserir(s);
    Ocorrencia *o = subtrie->ocorrencias;
    if (o){
        o = o->incrementar(arq);
        subtrie->ocorrencias = o;
    }
    else subtrie->ocorrencias = new Ocorrencia(arq);
}

////

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
        bolete(cursor->node<<": "<<c)
        if (cursor->node == c) return cursor;
        cursor = cursor->right;
    }
    return NULL;
}

Trie* Tree::procurar(std::string s)
{
    for (string::iterator x = s.begin(); x!=s.end(); ++x)
        *x=tolower(*x);
    char c = s.front();
    Tree * t = findChar(c);
    Trie * ti;
    if(t){
        ti = t->trie;
        while (ti){
            s.erase(s.begin());
            c = s.front();
            ti = ti->findChild(c);
            if(s.size()==1) return ti;
        }
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
