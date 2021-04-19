// PingPongOS - PingPong Operating System
// Prof. Carlos A. Maziero, DAINF UTFPR
// Versão 1.0 -- Março de 2015
//
// Estruturas de dados internas do sistema operacional
#include "posixver.h"
#ifndef __DATATYPES__
#define __DATATYPES__
#include <ucontext.h>

// Estrutura que define uma tarefa
typedef struct task_t
{
  // preencher quando necessário
  struct task_t *next;
  struct task_t *prev;
  int taskid;//identificador da tarefa
  int status;//status da tarefa; rodando = 1; inativa = 0;
  ucontext_t context;

} task_t ;

// estrutura que define um semáforo
typedef struct
{
  // preencher quando necessário
} semaphore_t ;

// estrutura que define um mutex
typedef struct
{
  // preencher quando necessário
} mutex_t ;

// estrutura que define uma barreira
typedef struct
{
  // preencher quando necessário
} barrier_t ;

// estrutura que define uma fila de mensagens
typedef struct
{
  // preencher quando necessário
} mqueue_t ;

#endif
