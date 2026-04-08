#ifndef PESSOA_H
#define PESSOA_H


// arquivo Pessoa.h


struct pessoa {
    char nome[100];
    int  idade;
    char endereco[200];
};
typedef struct pessoa Pessoa;


// cria uma nova pessoa 
Pessoa* pessoa_cria();


// libera uma pessoa da memória
void pessoa_libera(Pessoa* p);


// imprime os dados de uma pessoa na tela
void pessoa_imprime(Pessoa* p, int indice);


// atribui novos dados a uma pessoa 
void pessoa_atribui(Pessoa* p);


#endif
