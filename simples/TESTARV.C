/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico
*
*  Arquivo gerado:              TESTARV.C
*  Letras identificadoras:      TARV
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
*  $ED Descrição do módulo
*     Este módulo contém as funções específicas para o teste do
*     módulo árvore. Ilustra como redigir um interpretador de comandos
*     de teste específicos utilizando o arcabouço de teste para C.
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo árvore:
*
*     =criar        - chama a função ARV_CriarArvore( )
*     =insdir <Char>
*                   - chama a função ARV_InserirDireita( <Char> )
*                     Obs. notação: <Char>  é o valor do parâmetro
*                     que se encontra no comando de teste.
*
*     "=insesq" <Char>
*                   - chama a função ARV_InserirEsquerda( <Char> )
*     "=irpai"      - chama a função ARV_IrPai( )
*     "=iresq"      - chama a função ARV_IrEsquerda( )
*     "=irdir"      - chama a função ARV_IrDireita( )
*     "=obter" <Char>
*                   - chama a função ARV_ObterValorCorr( ) e compara
*                     o valor retornado com o valor <Char>
*     "=destroi"    - chama a função ARV_DestruirArvore( )
*	  "=costura"    - chama a função ARV_Costura( )
*	  "=imprime"    - chama a função ARV_Imprime( )
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <stdlib.h>

#include    "TST_ESPC.H"

#include    "generico.h"
#include    "lerparm.h"

#include    "arvore.h"

/* Tabela dos nomes dos comandos de teste específicos */

#define     CRIAR_ARV_CMD       "=criar"
#define     INS_DIR_CMD         "=insdir"
#define     INS_ESQ_CMD         "=insesq"
#define     IR_PAI_CMD          "=irpai"
#define     IR_ESQ_CMD          "=iresq"
#define     IR_DIR_CMD          "=irdir"
#define     OBTER_VAL_CMD       "=obter"
#define     DESTROI_CMD         "=destruir"
#define		COSTURA_CMD			"=costura"
#define		IMPRIME_CMD			"=imprime"

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TARV Efetuar operações de teste específicas para árvore
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     árvore sendo testado.
*
*  $EP Parâmetros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      ARV_tpCondRet CondRetObtido   = ARV_CondRetOK ;
      ARV_tpCondRet CondRetEsperada = ARV_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */

      char ValorEsperado = '?'  ;
      char ValorObtido   = '!'  ;
      char ValorDado     = '\0' ;
	  int ValorDado1     =  0   ;
	  int ValorDado2     =  0   ;
	  int ValorDado3     =  0   ;

      int  NumLidos = -1 ;

      TST_tpCondRet Ret ;

      /* Testar ARV Criar árvore */

         if ( strcmp( ComandoTeste , CRIAR_ARV_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "i" ,
                               &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_CriarArvore( ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar árvore." );

         } /* fim ativa: Testar ARV Criar árvore */

      /* Testar ARV Adicionar filho à direita */

         else if ( strcmp( ComandoTeste , INS_DIR_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ciiii" ,
                               &ValorDado , &ValorDado1, &ValorDado2, &ValorDado3, &CondRetEsperada ) ; //recebe do script os inteiros a serem passados para lista
            if ( NumLidos != 5 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_InserirDireita( ValorDado, ValorDado1, ValorDado2, ValorDado3 ) ; //passa os inteiros para serem inseridos na lista

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado inserir àa direita." );

         } /* fim ativa: Testar ARV Adicionar filho à direita */

      /* Testar ARV Adicionar filho à esquerda */

         else if ( strcmp( ComandoTeste , INS_ESQ_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ciiii" ,
                               &ValorDado , &ValorDado1, &ValorDado2, &ValorDado3, &CondRetEsperada ) ; //recebe do script os inteiros a serem passados para lista
            if ( NumLidos != 5 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_InserirEsquerda( ValorDado, ValorDado1, ValorDado2, ValorDado3 ) ; //passa os inteiros para serem inseridos na lista
			
            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao inserir à esquerda." );

         } /* fim ativa: Testar ARV Adicionar filho à esquerda */

      /* Testar ARV Ir para nó pai */

         else if ( strcmp( ComandoTeste , IR_PAI_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" ,
                               &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_IrPai( ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para pai." );

         } /* fim ativa: Testar ARV Ir para nó pai */

      /* Testar ARV Ir para nó à esquerda */

         else if ( strcmp( ComandoTeste , IR_ESQ_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" ,
                               &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_IrNoEsquerda( ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para esquerda." );

         } /* fim ativa: Testar ARV Ir para nó à esquerda */

      /* Testar ARV Ir para nó à direita */

         else if ( strcmp( ComandoTeste , IR_DIR_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" ,
                               &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_IrNoDireita( ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para direita." );

         } /* fim ativa: Testar ARV Ir para nó à direita */

      /* Testar ARV Obter valor corrente */

         else if ( strcmp( ComandoTeste , OBTER_VAL_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ci" ,
                               &ValorEsperado , &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */
            CondRetObtido = ARV_ObterValorCorr( &ValorObtido ) ;
            Ret = TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                   "Retorno errado ao obter valor corrente." );

            if ( Ret != TST_CondRetOK )
            {
               return Ret ;
            } /* if */

            return TST_CompararChar( ValorEsperado , ValorObtido ,
                                     "Conteúdo do nó está errado." ) ;

         } /* fim ativa: Testar ARV Obter valor corrente */

      /* Testar ARV Destruir árvore */

         else if ( strcmp( ComandoTeste , DESTROI_CMD ) == 0 )
         {

            ARV_DestruirArvore( ) ;

            return TST_CondRetOK ;

         }/* fim ativa: Testar ARV Destruir árvore */

	  /* Testar ARV Costurar folhas da árvore */

		 else if ( strcmp (ComandoTeste, COSTURA_CMD ) == 0 )
		 {
			NumLidos = LER_LerParametros( "i" ,
                               &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

			 CondRetObtido = ARV_CosturarFolhas( ) ;
			
			 return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Não foi possível realizar a costura." );
		 }/* fim ativa: Testar ARV Costurar folhas da árvore */

		 /* Testar ARV Imprimir costura */

		 else if ( strcmp (ComandoTeste, IMPRIME_CMD ) == 0 )
		 {

			NumLidos = LER_LerParametros( "i" ,
                               &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

			 CondRetObtido = ARV_ImprimirFolhasNaOrdem( ) ;
			
			 return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Não foi possível realizar a impressão." );

		 }/* fim ativa: Testar ARV Imprimir costura */


      return TST_CondRetNaoConhec ;
	  

   } /* Fim função: TARV Efetuar operações de teste específicas para árvore */

/********** Fim do módulo de implementação: Módulo de teste específico **********/

