// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: elefante.h

//
// #############################################################################

#ifndef ELEFANTE_H_INCLUDED
#define ELEFANTE_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "objrevolucion.h"
#include "esfera.h"
#include "semiesfera.h"
#include "cilindro.h"
#include "cono.h"
#include "textura.h"
#include "cabeza.h"
#include "cuerpo.h"
#include "material.h"

// *****************************************************************************
//
// clase elefante
//
// *****************************************************************************

// *****************************************************************************


class Elefante: public Malla3D
{
   public:
      Elefante();
      void draw();
    /*  void cuerno();
      void trompa();
      void ojo();
      void oreja();
      void cola();
      void pata();
      void cuerpo();
      void tronco();
      void cabeza();*/
    
      Cabeza * cabeza;
      Cuerpo * cuerpo;

    /*  Malla3D dibujaCuerno();
      ObjRevolucion * esfera;
      ObjRevolucion * semiesfera;
      ObjRevolucion * cono;
      ObjRevolucion * cilindro;*/

      float giroCabezaX;
      float giroCabezaY;
      float giroTrompaX;
      float giroTrompaZ;
      float giroPatas;
      float giroTrompaPequeniaX;
      float giroTrompaPequeniaZ;
      bool agacha;

      float cabezaXmax;
      float cabezaYmax;
      float trompaXMax;
      float trompaZMax;
      float patasMax;
      float trompitaXMax;
      float trompitaYMax;

      Textura * piel;
      Textura * marfil;
      Textura * ojos;
      Textura * orejas;

     

      virtual void modificaGiroTrompaX();
      virtual void modificaGiroTrompaZ();
      void modificaGiroCabezaX();
      void modificaGiroCabezaY();
      virtual void modificaGiroTrompaPequeniaX();
      virtual void modificaGiroTrompaPequeniaZ();
      virtual void giroPatasDerechas();   
      virtual void giroPatasIzquierdas();
      void agacharse();
  

     virtual void setGiroPatas(float valor);
     virtual void setGiroTrompaX(float valor);
     virtual void setGiroTrompaZ(float valor);
     void setGiroCabezaX(float valor);
     void setGiroCabezaY(float valor);
     virtual void setGiroTrompaPequeniaX(float valor);
     virtual void setGiroTrompaPequeniaZ(float valor);
     virtual void setAgacharse(bool valor);
     bool getAgacharse();

     virtual float getGiroPatas();
     virtual float getGiroTrompaX();
     virtual float getGiroTrompaZ();
     float getGiroCabezaX();
     float getGiroCabezaY();
     virtual float getGiroTrompaPequeniaX();
     virtual float getGiroTrompaPequeniaZ();

     float getPatasMax();
     float getTrompaXMax();
     float getTrompaZMax();
     float getCabezaXMax();
     float getCabezaYMax();
     float getTrompaPequeniaXMax();
     float getTrompaPequeniaZMax();

} ;




#endif
