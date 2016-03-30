#include <stdio.h>
#define RST "\e[m"
#define VRD "\033[1;32m"	//Verde
#define VML "\033[1;31m"	//Vermelho
#define PRT "\033[1;30m"	//Preto
#define AZL "\033[1;34m"	//Azul
#define M 10			//Tamanho MxM
#define B 5			//Num minas



int menuOpcoes(){
	int opcao;
	printf(PRT" _______________________________________\n"RST);
    	printf(PRT"|\t\t\t\t\t|\n"RST);
    	printf("%s|\t%sBem vindo ao Bomber!\t\t%s|\n%s", PRT, AZL, PRT, RST);
	printf(PRT"|\t\t\t\t\t|\n"RST);
    	printf("%s|\t%sO que deseja fazer? \t\t%s|\n%s",  PRT, AZL, PRT, RST);
    	printf("%s|\t%s1-Jogar 2-Sair 3-Records\t%s|\n%s",  PRT, AZL, PRT, RST);
    	printf(PRT"|_______________________________________|\n\n"RST);
	do{
		printf("Informe a Opção: ");
		scanf("%d", &opcao);
		if(opcao != 1 && opcao != 2 && opcao != 3)
			printf("Opção Inválida\n");
		}
	while(opcao != 1 && opcao != 2 && opcao != 3);

	return opcao;

}
void geraM(int minas[M][M]){
	int i, j, x, y;
	srand(time(NULL));
	for(i=0; i<B; i++){
		x=0; y=0;
		while(x == y){
			x=rand() % M;
			y=rand() % M;
		}
		minas[x][y]=8;

			if(x < (M-1)){
				minas[x+1][y]++;
				if(y < (M-1))
					minas[x+1][y+1]++;
				if(y != 0)
					minas[x+1][y-1]++;
			}

			if(x != 0){
					minas[x-1][y]++;
				if(y < (M-1))
					minas[x-1][y+1]++;
				if(y != 0)
					minas[x-1][y-1]++;
			}

			if(y < (M-1))
				minas[x][y+1]++;

			if(y != 0)
				minas[x][y-1]++;
	}
}

void geraRecord(int ponto){
	int i;
	FILE *p;
	char nome[5];
	p=fopen("record.txt", "a+");
	if(p == NULL){
		printf("Erro na Leitura do Arquivo\n");
		end();
	}
	printf("Nick (5 Caracter): ");
	scanf("%s", nome);
	fprintf(p, "%s %d\n", nome, ponto);
	system("clear");
	main();
}


void  mostraFim(int minas[M][M], int ponto){
	int i, j, cont=0, op=0, v;
	system("clear");
	printf("  ");
	for(i=0; i<M; i++){
		printf("%d ", cont);
		cont++;
	}
	printf("\n");
	cont=0;
	for(i=0 ; i<M; i++){
		printf("%d ", cont);
		for(j=0; j<M; j++){
			if(minas[i][j] == 0){
				printf(PRT"%d "RST, minas[i][j]);
			}
			else if(minas[i][j] >= 8){
				printf(VML "* "RST);
			}
			else{
				printf("%d ", minas[i][j]);
			}
		}
		cont++;
		printf("\n");
	}
	while(op != 1 && op !=2 && op!=3){
		if(v = 0){
			printf("%sPontos: %d - %sLOSER!%s\n", AZL, ponto, VML, RST);
		}
		if(v = 1){
			printf("%sPontos: %d - %sWINNER!%s\n", AZL, ponto, VML, RST);
		}
		printf(PRT" _______________________\n"RST);
		printf("%s|%s1 - Gravar Record\t%s|\n%s", PRT, AZL, PRT, RST);
		printf("%s|%s2 - Voltar ao Menu\t%s|\n%s", PRT, AZL, PRT, RST);
		printf("%s|%s3 - Sair\t\t%s|\n%s", PRT, AZL, PRT, RST);
		printf(PRT"|_______________________|\n"RST);
		printf("- ");
		scanf("%d", &op);
		if(op != 1 && op != 2 && op != 3)
			printf("Opção Inválida\n\n");
	}
	if(op==1){
		geraRecord(ponto);
	}
	if(op==2){
		system("clear");
		main();
	}
}

void mostraCampo(int minas[M][M], char campo[M][M]){
	int i, j, p=0, x, y, cont=0, vitoria, v;
	int verifica[M][M];
	int pontuacao=0;
	printf("  ");
	for(i=0; i<M; i++){
		printf("%d ", cont);
		cont++;
	}
	printf("\n");
	cont=0;
	vitoria=0;
	for(i=0 ; i<M; i++){
		printf("%d ", cont);
		for(j=0; j<M; j++){
			printf(AZL "%c "RST, campo[i][j]);
			verifica[i][j] = 0;
		}
		cont++;
		printf("\n");
	}
	while(p != -1){
		cont=0;
		printf("Pontos: %d - ", pontuacao);
		printf("Informe a jogada: ");
		scanf("%d %d", &x, &y);
		if ((x>(M-1) || x<0) || (y>(M-1) || y<0)){
			system("clear");
			printf("\nJogada inválida!\n\n");
			printf("  ");
			for(i=0; i<M; i++){
				printf("%d ", cont);
				cont++;
			}
			printf("\n");
			cont=0;
			for(i=0 ; i<M; i++){
				printf("%d ", cont);
				for(j=0; j<M; j++){
					if(i==x && j==y){
						if(minas[i][j]>=8){
							campo[i][j]='*';
							p = -1;
						}
						else if(minas[i][j] != 0){
							campo[i][j]=minas[i][j];
							pontuacao +=2;
							verifica[i][j] = 1;
							vitoria++;
						}
						else{
							campo[i][j]='0';
							pontuacao += 1;
							verifica[i][j] = 1;
							vitoria++;
						}
					 }

						if(campo[i][j] == '0'){
							printf(PRT"%c "RST, campo[i][j]);
						}
						else if(campo[i][j] == '*'){
							printf(VML "%c "RST, campo[i][j]);
						}
						else if(campo[i][j] >= '#'){
							printf(AZL "# "RST);
						}
						else{
							printf("%d ", campo[i][j]);
						}
				}
				printf("\n");
				cont++;
			}

		}
		else{
						if (verifica[x][y] == 1) {
						if (campo[x][y] == '0'){
							pontuacao -= 1;
							vitoria--;
						}
						if (minas[x][y] != 0){
							pontuacao -= 2;
							vitoria--;
						}
						system("clear");
						printf("\nJogada já realizada!\n\n");
						printf("  ");
						for(i=0; i<M; i++){
							printf("%d ", cont);
							cont++;
						}
						printf("\n");
						cont=0;
						for(i=0 ; i<M; i++){
							printf("%d ", cont);
							for(j=0; j<M; j++){
								if(i==x && j==y){
									if(minas[i][j]>=8){
										campo[i][j]='*';
										p = -1;
									}
									else if(minas[i][j] != 0){
										campo[i][j]=minas[i][j];
										pontuacao +=2;
										verifica[i][j] = 1;
										vitoria++;
									}
									else{
										campo[i][j]='0';
										pontuacao += 1;
										verifica[i][j] = 1;
										vitoria++;
									}
								 }

									if(campo[i][j] == '0'){
										printf(PRT"%c "RST, campo[i][j]);
									}
									else if(campo[i][j] == '*'){
										printf(VML "%c "RST, campo[i][j]);
									}
									else if(campo[i][j] >= '#'){
										printf(AZL "# "RST);
									}
									else{
										printf("%d ", campo[i][j]);
									}
							}
							printf("\n");
							cont++;
						}
					}
					else if (verifica[x][y] != 1){

						system("clear");
						printf("  ");

						for(i=0; i<M; i++){
							printf("%d ", cont);
							cont++;
							if(vitoria == ((M*M) - B)){
								p = -1;
								v = 1;
							}
						}
						printf("\n");
						cont=0;
						for(i=0 ; i<M; i++){
							printf("%d ", cont);
							for(j=0; j<M; j++){
								if(i==x && j==y){
									if(minas[i][j]>=8){
										campo[i][j]='*';
										p = -1;
										v = 0;
									}
									else if(minas[i][j] != 0){
										campo[i][j]=minas[i][j];
										pontuacao +=2;
										verifica[i][j] = 1;
										vitoria++;
									}
									else{
										campo[i][j]='0';
										pontuacao += 1;
										verifica[i][j] = 1;
										vitoria++;
									}
								 }

									if(campo[i][j] == '0'){
										printf(PRT"%c "RST, campo[i][j]);
									}
									else if(campo[i][j] == '*'){
										printf(VML "%c "RST, campo[i][j]);
									}
									else if(campo[i][j] >= '#'){
										printf(AZL "# "RST);
									}
									else{
										printf("%d ", campo[i][j]);
									}
							}
							printf("\n");
							cont++;
							if(vitoria == ((M*M) - B)){
								p = -1;
								v = 1;
							}
						}
					}
}


	}

	if(p=-1){
		mostraFim(minas, pontuacao);
	}
}

void jogo(){
	char campo[M][M];
	int minas[M][M];
	int verifica[M][M];
	int i, j, x, y;
	for(i=0; i<M; i++){
		for(j=0; j<M; j++){
			campo[i][j] = '#';
			minas[i][j] = 0;
			verifica[i][j] = 0;
		}
	}
	system("clear");
	geraM(minas);
	mostraCampo(minas, campo);
}

void imprimeRecord(){
	FILE *p;
	char c, m;
	int i, j, k=0, op=0;
	int maior[2];
	struct records{
		char nome[6];
		int r;
	};
	struct records vetor[100];
	p=fopen("record.txt", "r+");
	if(p == NULL){
		printf("Erro na Leitura do Arquivo\n");
		end();
	}
	while(!feof(p)){
		for(i=0; i<5; i++)
			fscanf(p, "%c", &vetor[k].nome[i]);
		fscanf(p, "%c", &vetor[k].nome[5]);
		fscanf(p, "%d", &vetor[k].r);
		fscanf(p, "%c", &m);
		k++;
	}
	maior[0]=vetor[0].r;
	maior[1]=0;
	for(i=0; i<(k-1); i++){
		if(vetor[i].r>maior[0]){
			maior[0]=vetor[i].r;
			maior[1]=i;
		}

	}
	printf("%s\tTOP: %s", VML, RST);
	for(j=0; j<5; j++){
			printf("%c", vetor[maior[1]].nome[j]);
	}
	printf(" - %d", maior[0]);
	printf("\n");
	for(i=0; i<(k-1); i++){
		for(j=0; j<5; j++){
			printf("%c", vetor[i].nome[j]);
		}
		printf(" - %d", vetor[i].r);
		printf("\n");
	}
	fclose(p);
	while(op != 1 && op != 2){
		printf(PRT" _______________________\n"RST);
		printf("%s|\t%s1 - Menu\t%s|\n%s", PRT, AZL, PRT, RST);
		printf("%s|\t%s2 - Sair\t%s|\n%s", PRT, AZL, PRT, RST);
		printf(PRT"|_______________________|\n"RST);
		scanf("%d", &op);
	}
	if(op==1){
		system("clear");
		main();
	}
}

int main(){
	system("clear");
	int opcao;
	opcao = menuOpcoes();
	if(opcao==1)
		jogo();
	else if(opcao==2)
		return 0;
	else
		imprimeRecord();
	return 0;
}
