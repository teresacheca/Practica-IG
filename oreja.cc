#include "aux.h"
#include "oreja.h"
#include "objrevolucion.h"

#include "malla.h"


Oreja::Oreja(){
    
   Semiesfera * s = new Semiesfera(30,30,1);
  
   semiesfera = new ObjRevolucion(s->p, s->n_instancias, s->t_sup, s->t_inf);
  
    textura = new Textura("oreja.jpg");
    semiesfera->setTextura(textura);
    
    semiesfera->setColor(1,0.9,0.9);

    Tupla4f tupla={0.0,0.75,0.75,0.75};
    Material * material =  new Material(tupla, tupla, tupla, 120.0);
    semiesfera->setMaterial(material);
    
}

void Oreja::draw(){
    glPushMatrix();
      glPushMatrix();
         glRotatef(180,0,0,1);
         glScalef(30,70,1);
         semiesfera->draw('I');
      glPopMatrix();
      glPushMatrix();
         glScalef(30,30,1);
         semiesfera->draw('I');
      glPopMatrix();
   glPopMatrix();
}
  
