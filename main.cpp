#include <iostream>
#include <fstream>
#include <string>

#include "Tree.h"
#define LC ('a'-'A')

using namespace std;


int doc = 0;
string arqPrefix = "arqinv/doc";
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

    while (1){
        enum modoEnum {SINGLE,AND,OR};
        int modo = SINGLE;
        Trie *a, *b, *c;
        Ocorrencia *o1, *o2, *ot, *oc;
        string in,in1,in2;
        int i;
        cin>>in;
        i = in.find_first_of("&|");
        if (i!=string::npos){
            if (in[i]=='&') modo = AND;
            else modo = OR;
            in1= in.substr(0,i);
            in2= in.substr(i+1);
        }
        switch (modo){
            case SINGLE:
                a = t->procurar(in);
                if (a){
                    if (a->ocorrencias) o1 = a->ocorrencias->getOrdenada();
                    else {o1 = NULL;cout<<"Not Found"<<endl;}
                    while (o1){
                        cout<<"encontradas "<<o1->getFrequencia()<<" entradas no arquivo doc"<<o1->getNumArquivo()<<".txt"<<endl;
                        o1 = o1->getProximo();
                    }
                } else cout<<"Not Found"<<endl;
            break;
            case OR:
                cout<<in1<<" OR "<<in2<<endl;
                a = t->procurar(in1);
                b = t->procurar(in2);
                oc = NULL;
                if ((a==NULL)&&(b==NULL)) cout<<"Not Found"<<endl;
                else {
                    if (a) o1 = a->ocorrencias; else o1 = NULL;
                    if (b) o2 = b->ocorrencias; else o2 = NULL;
                    while(o1||o2){
                        if (o1 == NULL) {ot = o2; o2 = o2->getProximo();}
                        else if(o2 == NULL) {ot = o1; o1 = o1->getProximo();}
                        else if (o1->getNumArquivo()<o2->getNumArquivo()){
                            ot = o2;
                            o2 = o2->getProximo();
                        }
                        else if (o2->getNumArquivo()<o1->getNumArquivo()){
                            ot = o1;
                            o1 = o1->getProximo();
                        }
                        else if (o1->getNumArquivo()==o2->getNumArquivo()){
                            ot = new Ocorrencia(o1->getNumArquivo());
                            ot->setFrequencia(o2->getFrequencia()+o1->getFrequencia());
                            o2 = o2->getProximo();
                            o1 = o1->getProximo();
                        }
                        if (oc) oc->getLast()->setProximo(new Ocorrencia(ot));
                        else oc = new Ocorrencia(ot);
                    }
                    ot = oc;
                    oc = oc->getOrdenada();
                    free(ot);
                    ot = oc;
                    while (ot){
                        cout<<"encontradas "<<ot->getFrequencia()<<" entradas no arquivo doc"<<ot->getNumArquivo()<<".txt"<<endl;
                        ot=ot->getProximo();
                    }
                }
            break;
            case AND:
                cout<<in1<<" and "<<in2<<endl;
                a = t->procurar(in1);
                b = t->procurar(in2);
                if ((a==NULL)||(b==NULL)) cout<<"Not found"<<endl;
                else{
                    o1 = a->ocorrencias;
                    o2 = b->ocorrencias;
                    oc = NULL;

                    while(o1&&o2){
                        if (o1->getNumArquivo()<o2->getNumArquivo()) o2= o2->getProximo();
                        else if (o2->getNumArquivo()<o1->getNumArquivo()) o1 = o1->getProximo();
                        else if (o1->getNumArquivo()==o2->getNumArquivo()){
                            ot = new Ocorrencia(o1->getNumArquivo());
                            ot->setFrequencia(o2->getFrequencia()+o1->getFrequencia());
                            o2 = o2->getProximo();
                            o1 = o1->getProximo();
                            if (oc) oc->getLast()->setProximo(new Ocorrencia(ot));
                            else oc = new Ocorrencia(ot);
                        }

                    }
                    ot = oc;
                    if (oc) oc = oc->getOrdenada();
                    else cout<<"nenhuma ocorrencia mutua encontrada"<<endl;
                    free(ot);
                    ot = oc;
                    while (ot){
                        cout<<"encontradas "<<ot->getFrequencia()<<" entradas no arquivo doc"<<ot->getNumArquivo()<<".txt"<<endl;
                        ot=ot->getProximo();
                    }
                }
            break;
        }
    }
    return 0;
}
