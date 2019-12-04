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

Ocorrencia::Ocorrencia(Ocorrencia *original){
    frequencia = original->frequencia;
    numArquivo = original->numArquivo;
    proximo = NULL;
}

Ocorrencia * Ocorrencia::copiarLista(){
    Ocorrencia * saida = new Ocorrencia(this);
    Ocorrencia * cursor = this;
    Ocorrencia * cursorSaida = saida;
    while(cursor->proximo){
        cursor = cursor->proximo;
        cursorSaida->proximo = new Ocorrencia(cursor);
        cursorSaida = cursorSaida->proximo;
    }
    return saida;
}

Ocorrencia * Ocorrencia::getOrdenada(){
    Ocorrencia *temp,*saida,*saidaCursor,*c1,*c2;
    temp = copiarLista();
    Ocorrencia * maior = temp;
    Ocorrencia * anterior = NULL;
    c1 = c2 = temp;
    saida = saidaCursor = NULL;
    while (temp){
        while (c2) {
            if (c2->frequencia>=maior->frequencia) {
                maior = c2;
                anterior = c1;
            }
            c1 = c2;
            c2 = c2->proximo;
        }
        if(saida == NULL) saida = new Ocorrencia (maior);
        else {
            saidaCursor = saida->getLast();
            saidaCursor->proximo = new Ocorrencia(maior);
        }
        anterior->proximo = maior->proximo;
        if (temp==maior) temp = maior->proximo;
        free(maior);
        c1 = c2 = temp;
    }
    return saida;
}

Ocorrencia* Ocorrencia::incrementar(int nA){
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

Ocorrencia *Ocorrencia::andOcorrencias(Ocorrencia * o2){
    Ocorrencia *c1, *c2,*saida;
    c1 = this;
    c2 = o2;
    while(c1->numArquivo!=c2->numArquivo){
        if (c1->numArquivo<c2->numArquivo) c2=c2->proximo;
        else c1=c1->proximo;
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

void Ocorrencia::setFrequencia(int f){
    frequencia = f;
}

Ocorrencia* Ocorrencia::getLast(){
    if (proximo) return proximo->getLast();
    else return this;
}
