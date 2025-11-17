#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main(){

   
    //ponteiro para arquivo
    FILE *fp;

    //long para o tamanho do arquivo
   long tamanho_arquivo = 0;
    //ponteiro para o texto
   char *str = NULL;
   char *str_compactado = NULL;
    
    //abre o arquivo confere se arquivo abriu
   if((fp = fopen("Arquivo de texto.txt","r")) == NULL){
    perror("ERRO: Falha ao abrir o arquvio");
    return 1;
   }
    
    /*Posiciona o ponteiro no final do arquivo para ler o tamnanho*/
    fseek(fp, 0 ,SEEK_END);/**/
    tamanho_arquivo = ftell(fp);
   
    /*Posiciona o ponteiro no inicio do arquivo*/
    fseek(fp,0,SEEK_SET);
    
    // CORREÇÃO DE SEGURANÇA: Se o arquivo estiver vazio
    if(tamanho_arquivo <= 0){
        perror("ERRO: Erro ao ler o arquivo.");
        fclose(fp);
        return 1;
    }
 

    //aloca memoria (tamanho + 1 para o \0)
    str = (char*) malloc(tamanho_arquivo + 1);

    //confere se a memoria foi alocada
   if(str == NULL){
    perror("ERROR: Alocacao de memoria nao realizada");
    fclose(fp);
    return 1;
   }

    //ler arquivo
   size_t  lidos = fread(str,1,tamanho_arquivo,fp);

    //finalizar a string com o \0 no final
   str[lidos] = '\0';

    //fechar o arquivo.
   fclose(fp);
    
    //imprimir o tamanho do arquivo e o texto
    //printf("TAMANHO DO ARQUIVO: %ld bytes\n", tamanho_arquivo);
    //printf("TEXTO DO ARQUIVO: \n%s\n", str);

    /*Função para obter o tamanho do arquivo compactado*/
    int i = 0,
        j = 0,
        y = 1;


    
    size_t tamanho_maximo = strlen(str);

    str_compactado = (char*)malloc(tamanho_maximo * 2 + 1);

    if(str_compactado == NULL){
        perror("ERROR: Falha ao alocar memoria em str_compactado");
    }

   // essas
     while(str[j] != '\0'){

        if(str[j] == str[j+1]){
            printf("\n caracter repedido \n");
            y += 1;
        }else{
            if(y > 1){
                printf("\n caracter repedido adicionado \n");
                str_compactado[i] = y + '0';
                str_compactado[i+1]= str[j-1];
                i += 2;
                y = 1;
                j++;
            }
            str_compactado[i] = '1';
            str_compactado[i+1]= str[j];
            
           // printf("%c",str_compactado[i]);
          //  printf("%c",str_compactado[i+1]);
            i += 2;
        }
       
        j++;

     }
        

    printf("TEXTO DO ARQUIVO: \n%s\n", str_compactado);


  //  printf("Valor de i %d\n, Valor de y %d\n", i, y);
    // 2. CORREÇÃO ESSENCIAL: Liberar a memória!
    free(str);
    free(str_compactado);
    str = NULL;
    str_compactado = NULL;

    return 0;
}

