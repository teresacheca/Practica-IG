// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: oreja.h

//
// #############################################################################

#ifndef OREJA_H_INCLUDED
#define OREJA_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"
#include "semiesfera.h"
#include "malla.h"


// *****************************************************************************
//
// clase ojo 
//
// *****************************************************************************

class Oreja
{
	public:
		Oreja();
		void draw();
  
		ObjRevolucion * semiesfera;
		Textura * textura;
} ;


#endif
