#include "aux.h"
#include "fondo.h"



Fondo::Fondo(){
   lata= new Lata();
   pelota = new Pelota();
   suelo = new Suelo();
   horizonte = new Horizonte();
}
void Fondo::draw(){
   glPushMatrix();
      glPushMatrix();
         glTranslatef(-300,-70,0);
         lata->draw();
      glPopMatrix();
      glPushMatrix();
         glTranslatef(-500, -40, 0);
         pelota->draw();
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,-120,0);
         suelo->draw();
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,0,-1000);
         horizonte->draw();
      glPopMatrix();
   glPopMatrix();
}