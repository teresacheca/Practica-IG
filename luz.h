// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: luz.h
//
//
// #############################################################################

#ifndef LUZ_H
#define LUZ_H

#include "aux.h"


class Luz
{

   private: 
      Tupla4f posicion;
      GLenum id;
      Tupla4f colorAmbiente;
      Tupla4f colorDifuso;
      Tupla4f colorEspecular;

      GLenum componente;

   public:
      void activar();
      void desactivar();

      void setPosicion(Tupla4f p);
      void setColorAmbiente(Tupla4f cA);
      void setId(GLenum i);
      void setColorEspecular(Tupla4f cE);
      void setColorDifuso(Tupla4f cD);

      Tupla4f getPosicion();
      Tupla4f getColorAmbiente();
      GLenum getId();
      Tupla4f getColorEspecular();
      Tupla4f getColorDifuso();

      

     
  
 
	
} ;


#endif
