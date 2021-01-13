// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Esfera.h
//
// #############################################################################

#ifndef ESFERA_H_INCLUDED
#define ESFERA_H_INCLUDED

#include "aux.h"


// *****************************************************************************
//
// clase esfera derivada de ObjRevolucion
//
// *****************************************************************************

class Esfera : public ObjRevolucion
{

	public:
	Esfera(const int num_vert_perfil, const int num_instancias_perf, const float radio);

	private:
	float radio;	
} ;


#endif
