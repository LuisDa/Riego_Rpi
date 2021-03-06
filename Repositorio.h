#ifndef REPOSITORIO_H
#define REPOSITORIO_H

#include <string>
#include <stdlib.h>

using namespace std;

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
		char getHoraInicio(char num_prog);
		char getMinutoInicio(char num_prog);
		void setDuracionValv(char num_prog, char num_valv, char duracion);
		void setIdProgramaSeleccionado(int id) { m_IdProgramaSeleccionado = id; }
		int getIdProgramaSeleccionado() {return m_IdProgramaSeleccionado; }
		void setEstadoValvula(int numValv, bool estado);
		bool getEstadoValvula(int numValv);
		char getDuracionValv(char num_prog, char num_valv);
		int programaIncluido(char hora_ini, char min_ini);
		void setProgramaActivo(int num_prog) { m_numProgramaActivo = num_prog; }
		int getProgramaActivo() {return m_numProgramaActivo; }
		void refrescarProgramas();	
		void actualizarHoraInicio(string str_hora, char num_prog);
				
	private:
		programa_riego_t* m_Programa1_p = NULL;
		programa_riego_t* m_Programa2_p = NULL;
		programa_riego_t* m_Programa3_p = NULL;
		int m_IdProgramaSeleccionado = 1;
		estado_valvulas_t* m_EstadoValvulas_p = NULL;
		int m_numProgramaActivo = 0;
};
#endif
