#ifndef OCORRENCIA_H
#define OCORRENCIA_H

class Ocorrencia
{
    public:
        Ocorrencia(int nA);
        Ocorrencia(Ocorrencia *o);
        Ocorrencia * copiarLista();
        Ocorrencia * andOcorrencias(Ocorrencia *o);
        Ocorrencia * getOrdenada();
        Ocorrencia * incrementar(int nA);
        int getFrequencia();
        int getNumArquivo();
        Ocorrencia * getProximo();
        void setProximo(Ocorrencia* o);
        void setFrequencia(int f);
        Ocorrencia * getLast();
        void showFrequencia();
    protected:

    private:
        int numArquivo;
        int frequencia;
        Ocorrencia *proximo;

};

#endif // OCORRENCIA_H
