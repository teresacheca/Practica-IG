// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: cola.h

//
// #############################################################################

#ifndef COLA_H_INCLUDED
#define COLA_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"
#include "semiesfera.h"
#include "malla.h"
#include "cilindro.h"
#include "esfera.h"
#include "cono.h"
#include "textura.h"
#include "material.h"


// *****************************************************************************
//
// clase cola
//
// *****************************************************************************

class Cola
{
	public:
		Cola();
		void draw();
  
		ObjRevolucion * cilindro;
		ObjRevolucion * semiesfera;
		ObjRevolucion * esfera;
		ObjRevolucion * cono;
		Textura * textura;
} ;


#endif
