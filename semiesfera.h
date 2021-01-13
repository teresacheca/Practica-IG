// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Semiesfera.h
//
// #############################################################################

#ifndef SEMIESFERA_H_INCLUDED
#define SEMIESFERA_H_INCLUDED

#include "aux.h"


// *****************************************************************************
//
// clase semiesfera derivada de ObjRevolucion
//
// *****************************************************************************

class Semiesfera : public ObjRevolucion
{

	public:
	Semiesfera(const int num_vert_perfil, const int num_instancias_perf, const float radio);

	private:
	float radio;	
} ;


#endif
