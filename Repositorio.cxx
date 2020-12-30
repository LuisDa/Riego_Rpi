#include "Repositorio.h"
#include <iostream>
#include <fstream>
//#include <string>
#include <bits/stdc++.h>

//using namespace std;


CRepositorio::CRepositorio()
{
	refrescarProgramas();	
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
	
	if (m_EstadoValvulas_p != NULL)
	{
		free(m_EstadoValvulas_p);
		m_EstadoValvulas_p = NULL;
	}	
}

void CRepositorio::refrescarProgramas()
{
	m_Programa1_p = (programa_riego_t*)malloc(sizeof(programa_riego_t));
	m_Programa2_p = (programa_riego_t*)malloc(sizeof(programa_riego_t));
	m_Programa3_p = (programa_riego_t*)malloc(sizeof(programa_riego_t));
	m_EstadoValvulas_p = (estado_valvulas_t*)malloc(sizeof(estado_valvulas_t));
	
	//Leemos de los ficheros de los programas los estados de las válvulas y las horas de inicio
	char* programas_riego[3] = {"programa_1.txt", "programa_2.txt", "programa_3.txt"};
	
	for (int i = 0; i < 3; i++)
	{
		char* nombre_fich = programas_riego[i];
		
		ifstream fichero_prog(nombre_fich);
		string linea;
		
		if (((bool)fichero_prog) && fichero_prog.is_open()) //Fichero programa_1.txt existe y está abierto
		{
			int num_valv = 1;
			
			programa_riego_t* programa_riego = NULL;	
			
			if (i == 0) programa_riego = m_Programa1_p;
			else if (i == 1) programa_riego = m_Programa2_p;
			else if (i == 2) programa_riego = m_Programa3_p;
			
						
			//programa_riego = m_Programa1_p + i * sizeof(programa_riego_t);
			
			//Primera línea: leer hora de inicio
			if (getline(fichero_prog, linea))
			{
				vector<string> tokens;
				stringstream check1(linea);
				string str_aux;
				
				//Primero analizamos la línea <<H hh:mm>>
				while(getline(check1, str_aux, ' '))
				{
					tokens.push_back(str_aux);
				}
				
				//Y después el token en sub-tokens: hora y minuto
				vector<string> subtokens;
				stringstream check2(tokens[1]);
				
				while(getline(check2, str_aux, ':'))
				{
					subtokens.push_back(str_aux);
				}
				
				programa_riego->hora_ini = atoi((char*)subtokens[0].c_str());
				programa_riego->minuto_ini = atoi((char*)subtokens[1].c_str());
			}
						
			while(getline(fichero_prog, linea))
			{			
				vector<string> tokens;
				stringstream check1(linea);
				string str_aux;
				
				while(getline(check1, str_aux, ' '))
				{
					tokens.push_back(str_aux);
				}
				
				//repositorio->setDuracionValv(1, num_valv, atoi((char*)tokens[2].c_str()));
							
				
				switch(num_valv)
				{
					case 1: programa_riego->duracion_valv1 = atoi((char*)tokens[1].c_str());
					case 2: programa_riego->duracion_valv2 = atoi((char*)tokens[1].c_str());
					case 3: programa_riego->duracion_valv3 = atoi((char*)tokens[1].c_str());
					case 4: programa_riego->duracion_valv4 = atoi((char*)tokens[1].c_str());
				}
							
				//for(int i = 0; i < tokens.size(); i++) cout << tokens[i] << '\n';
							
				num_valv++;
			}
		}		
	}
	
	
	printf ("PROGRAMA 1\n");
	
	printf (" * HORA: %d:%d\n", m_Programa1_p->hora_ini, m_Programa1_p->minuto_ini);		
	printf (" * V1: %d\n", m_Programa1_p->duracion_valv1);
	printf (" * V2: %d\n", m_Programa1_p->duracion_valv2);
	printf (" * V3: %d\n", m_Programa1_p->duracion_valv3);
	printf (" * V4: %d\n", m_Programa1_p->duracion_valv4);
			
	printf ("\n");	
	

	printf ("PROGRAMA 2\n");
	
	printf (" * HORA: %d:%d\n", m_Programa2_p->hora_ini, m_Programa2_p->minuto_ini);				
	printf (" * V1: %d\n", m_Programa2_p->duracion_valv1);
	printf (" * V2: %d\n", m_Programa2_p->duracion_valv2);
	printf (" * V3: %d\n", m_Programa2_p->duracion_valv3);
	printf (" * V4: %d\n", m_Programa2_p->duracion_valv4);
			
	printf ("\n");	
	
	printf ("PROGRAMA 3\n");
	
	printf (" * HORA: %d:%d\n", m_Programa3_p->hora_ini, m_Programa3_p->minuto_ini);				
	printf (" * V1: %d\n", m_Programa3_p->duracion_valv1);
	printf (" * V2: %d\n", m_Programa3_p->duracion_valv2);
	printf (" * V3: %d\n", m_Programa3_p->duracion_valv3);
	printf (" * V4: %d\n", m_Programa3_p->duracion_valv4);
			
	printf ("\n");			
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

char CRepositorio::getHoraInicio(char num_prog)
{
	switch(num_prog)
	{
		case 1: return m_Programa1_p->hora_ini;
		case 2: return m_Programa2_p->hora_ini;
		case 3: return m_Programa3_p->hora_ini;		
	}
	
	return 0;
}

char CRepositorio::getMinutoInicio(char num_prog)
{
	switch(num_prog)
	{
		case 1: return m_Programa1_p->minuto_ini;
		case 2: return m_Programa2_p->minuto_ini;
		case 3: return m_Programa3_p->minuto_ini;		
	}
	
	return 0;	
}

void CRepositorio::setDuracionValv(char num_prog, char num_valv, char duracion)
{
	//programa_riego_t* programa = (m_Programa1_p) + (sizeof(programa_riego_t) + (num_prog - 1));
	programa_riego_t* programa;
	
	switch(num_prog)
	{
		case 1: programa = m_Programa1_p; break;
		case 2: programa = m_Programa2_p; break;
		case 3: programa = m_Programa3_p; break;
	}
	
	switch(num_valv)
	{
		case 1: programa->duracion_valv1 = duracion; break;
		case 2: programa->duracion_valv2 = duracion; break;
		case 3: programa->duracion_valv3 = duracion; break;
		case 4: programa->duracion_valv4 = duracion; break;
	}
}

void CRepositorio::setEstadoValvula(int numValv, bool estado)
{
	switch(numValv)
	{
		case 1: m_EstadoValvulas_p->valvula1_sts = (estado==true)?1:0; break;
		case 2: m_EstadoValvulas_p->valvula2_sts = (estado==true)?1:0; break;
		case 3: m_EstadoValvulas_p->valvula3_sts = (estado==true)?1:0; break;
		case 4: m_EstadoValvulas_p->valvula4_sts = (estado==true)?1:0; break;
		case 5: m_EstadoValvulas_p->valvulaM_sts = (estado==true)?1:0; break;
	}
}

bool CRepositorio::getEstadoValvula(int numValv)
{
	switch (numValv)
	{
		case 1: return m_EstadoValvulas_p->valvula1_sts;
		case 2: return m_EstadoValvulas_p->valvula2_sts;
		case 3: return m_EstadoValvulas_p->valvula3_sts;
		case 4: return m_EstadoValvulas_p->valvula4_sts;
		case 5: return m_EstadoValvulas_p->valvulaM_sts;		
	}
	
	return false;
}


char CRepositorio::getDuracionValv(char num_prog, char num_valv)
{	
	programa_riego_t* prog_riego;// = m_Programa1_p + (num_prog - 1)*sizeof(programa_riego_t);
	
	switch(num_prog)
	{
		case 1: prog_riego = m_Programa1_p; break;
		case 2: prog_riego = m_Programa2_p; break;
		case 3: prog_riego = m_Programa3_p; break;
	}
	
	if (prog_riego)
	{
		switch(num_valv)
		{
			case 1: return prog_riego->duracion_valv1;
			case 2: return prog_riego->duracion_valv2;
			case 3: return prog_riego->duracion_valv3;
			case 4: return prog_riego->duracion_valv4;
			default: return 0;
		}
	}	
}

int CRepositorio::programaIncluido(char hora_ini, char min_ini)
{
	if ((m_Programa1_p->hora_ini == hora_ini) && (m_Programa1_p->minuto_ini == min_ini)) return 1;
	else if ((m_Programa2_p->hora_ini == hora_ini) && (m_Programa2_p->minuto_ini == min_ini)) return 2;
	else if ((m_Programa3_p->hora_ini == hora_ini) && (m_Programa3_p->minuto_ini == min_ini)) return 3;
	
	return 0;	
}


void CRepositorio::actualizarHoraInicio(string str_hora, char num_prog)
{
	vector<string> subtokens;
	stringstream check(str_hora);
	string str_aux;
	
	while(getline(check, str_aux, ':')) { subtokens.push_back(str_aux); }
	
	switch (num_prog)
	{
		case 1:
			m_Programa1_p->hora_ini = atoi((char*)subtokens[0].c_str());
			m_Programa1_p->minuto_ini = atoi((char*)subtokens[1].c_str());
			break;
		case 2:	
			m_Programa2_p->hora_ini = atoi((char*)subtokens[0].c_str());
			m_Programa2_p->minuto_ini = atoi((char*)subtokens[1].c_str());
			break;
		case 3:	
			m_Programa3_p->hora_ini = atoi((char*)subtokens[0].c_str());
			m_Programa3_p->minuto_ini = atoi((char*)subtokens[1].c_str());
			break;		
		default: 
			break;
	}
	
}
