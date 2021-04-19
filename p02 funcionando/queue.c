/* Alunos: Felipe Avelino & Julio Cesar
 */

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


//------------------------------------------------------------------------------
// Insere um elemento no final da fila.
// Condicoes a verificar, gerando msgs de erro:
// - a fila deve existir
// - o elemento deve existir
// - o elemento nao deve estar em outra fila

void queue_append (queue_t **queue, queue_t *elem) {
    //queue = fila
    //a gente usa a flexinha pra ponteiros
    //ptr->membro = (*ptr).membro
    //muito mais intuitivo
    //(*(*(*a).b).c).d // não intuitivo
    //a->b->c->d // intuitivo
    
    // Insere um elemento no final da fila.
    
    // - o elemento nao deve estar em outra fila
    
    //printf("funcao invocada!");
    

    //**queue eh um ponteiro de ponteiro que aponta pro primeiro 
    //elemento da lista, pra percorre-la, nós criamos um elemento 
    //auxiliar pra copiar o valor do primeiro 
    //e nao perdermos o valor original

    //aproveitando que a fila eh circular e duplamente encadeada

    
    
    if (queue != NULL) {//a fila deve existir
        //queue_t = NULL quer dizer que o ponteiro está vazio
        
        if (elem != NULL) {// - o elemento deve existir
            
            if((elem->next == NULL) && (elem->prev == NULL)) {//o elemento nao deve estar em outra fila
                //tudo certo! Pronto pra inserir!
                //printf("tudo ceerto! pronto pra inserir!\n");
                if (*queue == NULL) {//se a fila for vazia
                    elem->next = elem;
                    elem->prev = elem;
                    (*queue) = elem;
                    //printf("primeiro elemento na fila\n");
                } else {//se a fila nao for vazia
                    //printf("inseriondo outros elementos na fila\n");
                    queue_t *first = *queue;
                    queue_t *last = first->prev;
                    //coloco o novo elemento no final
                    last->next = elem;
                    //o antigo ultimo agora vai ser o penultimo, o proximo dele vai ser elem
                    elem->prev = last;
                    //o proximo depois do ultimo vai ser
                    elem->next = first;
                    first->prev = elem;

                }

                
            }else{
                //se elem->next != NULL eh porque ja tem dados salvos de outra fila
                printf("Elemento ja pertence a outra fila\n");
            }
        }else{
            printf("Elemento nao existe!\n");
        }
    }else{
        printf("fila inexistente\n");
    }
    
    
}


//------------------------------------------------------------------------------
// Remove o elemento indicado da fila, sem o destruir.
// Condicoes a verificar, gerando msgs de erro:
// - a fila deve existir
// - a fila nao deve estar vazia
// - o elemento deve existir
// - o elemento deve pertencer a fila indicada
// Retorno: apontador para o elemento removido, ou NULL se erro

queue_t *queue_remove (queue_t **queue, queue_t *elem) {
//queue = minha fila

queue_t *first = *queue;
queue_t *last = first->prev;

queue_t *aux = *queue;


    if (queue != NULL && (*queue) != NULL && elem != NULL) {//a fila deve existir
        //fila nao esta vazia
        //o elemento deve existir
        //vamos procurar o elemento na fila
        //se nao encontrar nao pertence a ela
        queue_t *anterior = elem->prev;
        queue_t *proximo = elem->next;
        
        //printf("removendo elementos!\n");

        if (elem == *queue) {//se o elemento esta no inicio, remove do inicio
            if (elem->next == elem) {//somente um elemento
                //printf("removendo o unico!\n");
                elem->next = NULL;
                elem->prev = NULL;
                *queue = NULL;
                
                return elem;
            }else{
                //last->next = proximo;
                //proximo->prev = last;
                aux->prev->next = aux->next;
                aux->next->prev = aux->prev;


                *queue = proximo;//mudamos o inicio
                //printf("removendo do inicio\n");

                //free(elem);
                elem->next = NULL;
                elem->prev = NULL;
                return elem;
            }


        }else{//senao vamos ter que percorrer os outros elementos
            aux = aux->next;
            
            //printf("procurando elemento!!!\n");
            while (aux != (*queue) && aux != elem) {
                anterior = aux;
                aux = aux->next;
                proximo = aux->next;
            }

            if (aux == (*queue)){//se percorreu e nao achou
                printf("elemento nao encontrado!!!\n");
            }else{//se achou
                //anterior->next = proximo;
                //proximo->prev = anterior;
                aux->prev->next = aux->next;
                aux->next->prev = aux->prev;

                //free(elem);
                elem->next = NULL;
                elem->prev = NULL;
                return elem;

            }
        }
            
    }
    return NULL;
}

//------------------------------------------------------------------------------
// Conta o numero de elementos na fila
// Retorno: numero de elementos na fila

int queue_size (queue_t *queue) {
    if (queue == NULL) {//fila nao existe
        return 0;
    }

    int tamanho = 0;
    queue_t *aux = queue;
    queue_t *last = aux->prev;
    //printf("executando caso seja diferente de zero\n");

    do {
        tamanho++;
        aux = aux->next;

    }  while (aux != queue);
    return tamanho;
}

//------------------------------------------------------------------------------
// Percorre a fila e imprime na tela seu conteúdo. A impressão de cada
// elemento é feita por uma função externa, definida pelo programa que
// usa a biblioteca. Essa função deve ter o seguinte protótipo:
//
// void print_elem (void *ptr) ; // ptr aponta para o elemento a imprimir

void queue_print (char *name, queue_t *queue, void print_elem (void*) ) {
    if (queue != NULL) {//se a fila existe
        queue_t *aux = queue;
        queue_t *last = aux->prev;
        int tamanho = queue_size(queue);
        int i = 0;
        

        printf("%s", name);
        
        
        printf("fila existe!!!\n");
            while (i != tamanho) {
                print_elem(aux);
                aux = aux->next;
                i++;
            }
        
    }else{
        printf("A fila nao existe!!!\n");
    }
    
}