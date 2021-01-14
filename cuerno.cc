#include "aux.h"
#include "cuerno.h"


Cuerno::Cuerno(){

   
    Semiesfera * s = new Semiesfera(30,30,1);
    Cilindro * ci =  new Cilindro(30,30,1,1);

    semiesfera = new ObjRevolucion(s->p, s->n_instancias, s->t_sup, s->t_inf);
    cilindro = new ObjRevolucion(ci->p, ci->n_instancias, ci->t_sup, ci->t_inf);
    
    
    textura =  new Textura("marfil.jpg");
    semiesfera->setTextura(textura);
    cilindro->setTextura(textura);
    
    semiesfera->setColor(0.9,0.9,0.9);
    cilindro->setColor(0.9,0.9,0.9);

    Tupla4f tupla={0.0,0.75,0.75,0.75};
    Material * material =  new Material(tupla, tupla, tupla, 120.0);
    semiesfera->setMaterial(material);
    cilindro->setMaterial(material);

}

void Cuerno::draw(){
    glPushMatrix();
        glPushMatrix();
            glTranslatef(0,-50,0);
            glRotatef(180,0,0,1);
            glScalef(5,5,5);
            semiesfera->draw('I');
        glPopMatrix();
        glPushMatrix();
            glScalef(5,100,5);
            cilindro->draw('I');
        glPopMatrix();
    glPopMatrix();
}