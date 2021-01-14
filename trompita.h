// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: trompita.h

//
// #############################################################################

#ifndef TROMPITA_H_INCLUDED
#define TROMPITA_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"
#include "esfera.h"
#include "malla.h"
#include "cilindro.h"
#include "semiesfera.h"


// *****************************************************************************
//
// clase trompita 
//
// *****************************************************************************

class Trompita 
{
	public:
		Trompita();
		void draw();
		void modificaGiroTrompaPequeniaX();
      	void modificaGiroTrompaPequeniaZ();

		void setGiroTrompaPequeniaX(float valor);
		void setGiroTrompaPequeniaZ(float valor);

		float getGiroTrompaPequeniaX();
		float getGiroTrompaPequeniaZ();
  
	private:
		ObjRevolucion * esfera;
		ObjRevolucion * semiesfera;
		Textura * textura;

		float giroTrompaPequeniaX;
      	float giroTrompaPequeniaZ;
} ;


#endif
