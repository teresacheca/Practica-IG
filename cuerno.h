// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: cuerno.h

//
// #############################################################################

#ifndef CUERNO_H_INCLUDED
#define CUERNO_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"
#include "cilindro.h"
#include "semiesfera.h"
#include "textura.h"


// *****************************************************************************
//
// clase cuerno 
//
// *****************************************************************************

class Cuerno 
{
	public:
		Cuerno();
		void draw();

		ObjRevolucion * cilindro;
		ObjRevolucion * semiesfera;
		Textura * textura;
   
} ;


#endif
