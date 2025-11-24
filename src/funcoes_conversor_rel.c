#include "../include/conversor_rel.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>


/*Function opening file*/
FILE *open_file(const char *file_nome,const char *mode){
   
    FILE *fp;
    fp = fopen(file_nome,mode);
    return fp;
}


long read_file_size(FILE *fp){
    /*Posiciona o ponteiro no final do arquivo para ler o tamananho*/
    fseek(fp, 0 ,SEEK_END);/**/
    long  tamanho_arquivo = ftell(fp);

    /*Posiciona o ponteiro no inicio do arquivo*/
    fseek(fp,0,SEEK_SET);

    return tamanho_arquivo;
}


int read_file(unsigned char *buffer, long len, FILE *fp){

    size_t  lidos = fread(buffer,1,len,fp);

    if(lidos != len){
        perror("ERRO: Erro ao ler o arquivo");
        return 0;
    }

    return 1;
    
}


long compact_file(unsigned char *str, long len, unsigned char *str_comp, long max_out)
{
    size_t count = 1;
    size_t i = 0; // posição no buffer de saída
    size_t j = 0; // posição no buffer de entrada

    while (j < len) {

        // Conta repetições
        count = 1;
        while ((j + 1 < len) && (str[j] == str[j + 1])) {
            count++;
            j++;
        }

        // Escrever o número (count)
        int written = snprintf((char *)&str_comp[i], max_out - i, "%zu", count);

        if (written < 0 || written >= (int)(max_out - i)) {
            // overflow detectado
            return -1;
        }

        i += written;

        // Escrever o caractere repetido
        if (i >= max_out - 1) {
            return -1; // Sem espaço para o caractere
        }

        str_comp[i++] = str[j];

        j++;
    }

    return i; // tamanho real do compactado
}


void write_file(unsigned char *str, long len){
    //codigo
}
