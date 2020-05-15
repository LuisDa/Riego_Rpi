#ifndef REPOSITORIO_H
#define REPOSITORIO_H

#include <stdlib.h>

class CRepositorio
{
	struct programa_riego_t
	{
		char hora_ini;
		char minuto_ini;
		char duracion_valv1;
		char duracion_valv2;
		char duracion_valv3;
		char duracion_valv4;
	};
	
	struct estado_valvulas_t
	{
		char valvula1_sts:1;
		char valvula2_sts:1;
		char valvula3_sts:1;
		char valvula4_sts:1;
		char valvulaM_sts:1; //Válvula maestra
	};
	
	public:
		CRepositorio();
		~CRepositorio();
		void setHoraInicio(char num_prog, char hora, char min);
		void setDuracionValv(char num_prog, char num_valv, char duracion);
		void setIdProgramaSeleccionado(int id) { m_IdProgramaSeleccionado = id; }
		int getIdProgramaSeleccionado() {return m_IdProgramaSeleccionado; }
		void setEstadoValvula(int numValv, bool estado);
		bool getEstadoValvula(int numValv);
		
				
	private:
		programa_riego_t* m_Programa1_p = NULL;
		programa_riego_t* m_Programa2_p = NULL;
		programa_riego_t* m_Programa3_p = NULL;
		int m_IdProgramaSeleccionado = 1;
		estado_valvulas_t* m_EstadoValvulas_p = NULL;
};
#endif
