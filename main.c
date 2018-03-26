#include <stdio.h>
#include <stdlib.h>
#include <conio.h>


int qtdEst = 2;

//DEFINE O QUANTO PODE SER ESCRITO
int qtdColum = 30;

int qtdSimbolos = 3;

int nFinal = 1;

int limNomeArquivo = 100;



//------------------   FUNCAO PARA ACHAR O ESTADO   ------------------	
int compara(char a[], char b[] ){
	int c;
	
	for(c = 0; a[c] != 0; c++){
		if(a[c] != b[c])
		{
			return 0;
		}
	}
	
	if(a[c] != b[c])
	{
		return 0;
	}
		return 1;
}

int iguais (char a[], char b[qtdEst][qtdColum]){
	int retIgual = 0, ctr;
	
	for(ctr = 0; ctr < qtdEst; ctr++){
		retIgual = compara(a, b[ctr]);
		
		if(retIgual == 1){
			return ctr;
		}
	}
	return -1;
}

//------------------   INICIAR E EXIBE MATRIZES   ------------------	
void iniciaMatriz(int a[][qtdSimbolos]){
	int i, j;
	
	for(i = 0; i< qtdEst; i++){
		
		for(j = 0; j < qtdSimbolos; j++){
			a[i][j] = -1;
		}
	}	
}

void imprime(int a[][qtdSimbolos]){
	int i, j;
	
	for(i = 0; i< qtdEst; i++){
		
		for(j = 0; j < qtdSimbolos; j++){
			printf(" x = %d, y = %d =>> %d  || ",i , j, a[i][j]);
		}
		printf("\n");
	}
}

void mostraEstados(char a[][qtdColum]){
	int i, j;
	
	for(i = 0; i< qtdEst; i++){
		
		for(j = 0; a[i][j] != '\0'; j++){
			printf(" %c ", a[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void mostraSimbolos(char sim[]){
	int i;
	
	for(i = 0; i< qtdSimbolos; i++){
		printf(" %c ", sim[i]);
	}
	printf("\n");
}

void mostraFinal(int a[]){
	int i;
	
	for(i = 0; i< nFinal; i++){

		printf(" %d ", a[i]);
	}
	printf("\n");
}

//------------------   LIDA COM A INSERCAO DO USUARIO   ------------------	
void insereSimbolo(char sim[] ){
	int i;
	
	for(i=0; i<qtdSimbolos; i++){
		fflush(stdin);
		printf("Qual o simbolo %d ?\n", i);
		scanf ("%c", &sim[i]);
	}
}

void insereEstados(char est[][qtdColum] ){
	int i;
	
	for(i = 0; i < qtdEst; i++){
		fflush(stdin);
		printf("Qual o nome do estado %d ?\n", i);
		scanf("%s", &est[i]);
	}
}

void insereEstInicial (char est[][qtdColum], char estInicial[]){
	char procuTemp[qtdColum];
	int resTemp = -1;
	int i;
	
	while(resTemp == -1){
		fflush(stdin);
		printf("Qual o estado inicial ?\n");
		scanf ("%s", &procuTemp);
		resTemp = iguais(procuTemp, est);
		
		if(resTemp == -1){
			printf("Estado inexistente, digite novamente...\n\n");
		}
	}
	
	for(i = 0; est[resTemp][i] != '\0'; i++){
		estInicial[i] = est[resTemp][i];
	}
	
	
}

void insereEstFinal(char est[][qtdColum], int vetFinal[]){
	int i;
	char procuTemp[qtdColum];
	int resTemp = 0;
	
	for(i=0; i<nFinal;i++){
		fflush(stdin);
		printf("Qual o estado final %d ?\n", i);
		scanf ("%s", &procuTemp);
		resTemp = iguais(procuTemp, est);
		
		if(resTemp != -1){
			vetFinal[i] = resTemp;
		}else{
			printf("Estado inexistente, digite novamente...\n\n");
			i--;
		}
	}
}

void criaArquivo(int tipo, char nome[], char sim[], char est[][qtdColum], char estInicial[], int vetFinal[], int func_transi[][qtdSimbolos] );


//-----***************************-------------   FUNCAO PRINCIPAL   ----======================================================---------------		

int main (int argc, char *argv[]){
	
	fflush(stdin);
	
	//INICIALIZA VALORES LOCAIS
	char sim[250] = {'a', 'b', 'c'};
	char est[qtdEst][qtdColum];
	char procura[10];
	char estInicial[qtdColum];
	
	int vetFinal[nFinal];
	int ctr, ctr2;

//------------------   INICIAR AS ENTRADAS DO USUÁRIO   -********----------------	

	//VARIAVEIS DE ENTRADA
	char nome[limNomeArquivo];
	int tipo, i = 1;


	//VALORES PARA TESTE
//	for(i = 0; i < qtdEst; i++){
//		fflush(stdin);
//		printf("Qual o nome do estado %d ?\n", i);
//		gets(est[i]);
//	}

	printf("Qual o nome do programa a ser gerado?\n");
	gets (nome);
	
	
	//ESCOLHE TIPO DE PROGRAMA 
	printf("Gerar em funcao(1) ou goTo(2)?\n");
	scanf ("%d", &tipo);


	//INSERE E EXIBE OS SIMBOLOS ADICIONADOS
	printf("Quantos simbolos tem o alfabeto?\n");
	scanf ("%d", &qtdSimbolos);
	insereSimbolo(sim);
	//mostraSimbolos(sim);
	
	
	//INSERE E EXIBE OS ESTADOS ADICIONADOS
	printf("Quantos estados?\n");
	scanf ("%d", &qtdEst);
	insereEstados(est);
	//mostraEstados(est);

	//RECEBE O VALOR DO ESTADO INICIAL
	insereEstInicial(est, estInicial);

	//printf("INICIAL %s\n", estInicial);
	printf("Quantos estados finais?\n");
	scanf ("%d", &nFinal);
	insereEstFinal(est, vetFinal);

	mostraEstados(est);

	//MATRIZ COM A FUNCAO DE TRANSICAO
	int func_transi[qtdEst][qtdSimbolos];

	//INICIALIZA MATRIZ DE TRANSICAO
	iniciaMatriz(func_transi);
	
printf("---------------------------------\n");
imprime(func_transi);
printf("---------------------------------\n");
mostraEstados(est);
printf("---------------------------------\n");

	//PROCESSA A MATRIZ DE TRANSICAO
	for( ctr = 0; ctr < qtdEst; ctr++){
		
		for(ctr2 = 0; ctr2 < qtdSimbolos; ctr2++){
			fflush(stdin);
			printf("Para o estado \"%s\" e o simbolo \"%c\" - qual o proximo estado ? \n", est[ctr], sim[ctr2]);
			gets(procura);
			
			//BUSCA O ESTADO INSERIDO 
			func_transi[ctr][ctr2] = iguais(procura, est);
			
			/*printf("CTR: %d    CTR2: %d\n\n",ctr,ctr2);
			printf("Retorno iguais:  %d\n", iguais(procura, est));
			printf("\n");*/
		}
	}

criaArquivo(tipo, nome, sim, est, estInicial, vetFinal, func_transi);

printf("---------------------------------\n");
imprime(func_transi);
printf("---------------------------------\n");

	getch();
	return 0;
}


//-----***************************-------------   MANIPULA ARQUIVO   ----======================================================---------------

void concatena (int tamanho, char a[], char b[]){

	int i;
	for(i = 0; b[i] != '\0' ; i++, tamanho++)
	{
		a[tamanho] = b[i];
	}
}

int varTamanho (char nome[]){
	int tamanho = 0;
	
	while(nome[tamanho]) tamanho++;
	
	return tamanho;
}

void espacamento(int q, char esp[], int tipo){
	int i;
	
//	if(tipo == 0){
//		q--;
//	}else{
//		q++;
//	}
//	
	int tamTab = q * 4;
	
	for(i = 0; i < tamTab; i++ ){
		esp[i] = ' ';
	}
	esp[i] = '\0';
}


//-----***************************-------------   CRIA ARQUIVO   ----======================================================---------------

void criaArquivo(int tipo, char nome[], char sim[], char est[][qtdColum], char estInicial[], int vetFinal[], int func_transi[][qtdSimbolos] ){
	
	FILE * fp;
	
	//----------------------CONFIGURA O PATH E EXTENCAO DO ARQUIVO
	char pathNome[100] = "resultado\\";
	char extencao[5] = ".c";
	int tamNome = 0;
	int tamPath = 0;
	int i, j, a;
	int eFinal = 0;
	char esp[256];
	int qtdTab = 0;
	
	//PRECISA ADAPTAR PARA USAR AS FUNCOES GENERICAS
	while(pathNome[tamPath]) tamPath++;
	
	for(i = 0; nome[i] != '\0' ; i++, tamPath++)
	{
		pathNome[tamPath] = nome[i];
	}

	for(i = 0; extencao[i] != '\0' ; i++, tamPath++)
	{
		pathNome[tamPath] = extencao[i];
	}
	
	printf("String final: %s\n", pathNome);


	//--------------------------INICIA ESCREVER O ARQUIVO	
	if((fp = fopen(pathNome, "wt")) == NULL ){
		printf("Erro ao o abrir arquivo");
		getch();
		exit(0);
	}
	
	fprintf(fp, "#include <stdio.h>\n");
	fprintf(fp, "#include <conio.h>\n");
	fprintf(fp, "#include <stdlib.h>\n");	
	fprintf(fp, "\n");
	
	if(tipo == 1)
	{
		int i = 0;
		for(i = 0; i < qtdEst; i++)
		{
			fprintf(fp, "void %s ();\n", est[i]);
		}
		
		fprintf(fp, "void aceita ();\n");
		fprintf(fp, "void rejeita ();\n");
		
		fprintf(fp, "char f[200];\n");
		fprintf(fp, "int p;\n");
		
		fprintf(fp, "\n");
		
		//ESCREVE AS FUNCOES
		for(i = 0; i < qtdEst; i++)
		{
			fprintf(fp, "void %s ()\n", est[i]);
			fprintf(fp, "{\n", est[i]);
							
				//============= TAB TAB TAB + + +
				qtdTab++;
				espacamento(qtdTab, esp, 1);
							
			for(a = 0; a < nFinal; a++){
				if(vetFinal[a] == i){
					eFinal = 1;
				}
			}
			
			for(a = 0; a < qtdSimbolos; a++)
			{
				if(func_transi[i][a] != -1){
					fprintf(fp, "%sif(f[p] == '%c' )\n", esp, sim[a]);	
					fprintf(fp, "%s{\n", esp);	
									
						//============= TAB TAB TAB + + +
						qtdTab++;
						espacamento(qtdTab, esp, 1);				
						fprintf(fp, "%sp++;\n", esp);												
						fprintf(fp, "%s%s();\n", esp,  est[func_transi[i][a]]);					
						//============= TAB TAB TAB - - -
						qtdTab--;
						espacamento(qtdTab, esp, 0);						
					fprintf(fp, "%s}\n", esp);
					fprintf(fp, "%selse\n", esp);
					fprintf(fp, "%s{\n", esp);
					//============= TAB TAB TAB + + +
						qtdTab++;
						espacamento(qtdTab, esp, 1);
				}
			}
			
				if(eFinal == 1){
					fprintf(fp, "%sif(f[p] == '\\0' )\n", esp);	
					fprintf(fp, "%s{\n", esp);				
						//============= TAB TAB TAB + + +
						qtdTab++;
						espacamento(qtdTab, esp, 1);						
						fprintf(fp, "%saceita();\n", esp);						
						//============= TAB TAB TAB - - -
						qtdTab--;
						espacamento(qtdTab, esp, 0);
					fprintf(fp, "%s}\n", esp);
					fprintf(fp, "%selse\n", esp);
					fprintf(fp, "%s{\n", esp);
					//============= TAB TAB TAB + + +
					qtdTab++;
					espacamento(qtdTab, esp, 1);	
				}

					fprintf(fp, "%srejeita();\n", esp);
					//============= TAB TAB TAB - - -
					qtdTab--;
					espacamento(qtdTab, esp, 0);
				//fprintf(fp, "%s}\n", esp);
				
			while(qtdTab >= 0){
                fprintf(fp, "%s}\n", esp);
                //============= TAB TAB TAB - - -
			    qtdTab--;
				espacamento(qtdTab, esp, 0);
			}
			//fprintf(fp, "}\n");
			fprintf(fp, "\n\n");
			
			eFinal = 0;
			qtdTab = 0;

		}
		
		
		fprintf(fp, "void aceita ()\n");
		fprintf(fp, "{\n");
			//============= TAB TAB TAB + + +
			qtdTab++;
			espacamento(qtdTab, esp, 1);
			fprintf(fp, "%sprintf(\"\\nAceita\\n\");\n", esp);
			fprintf(fp, "%sgetch();\n", esp);
			fprintf(fp, "%sexit(0);\n", esp);
			//============= TAB TAB TAB - - -
			qtdTab--;
			espacamento(qtdTab, esp, 0);	
		fprintf(fp, "}\n\n");
		
		
		fprintf(fp, "void rejeita ()\n");
		fprintf(fp, "{\n");
			//============= TAB TAB TAB + + +
			qtdTab++;
			espacamento(qtdTab, esp, 1);
			fprintf(fp, "%sprintf(\"\\nRejeita\\n\");\n", esp);
			fprintf(fp, "%sgetch();\n", esp);
			fprintf(fp, "%sexit(0);\n", esp);
			//============= TAB TAB TAB - - -
			qtdTab--;
			espacamento(qtdTab, esp, 0);		
		fprintf(fp, "}\n\n");
		
		
		fprintf(fp, "int main (int argc, char * argv[])\n");
		fprintf(fp, "{\n");
			//============= TAB TAB TAB + + +
			qtdTab++;
			espacamento(qtdTab, esp, 1);
			fprintf(fp, "%sp = 0;\n", esp);
			fprintf(fp, "%sprintf(\"Linha: \");\n", esp);
			fprintf(fp, "%sgets(f);\n", esp);
			
			concatena(varTamanho(estInicial), estInicial, "();\n");
			
			fprintf(fp, "%s%s", esp, estInicial);
			fprintf(fp, "%sreturn(0);\n", esp);
			
			//============= TAB TAB TAB - - -
			qtdTab--;
			espacamento(qtdTab, esp, 0);
		fprintf(fp, "}\n");
		
	}else if(tipo == 2){
		fprintf(fp, "int main (int argc, char * argv[])\n");
		fprintf(fp, "{\n");
			//============= TAB TAB TAB + + +
			qtdTab++;
			espacamento(qtdTab, esp, 1);
			fprintf(fp, "%schar f[200];\n", esp);
			fprintf(fp, "%sint p;\n", esp);
			fprintf(fp, "%sprintf(\"Linha: \");\n", esp);
			fprintf(fp, "%sgets(f);\n", esp);
			fprintf(fp, "%sp = 0;\n", esp);

			concatena(varTamanho(estInicial), estInicial, ";\n\n");
			
   			fprintf(fp, "%sgoto %s", esp, estInicial);
   			
   			//ESCREVE OS ESTADOS
			for(i = 0; i < qtdEst; i++)
			{
				fprintf(fp, "%s%s:\n", esp, est[i]);

					//============= TAB TAB TAB + + +
					qtdTab++;
					espacamento(qtdTab, esp, 1);

				for(a = 0; a < nFinal; a++){
					if(vetFinal[a] == i){
						eFinal = 1;
					}
				}

				for(a = 0; a < qtdSimbolos; a++)
				{
					if(func_transi[i][a] != -1){
						fprintf(fp, "%sif(f[p] == '%c' )\n", esp, sim[a]);
						fprintf(fp, "%s{\n", esp);

							//============= TAB TAB TAB + + +
							qtdTab++;
							espacamento(qtdTab, esp, 1);
							fprintf(fp, "%sp++;\n", esp);
							fprintf(fp, "%sgoto %s;\n", esp,  est[func_transi[i][a]]);
							//============= TAB TAB TAB - - -
							qtdTab--;
							espacamento(qtdTab, esp, 0);
						fprintf(fp, "%s}\n", esp);	
						fprintf(fp, "%selse\n", esp);
						fprintf(fp, "%s{\n", esp);
						//============= TAB TAB TAB + + +
							qtdTab++;
							espacamento(qtdTab, esp, 1);
					}
				}

					if(eFinal == 1){
					
						fprintf(fp, "%sif(f[p] == '\\0' )\n", esp);
						fprintf(fp, "%s{\n", esp);
							//============= TAB TAB TAB + + +
							qtdTab++;
							espacamento(qtdTab, esp, 1);
							fprintf(fp, "%sgoto ACEITA;\n", esp);
							//============= TAB TAB TAB - - -
							qtdTab--;
							espacamento(qtdTab, esp, 0);
						fprintf(fp, "%s} else\n", esp);
						fprintf(fp, "%s{\n", esp);
						//============= TAB TAB TAB + + +
						qtdTab++;
						espacamento(qtdTab, esp, 1);
					}

											
						fprintf(fp, "%sgoto REJEITA;\n", esp);
						//============= TAB TAB TAB - - -
						qtdTab--;
						espacamento(qtdTab, esp, 0);
					
					while(qtdTab >= 2){
		                fprintf(fp, "%s}\n", esp);
		                //============= TAB TAB TAB - - -
					    qtdTab--;
						espacamento(qtdTab, esp, 0);
						
					}
		
				fprintf(fp, "\n");

				eFinal = 0;
				qtdTab = 1;

				espacamento(qtdTab, esp, 1);
			}

   			fprintf(fp, "%sACEITA:\n", esp);
				//============= TAB TAB TAB + + +
				qtdTab++;
				espacamento(qtdTab, esp, 1);
				fprintf(fp, "%sprintf(\"\\nAceita\\n\");\n", esp);
				fprintf(fp, "%sgetch();\n", esp);
				fprintf(fp, "%sreturn(0);\n", esp);
				//============= TAB TAB TAB - - -
				qtdTab--;
				espacamento(qtdTab, esp, 0);
			fprintf(fp, "\n");


			fprintf(fp, "%sREJEITA:\n", esp);
				//============= TAB TAB TAB + + +
				qtdTab++;
				espacamento(qtdTab, esp, 1);
				fprintf(fp, "%sprintf(\"\\nRejeita\\n\");\n", esp);
				fprintf(fp, "%sgetch();\n", esp);
				fprintf(fp, "%sreturn(0);\n", esp);
				//============= TAB TAB TAB - - -
				qtdTab--;
				espacamento(qtdTab, esp, 0);


   			

			//============= TAB TAB TAB - - -
			qtdTab--;
			espacamento(qtdTab, esp, 0);
		fprintf(fp, "}\n");
	}
	else{
		printf("O valor digitado não é valido... ");
	}
	
	fclose(fp);
}
