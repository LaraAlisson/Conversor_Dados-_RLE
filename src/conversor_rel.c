#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"../include/conversor_rel.h"



int main(){

   
   /*Variaveis do sistema*/
    FILE *fp;
    long tamanho_arquivo = 0;
    unsigned char *str = NULL;
    unsigned char *str_compactado = NULL;
    const char *nome_arquivo_texto = "Arquivo de texto.txt";
    const char *nome_arquivo_compactado = "Arquivo compactado.rle";
    const char *leitura = "rb";
    const char *escrita = "wb";
     
    /*opening file*/
    fp = open_file(nome_arquivo_texto,leitura);
    if(fp == NULL){
        perror("ERRO: Falha ao abrir o arquivo");
        return 1;
    }
    
    /*Read size file*/
    tamanho_arquivo = read_file_size(fp);

    /*CORREÇÃO DE SEGURANÇA: Se o arquivo estiver vazio*/
    if(tamanho_arquivo <= 0){
        perror("ERRO: Erro ao ler o arquivo.");
        fclose(fp);
        return 1;
    }

    /*aloca memoria (tamanho )*/
    if((str = (unsigned char*) malloc(tamanho_arquivo)) == NULL){
        perror("ERROR: Alocacao de memoria nao realizada");
        fclose(fp);
        return 1;
    }

    /*ler arquivo*/
   if(!read_file(str, tamanho_arquivo, fp)){
        fclose(fp);
        free(str);
        return 1;
    }

    /*Fecha o arquivo a pós a leitura */
    fclose(fp);

    /*verefica leitura do arquivo*/
    if(str == NULL){
        perror("ERRO: Erro ao ler o arquivo.");
        fclose(fp);
    }
 
    
    /*Aloca memoria para o arquivo a ser compactado*/
    if((str_compactado = (unsigned char*)malloc(tamanho_arquivo * 2)) == NULL){
        perror("ERROR: Falha ao alocar memoria em str_compactado");
        return 1;
    }

    /*Compacta arquivo e retorna o tamanho*/
   long len = compact_file(str, tamanho_arquivo, str_compactado, tamanho_arquivo * 2);


   printf("Tamanho do arquivo compactado: %ld\n", len);

    /*Abre arquivo compactado caso não exista cria um*/
    fp = open_file(nome_arquivo_compactado,escrita);
    
    /*Escreve no arquivo*/
    fwrite(str_compactado,1,len,fp);

    /*fecha o arquivo*/
    fclose(fp);

    //printf("TEXTO DO ARQUIVO: \n%s\n", str_compactado);


 
    // 2. CORREÇÃO ESSENCIAL: Liberar a memória!
    free(str);
    free(str_compactado);
    str = NULL;
    str_compactado = NULL;

    return 0;
}