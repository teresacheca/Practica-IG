// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: textura.h
//
//
// #############################################################################

#ifndef TEXTURA_H
#define TEXTURA_H

#include "aux.h"
#include "jpg_imagen.hpp"
#include "jpg_jinclude.h"
//#include "jpg_memsrc.hpp"
#include "jpg_readwrite.hpp"

class Textura
{

   
   private:
      GLuint textura_id=0;
      std::vector<unsigned char> data;
      int width, height;
      unsigned char* texel;
      bool inicializado=false;
      
      

   public:
      Textura(std::string archivo);
      void activa();
    
        
 
	
};


#endif
