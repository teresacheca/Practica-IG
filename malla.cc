#include "aux.h"
#include "malla.h"
#include "ply_reader.h"
#include <math.h>
#include "material.h"

using namespace std;
// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

Malla3D::Malla3D(){

}


void Malla3D::setMaterial(Material *mat){
   material= mat;
}

// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato()
{
  // visualizar la malla usando glDrawElements,


   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);

   glVertexPointer(3, GL_FLOAT, 0, v.data());
   //glColorPointer(3, GL_FLOAT,0 , color.data());
 
  
   if(glIsEnabled(GL_LIGHTING)){
      
      glEnableClientState(GL_NORMAL_ARRAY);
      if(nv.size()==0){
         calcular_normales();
         //aplicar material  
          
      }
      material->aplicar();
      glNormalPointer(GL_FLOAT, 0, this->nv.data());
   }


      if(glIsEnabled(GL_TEXTURE_2D)){
      
         textura->activa();
        // calcular_textura();
         //setColor(1.0,1.0,1.0);
          glDisableClientState(GL_COLOR_ARRAY);
         glEnableClientState(GL_TEXTURE_COORD_ARRAY);
         glTexCoordPointer(2,GL_FLOAT,0, ct.data());      
     }

   if(ajedrez){
      dibujarAjedrez();
  
      glColorPointer(3, GL_FLOAT, 0, color_par.data());
      glDrawElements(GL_TRIANGLES, pares.size()*3, GL_UNSIGNED_INT, pares.data());

      glColorPointer(3, GL_FLOAT, 0, color_impar.data());
      glDrawElements(GL_TRIANGLES, impares.size()*3, GL_UNSIGNED_INT, impares.data());
  
   }else{ 
     
      glColorPointer(3, GL_FLOAT, 0, color.data());
      glDrawElements(GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, f.data());  
   }

   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_NORMAL_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
  // glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido()
{
   using namespace std;
   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
   // completar (práctica 1)
  glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);

    //VÉRTICES
    if(id_vbo_ver==0){
       id_vbo_ver= CrearVBO ( GL_ARRAY_BUFFER,  sizeof(Tupla3f)*v.size() , v.data() );
    }
      glBindBuffer ( GL_ARRAY_BUFFER , id_vbo_ver );  
      glVertexPointer ( 3 , GL_FLOAT , 0 , 0 );
     
      glBindBuffer ( GL_ARRAY_BUFFER , 0 );

   if(glIsEnabled(GL_LIGHTING)){
      
      glEnableClientState(GL_NORMAL_ARRAY);
      if(nv.size()==0){
         calcular_normales();
      }
     
      glNormalPointer(GL_FLOAT, 0, this->nv.data());
   }
    
  
   
   //TRIÁNGULOS
   if(id_vbo_tri==0){
      id_vbo_tri= CrearVBO ( GL_ELEMENT_ARRAY_BUFFER, sizeof(Tupla3i)*f.size()  , f.data() );
   }
  

   //COLORES
   if(id_vbo_color==0){
      id_vbo_color= CrearVBO ( GL_ARRAY_BUFFER, sizeof(Tupla3i)*color.size()  , color.data() );
   }
   
   if(ajedrez){
        //AJEDREZ
      if(id_vbo_pares==0 && id_vbo_impares==0){
          dibujarAjedrez();

         
         id_vbo_pares= CrearVBO ( GL_ARRAY_BUFFER, sizeof(Tupla3i)*pares.size()  , pares.data() );
         
         id_vbo_impares= CrearVBO ( GL_ARRAY_BUFFER, sizeof(Tupla3i)*impares.size()  , impares.data() );
        
      
      }
    
      glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , id_vbo_pares );  
     
      
      glColorPointer(3, GL_FLOAT, 0, color_par.data());
      glDrawElements(GL_TRIANGLES, pares.size()*3, GL_UNSIGNED_INT, 0);

      glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , id_vbo_impares );  

      
      glColorPointer(3, GL_FLOAT, 0, color_impar.data());
      glDrawElements(GL_TRIANGLES, impares.size()*3, GL_UNSIGNED_INT, 0);

   }else{
     
      glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , id_vbo_tri );  
      glEnable(GL_CULL_FACE);

 
      glColorPointer(3, GL_FLOAT, 0, color.data());
      glDrawElements(GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, 0);
   }
   
  
  
   glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , 0 );
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
  

}

 GLuint Malla3D::CrearVBO ( GLuint tipo_vbo , GLuint tamanio_bytes , GLvoid * puntero_ram )
   {
      GLuint id_vbo ;
      glGenBuffers ( 1 , & id_vbo );
      glBindBuffer ( tipo_vbo , id_vbo );
      glBufferData ( tipo_vbo , tamanio_bytes , puntero_ram , GL_STATIC_DRAW );
      glBindBuffer ( tipo_vbo , 0 );
      return id_vbo ;
   }

   void Malla3D::setModoAjedrez(bool a){
      ajedrez=a;
   }

   void Malla3D::setColor(float _r, float _g, float _b){
      r=_r;
      g=_g;
      b=_b;
      color.clear();
      color.resize(v.size());
      for(int i=0; i<v.size(); i++){
         color[i]={r,g,b};
      }

      
   }

   void Malla3D::setColorVertice(int indice, float a, float b, float c){
      color[indice]={a,b,c};

   }

   void Malla3D::setVertices(std::vector<Tupla3f> aux){
      this->v.resize(aux.size());
      for(int i=0; i<aux.size(); i++){
         this->v[i]=aux[i];
        
      }
      
   }
  

   std::vector<Tupla3f> Malla3D::getVertices(){
      
     return this->v; 
   }


   void Malla3D::setCaras(std::vector<Tupla3i> aux){
      this->f.resize(aux.size());
      for(int i=0; i<aux.size(); i++){
         this->f[i]=aux[i];
      }
   }


//MODO AJEDREZ

void Malla3D::dibujarAjedrez(){
   using namespace std;
  Tupla3f c_impar, c_par;
  c_par = {1,0,0};
  c_impar = {0,1,0};
  
   for(int i=0; i<f.size(); i++){

      if(i%2==0){
         pares.push_back(f[i]);
         color_par.push_back(c_par);
         color_par.push_back(c_par);
         color_par.push_back(c_par);
        
      }else{
         impares.push_back(f[i]);
         color_impar.push_back(c_impar);
         color_impar.push_back(c_impar);
         color_impar.push_back(c_impar);
        
      }
          
   }


}


// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(int m)
{ 
   
   material->aplicar();
   if(m=='I'){
      draw_ModoInmediato();
   }else if(m=='D'){
      draw_ModoDiferido();
   }

}


void Malla3D::calcular_normales(){

   //Primero, calculamos las normales de la caras
   Tupla3i cara;
   Tupla3f p,q,r, a, b,m;
   
    nv.resize(v.size());

   for(int i=0; i<f.size(); i++){

      //Sacamos una cara
      cara=f[i];

      //Obtenemos los vertices que componen la cara
      p=v[cara[0]];
      q=v[cara[1]];
      r=v[cara[2]];

      //Para calcular la normal de la cara necesitamos calcular a y b
      //Calculamos el vector a; a=q-p
      a[0]=q[0]-p[0];
      a[1]=q[1]-p[1];
      a[2]=q[2]-p[2];

      //Calculamos el vector b; b=r-p
      b[0]=r[0]-p[0];
      b[1]=r[1]-p[1];
      b[2]=r[2]-p[2];

     
      //Calculamos m, haciendo el productor vectorial de a y b; m= a x b
      //Usamos cross para calcular el producto vectorial de a y b
      m = a.cross(b);
     

      //Lo añadimos al vector de normales
      nv[cara[0]] = nv[cara[0]] +  m;
      nv[cara[1]] = nv[cara[1]] +  m;
      nv[cara[2]] = nv[cara[2]] +  m;


   }
 //Calculamos el vector normalizado
   for(int i=0; i<nv.size(); i++){
      nv[i] = nv[i].normalized();
   }
}

 void Malla3D::setTextura(Textura *tex){
    textura= tex;
 }

  

/*void Malla3D::calcular_textura(){
   ct.resize(v.size());
    ct = {
       {0.0,1.0}, {0.5,1.0}, 
      {0.5,0.0}, {0.0,0.0},
       {0.5,1.0},  {1.0,1.0},
        {1.0,0.0},  {0.5,0.0}
    };
}*/

