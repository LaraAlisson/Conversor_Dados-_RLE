#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main(){

   FILE *fp;
    long file_size;
    char *p_str;
    
    fp = fopen("Arquivo de texto.txt", "r");
    if (fp == NULL) {
        perror("ERROR: opening file");
        return 1;
    }

    // 1. Obter tamanho
    fseek(fp, 0, SEEK_END);
    file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    // 2. Alocar memória
    p_str = (char *)malloc(file_size + 1); 
    if (p_str == NULL) {
        fclose(fp);
        perror("ERROR: memory allocation failed");
        return 1;
    }

    // 3. Ler o arquivo
    fread(p_str, sizeof(char), file_size, fp);

    // 4. Finalizar string
    p_str[file_size] = '\0';

    fclose(fp);

    printf("Tamanho lido: %ld bytes\n", file_size);
    printf("Conteudo: \n%s\n", p_str);

    // 5. Liberar memória
    free(p_str);

    return 0;
}