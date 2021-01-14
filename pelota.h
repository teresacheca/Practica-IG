// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: pelota.h

//
// #############################################################################

#ifndef PELOTA_H_INCLUDED
#define PELOTA_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"
#include "esfera.h"
#include "textura.h"
#include "material.h"


// *****************************************************************************
//
// clase pelota
//
// *****************************************************************************

class Pelota
{
	public:
		Pelota();
		void draw();
	
	private:
		ObjRevolucion * esfera;
		Textura * textura;
	
} ;


#endif
