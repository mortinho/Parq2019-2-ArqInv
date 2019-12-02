#include "Ocorrencia.h"
#include <iostream>
using namespace std;

Ocorrencia::Ocorrencia(int nA)
{
    numArquivo = nA;
    frequencia = 1;
    proximo = NULL;
    //ctor
}

Ocorrencia* Ocorrencia::incrementar(int nA)
{
    if (nA==numArquivo){
        frequencia++;
        return this;
    }
    else {
        Ocorrencia* o = new Ocorrencia(nA);
        o->proximo = this;
        return o;
    }
}

void Ocorrencia::showFrequencia(){

}

int Ocorrencia::getFrequencia(){
    return frequencia;
}

int Ocorrencia::getNumArquivo(){
    return numArquivo;
}

Ocorrencia * Ocorrencia::getProximo(){
    return proximo;
}

void Ocorrencia::setProximo(Ocorrencia* o){
    proximo = o;
}

Ocorrencia* Ocorrencia::getLast(){
    if (proximo) return proximo->getLast();
    else return this;
}
