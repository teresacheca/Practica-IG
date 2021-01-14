#include "aux.h"
#include "textura.h"


using namespace std;
// *****************************************************************************
//
// Clase Textura
//
// *****************************************************************************

  Textura::Textura(std::string archivo){
      jpg::Imagen * pimg = NULL;
      pimg= new jpg::Imagen(archivo);
      width = pimg->tamX();
      height = pimg-> tamY();

      texel = pimg->leerPixels();

     
  }

Textura::~Textura(){
    data.clear();
}
    
  void Textura::activa(){
     // glEnable(GL_TEXTURE_2D);
    
    if(textura_id==0){ 
        glGenTextures(1, &textura_id);
        glBindTexture(GL_TEXTURE_2D, textura_id);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, texel);
    }
    glBindTexture(GL_TEXTURE_2D, textura_id);
  
  }
