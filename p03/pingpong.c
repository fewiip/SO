/*
 * Autores: Felipe Avelino
 */
#include "posixver.h"
#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>

#include "pingpong.h"
#include "queue.h"

// operating system check
#if defined(_WIN32) || (!defined(__unix__) && !defined(__unix) && (!defined(__APPLE__) || !defined(__MACH__)))
#warning Este codigo foi planejado para ambientes UNIX (LInux, *BSD, MacOS). A compilacao e execucao em outros ambientes e responsabilidade do usuario.
#endif

#define STACKSIZE 32768		/* tamanho de pilha das threads */
//#define _XOPEN_SOURCE 600	/* para compilar no MacOS */

//colocando aqui na esperança de todo mundo ver

task_t *main_task;//Tarefa principal
task_t *task_queue = NULL;//Fila de tarefas
task_t *taskatual;//Tarefa atual, a tarefa que está rodando agora
task_t dispatcher;


int taskstotal;

task_t *scheduler () {
    //função scheduler, responsável por determinar qual a próxima tarefa a executar a cada troca de contexto.


} 

void dispatcher_body () // dispatcher é uma tarefa
{
   while ( userTasks > 0 )
   {
      next = scheduler() ;  // scheduler é uma função
      if (next)
      {
         // ações antes de lançar a tarefa "next", se houverem
         task_switch (next) ; // transfere controle para a tarefa "next"
         // ações após retornar da tarefa "next", se houverem
} }
   task_exit(0) ; // encerra a tarefa dispatcher
}


void pingpong_init() {
    //Maziero mandou fazer
    #ifdef DEBUG
    printf ("pingpong_init: iniciando pingpong....\n") ;
    #endif

    //Maziero mandou fazer
    /* desativa o buffer da saida padrao (stdout), usado pela função printf */
    setvbuf (stdout, 0, _IONBF, 0) ;

    //o total de tasks criadas, no caso a primeira task vai comecar em zero
    taskstotal = 0;
    //task_t: estrutura de dados pra tarefas 
    main_task = (task_t*)malloc(sizeof(task_t));
    //vamos colocar todas as informacoes da task main agora
    //id, status, next, prev e contexto
    main_task->taskid = taskstotal;
    main_task->next = NULL;
    main_task->prev = NULL;
    main_task->status = 1;

    taskstotal++;
    
    taskatual = main_task;
    task_queue = main_task;
    
    #ifdef DEBUG
    //depuração
    printf("Programa Iniciado!\n");
    #endif
    
    getcontext(&main_task->context);
}

int task_create (task_t *task, void (*start_routine)(void *),  void *arg) {
/*
 * Cria uma nova tarefa
 * task: estrutura que referencia a tarefa criada
 * start_routine: função que será executada pela tarefa
 * arg: parâmetro a passar para a tarefa que está sendo criada
 * retorno: o ID da task ou valor negativo, se houver erro
 */

    if (task == NULL) {//testa se o ponteiro é valido
        #ifdef DEBUG
            printf("task_create: ponteiro task invalido!!!\n");
        #endif
        return -1;//para a execucao aqui
    }
    if (start_routine ==  NULL){
        #ifdef DEBUG
            printf("task_create: ponteiro start_routine invalido!!!\n");
        #endif
        return -1;
    }
    //Maziero mandou fazer
    #ifdef DEBUG
    printf ("task_create: criando a tarefa!\n") ;
    #endif

    task_t *aux = main_task;
    while (aux->next != NULL) {
        aux = aux->next;
    }

    //tasks vai servir como um elemento da lista/fila
    //vamos colocar as informacoes agora
    //id, status, next, prev e contexto
    task->taskid = taskstotal;
    //task->taskid = aux->taskid + 1;
    task->status = 0;//nao esta rodando ainda
    aux->next = task;
    task->prev = aux;
    task->next = NULL;

    //cada tarefa tem uma pilha 
    char* stack;
    stack = malloc (STACKSIZE);
    getcontext (&(task->context));
    

    if (stack) {
        #ifdef DEBUG   
            printf("task_create: pilha do contexto alocada!");
        #endif
        
        task->context.uc_stack.ss_sp = stack;
        task->context.uc_stack.ss_size = STACKSIZE;
        task->context.uc_stack.ss_flags = 0;
        task->context.uc_link = 0;
    }else{
        #ifdef DEBUG  
        printf("task_create: erro ao alocar a pilha do contexto");
        #endif
        perror ("Erro na criação da pilha: ");
        exit (1);
    }

    
    //so falta o contexto
    makecontext(&task->context, (void*)(*start_routine), 1, (char*) arg);
    taskstotal++;//NAO ESQUECER!!!
    
    //Maziero mandou fazer
    #ifdef DEBUG
    printf ("task_create: criou tarefa %d\n", task->taskid) ;
    #endif

    return task->taskid;
} 

int task_switch (task_t *task) {
    /*
    task: tarefa que irá assumir o processador
    retorno: valor negativo se houver erro, ou zero*/

    if (task == NULL)
        return -1; 

    taskatual->status = 0;
    task->status = 1;
    //variavel necessaria pra eu poder trocar o contexto
    task_t *aux;
    aux = taskatual;
    taskatual = task;//agora é a que tá rodando
    //preciso trocar as duas pra o swapcontext dar certo

    #ifdef DEBUG
        printf ("task_switch: trocando de tarefa %d -> %d\n", aux->taskid, taskatual->taskid);
    #endif
    return swapcontext(&(aux->context), &(taskatual->context));
    
}

void task_exit (int exit_code) {
    /*exit_code : código de término devolvido pela tarefa corrente (ignorar este parâmetro por enquanto, pois ele
somente será usado mais tarde)*/
    #ifdef DEBUG
        printf("task_exit: encerrando a tarefa e retornando a main\n");
    #endif

    task_switch(main_task);
}

int task_id () {
    /*retorno: Identificador numérico (ID) da tarefa corrente, que deverá ser 0 para main, ou um valor positivo para
as demais tarefas. Esse identificador é único: não devem existir duas tarefas com o mesmo ID.*/
    return taskatual->taskid;
}

