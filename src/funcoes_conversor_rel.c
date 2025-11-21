#include "../include/conversor_rel.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>


/*Function opening file*/
FILE *open_file(const char *file_nome,const char *mode){
    FILE *fp;

    if((fp = fopen(file_nome,mode)) == NULL){
    perror("ERRO: Falha ao abrir o arquvio");
    exit(EXIT_FAILURE);
   }

   return fp;
}


long read_file_size(FILE *fp){
    /*Posiciona o ponteiro no final do arquivo para ler o tamnanho*/
    fseek(fp, 0 ,SEEK_END);/**/
    long  tamanho_arquivo = ftell(fp);

    /*Posiciona o ponteiro no inicio do arquivo*/
    fseek(fp,0,SEEK_SET);

     // CORREÇÃO DE SEGURANÇA: Se o arquivo estiver vazio
    if(tamanho_arquivo <= 0){
        perror("ERRO: Erro ao ler o arquivo.");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    return tamanho_arquivo;
}

void read_file(char *str, long len, FILE *fp){

    size_t  lidos = fread(str,1,len,fp);

    /*finalizar a string com o \0 no final*/
    str[lidos] = '\0';

    /*fechar o arquivo.*/
    fclose(fp);
    
}


void compact_file(char *str, char *str_comp){
    int count = 1,
            i = 0,
            j = 0;
            
    while(str[j] != '\0'){
        count = 1;

        while(str[j] == str[j+1]){
            count += 1;
            j++;
        }
        i += sprintf(&str_comp[i], "%d", count);
        str_comp[i++]= str[j];
        j++;
    }
}

void write_file(char *str, long len){
    //codigo
}
