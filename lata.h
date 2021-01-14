// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: lata.h

//
// #############################################################################

#ifndef LATA_H_INCLUDED
#define LATA_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"
#include "cilindro.h"
#include "textura.h"
#include "material.h"


// *****************************************************************************
//
// clase lata
//
// *****************************************************************************

class Lata
{
	public:
		Lata();
		void draw();

	private:
  
		ObjRevolucion * cilindro;
		Textura * textura;
} ;


#endif
