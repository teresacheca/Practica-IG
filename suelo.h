// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: suelo.h

//
// #############################################################################

#ifndef SUELO_H_INCLUDED
#define SUELO_H_INCLUDED

#include "aux.h"
#include "cubo.h"
#include "textura.h"
#include "material.h"
#include "malla.h"
// *****************************************************************************
//
// clase suelo
//
// *****************************************************************************

class Suelo
{
	public:
		Suelo();
		void draw();
	
	private:
		Cubo * cubo;
		Textura * textura;
	
} ;


#endif
