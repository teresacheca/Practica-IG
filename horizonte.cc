#include "aux.h"
#include "horizonte.h"

Horizonte::Horizonte(){
     
   cubo = new Cubo();
   caseta = new Cubo();
   textura = new Textura("horizonte.jpg");
   t_caseta = new Textura("caseta.jpg");
   cubo->setTextura(textura);
   caseta->setTextura(t_caseta);

   Tupla4f tupla={0.0,0.75,0.75,0.75};
   Material * material =  new Material(tupla, tupla, tupla, 120.0);
   cubo->setMaterial(material);
   cubo->setColor(0.2,0.9,0.9);

   caseta->setMaterial(material);
   caseta->setColor(0.2,0.9,0.9);


}

void Horizonte::draw(){
   glPushMatrix();
      glPushMatrix();
         glScalef(1000, 1000,0.1);
         cubo->draw('D', cubo->getCaras().size());
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0, 1800,100);
         glScalef(40,40,0.1);
         caseta->draw('D', caseta->getCaras().size());
      glPopMatrix();
   glPopMatrix();
}
