/**********************************************************************
 PID EMBARCADOS
 
 Exemplo simples de calculador PID usando aproximacao retangular.
 
 Arquivo: PID.c
 Desc	: Modulo template para controlador PID
 
 
 Autor: FSN.
 
 Sobre Licenca: Use a vontade, nao espero ficar rico com isso
 
 **********************************************************************/
#ifndef _PID_h
#define _PID_h

/*********************************************************************
 Defines
 *********************************************************************/

//Coeficientes do controlador pid
#define  KP (float_t)1.0f
#define  KI (float_t)0.1f
#define  KD (float_t)0.1f

//Taxa de amostragem em Hz:
#define  TX_AMOSTRAGEM (uint32_t)1000

//coeficientes escalados para 16bits:
#define KP_INT (int16_t)(KP * 32768.0f)
#define KI_INT (int16_t)(KI * 32768.0f)
#define KD_INT (int16_t)(KD * 32768.0f)



/**********************************************************************
 Estruturas
 **********************************************************************/
typedef struct
{
	//Acumulador para as multiplicacoes
	int32_t dAcumulador;
    
	//Guarda a realimentacao
	int16_t wRealimentacao;
    
	//historico do erro
	int16_t wErro[2];
    
	//Variavel de saida:
	uint16_t wSaida;
    
}PID_t;

/**********************************************************************
 Prototipos das funcoes
 **********************************************************************/
void PID_vInit(PID_t *pxPID);
void PID_vArmazenaLeitura(void *pvSensor, uint8_t bDataWidth);
uint16_t PID_wComputa(PID_t *pxPID, int16_t wSetPoint);

#endif
