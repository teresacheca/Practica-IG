// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: cabeza.h

//
// #############################################################################

#ifndef CABEZA_H_INCLUDED
#define CABEZ_H_INCLUDED

#include "aux.h"
#include "trompa.h"
#include "cuerno.h"
#include  "ojo.h"
#include "objrevolucion.h"
#include "esfera.h"
#include "oreja.h"



// *****************************************************************************
//
// clase cabeza 
//
// *****************************************************************************

class Cabeza
{
	public:
		Cabeza();

		void draw();

		virtual void modificaGiroTrompaZ();
		virtual void modificaGiroTrompaX();

		virtual void setGiroTrompaX(float valor);
     	virtual void setGiroTrompaZ(float valor);

		virtual void modificaGiroTrompaPequeniaZ();
		virtual void modificaGiroTrompaPequeniaX();

		virtual void setGiroTrompaPequeniaX(float valor);
     	virtual void setGiroTrompaPequeniaZ(float valor);

		virtual float getGiroTrompaX();
		virtual float getGiroTrompaZ();
			
		virtual float getGiroTrompaPequeniaX();
		virtual float getGiroTrompaPequeniaZ();
	
	private:
  
		ObjRevolucion * esfera;
		Trompa * trompa;
		Ojo * ojo;
		Cuerno * cuerno;
		Oreja * oreja;
		Textura * textura;
		
	
} ;


#endif
