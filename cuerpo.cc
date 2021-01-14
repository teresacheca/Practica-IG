#include "aux.h"
#include "cuerpo.h"


Cuerpo::Cuerpo(){
     Esfera * e = new Esfera(30,30,1);
     tronco = new ObjRevolucion(e->p, e->n_instancias, e->t_sup, e->t_inf);

     pata = new Pata();
     cola = new Cola();

    textura = new Textura("elefante.jpg");
    tronco->setColor(0.6,0.6,0.6);
    tronco->setTextura(textura);

    

   Tupla4f tupla={0.0,0.75,0.75,0.75};
   Material * material =  new Material(tupla, tupla, tupla, 120.0);
   tronco->setMaterial(material);
  
}

void Cuerpo::draw(){
    glPushMatrix();
         //TRONCO
        glPushMatrix();
            glScalef(200,100,100);
            tronco->draw('I');
        glPopMatrix();
      //COLA
        glPushMatrix();
            //grados de libertad
            glTranslatef(sin((45*M_PI/180))*180, cos((45*M_PI/180))*120,0);
            cola->draw();
        glPopMatrix();
      //PATAS
     
        glPushMatrix();
            glTranslatef(0,-25,0);
            glTranslatef(0,-sin((45*M_PI/180))*100,0);
            
            //IZQUIERDA
            glPushMatrix();
                glTranslatef(0,0, cos((45*M_PI/180))*100);
                glPushMatrix();   
                    //pata izquierda delantera
                    glTranslatef(-sin((45*M_PI/180))*100,0,0);
                   
                    if(agacha){
                        glRotatef(-90,0,0,1);
                    }              
                    giroPatasIzquierdas();  
                    pata->draw();
                glPopMatrix();
                    glPushMatrix();
                    //Pata izquierda trasera
                    glTranslatef(sin((45*M_PI/180))*100,0,0);
                  
                    if(agacha){
                        glRotatef(-90,0,0,1);
                    }   
                    giroPatasIzquierdas();
                    pata->draw();
                glPopMatrix();
            glPopMatrix();
            //DERECHA
            glPushMatrix();
                glTranslatef(0,0, -cos((45*M_PI/180))*100);
                    glPushMatrix();
                    //Pata derecha delantera   
                    glTranslatef(-sin((45*M_PI/180))*100,0,0);
                   
                    if(agacha){
                        glRotatef(-90,0,0,1);
                    }   
                    giroPatasDerechas();
                    pata->draw();
                    glPopMatrix();
                glPushMatrix();
                    //Pata derecha trasera
                    glTranslatef(sin((45*M_PI/180))*100,0,0);
                   
                    if(agacha){
                        glRotatef(-90,0,0,1);
                    }   
                    giroPatasDerechas();
                    pata->draw();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
         
 
}

void Cuerpo::giroPatasDerechas(){
      float giro = giroPatas;
       if(giro <= 60 && giro>=-60){
         glRotatef(giro,0,0,1);
      }else{
         giroPatas=0;
      }
   }

   void Cuerpo::giroPatasIzquierdas(){
      float giro = -giroPatas;
       if(giro <= 60 && giro>=-60){
         glRotatef(giro,0,0,1);
      }else{
         giroPatas=0;
      }
   }

	void Cuerpo::setGiroPatas(float valor){
        giroPatas+=valor;
     }

     void Cuerpo::setAgacharse(bool a){
         agacha=a;
     }

     float Cuerpo::getGiroPatas(){
         return giroPatas;
     }