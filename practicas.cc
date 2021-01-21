//**************************************************************************
// Prácticas
//
// F.J. melero
//
// GPL
//**************************************************************************


#include "aux.h" // includes de OpenGL, windows, y librería std de C++
#include "escena.h"
#include <unistd.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
// variable que contiene un puntero a la escena
Escena *escena = nullptr ;


//***************************************************************************
// Funcion principal que redibuja la escena
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void draw_scene(void)
{
	if ( escena != nullptr )
      escena->dibujar();
	glutSwapBuffers();
}

//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size( int newWidth, int newHeight )
{
	if ( escena != nullptr )
      escena->redimensionar(newWidth,newHeight);
	glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys( unsigned char tecla, int x, int y )
{
	int salir = 0;

   if ( escena!= nullptr )
      salir = escena->teclaPulsada( tecla, x, y );

	if ( salir )   {
		delete escena;
        escena = nullptr ;
		exit(0);
	}
   else
		glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys( int tecla, int x, int y )
{
	if (escena!=NULL)
		escena->teclaEspecial( tecla, x, y );
	glutPostRedisplay();
}


/*-------------------------------ANIMACION --------------------------------*/

void funcion_idle(){
   if(escena!=0)
      escena->animarModeloJerarquico();
   glutPostRedisplay();
}

/*-------------------------------MOVIMIENTO DEL RATON --------------------------------*/

void ratonMovido(int x, int y){
   if(escena->getMoverse()){
      cout << "X " << x << ", Y " << y << endl; 
      escena->ratonMovido(x, y);
   }
}


void clickRaton(int boton, int estado, int x, int y){
    if(boton == GLUT_LEFT_BUTTON){
      if(estado == GLUT_DOWN){
       //  cout << "X " << x << ", Y " << y << endl; 
         escena->setMoverse(true);
         ratonMovido(x, y);
         
      }else{
         escena->setMoverse(false);
      }
   }else if(boton == GLUT_RIGHT_BUTTON){
         if(estado == GLUT_DOWN){
            cout << "Objeto seleccionado "  << endl;
            escena->objetoSeleccionado(x, y);
         }
      }
   glutPostRedisplay();  
}

void mouseWheel(int button, int dir, int x, int y){
   cout << "dir " << dir << endl;
      if(dir>0){
         escena->zoom(true);
         cout << "dir " << dir << endl;
      }else{
         escena->zoom(false);
         cout << "dir " << dir << endl;
      }
  
}



//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main( int argc, char **argv )
{
   using namespace std ;

   // crear la escena (un puntero a la misma)
   escena = new Escena();

   // Incialización de GLUT

   // se llama a la inicialización de glut
   glutInit( &argc, argv );

   // se indica las caracteristicas que se desean para la visualización con OpenGL
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

   // variables que determninan la posicion y tamaño de la ventana X
   const int UI_window_pos_x  = 50,
             UI_window_pos_y  = 50,
             UI_window_width  = 500,
             UI_window_height = 500;

   // posicion de la esquina inferior izquierdad de la ventana
   glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

   // tamaño de la ventana (ancho y alto)
   glutInitWindowSize(UI_window_width,UI_window_height);

   // llamada para crear la ventana, indicando el titulo
   // SUSTITUIR EL NOMBRE DEL ALUMNO
   glutCreateWindow("Practicas IG: TERESA CHECA");

   // asignación de la funcion llamada "dibujar" al evento de dibujo
   glutDisplayFunc( draw_scene );

   // asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
   glutReshapeFunc( change_window_size );
   cout << "Opciones: " << endl;
   cout << " O: seleccion de objeto \n V: seleccion de modo de visualizacion \n D: seleccion de modo de dibujado \n C: seleccion de camaras \n";
   
   // asignación de la funcion llamada "tecla_normal" al evento correspondiente
   glutKeyboardFunc( normal_keys );

   // asignación de la funcion llamada "tecla_Especial" al evento correspondiente
   glutSpecialFunc( special_keys );

   //ANIMACION
   glutIdleFunc(funcion_idle);

   // inicialización de librería GLEW (solo en Linux)
   #ifdef LINUX
   const GLenum codigoError = glewInit();

   if ( codigoError != GLEW_OK ) // comprobar posibles errores
   {
      cout << "Imposible inicializar ’GLEW’, mensaje recibido: "
             << glewGetErrorString(codigoError) << endl ;
      exit(1) ;
   }
   #endif

   // funcion de inicialización de la escena (necesita que esté la ventana creada)
   escena->inicializar( UI_window_width, UI_window_height );

   glutMouseFunc(clickRaton);
   glutMotionFunc(ratonMovido);
   glutMouseWheelFunc(mouseWheel);


   // ejecutar del bucle de eventos
   glutMainLoop();

   return 0;
}
