#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"../include/conversor_rel.h"



int main(){

   
   /*Variaveis do sistema*/
    FILE *fp;
    long tamanho_arquivo = 0;
    char *str = NULL;
    char *str_compactado = NULL;
    const char *nome_arquivo_texto = "Arquivo de texto.txt";
    const char *nome_arquivo_compactado = "Arquivo compactado.txt";
    const char *leitura = "r";
    const char *escrita = "w";
     
    /*opening file*/
   fp = open_file(nome_arquivo_texto,leitura);
    
    /*Read size file*/
    tamanho_arquivo = read_file_size(fp);
    
    /*aloca memoria (tamanho + 1 para o \0)*/
  
    if((str = (char*) malloc(tamanho_arquivo + 1)) == NULL){
        perror("ERROR: Alocacao de memoria nao realizada");
        fclose(fp);
        return 1;
    }

    /*ler arquivo*/
    read_file(str,tamanho_arquivo,fp);
 
    size_t tamanho_maximo = strlen(str);

    if((str_compactado = (char*)malloc(tamanho_maximo * 2 + 1)) == NULL){
        perror("ERROR: Falha ao alocar memoria em str_compactado");
        return 1;
    }

    /*Compacta arquivo*/
    compact_file(str,str_compactado);
   


    fp = open_file(nome_arquivo_compactado,escrita);

    fwrite(str_compactado,1,tamanho_maximo,fp);
    fclose(fp);

    printf("TEXTO DO ARQUIVO: \n%s\n", str_compactado);


  //  printf("Valor de i %d\n, Valor de y %d\n", i, y);
    // 2. CORREÇÃO ESSENCIAL: Liberar a memória!
    free(str);
    free(str_compactado);
    str = NULL;
    str_compactado = NULL;

    return 0;
}