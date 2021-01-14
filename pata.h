// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: pata.h

//
// #############################################################################

#ifndef PATA_H_INCLUDED
#define PATA_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"
#include "cilindro.h"
#include "semiesfera.h"
#include "textura.h"
#include "material.h"

// *****************************************************************************
//
// clase pata
//
// *****************************************************************************

class Pata
{
	public:
		Pata();
		void draw();

		ObjRevolucion * cilindro;
		ObjRevolucion * semiesfera;
		Textura * textura;
} ;


#endif
