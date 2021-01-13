// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: material.h
//
//
// #############################################################################

#ifndef MATERIAL_H
#define MATERIAL_H

#include "aux.h"


class Material
{

   
   private:
      Tupla4f ambiente;
      Tupla4f especular;
      Tupla4f difuso;
      float brillo;
      

   public:
      Material(Tupla4f mdifuso, Tupla4f mespecular, Tupla4f mambiente, float brillo);

      void aplicar();

     /* Tupla4f getAmbiente();
      Tupla4f getEspecular();
      Tupla4f getDifuso();
      float getBrillo();

      void setAmbiente(Tupla4f am);
      void setEspecular(Tupla4f es);
      void setDifuso(Tupla4f di);
      void setBrillo(float b);*/
 
  
 
	
} ;


#endif
