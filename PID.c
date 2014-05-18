/**********************************************************************
 	 	 	 	 	 	 	PID EMBARCADOS

 	 Exemplo simples de calculador PID usando aproximacao retangular.

 	 Arquivo: PID.c
 	 Desc	: Modulo template para controlador PID


 	 Autor: FSN.

 	 Sobre Licenca: Use a vontade, nao espero ficar rico com isso

 **********************************************************************/


/**********************************************************************
 	 	 	 	 	 Includes
 **********************************************************************/
#include <stdint.h>
#include <string.h> //para funcao memset
#include "PID.h"

/**********************************************************************
 	 	 	 	 	 Variaveis desse modulos
 **********************************************************************/

/**********************************************************************
 	 	 	 	 	 Funcoes
 **********************************************************************/

/**********************************************************************
 	 	 	PID_vInit()

 	 	 	Desc: Iniciaciza bloco de controle PID

 	 	 	Param: pxPID - Ponteiro para bloco de controle PID

 	 	 	Retorna: N/A

 **********************************************************************/
void PID_vInit(PID_t *pxPID)
{
	//Checa parametros:

	//Ponteiro nulo?
	if((PID_t *)0 == pxPID)
	{
		//encerra funcao
		return;
	}

	//Limpa bloco de controle:
	memset((uint8_t*)pxPID, 0 , sizeof(PID_t));
}
/**********************************************************************
 	 	 	PID_vArmazenaLeitura()

 	 	 	Desc: Armazena e escala o valor de um sensor para
 	 	 		  16 bits com sinal

 	 	 	Param: pvSensor - ponteiro generico para o local
 	 	 				      onde o valor esta armazenado

 	 	 			bDataWidth - Largura de dados do sensor em
 	 	 				      	 bits

 	 	 	Retorna: N/A
 **********************************************************************/
void PID_vArmazenaLeitura(PID_t *pxPID, void *pvSensor, uint8_t bDataWidth)
{
	//Variaveis auxiliares;
	uint32_t dTemp;

	//checa variaveis:
	if((PID_t *)0 == pxPID) return;

	//checa variaveis:
	if((void *)0 == pvSensor) return;

	//Formata os dados de acordo com a largura desejada:
	switch(bDataWidth)
	{
		case 8:

			//Escala para 16bits:
			dTemp = ((uint32_t)*pvSensor) << 8;

		break;

		case 16:

			//se ja for 16 bits nao escala:
			dTemp = (uint32_t) *pvSensor;

		break;

		case 24:

			//24 bits centraliza valor em 16:
			dTemp = ((uint32_t)*pvSensor) >> 8;

		break;

		case 32:

			//32bits centraliza em 16:
			dTemp = ((uint32_t)*pvSensor) >> 16;


		break;

		default:
			//encerra em caso de largura invalida:
			return;
		break;
	}


	//uma vez escalado coloca o sinal, na variavele
	//salva na estrutura
	pxPID->wRealimentacao = (int16_t)dTemp;

}

/**********************************************************************
 	 	 	PID_wComputa()

 	 	 	Desc: Computa um novo valor de saida do PID

 	 	 	Param: pxPID - Ponteiro para bloco de controle PID
 	 	 		   wSetPoint - Valor corrente desejado

 	 	 	Retorna: Resultado 16 bits sem sinal contendo o valor
 	 	 			 que deve ir a planta de controle

 **********************************************************************/
uint16_t PID_bComputa(PID_t *pxPID, int16_t wSetPoint)
{
	//Variaveis auxiliares:
	int32_t  dSaida = 0;
	uint16_t wSaida_PID = 0;

	//Checa parametros:

	//checa por ponteiro nulo:
	if((PID_t *)0 == pxPID)
	{
		//encerra funcao:
		return(0);

	}

	//computa o erro corrente:
	pxPID->wErro[0] = wSetPoint - pxPID->wRealimentacao;

	//integra erro
	dAcumulador += KI * pxPID->wErro[0];

	//Calcula termo derivativo:
	dSaida = KD * (pxPID->wErro[0] - pxPID->wErro[1]);

	//Calcula termo proporcional:
	dSaida += KP * pxPID->wErro[0];

	//soma o integral e encerra a computacao:
	dSaida += dAcumulador ;

	//escala valor para 16bits sem sinal:
	pxPID->wSaida  = (uint16_t)(dSaida >> 16);

	//atualiza o historico de erro:
	pxPID->wErro[1] = pxPID->wErro[1];

	//retorna variavel de saida:
	return(pxPID->wSaida);
}
