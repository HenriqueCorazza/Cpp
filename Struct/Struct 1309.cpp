#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<conio2.h>

#define TF 20

struct tpData
	{
		int d,m,a;
	};
	
struct tpProduto
{
	int Cod,Estoque;
	tpData Valid;
	char Descr[TF];
	float Preco;
};

void OrdenarDescr(tpProduto Tab[TF], int TL){
	int i, j;
	tpProduto RegAux;
	char aux[20];
	clrscr();
	if(TL==0){
		printf("\nNao ha dados para ordenar!\n");
	}
	else{
		for(i=0; i<TL-1; i++)
			for(j=i+1;j<TL;j++)
				if(stricmp(Tab[i].Descr,Tab[j].Descr)>0){
					RegAux = Tab[i];
					Tab[i] = Tab[j];
					Tab[j] = RegAux;
				}
	printf("\nProdutos Ordenados!\n");
	}
	getch();
}

int BuscaCod(tpProduto Tab[TF], int TLP, int CodProd){
	int pos=0;
	
	while(pos<TLP && CodProd != Tab[pos].Cod)
		pos++;
	if(pos<TLP)
		return pos;
	else
		return -1;
}

void ExcluirProd(tpProduto Tab[TF], int &TL){
	int i, Cod, pos;
	if(TL==0){
		printf("Nao ha produtos cadastrados!\n");
	}
	else{
		do{
		clrscr();
		printf("# Digite um codigo para excluir #\n");
		scanf("%d", &Cod);
		pos = BuscaCod(Tab, TL, Cod);
		clrscr();
		if(pos == -1 && Cod != 0){
			printf("Produto inexistente\n");
		}
		if(Cod!=0){
			for(i=pos; i<TL; i++){
				Tab[i] = Tab[i+1];
				TL--;
				printf("Produto excluido!\n");
			}
		}
		getch();
		}while(Cod != 0 && Cod != 27);
	}
}

void Relatorio(tpProduto Tab[TF],int TL)
{
	int i;
	clrscr();
	if(TL==0){
		printf("* * Nao ha produtos cadastrados! * *\n");
	}
	for(i=0;i<TL;i++)
	{
		printf("\nCodigo do Produto: %d",Tab[i].Cod);
		printf("\nQuantidade em Estoque: %d",Tab[i].Estoque);
		printf("\nDescricao do Produto: %s",Tab[i].Descr);
		printf("\nPreco: %.2f",Tab[i].Preco);
		printf("\nValidade: %d/%d/%d\n\n",Tab[i].Valid.d,Tab[i].Valid.m,Tab[i].Valid.a);
		printf("-----------------------------------\n");
	}
	getch();
}
void VendaProd(tpProduto Tab[TF], int TL){
	int q, cod, pos;
	clrscr();
	if(TL==0){
		printf("* * Nao ha produtos cadastrados! * *\n");
	}
	else{
		do{
		clrscr();
		printf("* * Digite o Codigo do Produto que deseja vender * *\n");
		scanf("%d", &cod);
		pos = BuscaCod(Tab, TL, cod);
		clrscr();
		if(pos == -1 && cod != 0){
			printf("* * Produto inexistente * *\n");
		}
		if(cod!=0 && Tab[pos].Estoque != 0 && pos != -1){
			printf("* * * Detalhes do Produto * * *\n\n");
			printf("Produto: %s | Quantidade em Estoque: %d\n", Tab[pos].Descr, Tab[pos].Estoque);
			printf("Digite quantos itens deseja vender: ");
			scanf("%d",&q);
			if(q>Tab[pos].Estoque)
				printf("Quantidade indisponivel");
				
			if(q<=Tab[pos].Estoque && q!=0){
				Tab[pos].Estoque -= q;
				clrscr();
				printf("* * Venda Realizada! * *");
			}
			if(q==0){
				clrscr();
				printf("* * Nao ha como vender 0 unidades * *\n");
			}
		}
		if(pos!= -1 && Tab[pos].Estoque == 0){
			clrscr();
			printf("* * O Produto acabou! * *\n");
		}
		getch();
		
		}while(cod != 0 && cod != 27);
	}
}


void CadProd(tpProduto TabProd[TF],int &TLP)
{
	int AuxCod, pos;
	
	clrscr();
	printf("\n** Cadastro de Produtos **\n");
	printf("\nCodigo do Produto: ");
	scanf("%d",&AuxCod);
	while(TLP<TF && AuxCod>0)
	{
		pos = BuscaCod(TabProd,TLP,AuxCod);
		if(pos==-1){
			TabProd[TLP].Cod=AuxCod;
			printf("\nDescricao do Produto: ");
			fflush(stdin);
			gets(TabProd[TLP].Descr);
			printf("\nQuantidade em Estoque: ");
			scanf("%d",&TabProd[TLP].Estoque);
			printf("\nPreco: ");
			scanf("%f",&TabProd[TLP].Preco);
			printf("\nData de Validade[dd mm aa]: ");
			scanf("%d %d %d",&TabProd[TLP].Valid.d,&TabProd[TLP].Valid.m,&TabProd[TLP].Valid.a);
			TLP++;
		}
		else{
			printf("\nProduto Cadastrado!\n");
			printf("Produto [%d] - Descricao: [%s]\n\n", pos+1, TabProd[pos].Descr);
		}
		if(TLP<TF)
			{
				printf("\nCodigo do Produto: ");
				scanf("%d",&AuxCod);
			}
		else{
			printf("\nTabela Cheia!\n")/
			getch();
		}
	}
}

char Menu(void){
	clrscr();
	printf("\n # # #  M E N U  # # #\n");
	printf("\n[A] Cadastrar Produtos");
	printf("\n[B] Relatorio de Produtos");
	printf("\n[C] Ordenar Produtos");
	printf("\n[D] Excluir Produtos");
	printf("\n[E] Vender Produtos");
	printf("\n[F] Comprar Produtos");
	printf("\n[G] Exibir Produtos que comecam com uma determinada letra");
	printf("\n[H] Ordenar Produtos pelo preco - Maior par Menor");
	printf("\n[ESC] Sair\n");
	printf("\nOpcao Desejada: ");
	return toupper(getche());
}

int main(void)
{
	tpProduto Prods[TF];
	int TL=0;
	char resp;
	do{
	resp = Menu();
	switch(resp){
	case 'A':
		CadProd(Prods,TL);
		break;
	case 'B':
		Relatorio(Prods,TL);
		break;
	case 'C':
		OrdenarDescr(Prods,TL);
		break;
	case 'D':
		ExcluirProd(Prods,TL);
		break;
	case 'E':
		VendaProd(Prods,TL);
		break;
	}
	}while(resp!=27);
	return 0;
}
