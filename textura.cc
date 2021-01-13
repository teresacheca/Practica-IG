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

     
     /*  for(int i=0; i<width; i++){
          for(int j=0; j<height; j++){
             
                data.push_back(*(pimg->leerPixel(i, j)));
                data.push_back(*(pimg->leerPixel(i, j)+1));
                data.push_back(*(pimg->leerPixel(i, j)+2));
          }
      }*/
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
