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
	
	public:
		CRepositorio();
		~CRepositorio();
		void setHoraInicio(char num_prog, char hora, char min);
		void setDuracionValv(char num_prog, char num_valv, char duracion);
		void setIdProgramaSeleccionado(int id) { m_IdProgramaSeleccionado = id; }
		int getIdProgramaSeleccionado() {return m_IdProgramaSeleccionado; }
		
	private:
		programa_riego_t* m_Programa1_p = 0;
		programa_riego_t* m_Programa2_p = 0;
		programa_riego_t* m_Programa3_p = 0;
		int m_IdProgramaSeleccionado = 1;
};
