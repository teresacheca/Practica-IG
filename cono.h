// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cono.h

//
// #############################################################################

#ifndef CONO_H_INCLUDED
#define CONO_H_INCLUDED

#include "aux.h"


// *****************************************************************************
//
// clase cono derivada de ObjRevolucion
//
// *****************************************************************************

class Cono : public ObjRevolucion
{
	public:
	Cono(const int num_vert_perfil, const int num_instancias_perf, const float altura, const float radio);
  
	private:
	float altura;
	float radio;
   
} ;


#endif
