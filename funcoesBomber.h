#define z 10
#define w 10



int main(); //função principal

char system( char j[6]);  //usar comandos no terminal

int srand(int funTime);   //geral semente aleatoria das minas

int time(char *aloka);   // não faço ideia

int rand();   //aleaotiedade no X e no Y

void end();    //fim

void jogo();    //cria o campo minado

void mostraCampo(int a[z][w], char b[z][w]);    //mostra o campo do jogo

void geraM(int a[z][w]);    //gera as minas do jogo

int menuOpcoes();   //menu inicial

void geraRecord(int c);   //gera e grava o record do jogador

void mostraFim(int a[z][w], int c);   //mostra a tela de fim de jogo e a pontuação do jogador

void imprimeRecord();   //mostra na tela os records gravados
