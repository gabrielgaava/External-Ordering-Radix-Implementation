//  Trabalho (P1) de Estrutura de Dados II
//  Grupo:
//  > Gabriel Henrique da Silva Gava
//  > Gustavo Henrique Oliveira Villar
//  > Filipe Rodrigues Ferreira
//
//  Professor: Guilherme Botazzo Rozendo



#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <time.h>
using namespace std;

//Define clear e cls para funcionar tanto em windows como em (l)unix
#ifdef _unix_
#define clear "clear"
#else
#define clear "cls"
#endif

//FItas que serao utilizadas em todo o programa
FILE * fitaLeitura[3]; // <---- FItas que serão utilizadas para LEITURA
FILE * fitaEscrita[3]; // <----- FItas que serão utilizadas para ESCRITA
FILE * Saida; // <----- Arquivo de Saida final


//Variaveis auxiliares do programa
int tamanhoMemoria = 0, numeroDeRegistros = 0, numDeInteracoes = 0;

//Função de Ordenação Interna
void Quick(int vetor[], int inicio, int fim){

   int pivo, aux, i, j, meio;

   i = inicio;
   j = fim;

   meio = (int) ((i + j) / 2);
   pivo = vetor[meio];

   do{
      while (vetor[i] < pivo) i = i + 1;
      while (vetor[j] > pivo) j = j - 1;

      if(i <= j){
         aux = vetor[i];
         vetor[i] = vetor[j];
         vetor[j] = aux;
         i = i + 1;
         j = j - 1;
      }
   }while(j > i);

   if(inicio < j) Quick(vetor, inicio, j);
   if(i < fim) Quick(vetor, i, fim);

}

//Encontrar o menor nuemro
int encontrarMenor(int vet[], int tamanho){
  int pos, count = 0, menor=2000;

  for(int i = 0; i < tamanho; i++){
    if(vet[i] != -1){
      if(vet[i] < menor){
        menor = vet[i];
        pos = i;
      }
    } else {
      count++;
    }
  }
  if(count == 3){
    return -1;
  }
  else{
    return pos;
  }
}

// Fecha !TODAS! fitas
void fecharFitas() {
  for (int i = 0; i < 3; i++) {
      if (fitaLeitura[i]) {
          fclose(fitaLeitura[i]);
      }
      if (fitaEscrita[i]) {
          fclose(fitaEscrita[i]);
      }
  }
}

//Trocando as fitas de entrada e saida do programa
void trocarFitas() {

  fecharFitas();

  if (numDeInteracoes % 2 == 0) {
    fitaLeitura[0] = fopen("Fitas/Fita1.txt", "r");
    fitaLeitura[1] = fopen("Fitas/Fita2.txt", "r");
    fitaLeitura[2] = fopen("Fitas/Fita3.txt", "r");

    fitaEscrita[0] = fopen("Fitas/Fita4.txt", "w");
    fitaEscrita[1] = fopen("Fitas/Fita5.txt", "w");
    fitaEscrita[2] = fopen("Fitas/Fita6.txt", "w");
  } else {
    fitaLeitura[0] = fopen("Fitas/Fita4.txt", "r");
    fitaLeitura[1] = fopen("Fitas/Fita5.txt", "r");
    fitaLeitura[2] = fopen("Fitas/Fita6.txt", "r");

    fitaEscrita[0] = fopen("Fitas/Fita1.txt", "w");
    fitaEscrita[1] = fopen("Fitas/Fita2.txt", "w");
    fitaEscrita[2] = fopen("Fitas/Fita3.txt", "w");
  }
}

//Limpa o conteudo de TODOS os arquivos, tanto os de entrada como os de saida
void limparContudoFitas(){
  FILE * temp[8];
  temp[0] = fopen("Fitas/Fita1.txt", "w");
  temp[1] = fopen("Fitas/Fita2.txt", "w");
  temp[2] = fopen("Fitas/Fita3.txt", "w");
  temp[3] = fopen("Fitas/Fita4.txt", "w");
  temp[4] = fopen("Fitas/Fita5.txt", "w");
  temp[5] = fopen("Fitas/Fita6.txt", "w");
  temp[6] = fopen("Entrada.txt", "w");
  temp[7] = fopen("Output.txt", "w");

  for(int i = 0; i < 8; i ++){
    fclose(temp[i]);
  }
}

//Criar arquivo de entrada com numeros desordenados
void criarArquivoDesordenado(int qntd){
  FILE * Entrada;
  Entrada = fopen("./Entrada.txt", "w");

  if(Entrada != NULL){
    for(int i = 0; i < qntd; i++){
      fprintf(Entrada, "%d\n", rand() % 999);
    }
  } else {
    puts("ERRO: Nao foi possivel abrir o arquivo: 'Entrada.txt'");
  }

  fclose(Entrada);
}

//Copia o conteudo de um arquivo para outro
void copiarArquivo(){
  int reg;
  FILE * a1;

  if(numDeInteracoes % 2 == 0){
    a1 = fopen("Fitas/Fita1.txt", "r");
    cout << "\n> Saida final finalizada na 'Fita1.txt'" << endl;
  } else {
    a1 = fopen("Fitas/Fita4.txt", "r");
    cout << "\n> Saida final fanalizada na 'Fita4.txt'" << endl;
  }

  Saida = fopen("Output.txt", "w");

  while (fscanf(a1, "%d", &reg) == 1) {
    if(reg != -1)
      fprintf(Saida, "%d\n", reg);
  }

  cout << "> Conteudo salvo em 'Output.txt' " << endl;

  fclose(a1);
  fclose(Saida);
}

//Função que recebe o vetor desordenado e realiza a ordenação
//E em seguida grava na fita
int inserirBloco(int vet[], int fim, int indiceAtual){
  //Ordenando os dados da memoria
  Quick(vet, 0, tamanhoMemoria);

  //Printando os dados na fita correspondende ao indice
  for (int i = 0; i < fim; i++) {
    fprintf(fitaEscrita[indiceAtual], "%d\n", vet[i]);
  }
  fprintf(fitaEscrita[indiceAtual], "%d\n", -1);

  if(indiceAtual < 2) { indiceAtual++; } //Atualizando a proximas fitas
  else { indiceAtual = 0; } //Ou resetando, para começar de novo

  return indiceAtual;
}

//Função que tranfere de forma ordenada as chaves do arquivo de entrada para as 3
//primeiras fitas de saida
void primeiraPassagem() {
  int *memoriaInterna = (int *) malloc(sizeof(int) * tamanhoMemoria);
  int contador = 0, dado, indiceAtual = 0;

  FILE * entrada;
  entrada = fopen("./Entrada.txt", "r");

  if (entrada != nullptr) {
    //Faz a leitura da entrada e insere na memoria principal
    while (fscanf(entrada, "%d", &dado) == 1) {
      //Ja atingiu o tamanho da memoria
      if (contador == tamanhoMemoria) {
        indiceAtual = inserirBloco(memoriaInterna, tamanhoMemoria, indiceAtual);
        contador = 0;
        memoriaInterna[contador] = dado;
        contador++;
      } else {
        memoriaInterna[contador] = dado;
        contador++;
      }

    } // Fim While
    indiceAtual = inserirBloco(memoriaInterna, contador, indiceAtual);
  } else {
    cout << "ERRO: Arquivo de entrada não encontrado!" << endl;
  }
  numDeInteracoes++;
}

//Faz a leitura do fita atual e e retorna o numero da leitura
int lerNumero(int indiceLeitura) {
    int reg;

    if (fscanf(fitaLeitura[indiceLeitura], "%d", &reg) == 1 ) {
        return reg;
    } else {
        return -1;
    }
}

//intercalo o bloco atual das 3 fitas de leitura para a fita de escrita
int intercalarBlocos(int fitaAtual) {
    int aux, memoriaInterna[3];


    memoriaInterna[0] = lerNumero(0);
    memoriaInterna[1] = lerNumero(1);
    memoriaInterna[2] = lerNumero(2);

    aux = encontrarMenor(memoriaInterna, 3);

    if (aux == -1) {
        return 0;
    }

    while (aux != -1) {
        // Encontra o menor número da memória e coloca ele no arquivo.
        aux = encontrarMenor(memoriaInterna, 3);
        if (aux != -1) {
            //printf("Escolhido: %d\n", memoriaInterna[aux]);
            fprintf(fitaEscrita[fitaAtual], "%d\n", memoriaInterna[aux]);

            // Pega o próximo número da fita escolhida.
            memoriaInterna[aux] = lerNumero(aux);
        }
    }
    fprintf(fitaEscrita[fitaAtual], "%d\n", -1);

    return 1;
}

//Função principal para intercalar entre as fitas 1,2,3 para as 4,5,6
// ou o inverso, até que esteja totalmente ordenado
void intercalarFitas() {
    int sentinela;
    int fitaAtual;
    int contador = 2;

    while (contador > 1) {
        trocarFitas();
        contador = 0;
        sentinela = 1;
        fitaAtual = 0;
        while (sentinela == 1) {
            sentinela = intercalarBlocos(fitaAtual);
            fitaAtual++;
            contador += sentinela;

            if (fitaAtual == 3) {
                fitaAtual = 0;
            }
        }
        cout << "> Intercalacao de blocos \n    Pressione qualquer botao para continuar...." << "\n    Numero de interacoes: " << numDeInteracoes << endl;
        getchar();
        numDeInteracoes++;

    }

    fecharFitas();
    copiarArquivo();



}

//Função principal de exuecução do programa
int main(int argc, char const *argv[]) {

  limparContudoFitas();
  int flag = 0;

  numDeInteracoes = 1;
  trocarFitas();

  cout << "Quantidade de registros a ser gerado: ";
  cin >> numeroDeRegistros;

  do { //Checagem de memoria, para evitar problemas de ordenação
    cout << "Qual o tamanho da memoria interna: ";
    cin >> tamanhoMemoria;
    if(tamanhoMemoria <= 2) {
      flag = 0;
      cout << "\n!Erro: Para este tipo de ordenacao eh necessario que o tamanho da memoria seja superior a 2!" << endl;
      cout << "Insira um novo valor para a memoria interna...\n" << endl;
    } else {
      flag = 1;
    }
  } while(flag != 1);

  system(clear);

  cout << "> Criando arquivo de registros ... \n" << endl;
  criarArquivoDesordenado(numeroDeRegistros);
  cout << "> Arquivo de registro gerado!\n    Pressione qualquer botao para continuar...." << endl;
  getchar();
  getchar();

  primeiraPassagem();
  cout << "\n> Primeira passagem finalizada\n    Pressione qualquer botao para continuar...." << endl;
  getchar();

  intercalarFitas();
  cout << "> Processo de intercalacao finalizado!\n    Pressione qualquer botao para continuar...." << endl;
  getchar();

  return 0;
}
