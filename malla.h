// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"
#include "material.h"
#include "textura.h"



// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class Malla3D
{

  
  public:

    Malla3D();
    ~Malla3D();

    // dibuja el objeto en modo inmediato
    void draw_ModoInmediato(int size);

    // dibuja el objeto en modo diferido (usando VBOs)
    void draw_ModoDiferido(GLuint vbo_caras, GLuint vbo_colores, int size);

    // función que redibuja el objeto
    // está función llama a 'draw_ModoInmediato' (modo inmediato)
    // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
    virtual void draw(char m, int numero_caras) ;


    GLuint CrearVBO ( GLuint tipo_vbo , GLuint tamanio_bytes , GLvoid * puntero_ram );

    void setModoAjedrez(bool a);
    void setColor(Tupla3f &c);
    void setColor(float _r, float _g, float _b);
    void setColorVertice(int indice, float a, float b, float c);
    inline void setVertices(const std::vector<Tupla3f>& aux) { v = aux; }

    void setCaras(const std::vector<Tupla3i>& aux);
    const std::vector<Tupla3i>& getCaras();
    const std::vector<Tupla3f>& getVertices();  // <- Si se va a cambiar, referencia normal
    void construirAjedrez();


    void setMaterial(Material *mat);
    void setTextura(Textura *tex);

    void calcular_textura();

    void normales();
    void texturas();

  
    Material *  material=nullptr;

    Textura * textura=nullptr;

  


  protected:

    void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)

    
    std::vector<Tupla3f> v ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
    std::vector<Tupla3i> f ; // una terna de 3 enteros por cada cara o triángulo
    std::vector<Tupla4f> c ; 
    std::vector<Tupla3f> nv ; // una terna de 3 enteros por cada cara o triángulo

    std::vector<Tupla3i> pares, impares; // vectores de tuplas para el modo ajedrez

    std::vector<Tupla2f> ct;    //tabla de coordenadas de textura
        
    GLuint id_vbo_ver=0;
    GLuint id_vbo_tri=0;
    GLuint id_vbo_color=0;
    GLuint id_vbo_pares=0;
    GLuint id_vbo_impares=0;
    GLuint id_vbo_color_par=0;
    GLuint id_vbo_color_impar=0;
    GLuint id_vbo_normales=0;
    GLuint id_vbo_textura=0;
    std::vector<Tupla3f> color;
    std::vector<Tupla3f> color_par;
    std::vector<Tupla3f> color_impar;
    bool ajedrez=false; 
    
    float r=0.2, g=0.9, b=0.95;
   

    
	
} ;


#endif
