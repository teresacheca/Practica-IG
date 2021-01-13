#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "tetraedro.h"
#include "objply.h"
#include "objrevolucion.h"
#include "cilindro.h"
#include "cono.h"
#include "esfera.h"
#include "luz.h"
#include "luzDireccional.h"
#include "luzPosicional.h"
#include "semiesfera.h"
#include "elefante.h"

using namespace std;

typedef enum {NADA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO, SIMULTANEOS, TAPAS, ILUMINACION, ELEFANTE, MOVER, GIRAR} menu;
class Escena
{

   private:

         

      // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)
            
            // variables que definen la posicion de la camara en coordenadas polares
         GLfloat Observer_distance;
         GLfloat Observer_angle_x;
         GLfloat Observer_angle_y;

         // variables que controlan la ventana y la transformacion de perspectiva
         GLfloat Width, Height, Front_plane, Back_plane;

         // Transformación de cámara
         void change_projection( const float ratio_xy );
         void change_observer();
         


         void clear_window();

         menu modoMenu=NADA;
         // Objetos de la escena
         Ejes ejes;
         Cubo * cubo = nullptr ; // es importante inicializarlo a 'nullptr'
         Tetraedro * tetraedro= nullptr ; // es importante inicializarlo a 'nullptr'
         char figura;
         int modo_dibujado;
         std::vector<Tupla3f> color;
         char visualizacion;

         //PRÁCTICA 2
         ObjPLY * objeto=nullptr;
         Cilindro * cilindro = nullptr;
         Cono * cono = nullptr;
         Esfera * esfera = nullptr;
         Semiesfera * semiesfera = nullptr;

         ObjRevolucion * objI = nullptr;
         ObjRevolucion * objC = nullptr;
         ObjRevolucion * objE = nullptr;

         ObjRevolucion * objS = nullptr;

         Elefante * elefante;

         bool tapas;
         char letra;

         bool ilumina;
         char angulo;

         char parte;
         int giro;
         void moverElefante();
         bool agachar;
         int cambioSentido;

         LuzDireccional * luz0;     //Luz direccional
     
         LuzPosicional * luz1;
         LuzPosicional * luz2;
         LuzPosicional * luz3;
         LuzPosicional * luz4;
         LuzPosicional * luz5;
         LuzPosicional * luz6;
         LuzPosicional * luz7;

         bool l0;
         bool l1;
         bool l2;
         bool l3;
         bool l4;
         bool l5;
         bool l6;
         bool l7;

         Tupla3f posicion;

         Textura * textura = nullptr;
         bool text;
         void habilitar_textura();
         
   public:

      Escena();
      void inicializar( int UI_window_width, int UI_window_height );
      void redimensionar( int newWidth, int newHeight ) ;

      // Dibujar
      void dibujar() ;

      // Interacción con la escena
      bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
      void teclaEspecial( int Tecla1, int x, int y );

      bool select_objeto(unsigned char tecla, int x, int y);
      void dibujar_objeto();
      void dibujar_simultaneos();
      bool modoAjedrez;
      int simultaneos;

      void cambio_color(float _r, float _g, float _b);
      void seleccion_visualizacion();

      void variosObjetos();

      void encenderLuces(bool encender);

      void luces(char id);
      void inicializaLuces();

      void animarModeloJerarquico();
	
};
#endif
