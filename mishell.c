/*

Nome: Michel Gomes de Souza                 1858351
Data: 16/04/2019

*Create Own Shell in C

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_LINE 80 /* O comando de tamanho máximo */

int main( ){
  char *args[MAX_LINE/2 + 1]; /* argumentos de linha de comando */
  int linha = 3;
  int total_linha = 0;
  char history[linha][100];

  total_linha = 0;

 
  
  int should_run = 1; /* flag para determinar quando encerrar o programa */

  pid_t c_pid, pid;
  int status;
  int setE = 0;


  while (should_run) {
    char v3[100];
    char* pch;
    printf("\033[1;32m");
    printf("\nmiShell> ");
    printf("\033[0m");
    gets(v3);

    if(strrchr(v3, '&') != NULL) setE = 1;
    // printf("setE %d", setE);

     printf("\033[1;31m");
    if(memcmp(v3, "history", 8) == 0){
      printf("\033[1;35m");
      if (total_linha <= 0) printf("Nenhum comando no histórico");
          int tmp = total_linha;
      if (total_linha > linha) tmp = 3;
      for(int i = 0; i < tmp; i++)  printf("\n history[%d] : %s \n",i, history[i]);
    }else{
 
    

    if(memcmp(v3, "quit", 4) == 0) exit(0);
    if(memcmp(v3, "--help", 6) == 0) printf("Comandos Proprios do miShell:\n> --help\n> history\n> quit\n\nVocê poderá usar o &.");


      if(memcmp(v3, "!!", 2) == 0){
        printf("\033[1;36m");
        strcpy(v3, history[(total_linha)%linha]);
        //printf("Entrou !! \n");
      }else{
       
        char* a;
        char copy[100];
        strcpy(copy, v3);
        a = strtok (copy,"!");
        // printf("Teste %s\n", a);
         //printf("ATOI %d \n",atoi(a));
         //printf("a< =>> %s \n\n", strstr(copy, "!"));
        if(strstr(copy, "!") != NULL && atoi(a) >= 0){
        //printf("\n Numero na frente %d \n",atoi(a));
        strcpy(v3, history[atoi(a)]);
        //printf("hitory[%d] = %s| v3 = %s \n\n",atoi(a),history[atoi(a)],v3);
      }
    }

    strcpy(history[(total_linha)%linha], v3);
    total_linha++;
    //exit(0);
    
    //printf("ULTIMO[%d] >> %s \n",(total_linha)%linha,history[(total_linha)%linha]);  


    pch = strtok (v3," ");
    args[0] = pch;
    int i = 1;


    while (pch != NULL){
      pch = strtok (NULL, " ");
      args[i] = pch;
      // printf("\n => %s", args[i]);
      i++;
    }
    
  if (setE == 1){

      if (memcmp(args[i-2], "&", 1) == 0){
        args[i-2] = NULL;
      }else{

        strtok (args[i-2], "&");

      }
    }  

    args[i] = NULL;


    fflush(stdout);



    c_pid = fork();

   if (c_pid == 0){
       //printf("Filho: executando o %s \n", args[0]);

       execvp(args[0], args);
       perror("Deu errado o execvp");
   }else if(c_pid > 0){
       /* PAI */

       if( (pid=wait(&status)) < 0 && setE == 1){
           printf("WAIT");
           perror("wait");
          _exit(1);
       }

       //printf("PAI: Finalizado");

   }else{
       perror("Fork Falhou");
        _exit(1);
   }

  }
  printf("\033[0m");
  }
  return 0;

  //exit(0);
 }
