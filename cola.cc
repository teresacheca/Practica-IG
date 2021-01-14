#include "aux.h"
#include "cola.h"



Cola::Cola(){
    
   Esfera * e = new Esfera(30,30,1);
   Semiesfera * s = new Semiesfera(30,30,1);
   Cono * co = new Cono(30,30,1,1);
   Cilindro * ci =  new Cilindro(30,30,1,1);

   esfera = new ObjRevolucion(e->p, e->n_instancias, e->t_sup, e->t_inf);
   semiesfera = new ObjRevolucion(s->p, s->n_instancias, s->t_sup, s->t_inf);
   cono = new ObjRevolucion(co->p, co->n_instancias, co->t_sup, co->t_inf);
   cilindro = new ObjRevolucion(ci->p, ci->n_instancias, ci->t_sup, ci->t_inf);

 
    textura = new Textura("elefante.jpg");
    semiesfera->setTextura(textura);
    esfera->setTextura(textura);
    cono->setTextura(textura);
    cilindro->setTextura(textura);
    
    cilindro->setColor(0.75,0.75,0.75);
    semiesfera->setColor(0.75,0.75,0.75);
    esfera->setColor(0.0,0.0,0.0);
    cono->setColor(0.0,0.0,0.0);


   Tupla4f tupla={0.0,0.75,0.75,0.75};
   Material * material =  new Material(tupla, tupla, tupla, 120.0);
   esfera->setMaterial(material);
   semiesfera->setMaterial(material);
   cono->setMaterial(material);
   cilindro->setMaterial(material);
    
}

void Cola::draw(){
  glPushMatrix();
      glRotatef(45,0,0,1);
      glTranslatef(0,-100,0);
      glPushMatrix();
         glScalef(5,40,5);
         cilindro->draw('I');
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,20,0);
         glScalef(5,5,5);
         semiesfera->draw('I');
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,-25,0);
         glScalef(5,5,5);
         esfera->draw('I');
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,-32,0);
         glRotatef(180,0,0,1);
         glScalef(5,10,5);
         cono->draw('I');
      glPopMatrix();
   glPopMatrix();

}
  
