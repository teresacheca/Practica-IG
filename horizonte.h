// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: horizonte.h

//
// #############################################################################

#ifndef HORIZONTE_H_INCLUDED
#define HORIZONTE_H_INCLUDED

#include "aux.h"
#include "cubo.h"
#include "textura.h"
#include "material.h"
#include "malla.h"
// *****************************************************************************
//
// clase horizonte
//
// *****************************************************************************

class Horizonte
{
	public:
		Horizonte();
		void draw();
	
	private:
		Cubo * cubo;
		Cubo * caseta;
		Textura * textura;
		Textura * t_caseta;
	
} ;


#endif
