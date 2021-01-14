#include "aux.h"
#include "objrevolucion.h"
#include "ply_reader.h"
#include <math.h>

using namespace std;


// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::~ObjRevolucion(){
   p.clear();
   c.clear();
}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
   // completar ......(práctica 2)
   std::vector<Tupla3f>perfil;
   ply::read_vertices(archivo, perfil);
   crear(perfil, num_instancias, tapa_sup, tapa_inf);
  
   
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> perfil, int num_instancias, bool tapa_sup, bool tapa_inf) {
   crear(perfil, num_instancias, tapa_sup, tapa_inf);

}



void ObjRevolucion::crear(std::vector<Tupla3f>perfil, int num_instancias, bool tapa_sup, bool tapa_inf){
 bool conTapa=false;
   if(tapa_sup||tapa_inf){
      conTapa=true;
   }

   n_instancias=num_instancias;
   
   n_ver=perfil.size();

   if(p.size()==0){

      crearMalla(perfil, num_instancias, conTapa);
 
      //this->c_sinTapas = c;
      
      num_caras_sinTapas=c.size();
      

      aniadirTapas(tapa_inf, tapa_sup);

      float a = 0.0005*p.size();
      float b = 0.0005*p.size();
      float d = 0.001*p.size();

      setColorMaterial({a,d,b,0});

      
      material =  new Material(colorMaterial, colorMaterial, colorMaterial, 120.0);
      
      num_caras_conTapas = c.size();
     

      setCaras(c);

      setColor(0.2, 0.9, 0.95);
   }
   

 
}

 void ObjRevolucion::setColorMaterial(Tupla4f c){
    this->colorMaterial=c; 
 }

   Tupla4f ObjRevolucion::getColorMaterial(){
      return this->colorMaterial;
   }

bool ObjRevolucion::esUnPolo(Tupla3f polo){
   bool esPolo=false;
   if(polo[0]< abs(epsilon) && polo[2]< abs(epsilon)){
      esPolo=true;
   }
   return esPolo;
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, const bool conTapas) { 

   std::vector<Tupla3f> vertices;
   vertices=perfil_original;
   Tupla3f polo_sur, polo_norte;
  

   polo_sur= vertices[0];
   polo_norte=vertices[vertices.size()-1];

   if(conTapas){

      if(esUnPolo(polo_sur)){
         polo_sur=vertices[0];
         vertices.erase(vertices.begin());
         sur=true;
        
      }else{
         Tupla3f aux= vertices[0];
         polo_sur={0, aux[1], 0};
         sur=false;

      }
     
      if(esUnPolo(polo_norte)){
         polo_norte=vertices[vertices.size()-1];
         vertices.pop_back();
         norte=true;

      }else{
         Tupla3f aux= vertices[vertices.size()-1];
         polo_norte={0, aux[1], 0};
         norte=false;
      }
   }

   n_ver = vertices.size();
   coordTextura();
   int num_vertices=vertices.size();
   
   p.clear();  
   p.resize(num_instancias*num_vertices);
   
   int contador =0;
   //Tabla de vertices 
   Tupla3f aux;
   for(int i=0; i<num_instancias; i++){
      for(int j=0; j<num_vertices; j++){
         aux=vertices[j];             
         aux[0]*=cos((2*M_PI/num_instancias)*i);    //rotamos la variable del eje y
         aux[2]*=sin((2*M_PI/num_instancias)*i);
      
         p[contador]=aux;
         contador++;
      }
   }


   c.clear();

   //Tabla de triángulos
   contador=0;
   Tupla3i t;
   //i (instancias) columnas, j (vertices) filas
   for(int i=0; i<num_instancias; i++){
      for(int j=0; j<num_vertices-1; j++){

              t[0]=(num_vertices*i)+j;
         t[2]=(num_vertices*((i+1)%num_instancias))+j;
         t[1]=(num_vertices*((i+1)%num_instancias))+(j+1);
         c.push_back(t);

         t[0]=(num_vertices*i)+j;
         t[2]=(num_vertices*((i+1)%num_instancias))+(j+1);
         t[1]=(num_vertices*i)+(j+1);
         c.push_back(t);


      }
   }

   if(conTapas){
         p.push_back(polo_sur); 
         p.push_back(polo_norte);
   }
 


}

//Para ponerle y quitarle las tapas al objeto
 void ObjRevolucion::ponerTapas(bool tapas){
    this->tapas = tapas;
 }


 void ObjRevolucion::aniadirTapas(bool tapa_inf, bool tapa_sup){

   int aux;
   Tupla3i t;
  

   setVertices(p);

   if(tapa_inf){
     
      aux=(p.size()-2);       //polo sur
      for(int i=0; i<=n_instancias; i++){
         t[0]=aux;
         t[1]=(i*(n_ver));
         t[2]=(((i+1)%n_instancias)*(n_ver));

         c.push_back(t);

      }
      
   }


   if(tapa_sup){
      aux=(p.size()-1);      //polo norte
       for(int i=0; i<n_instancias; i++){
         t[0]=aux;
         t[2]=(i*n_ver)+(n_ver-1);
         t[1]=(((i+1)%n_instancias)*n_ver)+(n_ver-1);
       
         c.push_back(t);
         
      }
      
   }

 }


void ObjRevolucion::coordTextura() {
   ct.resize(p.size());
    

   Tupla2f coordenada;
   float trozoX = 1.0/n_instancias;
   float trozoY = 1.0/n_ver;
 
   for(int i=0; i<n_instancias; i++){
      for(int j=0; j<n_ver; j++){
         coordenada={trozoX*i,trozoY*(n_ver-j)};
         ct.push_back(coordenada);
      }
   }
   
}

void ObjRevolucion::draw(char letra) {
   if(tapas) {
      Malla3D::draw(letra, num_caras_conTapas);
   } else {
      Malla3D::draw(letra, num_caras_sinTapas);
   }
}