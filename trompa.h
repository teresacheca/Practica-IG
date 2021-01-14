// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: trompa.h

//
// #############################################################################

#ifndef TROMPA_H_INCLUDED
#define TROMPA_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"
#include "esfera.h"
#include "malla.h"
#include "cilindro.h"
#include "semiesfera.h"
#include "trompita.h"


// *****************************************************************************
//
// clase trompa
//
// *****************************************************************************

class Trompa 
{
	public:
		Trompa();
		void draw();

		void modificaGiroTrompaZ();
		void modificaGiroTrompaX();

		void setGiroTrompaX(float valor);
     	void setGiroTrompaZ(float valor);

		virtual void modificaGiroTrompaPequeniaX();
      	virtual void modificaGiroTrompaPequeniaZ();

		virtual void setGiroTrompaPequeniaX(float valor);
     	virtual void setGiroTrompaPequeniaZ(float valor);

		float getGiroTrompaX();
		float getGiroTrompaZ();
			
		virtual float getGiroTrompaPequeniaX();
		virtual float getGiroTrompaPequeniaZ();
		
	
	private:
		ObjRevolucion * esfera;
		ObjRevolucion * semiesfera;
		ObjRevolucion * cilindro;
		Textura * textura;
		Trompita * trompita;

		float giroTrompaX;
      	float giroTrompaZ;
		
} ;


#endif
