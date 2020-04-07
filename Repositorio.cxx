#include <stdlib.h>
#include "Repositorio.h"

CRepositorio::CRepositorio()
{
	m_Programa1_p = (programa_riego_t*)malloc(sizeof(programa_riego_t));
	m_Programa2_p = (programa_riego_t*)malloc(sizeof(programa_riego_t));
	m_Programa3_p = (programa_riego_t*)malloc(sizeof(programa_riego_t));
}

CRepositorio::~CRepositorio()
{
	if (m_Programa1_p != NULL)
	{
		free(m_Programa1_p);
		m_Programa1_p = NULL;
	}
	
	if (m_Programa2_p != NULL)
	{
		free(m_Programa2_p);
		m_Programa2_p = NULL;
	}	
	
	if (m_Programa3_p != NULL)
	{
		free(m_Programa3_p);
		m_Programa3_p = NULL;
	}		
}

void CRepositorio::setHoraInicio(char num_prog, char hora, char min)
{
	switch(num_prog)
	{
		case 1:
			m_Programa1_p->hora_ini = hora;
			m_Programa1_p->minuto_ini = min;
			break;
		case 2:
			m_Programa2_p->hora_ini = hora;
			m_Programa2_p->minuto_ini = min;
			break;			
		case 3:
			m_Programa3_p->hora_ini = hora;
			m_Programa3_p->minuto_ini = min;
			break;					
	}
}

void CRepositorio::setDuracionValv(char num_prog, char num_valv, char duracion)
{
	programa_riego_t* programa = (m_Programa1_p) + (sizeof(programa_riego_t) + (num_prog - 1));
	
	switch(num_valv)
	{
		case 1: programa->duracion_valv1 = duracion; break;
		case 2: programa->duracion_valv2 = duracion; break;
		case 3: programa->duracion_valv3 = duracion; break;
		case 4: programa->duracion_valv3 = duracion; break;
	}
}