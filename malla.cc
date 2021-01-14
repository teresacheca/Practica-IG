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

Malla3D::~Malla3D(){
  material->~Material();
  textura->~Textura();
  v.clear();
  f.clear();
  c.clear();
  nv.clear();
  pares.clear();
  impares.clear();
  ct.clear();
  color.clear();
  color_par.clear();
  color_impar.clear();

}

void Malla3D::setMaterial(Material *mat){
   material= mat;
}

// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato(int size)
{
  // visualizar la malla usando glDrawElements,
 

   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);

   glVertexPointer(3, GL_FLOAT, 0, v.data());
   //glColorPointer(3, GL_FLOAT,0 , color.data());
 
  
   if(glIsEnabled(GL_LIGHTING)){
      normales();
      glNormalPointer(GL_FLOAT, 0, this->nv.data());
   }


   if(glIsEnabled(GL_TEXTURE_2D)){
      texturas();
         glTexCoordPointer(2,GL_FLOAT,0, ct.data());      
   }
   
      

   if(ajedrez){
      construirAjedrez();
  
      glColorPointer(3, GL_FLOAT, 0, color_par.data());
      glDrawElements(GL_TRIANGLES, pares.size()*3, GL_UNSIGNED_INT, pares.data());

      glColorPointer(3, GL_FLOAT, 0, color_impar.data());
      glDrawElements(GL_TRIANGLES, impares.size()*3, GL_UNSIGNED_INT, impares.data());
  
   }else{ 
     
      glColorPointer(3, GL_FLOAT, 0, color.data()); 
      glDrawElements(GL_TRIANGLES, size*3, GL_UNSIGNED_INT, f.data());  
   }

   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_NORMAL_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
  // glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido(GLuint vbo_caras, GLuint vbo_colores, int size)
{
   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
   // completar (práctica 1)
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);


    //VÉRTICES
    if(id_vbo_ver==0){
      // si id_vbo_ver es 0, entendemos que los demás también son 0
      
      //VERTICES
      id_vbo_ver= CrearVBO ( GL_ARRAY_BUFFER,  sizeof(Tupla3f)*v.size() , v.data() );
      
      //TRIANGULOS
      id_vbo_tri= CrearVBO ( GL_ELEMENT_ARRAY_BUFFER, sizeof(Tupla3i)*f.size()  , f.data() );
      
      //NORMALES
      id_vbo_normales = CrearVBO(GL_ARRAY_BUFFER, sizeof(Tupla3f)*nv.size(), nv.data());
      
      //COLORES
      id_vbo_color= CrearVBO ( GL_ARRAY_BUFFER, sizeof(Tupla3i)*color.size()  , color.data() );

      //AJEDREZ
      id_vbo_pares= CrearVBO ( GL_ARRAY_BUFFER, sizeof(Tupla3i)*pares.size()  , pares.data() );
      id_vbo_color_par= CrearVBO ( GL_ARRAY_BUFFER, sizeof(Tupla3i)*color_par.size()  , color_par.data() );
         
      id_vbo_impares= CrearVBO ( GL_ARRAY_BUFFER, sizeof(Tupla3i)*impares.size()  , impares.data() );
      id_vbo_color_impar= CrearVBO ( GL_ARRAY_BUFFER, sizeof(Tupla3i)*color_impar.size()  , color_impar.data() );
   
      //TEXTURA
      id_vbo_textura = CrearVBO(GL_ARRAY_BUFFER, sizeof(Tupla2f)*ct.size(), ct.data());
      
   }
   if(vbo_caras==0 && !ajedrez){
      vbo_caras=id_vbo_tri;
      vbo_colores = id_vbo_color;
   }else if(vbo_caras && ajedrez){
      vbo_caras = id_vbo_pares;
      vbo_colores = id_vbo_color_par;
   }

      glBindBuffer ( GL_ARRAY_BUFFER , id_vbo_ver );  
      glVertexPointer ( 3 , GL_FLOAT , 0 , 0 );
     
      glBindBuffer ( GL_ARRAY_BUFFER , 0 );

   if(glIsEnabled(GL_LIGHTING)){
      normales();
      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_normales);
      glNormalPointer(GL_FLOAT, 0, 0);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
   }
    
   if(glIsEnabled(GL_TEXTURE_2D)){
      texturas();
      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_textura);
      glTexCoordPointer(2,GL_FLOAT,0,0);  
      glBindBuffer(GL_ARRAY_BUFFER, 0);
   }

   glBindBuffer(GL_ARRAY_BUFFER, vbo_colores);
   glColorPointer(3, GL_FLOAT, 0, 0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_caras);
   glDrawElements(GL_TRIANGLES, size*3, GL_UNSIGNED_INT, 0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
   
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
  

   const std::vector<Tupla3f>& Malla3D::getVertices(){
      
     return this->v; 
   }


   void Malla3D::setCaras(const std::vector<Tupla3i>& aux){
      this->f.resize(aux.size());
      for(int i=0; i<aux.size(); i++){
         this->f[i]=aux[i];
      }
   }


//MODO AJEDREZ

void Malla3D::construirAjedrez(){
   if(pares.size() != 0)
      return;

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


const std::vector<Tupla3i>& Malla3D::getCaras(){
   return f;
}

// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(char m, int numero_caras)
{ 
   construirAjedrez();

   material->aplicar();
   
   switch (m)
   {
      case 'I':
         draw_ModoInmediato(numero_caras);
      break;
      case 'D':
         if(ajedrez) {
            draw_ModoDiferido(id_vbo_pares, id_vbo_color_par, pares.size());
            draw_ModoDiferido(id_vbo_impares, id_vbo_color_impar, impares.size());
         } else {
            draw_ModoDiferido(id_vbo_tri, id_vbo_color, numero_caras);
         }
      break;
   }
}


void Malla3D::calcular_normales(){

   //Primero, calculamos las normales de la caras
   Tupla3i cara;
   Tupla3f p,q,r, a, b,m;
   
    nv.resize(v.size(), Tupla3f(0, 0, 0));

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
      //nv[cara[0]] es una tupla, le estamos sumando m que también es otra tupla
      nv[cara[0]] =  nv[cara[0]] + m;
      nv[cara[1]] =  nv[cara[1]] + m;
      nv[cara[2]] =  nv[cara[2]] + m;


   }
 //Calculamos el vector normalizado
   for(int i=0; i<nv.size(); i++){
      nv[i] = nv[i].normalized();
   }
}

// ↓ Lo más inline que existe ↓
 void Malla3D::setTextura(Textura *tex){
    textura= tex;
 }

  

void Malla3D::normales(){
   glEnableClientState(GL_NORMAL_ARRAY);
      if(nv.size()==0){
         calcular_normales();
         //aplicar material  
          
      }
      material->aplicar();

}

void Malla3D::texturas(){
   textura->activa();
   glEnableClientState(GL_TEXTURE_COORD_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
}
