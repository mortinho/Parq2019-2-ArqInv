#ifndef OCORRENCIA_H
#define OCORRENCIA_H

class Ocorrencia
{
    public:
        Ocorrencia(int nA);
        Ocorrencia* incrementar(int nA);
        int getFrequencia();
        int getNumArquivo();
        Ocorrencia *getProximo();
        void setProximo(Ocorrencia* o);
        Ocorrencia *getLast();
        void showFrequencia();
    protected:

    private:
        int numArquivo;
        int frequencia;
        Ocorrencia *proximo;

};

#endif // OCORRENCIA_H
