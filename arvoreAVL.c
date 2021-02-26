#include "arvoreAVL.h"

no *Alocar(int chave)
{
    no *novo = (no*)malloc(sizeof(no));
    novo->esquerda = NULL;
    novo->direito = NULL;
    novo->pai = NULL;
    novo->chave = chave;
    return novo;

}

void PercurssoEmOrdem(no *inicio)
{
    if(inicio != NULL){
        PercurssoEmOrdem(inicio->esquerda);
        printf("%d", inicio->chave);
        PercurssoEmOrdem(inicio->direito);
    }

}

void PercurssoPreOrdem(no *inicio)
{
    if(inicio != NULL){
        printf("%d", inicio->chave);
        PercurssoPreOrdem(inicio->esquerda);
        PercurssoPreOrdem(inicio->direito);
    }
}

void PercurssoPosOrdem(no *inicio)
{
    if(inicio != NULL){
        PercurssoPosOrdem(inicio->esquerda);
        PercurssoPosOrdem(inicio->direito);
        printf("%d", inicio->chave);
    }

}

void Inserir(arvore *inicio, no *novo)
{
    no *anterior = NULL;

	no *proximo = inicio->raiz;

	while(proximo != NULL){

		anterior = proximo;

		if(novo->chave < proximo->chave ){

			proximo = proximo->esquerda;

		}else{

			proximo = proximo->direito;

		}

	}

	novo->pai = anterior;

	if(anterior == NULL){

		inicio->raiz = novo;

	}

	else if(novo->chave < anterior->chave){

		anterior->esquerda = novo;

	}

	else{

		anterior->direito = novo;

	}

  /*  no* desreg  = Nodesregulado(novo);
    
    if(desreg != NULL)
    {
       //Balancear(inicio, desreg);
    }*/
}

no *Busca(no *inicio, int chave)
{
    if(inicio == NULL || inicio->chave == chave){
        
        return inicio;
    }
    if(chave < inicio->chave)
    {
        
        return Busca(inicio->esquerda, chave);
    }
    else
    {
        return Busca(inicio->direito, chave);

    }
}

no *Maximo(no *inicio)
{
    if(inicio != NULL){
        while(inicio->direito != NULL){
            inicio = inicio->direito;
        }
        return inicio;
    }
}

no *Minimo(no *inicio)
{
    if(inicio != NULL){
        while(inicio->esquerda != NULL){
            inicio = inicio->esquerda;
        }
        return inicio;
    }
}

no *Sucessor(no *inicio)
{
    no *anterior;
    anterior = inicio->pai;
    if(inicio != NULL)
    {
        if(inicio->direito != NULL){
            return Minimo(inicio->direito);
        }
        else{
            while(anterior != NULL && inicio == anterior->direito){

                inicio = anterior;
				anterior = anterior->pai;
            }
            return anterior;
        }

    }
        
    
}

no *Predecessor(no *inicio)
{
    no *anterior;
    anterior = inicio->pai;
    if(inicio != NULL)
    {
        if(inicio->esquerda != NULL)
        {
            Maximo(inicio->esquerda);
        }else{
            while(anterior != NULL && inicio == anterior->esquerda){

                inicio = anterior;
                anterior = anterior->pai;
            }
            return anterior;
        }
    }

}

void Transplant(arvore *inicio, no *x, no *y)
{
    if(x == NULL || x == inicio->raiz)
    {
        inicio->raiz = y;
    }
    else if(x == x->pai->esquerda)
    {
        x->pai->esquerda = y;
    }
    else
    {
        x->pai->direito = y;
    }
    if( y != NULL)
    {
        y->pai = x->pai;
    }
}
void Deletar(arvore *inicio, no *chave)
{
    no *aux = NULL;
    if (chave->esquerda == NULL)
    {
        Transplant(inicio, chave, chave->direito);
    }
    else if(chave->direito == NULL)
    {
        Transplant(inicio, chave, chave->esquerda);
    }
    else
    {
        aux = Maximo(chave->direito);
        if(aux->pai != chave)
        {
            Transplant(inicio, aux, aux->direito);
            aux->direito = chave->direito;
            aux->direito->pai = chave;
        };
        Transplant(inicio, chave, aux);
        aux->esquerda = chave->esquerda;
        aux->esquerda->pai = aux;
    }
}


int MaiorElemento(int x, int y)
{
    if(x > y)
    {
        return x;
    }
    else
    {
        return y;
    }
}


int Altura(no *inicio)
{
    if(inicio == NULL)
    {
        return 0;
    }
    else
    {
        return MaiorElemento(Altura(inicio->esquerda), Altura(inicio->direito)+1);
    }
}


no *Nodesregulado(no *inicio)
{
    no *pai = inicio->pai;
    if(pai == NULL)
    {
        return NULL;
    }
    while(pai != NULL)
    {
        if ((Altura(pai->esquerda) - Altura(pai->direito)) > 1)
        {
            return pai;
        }
        pai = pai->pai;
    }
    return NULL;

}


void RotacaoSimplesDireita(arvore *AVL, no *x)
{
    no *y = x->esquerda;

    if(y = NULL)
    {
        x->esquerda = y->direito;
    }
    
    if(y->direito != NULL)
    {
        y->direito->pai = x;
    }

    y->pai = x->pai;
    
    if(x->pai == NULL)
    {
        AVL->raiz = y;
    }

    else if(x == x->pai->esquerda)
    {
        x->pai->esquerda = y;
    }

    else
    {
        x->pai->direito = y;
    }

    y->direito = x;
    x->pai = y;

    printf("Rotacao Completa");
}