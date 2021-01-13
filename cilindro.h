// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cilindro.h
//
// #############################################################################

#ifndef CILINDRO_H_INCLUDED
#define CILINDRO_H_INCLUDED

#include "aux.h"


// *****************************************************************************
//
// clase cilindro derivada de ObjRevolucion
//
// *****************************************************************************

class Cilindro : public ObjRevolucion
{
	public:	
	Cilindro(const int num_vert_perfil, const int num_instancias_perf, const float altura, const float radio);
  
	private:
	float altura;
	float radio;
} ;


#endif
