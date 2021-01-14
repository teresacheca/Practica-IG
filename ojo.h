// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: ojo.h

//
// #############################################################################

#ifndef OJO_H_INCLUDED
#define OJO_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"
#include "esfera.h"
#include "malla.h"


// *****************************************************************************
//
// clase ojo 
//
// *****************************************************************************

class Ojo
{
	public:
		Ojo();
		void draw();
  
		ObjRevolucion * esfera;
		Textura * textura;
} ;


#endif
