/***************************************************************************
*  $MCI Módulo de implementação: Módulo árvore
*
*  Arquivo gerado:              ARVORE.C
*  Letras identificadoras:      ARV
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: avs - Arndt von Staa
*			irf - Iago Ribeiro Farroco
*
*  $HA Histórico de evolução:
*     Versão   Autor    Data     Observações
*		3.50   irf	  03/04/2019 Fazendo as funções de costura e de impressão receberem parâmetro valor esperado pelo script.
*		3.40   irf	  01/03/2019 Padronizando código.
*		3.20   irf    27/03/2019 Adicionada a função de imprimir a costura.
*		3.10   irf    25/03/2019 Adicionadas as funçôes de criar vetor e costura das folhas.
*       3.00   avs    28/02/2003 Uniformização da interface das funções e
*                                de todas as condições de retorno.
*       2.00   avs    03/08/2002 Eliminação de código duplicado, reestruturação
*       1.00   avs    15/08/2001 Início do desenvolvimento
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>
#include   <stdlib.h>
#include   "lista.h"

#define ARVORE_OWN
#include "ARVORE.H"
#undef ARVORE_OWN


/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor do nó da árvore
*
*
*  $ED Descrição do tipo
*     Descreve a organização do nó
*
***********************************************************************/

   typedef struct tgNoArvore {

         struct tgNoArvore * pNoPai ;
               /* Ponteiro para pai
               *
               *$EED Assertivas estruturais
               *   É NULL sse o nó é raiz
               *   Se não for raiz, um de pNoEsq ou pNoDir de pNoPai do nó
               *   corrente apontam para o nó corrente */

         struct tgNoArvore * pNoEsq ;
               /* Ponteiro para filho à esquerda
               *
               *$EED Assertivas estruturais
               *   se pNoEsq do nó X != NULL então pNoPai de pNoEsq aponta para o nó X */

         struct tgNoArvore * pNoDir ;
               /* Ponteiro para filho à direita
               *
               *$EED Assertivas estruturais
               *   se pNoDir do nó X != NULL então pNoPai de pNoDir aponta para o nó X */
		 
		 char Chave ;
				/* Variável que armazena a chave do nó */
		 struct tgNoArvore * next ;
				/* Ponteiro para a próxima folha da costura 
				*
                *$EED Assertivas estruturais
                *   É NULL sse o nó for a última folha da costura
					Caso não seja a última folha, aponta para a próxima folha da costura */

         LIS_tppLista Valor ;
		 /* Armazena a lista encadeada de números inteiros */

   } tpNoArvore ;

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor da cabeça de uma árvore
*
*
*  $ED Descrição do tipo
*     A cabe‡a da árvore é o ponto de acesso para uma determinada árvore.
*     Por intermédio da referência para o nó corrente e do ponteiro
*     pai pode-se navegar a árvore sem necessitar de uma pilha.
*     Pode-se, inclusive, operar com a árvore em forma de co-rotina.
*
***********************************************************************/

   typedef struct tgArvore {

         tpNoArvore * pNoRaiz ;
               /* Ponteiro para a raiz da árvore */

         tpNoArvore * pNoCorr ;
               /* Ponteiro para o nó corrente da árvore */

   } tpArvore ;

/*****  Dados encapsulados no módulo  *****/

      static tpArvore * pArvore = NULL ;

	  static tpNoArvore ** vetor = NULL ;
            /* Ponteiro para a cabe‡a da árvore */

/***** Protótipos das funções encapuladas no módulo *****/

   static tpNoArvore * CriarNo( char ValorParm, int pri, int sci, int la ) ;

   static ARV_tpCondRet CriarNoRaiz( char ValorParm, int pri, int sci, int la ) ;

   static void DestroiArvore( tpNoArvore * pNo ) ;

   void DestruirValor( void * pValor ) ;

   static int compararNome(const void * a, const void * b) ;


/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: ARV Criar árvore
*  ****/

   ARV_tpCondRet ARV_CriarArvore( void )
   {

      if ( pArvore != NULL )
      {
         ARV_DestruirArvore( ) ;
      } /* if */

      pArvore = ( tpArvore * ) malloc( sizeof( tpArvore )) ;
      if ( pArvore == NULL )
      {
         return ARV_CondRetFaltouMemoria ;
      } /* if */

      pArvore->pNoRaiz = NULL ;
      pArvore->pNoCorr = NULL ;
      return ARV_CondRetOK ;

   } /* Fim função: ARV Criar árvore */

/***************************************************************************
*
*  Função: ARV Destruir árvore
*  ****/

   void ARV_DestruirArvore( void )
   {

      if ( pArvore != NULL )
      {
         if ( pArvore->pNoRaiz != NULL )
         {
            DestroiArvore( pArvore->pNoRaiz ) ;
         } /* if */
         free( pArvore ) ;
         pArvore = NULL ;
      } /* if */

   } /* Fim função: ARV Destruir árvore */

/***************************************************************************
*
*  Função: ARV Adicionar filho à esquerda
*  ****/

   ARV_tpCondRet ARV_InserirEsquerda( char ValorParm, int pri, int sci, int la )
   {

      ARV_tpCondRet CondRet ;

      tpNoArvore * pCorr ;
      tpNoArvore * pNo ;

      /* Tratar vazio, esquerda */

         CondRet = CriarNoRaiz( ValorParm, pri, sci, la ) ;
         if ( CondRet != ARV_CondRetNaoCriouRaiz )
         {
            return CondRet ;
         } /* if */

      /* Criar nó à esquerda de folha */

         pCorr = pArvore->pNoCorr ;
         if ( pCorr == NULL )
         {
            return ARV_CondRetErroEstrutura ;
         } /* if */
               
         if ( pCorr->pNoEsq == NULL )
         {
            pNo = CriarNo( ValorParm, pri, sci, la ) ;
            if ( pNo == NULL )
            {
               return ARV_CondRetFaltouMemoria ;
            } /* if */

            pNo->pNoPai        = pCorr ;
            pCorr->pNoEsq      = pNo ;
            pArvore->pNoCorr   = pNo ;
			pNo->pNoPai->Valor = NULL ;

            return ARV_CondRetOK ;
         } /* if */

      /* Tratar não folha à esquerda */

         return ARV_CondRetNaoEhFolha ;

   } /* Fim função: ARV Adicionar filho à esquerda */

/***************************************************************************
*
*  Função: ARV Adicionar filho à direita
*  ****/

   ARV_tpCondRet ARV_InserirDireita( char ValorParm, int pri, int sci, int la )
   {

      ARV_tpCondRet CondRet ;

      tpNoArvore * pCorr ;
      tpNoArvore * pNo ;

      /* Tratar vazio, direita */

         CondRet = CriarNoRaiz( ValorParm, pri, sci, la ) ;
         if ( CondRet != ARV_CondRetNaoCriouRaiz )
         {
            return CondRet ;
         } /* if */

      /* Criar nó à direita de folha */

         pCorr = pArvore->pNoCorr ;
         if ( pCorr == NULL )
         {
            return ARV_CondRetErroEstrutura ;
         } /* if */

         if ( pCorr->pNoDir == NULL )
         {
            pNo = CriarNo( ValorParm, pri, sci, la ) ;
            if ( pNo == NULL )
            {
               return ARV_CondRetFaltouMemoria ;
            } /* if */

            pNo->pNoPai      = pCorr ;
            pCorr->pNoDir    = pNo ;
            pArvore->pNoCorr = pNo ;
			pNo->pNoPai->Valor = NULL ;

            return ARV_CondRetOK ;
         } /* if */

      /* Tratar não folha à direita */

         return ARV_CondRetNaoEhFolha ;

   } /* Fim função: ARV Adicionar filho à direita */

/***************************************************************************
*
*  Função: ARV Ir para nó pai
*  ****/

   ARV_tpCondRet ARV_IrPai( void )
   {

      if ( pArvore == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */

      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

      if ( pArvore->pNoCorr->pNoPai != NULL )
      {
         pArvore->pNoCorr = pArvore->pNoCorr->pNoPai ;
         return ARV_CondRetOK ;
      } else {
         return ARV_CondRetNohEhRaiz ;
      } /* if */

   } /* Fim função: ARV Ir para nó pai */

/***************************************************************************
*
*  Função: ARV Ir para nó à esquerda
*  ****/

   ARV_tpCondRet ARV_IrNoEsquerda( void )
   {

      if ( pArvore == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */

      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

      if ( pArvore->pNoCorr->pNoEsq == NULL )
      {
         return ARV_CondRetNaoPossuiFilho ;
      } /* if */

      pArvore->pNoCorr = pArvore->pNoCorr->pNoEsq ;
      return ARV_CondRetOK ;

   } /* Fim função: ARV Ir para nó à esquerda */

/***************************************************************************
*
*  Função: ARV Ir para nó à direita
*  ****/

   ARV_tpCondRet ARV_IrNoDireita( void )
   {

      if ( pArvore == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */

      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

      if ( pArvore->pNoCorr->pNoDir == NULL )
      {
         return ARV_CondRetNaoPossuiFilho ;
      } /* if */

      pArvore->pNoCorr = pArvore->pNoCorr->pNoDir ;
      return ARV_CondRetOK ;

   } /* Fim função: ARV Ir para nó à direita */

/***************************************************************************
*
*  Função: ARV Obter valor corrente
*  ****/

   ARV_tpCondRet ARV_ObterValorCorr( char * ValorParm )
   {
      if ( pArvore == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */

      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

      * ValorParm = pArvore->pNoCorr->Chave ;
      return ARV_CondRetOK ;

   } /* Fim função: ARV Obter valor corrente */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: ARV Criar nó da árvore
*
*  $FV Valor retornado
*     Ponteiro para o nó criado.
*     Será NULL caso a memória tenha se esgotado.
*     Os ponteiros do nó criado estarão nulos e o valor é igual ao do
*     parâmetro.
*
***********************************************************************/

   tpNoArvore * CriarNo( char ValorParm, int pri, int sci, int la )
   {
	  tpNoArvore * pNo ;
      pNo = ( tpNoArvore * ) malloc( sizeof( tpNoArvore )) ;
      if ( pNo == NULL )
      {
         return NULL ;
      } /* if */

      pNo->pNoPai = NULL ;
      pNo->pNoEsq = NULL ;
      pNo->pNoDir = NULL ;
	  pNo->Valor  = LIS_CriarLista(DestruirValor) ; /* Cria lista no campo valor */
	  pNo->next   = NULL ;
	  pNo->Chave  = ValorParm ; /* Usa a variavel valorParm que é passada no script como chave */
	  
	  LIS_InserirElementoAntes(pNo->Valor, &la) ; /* Insere o terceiro elemento na lista */
	  LIS_InserirElementoAntes(pNo->Valor, &sci) ; /* Insere o segundo elemento na lista */
	  LIS_InserirElementoAntes(pNo->Valor, &pri) ; /* Insere o primeiro elemento na lista */
      
	  return pNo ;

   } /* Fim função: ARV Criar nó da árvore */


/***********************************************************************
*
*  $FC Função: ARV Criar nó raiz da árvore
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetFaltouMemoria
*     ARV_CondRetNaoCriouRaiz
*
***********************************************************************/

   ARV_tpCondRet CriarNoRaiz( char ValorParm, int pri, int sci, int la )
   {

      ARV_tpCondRet CondRet ;
      tpNoArvore * pNo ;

      if ( pArvore == NULL )
      {
         CondRet = ARV_CriarArvore( ) ;

         if ( CondRet != ARV_CondRetOK )
         {
            return CondRet ;
         } /* if */
      } /* if */

      if ( pArvore->pNoRaiz == NULL )
      {
         pNo = CriarNo( ValorParm, pri, sci, la ) ;
         if ( pNo == NULL )
         {
            return ARV_CondRetFaltouMemoria ;
         } /* if */

         pArvore->pNoRaiz = pNo ;
         pArvore->pNoCorr = pNo ;

         return ARV_CondRetOK ;
      } /* if */

      return ARV_CondRetNaoCriouRaiz ;

   } /* Fim função: ARV Criar nó raiz da árvore */


/***********************************************************************
*
*  $FC Função: ARV Destruir a estrutura da árvore
*
*  $EAE Assertivas de entradas esperadas
*     pNoArvore != NULL
*
***********************************************************************/

   void DestroiArvore( tpNoArvore * pNo )
   {
	
      if ( pNo->pNoEsq != NULL )
      {
         DestroiArvore( pNo->pNoEsq ) ;
      } /* if */

      if ( pNo->pNoDir != NULL )
      {
         DestroiArvore( pNo->pNoDir ) ;
      } /* if */
      free( pNo ) ;

   } /* Fim função: ARV Destruir a estrutura da árvore */

   
/***********************************************************************
*  $FC Função: ARV Criar Vetor para ordenar as folhas da árvore
*  
*
*  $EAE Assertivas de entradas esperadas
*  pNo != NULL
*
*  $FV Valor retornado
*	 ARV_CondRetOK
*	 ARV_CondRetFaltouMemoria
*	 ARV_CondRetNaoCriouRaiz
***********************************************************************/


   ARV_tpCondRet CriaLista( struct tgNoArvore * pNo , int * j)
   {
	   if (pNo == NULL)
	   {
		/* Verifica se existe raiz */
		if (*j == 0)
		{
			return ARV_CondRetNaoCriouRaiz ;
		}/* if */

		/* Caso base */
		return ARV_CondRetOK ;
	   }/* if */

	   if (!pNo->pNoDir && !pNo->pNoEsq)
	   {
		   *j+=1 ;
		   vetor = (tpNoArvore **)realloc(vetor,*j*sizeof(tpNoArvore*)) ;
		   
		   /* Verifica se deu erro na alocação */

		   if (vetor[*j] == NULL)
		   {
			   return ARV_CondRetFaltouMemoria ;
		   }/* if */

		   vetor[*j-1] = pNo ;

	   }/* if */

	   CriaLista(pNo->pNoDir, j) ;
	   CriaLista(pNo->pNoEsq, j) ;   

   }/* Fim função: ARV Criar Vetor para ordenar as folhas da árvore */

/***********************************************************************
*
*  $FC Função: Comparar as chaves dos nós da arvore para usar na qsort
*
*  $EAE Assertivas de entradas esperadas
*  a != NULL
*  b != NULL
*
***********************************************************************/

   static int compararNome(const void * a, const void * b)
   {

		tpNoArvore** NoA = (tpNoArvore **)a ;
		tpNoArvore** NoB = (tpNoArvore **)b ;
		return (( *NoA )->Chave > ( *NoB )->Chave) ;

   }/* Fim função: Comparar os nós da arvore */

/***********************************************************************
*
*  $FC Função: Destroi valor
*
*  $EAE Assertivas de entradas esperadas
*  pValor != NULL

***********************************************************************/

	void DestruirValor( void * pValor )
   {

      free( pValor ) ;

	}/* Fim função: Destroi valor */

/***********************************************************************
*  $FC Função: ARV Costura folhas
*  
*  $FV Valor retornado
*   ARV_CondRetOK
***********************************************************************/

   ARV_tpCondRet ARV_CosturarFolhas( void )
   { 
		ARV_tpCondRet CondRet ;
		int i, j = 0 ;
		
		CondRet = CriaLista(pArvore->pNoRaiz, &j) ;
		
		qsort (vetor, j, sizeof(tpNoArvore*), compararNome) ;
		
		for(i=1; i<j;i++)
		{
			vetor[i-1]->next = vetor[i] ;
		}

		return CondRet ;
   }/* Fim função: ARV Costura folhas da árvore */

/***********************************************************************
*  $FC Função: ARV Imprime costura na ordem
*  
*  $FV Valor retornado
*	 ARV_CondRetOK
***********************************************************************/

   ARV_tpCondRet ARV_ImprimirFolhasNaOrdem( void )
   { 
		int i ;
		
		printf("\n\n\tOrdem de costura: %c", vetor[0]->Chave) ;
		
		for(i=0; vetor[i]->next!=NULL; i++)
		{
			printf(" --> %c", vetor[i]->next->Chave) ;
		}
		
		printf("\n");

		return ARV_CondRetOK ;
   }/* Fim função: ARV Imprime costura */

/********** Fim do módulo de implementação: Módulo árvore **********/
