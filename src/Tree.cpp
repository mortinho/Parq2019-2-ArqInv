#include <iostream>
#include "Tree.h"

using namespace std;

Tree::Tree()
{
    node = 0;
    left = right = NULL;
    trie = NULL;
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
    else if (c<node)
        if (left) return left->findChar(c);
        else return NULL;
    else if (c>node)
        if (right) return right->findChar(c);
        else return NULL;
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
