


int M = 10;		//Tamanho do campo (M x M)
int B = 5;		//Numero de bombas

void jogo(){
	char campo[M][M];
	int minas[M][M];
	int verifica[M][M];
	int i, j;
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


int menuOpcoes(){
	int opcao;
	printf(" _______________________________________\n");
    	printf("|\t\t\t\t\t|\n");
    	printf("|\tBem vindo ao Bomber!\t\t|\n");
	printf("|\t\t\t\t\t|\n");
    	printf("|\tO que deseja fazer? \t\t|\n");
    	printf("|\t1-Jogar 2-Sair 3-Records\t|\n");
    	printf("|_______________________________________|\n\n");
	do{
		printf("Informe a Opção: ");
		scanf("%d", &opcao);
		switch (opcao) {
			case 1: jogo();  return opcao; break;
			case 2: return 0; return opcao; break;
			case 3: imprimeRecord(); return opcao; break;
			default: system("clear"); printf("\nPor favor, selecione uma opção válida\n"); menuOpcoes();  break;
		}

	} while(opcao != 1 && opcao != 2 && opcao != 3);

	return opcao;
}

// Insere as minas a matrirz M por M, e incrementa as adjacencias das minas.
void geraM(int minas[M][M]){
	int x, y, i;
	srand(time(NULL));
	for(i=0; i<B; i++) {
		x=0; y=0;
		while(x == y){
			x=rand() % M;
			y=rand() % M;
		}
		//**ACHO QUE FALTA FAZER A VERIFICAÇÂO SE A POSIÇÂO DA MINA (x,y) JÁ FOI UTILIZADA**//

		minas[x][y]=8; //Posição (x,y) recebe uma mina.
			// Sequencia de IF's para incrementar as posição em volta da mina.
			if(x < (M-1)){			// Se a mina estiver fora da borda direita.
				minas[x+1][y]++;		// Incremente a posição direita à mina.
				if(y < (M-1))			// Se a mina estiver fora da borda inferior.
					minas[x+1][y+1]++;		// Incremente a diagonal direita/inferior da mina.
				if(y != 0)			// Se a mina estiver fora da borda superior.
					minas[x+1][y-1]++;		// Incremente a diagonal direita/superior da mina.
			}

			if(x != 0){			// Se a mina estiver fora da borda esquerda.
				minas[x-1][y]++;		// Incremete a posição esquerda à mina.
				if(y < (M-1))			// Se a mina estiver fora da borda inferior.
					minas[x-1][y+1]++;		// Incremente a diagonal esquerda/inferior da mina.
				if(y != 0)			// Se a mina estiver fora da borda superior.
					minas[x-1][y-1]++;		// Incremente a diagonal esqueda/superior da mina.
			}

			if(y < (M-1))			// Se a mina estiver fora da borda inferior.
				minas[x][y+1]++;		// Incrementa a posição a baixo da mina.

			if(y != 0)			// Se a mina estiver fora da borda superior.
				minas[x][y-1]++;		// Incrementa a posição a cima da mina.
	}
}

void geraRecord(int ponto){

	FILE *p;
	char nome[5];
	p=fopen("record.txt", "a+");
	if(p == NULL){
		printf("Erro na Leitura do Arquivo\n");
		end();
	}
	printf("Nick (5 Caracter): ");
	scanf("", nome);
	fprintf(p, " %d\n", nome, ponto);
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
				printf("%d ", minas[i][j]);
			}
			else if(minas[i][j] >= 8){
				printf( "* ");
			}
			else{
				printf("%d ", minas[i][j]);
			}
		}
		cont++;
		printf("\n");
	}
	while(op != 1 && op !=2 && op!=3){
		if((v = 0)){
			printf("Pontos: %d - LOSER!\n", ponto );
		}
		if((v = 1)){
			printf("Pontos: %d - WINNER!\n", ponto );
		}
		printf(" _______________________\n");
		printf("|1 - Gravar Record\t|\n"  );
		printf("|2 - Voltar ao Menu\t|\n"  );
		printf("|3 - Sair\t\t|\n"  );
		printf("|_______________________|\n");
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
			printf( "%c ", campo[i][j]);
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
							printf("%c ", campo[i][j]);
						}
						else if(campo[i][j] == '*'){
							printf( "%c ", campo[i][j]);
						}
						else if(campo[i][j] >= '#'){
							printf( "# ");
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
										printf("%c ", campo[i][j]);
									}
									else if(campo[i][j] == '*'){
										printf( "%c ", campo[i][j]);
									}
									else if(campo[i][j] >= '#'){
										printf( "# ");
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
										printf("%c ", campo[i][j]);
									}
									else if(campo[i][j] == '*'){
										printf( "%c ", campo[i][j]);
									}
									else if(campo[i][j] >= '#'){
										printf( "# ");
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

	if((p=-1)){
		mostraFim(minas, pontuacao);
	}
}


void imprimeRecord(){
	FILE *p;
	char m;
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
	printf("\tTOP: " );
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
		printf(" _______________________\n");
		printf("|\t1 - Menu\t|\n"  );
		printf("|\t2 - Sair\t|\n"  );
		printf("|_______________________|\n");
		scanf("%d", &op);
	}
	if(op==1){
		system("clear");
		main();
	}
}

/*int main(){
	system("clear");
	int opcao;
	opcao = menuOpcoes();

	switch (opcao)
	{
		case 1: jogo(); break;
		case 2: return 0; break;
		case 3: imprimeRecord(); break;
		default: system("clear"); printf("Por favor, selecione uma opção válida\n"); menuOpcoes();  break;
	}

	return 0;
}*/
