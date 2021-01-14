#include "aux.h"
#include "pelota.h"

Pelota::Pelota(){
     
   Esfera * e = new Esfera(30,30,1);

   esfera = new ObjRevolucion(e->p, e->n_instancias, e->t_sup, e->t_inf);
 
   textura = new Textura("pelota.jpg");
   esfera->setTextura(textura);

   Tupla4f tupla={0.0,0.75,0.75,0.75};
   Material * material =  new Material(tupla, tupla, tupla, 120.0);
   esfera->setMaterial(material);
   esfera->setColor(0.0,1.0,0.5);

}

void Pelota::draw(){
   glPushMatrix();
      glScalef(80,80,80);
      esfera->draw('D');
   glPopMatrix();
}
