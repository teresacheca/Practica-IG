// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: cuerpo.h

//
// #############################################################################

#ifndef CUERPO_H_INCLUDED
#define CUERPO_H_INCLUDED

#include "aux.h"
#include "cola.h"
#include "pata.h"
#include "esfera.h"
#include "objrevolucion.h"
#include "textura.h"
#include "material.h"


// *****************************************************************************
//
// clase cuerpo derivada de ObjRevolucion
//
// *****************************************************************************

class Cuerpo 
{
	public:
		Cuerpo();
		void draw();
		void giroPatasDerechas();
   		void giroPatasIzquierdas();
		void setGiroPatas(float valor);
		void setAgacharse(bool a);
		float getGiroPatas();
		
	private:

		ObjRevolucion * tronco;
		Pata * pata;
		Cola * cola;
		Textura * textura;
		float giroPatas;
		bool agacha;

   
} ;


#endif
