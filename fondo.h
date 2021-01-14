// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: fondo.h

//
// #############################################################################

#ifndef FONDO_H_INCLUDED
#define FONDO_H_INCLUDED

#include "aux.h"
#include "lata.h"
#include "pelota.h"


// *****************************************************************************
//
// clase cola
//
// *****************************************************************************

class Fondo
{
	public:
		Fondo();
		void draw();
		
	private:
		Lata * lata;
		Pelota * pelota;
} ;


#endif
