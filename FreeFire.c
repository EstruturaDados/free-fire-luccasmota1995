//import das bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//constante que determina tamanho maixmo da mochila
#define MAX_ITENS 10

//defiinicao das structs item e mochila
typedef struct{
    char nome[30];
    char tipo[20];
    int quantidade;
}Item;

typedef struct{
    Item itens[MAX_ITENS];
    int quantidade;
}Mochila;

//interface das funcoes (definidas apos o main)
void inicializarMochila(Mochila *mochila);
void inserirItem(Mochila *mochila);
void removerItem(Mochila *mochila);
void listarItens(Mochila *mochila);
void buscarItem(Mochila *mochila);
void limpaBuffer();

//main
void main(){

    //define e inicializa a "mochila" que sera manipulada no programa
    Mochila mochila;
    inicializarMochila(&mochila);
    int entrada;
    //loop principal do menu do programa (continua enquanto entrada é diferente de 0)
    do{
        printf("\n==================================================\n");
        printf("================ MENU DA MOCHILA =================\n");
        printf("==================================================\n");
        printf("  1 - Cadastrar item\n");
        printf("  2 - Listar Itens\n");
        printf("  3 - Buscar Item\n");
        printf("  4 - Remover Item\n");
        printf("  0 - Finalizar programa\n");
        printf("==================================================\n");
        printf("digite sua opcao: ");
        scanf("%d", &entrada);
        limpaBuffer();
        //switch com as opcoes do menu e suas respectivas chamadas para funcoes
        switch(entrada){
            case 1:
                inserirItem(&mochila);
                break;
            case 2:
                listarItens(&mochila);
                break;
            case 3:
                buscarItem(&mochila);
                break;
            case 4:
                removerItem(&mochila);
                break;
            case 0:
                printf("\nEncerrando o progrma!\n");
                break;
            default:
                printf("Opcao invlaida! Tente novamente.\n");
        }
    }while (entrada != 0);

}

//inicializa a quantidade de itens dentro da mochila com 0
void inicializarMochila(Mochila *mochila){
    mochila->quantidade = 0;
}
//funcao para inserir um item dentro da mochila
void inserirItem(Mochila *mochila){
    //checar se a mochila está cheia
    if (mochila->quantidade >= MAX_ITENS){
        printf("\nA MOCHILA ESTA CHEIA!!\n");
        return;
    }
    //definicao de um item auxiliar para encapsular a logica de acesso o PRIMEIRA CELULA LIVRE do array de itens
    Item *item = &mochila->itens[mochila->quantidade];
    //inputs do usuario e manipulacao para remover caracter de quebra de linha indesejavel do fgets
    printf("\nDigite o nome do item: ");
    fgets(item->nome, sizeof(item->nome), stdin);
    item->nome[strcspn(item->nome, "\n")] = '\0';

    printf("\nDigite o tipo do item: ");
    fgets(item->tipo, sizeof(item->tipo), stdin);
    item->tipo[strcspn(item->tipo, "\n")] = '\0';

    printf("\nDigite a quantidade: ");
    scanf("%d", &item->quantidade);
    limpaBuffer();

    //incremento do controle de quantidade de itens registrados na mochila
    mochila->quantidade++;
}
//funcao para remover um item da mochila atraves do nome do item passado pelo usuario
void removerItem(Mochila *mochila){
    //variaveis auxiliares para contador dos loop for, posicao em que o item for encontrado e string auxiliar para armazenar entrada do usuario, respectiviamente
    int i, posicao = -1;
    char aux[30];
    //entrada do usuario e remocao de quebra de linha indesejavel
    printf("Digite o nome do intem para excluir: ");
    fgets(aux, sizeof(aux), stdin);
    aux[strcspn(aux, "\n")] = '\0';
    //loop de varredura do vetor e comparacao de o nome do objeto iterado é igual a entrada do usuario
    for (int i = 0; i < mochila->quantidade; i++){
        if (strcmp(aux, mochila->itens[i].nome) == 0){
            //guardando em "posicao" o indice em que o item desejado foi encontrado
            posicao = i;
            break;
        }
    }
    //caso nao tenha sido encontrado item com o nome procurado (posicao nao foi atualizado pela busca acima, avisa ao usuario e encerra a execucao da funcao)
    if (posicao == -1){
        printf("\nO item de nome '%s' não foi encontrado na mochila!\n", aux);
        return;
    }
    //loop para mover todos os itens "a direita" da posicao do item a ser excluido do vetor, 1 casa para a esquerda, o item da posicao+1 acaba sobrepondo o item a ser excluido
    for (i = posicao; i < mochila->quantidade; i++){
        mochila->itens[i] = mochila->itens[i+1];
    }
    //decremento da quantidade de itens atuais na mochila
    mochila->quantidade--;
    printf("Item '%s' removido com sucesso!\n", aux);
}
//funcao que percorre o vetor printando os itens da mochila
void listarItens(Mochila *mochila){
    //verificacao se  a mochila esta vazia
    if (mochila->quantidade == 0){
        printf("\nA mochila esta vazia!\n");
    }
    printf("\n----- ITENS DA MOCHILA -----\n");
    //loop que percorre a mochila printando
    for (int i = 0; i < mochila->quantidade; i++){
        printf("Item %d: %s || Tipo: %s || Quantidade: %d\n", i + 1, mochila->itens[i].nome, mochila->itens[i].tipo, mochila->itens[i].quantidade);
    }
}
//busca item na mochila e printa no console
void buscarItem(Mochila *mochila){
    //auxiliar para entrada do do usuario
    char aux[30];
    //recebe o nome do item para buscar e remove quebra de linha
    printf("Digite o nome do intem para buscar: ");
    fgets(aux, sizeof(aux), stdin);
    aux[strcspn(aux, "\n")] = '\0';

    //loop de procura e comparacao para encontrar o item no vetor
    for (int i = 0; i < mochila->quantidade; i++){
        //compara as string entrada do usuario com a string do nome do item iterado
        if (strcmp(aux, mochila->itens[i].nome) == 0){
            printf("--- Item encontrado na mochila ---\n");
            printf("    Item %d: %s || Tipo: %s || Quantidade: %d\n", i+1, mochila->itens[i].nome, mochila->itens[i].tipo, mochila->itens[i].quantidade);
        }
    }
}
//limpar buffer de entrada de scanf
void limpaBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

