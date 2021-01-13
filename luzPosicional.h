// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: luzPosicional.h
//
//
// #############################################################################

#ifndef LUZ_POSICIONAL_H
#define LUZ_POSICIONAL_H

#include "aux.h"
#include "luz.h"

class LuzPosicional : public Luz
{

      

   public: 
     
     LuzPosicional(Tupla3f posicion, GLenum idLuzOpenGl, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso);
     
     LuzPosicional(const Tupla3f & posicion);

     void mover(Tupla3f p);
	
} ;


#endif
