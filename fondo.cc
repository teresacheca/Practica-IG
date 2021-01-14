#include "aux.h"
#include "fondo.h"


Fondo::Fondo(){
   lata= new Lata();
   pelota = new Pelota();
}
void Fondo::draw(){
   glPushMatrix();
      glPushMatrix();
         glTranslatef(-300,-100,0);
         lata->draw();
      glPopMatrix();
      glPushMatrix();
         glTranslatef(-500, -80, 0);
         pelota->draw();
   glPopMatrix();
}