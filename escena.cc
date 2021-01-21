

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....
#include "objrevolucion.h"
#include "luz.h"
#include "luzDireccional.h"
#include <chrono>
#include <unistd.h>
//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************


/*-----------------------------------------CONSTRUCTOR---------------------------------------------*/
Escena::Escena()
{
    Front_plane       = 50.0;
    Back_plane        = 2000.0;
    Observer_distance = 4*Front_plane;
    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;

    ejes.changeAxisSize( 5000 );

   glEnable(GL_NORMALIZE);

   // crear los objetos de la escena
   //La figura por defecto que aparecerá es el cubo
   
   modo_dibujado=1;
   simultaneos=0;
   modoAjedrez=false;
   
   
   cubo= new Cubo();
   tetraedro = new Tetraedro();

   cilindro= new Cilindro(4, 30, 100, 10);

   cono = new Cono(6, 30, 100, 50);

   objeto = new ObjPLY( "plys/beethoven.ply");

   esfera = new Esfera(30, 30, 50);

   semiesfera = new Semiesfera(30, 30, 50);

   textura= new Textura("text-lata-1.jpg");
   cubo->setTextura(textura);
   tetraedro->setTextura(textura);
 

   tapas=true;

   letra='I';
   

   giro=0;
   parte=0;

   objI= new ObjRevolucion(cilindro->p, cilindro->n_instancias, cilindro->t_sup, cilindro->t_sup);
   objC = new ObjRevolucion(cono->p, cono->n_instancias, cono->t_sup, cono->t_sup);
   objE = new ObjRevolucion(esfera->p, esfera->n_instancias, esfera->t_sup, esfera->t_sup);

   objS = new ObjRevolucion(semiesfera->p, semiesfera->n_instancias, semiesfera->t_sup, semiesfera->t_sup);

   objI->setTextura(textura);
   objC->setTextura(textura);
   objE->setTextura(textura);
 
   ilumina = false;
   angulo = 'X';         //Lo inicializamos a una letra que dará error si no seleccionamos el angulo antes

   //cambio_color(0.2,0.9,0.95);
  
    /* cubo->setColor(0.2,0.9,0.95); 
  
      tetraedro->setColor(0.2,0.9,0.95); 
   
      objeto->setColor(0.2,0.9,0.95); 
   
      objI->setColor(0.2,0.9,0.95); 
  
      objC->setColor(0.2,0.9,0.95); 
  
      objE->setColor(0.2,0.9,0.95); */
   
   inicializaLuces();

   elefante = new Elefante();
   agachar=false;

   cambioSentido = 1;

 
   text=false;
   glDisable(GL_TEXTURE_2D);

   automatico = auto_cabeza = auto_trompa = auto_trompita = 1;

   //Práctica 6
   moverse=false;
   x = y = 0;
   camaraActiva = 0;
   camarasActivadas = false;
   objetoEncontrado = false;
   iniciarCamaras();
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer

	Width  = UI_window_width/10;
	Height = UI_window_height/10;

   change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );
}


void Escena::inicializaLuces(){
   const Tupla4f ambiente = {1.0,0.0,0.0,1.0}; 
   const Tupla4f especular = {1.0,1.0,0.0,1.0}; 
   const Tupla4f difuso = {0.0,0.0,1.0,1.0}; 

   // luzDireccional = new LuzDireccional(posicion);
   Tupla2f direccion = {0.0,0.0};
   luz0 = new LuzDireccional(direccion, GL_LIGHT0, ambiente, especular, difuso);

   posicion = {200,200,200}; 
   lucesPosicionales.push_back(new LuzPosicional(posicion, GL_LIGHT1, ambiente, especular, difuso));

   posicion = {500,500,-300};
   lucesPosicionales.push_back(new LuzPosicional(posicion, GL_LIGHT2, ambiente, especular, difuso));

   
   posicion = {300,-400,300};
   lucesPosicionales.push_back(new LuzPosicional(posicion, GL_LIGHT3, ambiente, especular, difuso));

  
   posicion = {-300,300,300};
   lucesPosicionales.push_back(new LuzPosicional(posicion, GL_LIGHT4, ambiente, especular, difuso));

  
   posicion = {200,-400,-500};
   lucesPosicionales.push_back(new LuzPosicional(posicion, GL_LIGHT5, ambiente, especular, difuso));

   
   posicion = {-500,-500,500};
   lucesPosicionales.push_back(new LuzPosicional(posicion, GL_LIGHT6, ambiente, especular, difuso));

   
   posicion = {-500,500,-500};
   lucesPosicionales.push_back(new LuzPosicional(posicion, GL_LIGHT7, ambiente, especular, difuso));

   l0=false;
  
   lucesPosicionales_activadas.clear();
   lucesPosicionales_activadas.resize(7);
   for(int i=0; i<7; i++){
      lucesPosicionales_activadas.push_back(false);
   }
}

/*-----------------------------------PRÁCTICA 6: INICIALIZAR CAMARAS-------------------------------*/
void Escena::iniciarCamaras(){
   camaras.resize(3);
   camaras[0] = new Camara({0.0, 100.0, 0.0}, {0.0, 0.0, 0.0}, {-1.0, -1.0, 0.0}, PERSPECTIVA, 1.0, -1.0, 1.0, 450.0, 1.0,1.0);
   camaras[1] = new Camara({0.0, -100.0, 200.0}, {0.0, 0.0, 0.0}, {1.0, 1.0, 0.0}, PERSPECTIVA, -1.0, 1.0, 1.0, 450.0, 1.0,1.0);
   camaras[2] = new Camara({0.0, 100.0, -200.0}, {0.0, 0.0, 0.0}, {-1.0, 1.0, 0.0}, ORTOGONAL, -1.0, 1.0, 0.5, 450.0, 1.0,1.0);
}

// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

/*--------------------------------------MÉTODO DIBUJA----------------------------------------------*/
void Escena::dibujar()
{  
   
   // COMPLETAR
    //   Dibujar los diferentes elementos de la escena
    // Habrá que tener en esta primera práctica una variable que indique qué objeto se ha de visualizar
    // y hacer 
   
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
   //glEnable(GL_CULL_FACE);
	change_observer();
   ejes.draw();
  

   glEnable(GL_NORMALIZE);

    
   encenderLuces(ilumina);
   glShadeModel(GL_SMOOTH);

   glPointSize(3);
    
   variosObjetos();
  
   
   if(simultaneos==0){
      seleccion_visualizacion();
      dibujar_objeto();
   }else{
      dibujar_simultaneos();
   }
   
}

/*--------------------------------------DIBUJAR OBJETOS--------------------------------------------*/

void Escena::dibujar_objeto(){
  
   if(modo_dibujado==1){
     letra='I';
   }else if (modo_dibujado==2){
     letra='D';
   }
   if(figura=='C'){
      cubo->setModoAjedrez(modoAjedrez);
      cubo->draw(letra, cubo->getCaras().size());
   }else if(figura=='T'){
      tetraedro->setModoAjedrez(modoAjedrez);
      tetraedro->draw(letra, tetraedro->getCaras().size());
   }else if(figura=='P'){
      objeto->setModoAjedrez(modoAjedrez);
      objeto->draw(letra, objeto->getCaras().size());
   }else if(figura=='I'){
      objI->setModoAjedrez(modoAjedrez);
      objI->ponerTapas(tapas);
      objI->draw(letra);
   }else if(figura=='O'){
      objC->setModoAjedrez(modoAjedrez);
      objC->ponerTapas(tapas);
      objC->draw(letra);
   }else if(figura=='E'){
      objE->setModoAjedrez(modoAjedrez);
      objE->ponerTapas(tapas);
      objE->draw(letra);
   }
   else if(figura=='L'){
      elefante->draw();
   }
}

void Escena::seleccion_visualizacion(){
   if(visualizacion=='P'){
      encenderLuces(ilumina);
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
   }else if (visualizacion=='L'){
      encenderLuces(ilumina);
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   }else if(visualizacion=='S' || visualizacion=='A'){
      encenderLuces(ilumina);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   }
}


void Escena::dibujar_simultaneos(){
   using namespace std;
   GLenum e1, e2, e3=0;

   if(simultaneos==1){
      //puntos y lineas
      e1=GL_POINT;
      e2=GL_LINE;
     
   }else if(simultaneos==2){
      //puntos y solido
      e1=GL_POINT;
      e2=GL_FILL;
      
   }else if(simultaneos==3){
      //lineas y solido
      e1=GL_LINE;
      e2=GL_FILL;
     
   }else if(simultaneos==4){
      // puntos, lineas y solido
      e1=GL_POINT;
      e2=GL_LINE;
      e3=GL_FILL;     
   }

      glPointSize(5);
      cambio_color(1.0,0.0,0.0);
      glPolygonMode(GL_FRONT_AND_BACK, e1);
      dibujar_objeto();
      cambio_color(0.0,0.0,1.0);
      glPolygonMode(GL_FRONT_AND_BACK, e2);
      dibujar_objeto();

   if(e3!=0){
      cambio_color(0.0,1.0,0.0);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      dibujar_objeto();

   }
}


void Escena::cambio_color(float _r, float _g, float _b){
   if(figura=='C'){
      cubo->setColor(_r,_g,_b);
   }else if(figura=='T'){
      tetraedro->setColor(_r,_g,_b);
   }else if(figura=='P'){
      objeto->setColor(_r,_g,_b);
   }else if(figura=='I'){
      objI->setColor(_r,_g,_b);
   }else if(figura=='O'){
      objC->setColor(_r,_g,_b);
   } else if(figura=='E'){
      objE->setColor(_r,_g,_b);
   } 
}

void Escena::variosObjetos(){
    //MOSTRAR VARIOS ELEMENTOS A LA VEZ EN LA ESCENA
    if(figura=='V'){
      glPushMatrix();
         glTranslatef(100, 0, 0);
         objE->draw('I');
      glPopMatrix();
      glPushMatrix();
         glTranslatef(-50, 0, 0);
         objC->draw('I');
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0, 50, 0);
         objI->draw('I');
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0, -200, 0);
         cubo->draw('I', cubo->getCaras().size());
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0, 0, 100);
         tetraedro->draw('I', tetraedro->getCaras().size());
      glPopMatrix();
      /*glPushMatrix();
         glTranslatef(0, 0, -100);
         objeto->draw('I');
      glPopMatrix();*/
    }
  
}
//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

/*-------------------------------------MENÚ DE TECLAS-----------------------------------------------*/
bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   
   cout << "Tecla pulsada: '" << tecla << "'" << endl;
   bool salir=false;
   /*-----------------------------------MENÚ INICIAL------------------------------------------------*/
   if (modoMenu==NADA){
      switch( toupper(tecla) )
       {
      case 'Q' :
         if (modoMenu!=NADA)
            modoMenu=NADA;            
         else {
            salir=true ;
         }
      break ;
      case 'O' :
         // ESTAMOS EN MODO SELECCION DE OBJETO
         modoMenu=SELOBJETO; 
         cout << "Seleccion de objeto \n";
         cout << "Opciones: \n C: Cubo \n T: Tetraedro \n P: Objeto PLY cargado \n I: Cilindro \n O: Cono \n E: Esfera \n V: Varios Objetos \n L: Elefante \n Q: Salir" << endl;
      break;
      case 'V' :
         // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
         modoMenu=SELVISUALIZACION;
         cout << "Seleccion del modo de visualizacion \n";
         cout << "Opciones: \n P: modo puntos \n L: modo Líneas \n S: modo Solido \n A: modo Ajedrez \n M: modo visualizacion simultanea \n I: Iluminacion \n T: Textura \n Q: Salir" << endl;
      break ;
      case 'D' :
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
         cout << "Seleccion del modo de dibujado\n";
         cout << "Opciones: \n 1: modo Inmediato \n 2: modo Diferido \n Q: Salir" << endl;
         modoMenu=SELDIBUJADO;
      break ;
      case 'C' :
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
         if(!camarasActivadas){
            cout << "Seleccion de camaras\n";
            cout << "Opciones: \n 1: perspectiva 1 \n 2: perspectiva 2 \n 3: Ortogonal \n Q: Salir" << endl;
            camarasActivadas = true;
            modoMenu=CAMARAS;
         }else{
            cout << "Desactivar camaras" << endl;
            camarasActivadas=false;
            modoMenu = NADA;
         }
         
      break ;
         // COMPLETAR con los diferentes opciones de teclado
            
      }
   }else if(modoMenu==SELOBJETO){
      /*--------------------------MENÚ SELECCIÓN DE OBJETO--------------------------------------*/
      switch(toupper(tecla)){
      case 'Q' :
         if (modoMenu!=NADA){
            cout << "Opciones: " << endl;
            cout << " O: seleccion de objeto \n V: seleccion de modo de visualizacion \n D: seleccion de modo de dibujado \n C: seleccion de camaras \n";
            modoMenu=NADA;   
         }else {
            salir=true ;
         }
      break ;
      case 'C' :
         
         cout << "Cubo" << endl;
         if(figura=='C'){
            figura=0;
         }else{
            color.resize(8);
            figura = 'C'; 
         }   
      break;
      case 'T' :
         cout<< "Tetraedro" << endl;
         if(figura=='T'){
            figura=0;
         }else{
            color.resize(4);
             figura = 'T';
         }
      break ;
      case 'P' :
         cout<< "Objeto PLY cargado" << endl;
         if(figura=='P'){
            figura=0;
         }else{
            
             figura = 'P';
         }
      break ;
      case 'I':
         cout << "Cilindro" << endl;
         if(figura=='I'){
            figura=0;
         }else{
            figura='I';
         }
         cout<< "Con tapas \n 1: Si \n 2: No  \n Q: Salir \n" ;
         modoMenu = TAPAS;
      break;
       case 'O':
         cout << "Cono" << endl;
         if(figura=='O'){
            figura=0;
         }else{
            figura='O';
         }
          cout<< "Con tapas \n 1: Si \n 2: No  \n Q: Salir \n" ;
          modoMenu = TAPAS;
      break;
      case 'E':
         cout << "Esfera" << endl;
         if(figura=='E'){
            figura=0;
         }else{
            figura='E';
         }
         color.clear();
          cout<< "Con tapas \n 1: Si \n 2: No \n Q: Salir \n" ;
          modoMenu = TAPAS;
      break;
      case 'V':
         cout << "Varios Objetos" << endl;
         if(figura=='V'){
            figura=0;
         }else{
            figura='V';
         }
      break;
      case 'L':
         cout << "Elefante" << endl;
         if(figura=='L'){
            figura=0;
         }else{
            figura='L';
            modoMenu=ELEFANTE;
            cout << "Mueve al elefante " << endl;
            cout << " A: Mover cabeza en X \n B: Mover cabeza en Y \n C: Mover trompa en Z \n D: Mover trompa en X \n E: Mover trompita en X \n F: Mover trompita en Z \n G: Mover Patas \n H: Agachar \n I: Automatico \n Q:Salir \n ";
    
         }
      break;
      }
        
   }else if(modoMenu==SELVISUALIZACION){
      /*----------------------------MENÚ SELECCIÓN DE VISUALIZACIÓN---------------------------------------*/
      switch(toupper(tecla)){
         case 'Q':
            if (modoMenu!=NADA){
               cout << "Opciones: " << endl;
               cout << " O: seleccion de objeto \n V: seleccion de modo de visualizacion \n D: seleccion de modo de dibujado \n C: seleccion de camaras \n";
               modoMenu=NADA;    
            }else {
               salir=true ;
            }
         break;
         case 'P':
            cout << "modo puntos" << endl;
            visualizacion='P';
         break;
         case 'L':
            cout << "modo lineas" << endl;
            visualizacion='L';
            
         break;
         case 'S':
            cout << "modo solido" << endl;
            visualizacion='S';
         break;
         case 'A':
            cout << "modo ajedrez" << endl;
            //Si el modoAjedrez está activada, pulsando de nuevo A, se desactiva
            if(modoAjedrez==true){
               modoAjedrez=false;
            }else{
               modoAjedrez=true;
               visualizacion='A';
            }
         break;
         case 'M': 
            cout << "modo visualizacion simultanea" << endl;
            cout << "Modo simultaneo: \n 1: Puntos y lineas \n 2: Puntos y solido \n 3: Lineas y solido \n 4: Puntos, lineas y solido \n Q: Salir \n";
            modoMenu=SIMULTANEOS;
         break;
         case 'I': 
            cout << "seleccion de iluminacion" << endl;
            if(ilumina){
               cout << "Luces apagadas" << endl;
               ilumina = false;
            }else{
               cout << "Luces encendidas" << endl; 
               ilumina = true;
               modoMenu=ILUMINACION;
            }
            
         break;
         case 'T': 
            cout << "seleccion de Textura" << endl;
            if(text){
               text = false;
            }else{
               text = true;
            }

            habilitar_textura();
            
         break;
      }

   }else if(modoMenu==SELDIBUJADO){
      /*-----------------------------MENÚ SELECCIÓN DE VISUALIZACIÓN----------------------------------------*/
      switch(toupper(tecla)){
          case 'Q':
         if (modoMenu!=NADA){
            cout << "Opciones: " << endl;
            cout << " O: seleccion de objeto \n V: seleccion de modo de visualizacion \n D: seleccion de modo de dibujado \n C: seleccion de camaras \n";
            modoMenu=NADA;    
         }else {
            salir=true ;
         }
      break;
      case '1':
         cout << "Seleccionado el modo Inmediato" << endl;
         modo_dibujado=1;
      break;
      case '2':
         cout << "Seleccionado el modo Diferido" << endl;
         modo_dibujado=2;
      break;
     
      }
   }else if(modoMenu==SIMULTANEOS){
      /*---------------------------MENÚ VISUALIZACIÓN SIMULTÁNEA----------------------------------------------*/
      switch(toupper(tecla)){
               case 'Q':
               if(modoMenu!=NADA){
                  cout << "Opciones: " << endl;
                  cout << "Opciones: \n P: modo puntos \n L: modo Líneas \n S: modo Solido \n A: modo Ajedrez \n M: modo visualizacion simultanea \n Q: Salir" << endl;
                  modoMenu=SELVISUALIZACION;  
               }else{
                  salir=true;
               }
               break;
               case '1':
                  simultaneos=1;
                  modoMenu=SELVISUALIZACION;  
               break;
               case '2':
                  simultaneos=2;
                  modoMenu=SELVISUALIZACION;  
               break;
               case '3':
                  simultaneos=3;
                  modoMenu=SELVISUALIZACION; 
               break;
               case '4':
                  simultaneos=4;
                  modoMenu=SELVISUALIZACION; 
               break;
               
            }
         cout << "Seleccion del modo de visualizacion \n";
         cout << "Opciones: \n P: modo puntos \n L: modo Líneas \n S: modo Solido \n A: modo Ajedrez \n M: modo visualizacion simultanea \n Q: Salir" << endl;
      
   }else if(modoMenu == TAPAS){
      /*---------------------------MENÚ TAPAS (DURANTE LA EJECUCIÓN)-----------------------------------------*/
      switch(toupper(tecla)){
         case '1':
            tapas = true;
         break;
         case '2':
            tapas = false;
         break;
         case 'Q':
            cout << "Seleccion de objeto \n";
            cout << "Opciones: \n C: Cubo \n T: Tetraedro \n P: Objeto PLY cargado \n I: Cilindro \n O: Cono \n E: Esfera \n L:Elefante \n Q: Salir" << endl;
     
            modoMenu=SELOBJETO;
      }
   }else if(modoMenu == ILUMINACION){
      /*----------------------------MENÚ ILUMINACIÓN---------------------------------------------------------*/
      cout << "Seleccion de iluminacion " << endl;
      cout << "0..7: Luces de la 0 a la 7 \n I: Desactivar iluminacion \n A: Variar angulo ALPHA \n B: Variar angulo BETA \n >: Incrementar angulo \n <: Decrementar angulo \n Q:Salir \n ";
      switch(toupper(tecla)){
         case 'Q':
               if(modoMenu!=NADA){
                  cout << "Seleccion del modo de visualizacion \n";
                  cout << "Opciones: \n P: modo puntos \n L: modo Líneas \n S: modo Solido \n A: modo Ajedrez \n M: modo visualizacion simultanea \n I; Iluminacion \n T: Textura \n Q: Salir" << endl;
                  modoMenu=SELVISUALIZACION;  
               }else{
                  salir=true;
               }
               break;
         case 'I':
            cout << "Luces apagadas" << endl;
            ilumina=false;
            modoMenu=SELVISUALIZACION;
            cout << "Seleccion del modo de visualizacion \n";
            cout << "Opciones: \n P: modo puntos \n L: modo Líneas \n S: modo Solido \n A: modo Ajedrez \n M: modo visualizacion simultanea \n I; Iluminacion \n T: Textura \n Q: Salir" << endl;
                
         break;
         //VARIAR ÁNGULO DE LAS LUCES
         case 'A':
            cout << "Variar el angulo ALPHA" << endl;
            angulo ='A';
         break;
         case 'B':
            cout << "Variar el angulo BETA"  << endl;
            angulo = 'B';
         break;
         case '>':
            if(angulo == 'X'){
               cout << "ERROR: seleccionar angulo" << endl;
            }else{
               cout << "Incremento del angulo " << angulo << endl;
               if(angulo=='A'){
                  luz0->variarAnguloAlpha(5);
               }else if(angulo=='B'){
                  luz0->variarAnguloBeta(5);
               }
            }
            
         break;
         case '<':
           if(angulo == 'X'){
               cout << "ERROR: seleccionar angulo" << endl;
            }else{
               cout << "Decremento del angulo" << angulo << endl;
                if(angulo=='A'){
                  luz0->variarAnguloAlpha(-5);
               }else if(angulo=='B'){
                  luz0->variarAnguloBeta(-5);
               }
            }
         break;
         //LUCES DE 0 A 7
         case '0':
            luces(0);
            
         break;
         case '1':
            luces(1);
         break;
         case '2':
            luces(2);
         break;
         case '3':
            luces(3);
         break;
         case '4':
           luces(4);
         break;
         case '5':
            luces(5);
         break;
         case '6':
            luces(6);
         break;
         case '7':
            luces(7);
         break;

         

      }
   }else if(modoMenu == GIRAR){
    /*-------------------------MENÚ VARIAR POSICION LUCES------------------------------------------------*/
      switch(toupper(tecla)){
         case 'Q':
               if(modoMenu!=NADA){
                  cout << "Seleccion de iluminacion " << endl;
                  cout << "0..7: Luces de la 0 a la 7 \n I: Desactivar iluminacion \n A: Variar angulo ALPHA \n B: Variar angulo BETA \n >: Incrementar angulo \n <: Decrementar angulo \n Q:Salir \n ";
                  modoMenu=ILUMINACION;  
               }else{
                  salir=true;
               }
         break;
         case '+':
            cout<< "Aumento" << endl;
            moverLuces(true);
         break;
         case '-':
            cout << "Disminuyo" << endl;
            moverLuces(false);
       
         break;

      }
   }else if(modoMenu == ELEFANTE){
      /*-------------------------------MENÚ ELEFANTE---------------------------------------*/
      cout << "Mueve al elefante " << endl;
      cout << " A: Mover cabeza en X \n B: Mover cabeza en Y \n C: Mover trompa en Z \n D: Mover trompa en X \n E: Mover trompita en X \n F: Mover trompita en Z \n G: Mover las patas \n H: Agachar \n I: Automatico \n Q:Salir \n ";
      switch(toupper(tecla)){
         case 'Q':
               if(modoMenu!=NADA){
                    cout << "Seleccion de objeto \n";
                     cout << "Opciones: \n C: Cubo \n T: Tetraedro \n P: Objeto PLY cargado \n I: Cilindro \n O: Cono \n E: Esfera \n L: Elefante \n Q: Salir" << endl;
                      modoMenu=SELOBJETO;  
               }else{
                  salir=true;
               }
         break;
         
         case 'A':
            cout << "Mover cabeza en X" << endl;
            parte = 'A';
            modoMenu = MOVER;
            cout << "Mueve al elefante " << endl;
            cout << "+ : Aumenta giro \n - : Disminuye giro \n Q:Salir \n ";
         break;
         case 'B':
            cout << "Mover cabeza en Y" << endl;
            parte = 'B';
            modoMenu = MOVER;
            cout << "Mueve al elefante " << endl;
            cout << "+ : Aumenta giro \n - : Disminuye giro \n Q:Salir \n ";
         break;
         case 'C':
            cout << "Mover Trompa en Z" << endl;
            parte = 'C';
            modoMenu = MOVER;
            cout << "Mueve al elefante " << endl;
            cout << "+ : Aumenta giro \n - : Disminuye giro \n Q:Salir \n ";
         break;
         case 'D':
            cout << "Mover Trompa en X" << endl;
            parte = 'D';
            modoMenu = MOVER;
            cout << "Mueve al elefante " << endl;
            cout << "+ : Aumenta giro \n - : Disminuye giro \n Q:Salir \n ";
         break;
         case 'E':
            cout << "Mover Trompita en X" << endl;
            parte = 'E';
            modoMenu = MOVER;
            cout << "Mueve al elefante " << endl;
            cout << "+ : Aumenta giro \n - : Disminuye giro \n Q:Salir \n ";
         break;
         case 'F':
            cout << "Mover Trompita en Z" << endl;
            parte = 'F';
            modoMenu = MOVER;
            cout << "Mueve al elefante " << endl;
            cout << "+ : Aumenta giro \n - : Disminuye giro \n Q:Salir \n ";
         break;
         case 'G':
            cout << "Mover Patas" << endl;
            parte = 'G';
            modoMenu = MOVER;
            cout << "Mueve al elefante " << endl;
            cout << "+ : Aumenta giro \n - : Disminuye giro \n Q:Salir \n ";
         break;
         case 'H':
            cout << "Agacharse" << endl;
            parte = 'H';
            if(agachar){
               agachar=false;
            }else{
               agachar=true;
            }
             moverElefante();
         break;
         case 'I':
            cout << "Automatico " << endl;
            parte='I';
            modoMenu = PARTE;
            cout << "Cambia la velocidad de movimiento " << endl;
            cout << " G: General \n C: Cabeza \n T: Trompa \n P: Trompita \n Q:Salir \n ";
                
         break;
      }
       
   }else if(modoMenu == MOVER){
    /*-------------------------MENÚ VARIAR ÁNGULO DE GIRO------------------------------------------------*/
      switch(toupper(tecla)){
         case 'Q':
               if(modoMenu!=NADA){
                    cout << "Mueve al elefante " << endl;
                   cout << "A: Mover cabeza en X \n B: Mover cabeza en Y \n C: Mover trompa en Z \n D: Mover trompa en X \n E: Mover trompita en X \n F: Mover trompita en Z \n G: Mover Patas \n H: Agachar \n I: Automatico  \n  Q:Salir \n ";
                  modoMenu=ELEFANTE;  
               }else{
                  salir=true;
               }
         break;
         case '+':
            giro = 5;
            moverElefante();
         break;
         case '-':
            giro = -5;

            moverElefante();
         break;

      }
   }else if(modoMenu == PARTE){
    /*-------------------------MENÚ VARIAR ÁNGULO DE GIRO------------------------------------------------*/
      switch(toupper(tecla)){
         case 'Q':
               if(modoMenu!=NADA){
                  cout << "Mueve al elefante " << endl;
                  cout << "A: Mover cabeza en X \n B: Mover cabeza en Y \n C: Mover trompa en Z \n D: Mover trompa en X \n E: Mover trompita en X \n F: Mover trompita en Z \n G: Mover Patas \n H: Agachar \n I: Automatico  \n  Q:Salir \n ";
                  modoMenu=ELEFANTE;  
               }else{
                  salir=true;
               }
         break;
         case 'G':
            mover = 'G';
            modoMenu = AUTOMATICO;
            cout << " +: Aumenta \n -: Disminuye \n Q: Salir \n";
         break;
         case 'C':
            mover = 'C';
            modoMenu = AUTOMATICO;
            cout << " +: Aumenta \n -: Disminuye \n Q: Salir \n";
         break;
         case 'T':
            mover = 'T';
            modoMenu = AUTOMATICO;
            cout << " +: Aumenta \n -: Disminuye \n Q: Salir \n";
         break;
         case 'P':
            mover = 'P';
            modoMenu = AUTOMATICO;
            cout << " +: Aumenta \n -: Disminuye \n Q: Salir \n";
         break;

      }
   }
   else if(modoMenu == AUTOMATICO){
    /*-------------------------MENÚ VARIAR ÁNGULO DE GIRO------------------------------------------------*/
      switch(toupper(tecla)){
         case 'Q':
               if(modoMenu!=NADA){
                  cout << "Cambia la velocidad de movimiento " << endl;
                  cout << " G: General \n C: Cabeza \n T: Trompa \n P: Trompita \n Q:Salir \n ";
                  modoMenu=PARTE;  
               }else{
                  salir=true;
               }
         break;
         case '+':
            variarGiroAutomatico(mover, true);
         break;
         case '-':
            variarGiroAutomatico(mover, false);
         break;

      }
   } else if(modoMenu == CAMARAS){
    /*-------------------------MENÚ VARIAR ÁNGULO DE GIRO------------------------------------------------*/
      switch(toupper(tecla)){
         case 'Q':
               if(modoMenu!=NADA){
                  cout << "Opciones: " << endl;
                  cout << " O: seleccion de objeto \n V: seleccion de modo de visualizacion \n D: seleccion de modo de dibujado \n C: seleccion de camaras \n";
                  modoMenu=NADA;  
               }else{
                  salir=true;
               }
         break;
         case '1':
            if(camarasActivadas){
               cout << "Camara 1 activada" << endl;
               camaraActiva=0;
            }else{
               cout << "Camaras desactivadas " << endl;
            }
         break;

         case '2':
            if(camarasActivadas){
               cout << "camara 2 activiada " << endl;
               camaraActiva = 1;
            }else{
               cout << "Camaras desactivadas " << endl;
            }
            
         break;
         case '3':
         if(camarasActivadas){
            cout << "camara 3 activada " << endl;
            camaraActiva=2;
         }else{
            cout << "Camaras desactivadas " << endl;
         }
            
         break;
       
         

      }
   }

   return salir;
}


void Escena::variarGiroAutomatico(char l, bool mas){
   switch (l)
   {
   case 'G':
      if(mas){
         automatico *= 2;
      }else{
         automatico /= 2;
      }
   break;
   case 'C':
    if(mas){
         auto_cabeza *= 2;
      }else{
         auto_cabeza /= 2;
      }
   break;
   case 'T':
    if(mas){
         auto_trompa *= 2;
      }else{
         auto_trompa /= 2;
      }
   break;
   case 'P':
    if(mas){
         auto_trompita *= 2;
      }else{
         auto_trompita /= 2;
      }
   break;
   }

}

/*-------------------------------------------LUCES------------------------------------------------*/

//Activar iluminacion central
void Escena::encenderLuces(bool encender){
   if(encender){             
      glEnable(GL_LIGHTING);
   }else{
      glDisable(GL_LIGHTING);
   }
}

void Escena::luces(int id){
   if(id==0){
      if(l0){
               cout << "Luz 0 desactivada" << endl;
               l0=false;
               luz0->desactivar();
            }else{
               cout<< "Luz 0 activada" << endl;
               l0=true;
               luz0->activar();
            }
            
   }else{
      for(int i=1; i<8; i++){
         if(id==i){
             if(lucesPosicionales_activadas[i]){
               cout << "Luz "<< i << " desactivada" << endl;
               lucesPosicionales_activadas[i]=false;
               lucesPosicionales[i]->desactivar();
            }else{
               cout<< "Luz " << i << " activada" << endl;
               lucesPosicionales_activadas[i]=true;
               lucesPosicionales[i]->activar();
      
               modoMenu=GIRAR;
               cout << "Gira las luces " << endl;
               cout << "+: Aumnentar \n-: Disminuir \n Q: Salir \n";
            }
         }
      }
   }
  
}


void Escena::moverLuces(bool mover){
   //Mueve todas las luces posicionales que estén activadas 
   for(int i=0; i<7; i++){
      if(lucesPosicionales_activadas[i]){
           posicion = lucesPosicionales[i]->getPosicion();
            if(mover){
               posicion[0]  += 10;
               posicion[1]  += 10;
               posicion[2]  += 10;  
               
            }else{
               posicion[0]  -= 10;
               posicion[1]  -= 10;
               posicion[2]  -= 10;  
            }   
      }
      lucesPosicionales[i]->mover(posicion);
   }
      
  
}

/*---------------------------------MOVIMIENTOS DEL ELEFANTE------------------------------------------*/

void Escena::moverElefante(){
   switch (parte)
   {
      case 'A':
         elefante->setGiroCabezaX(giro);
      break;
      case 'B':
         elefante->setGiroCabezaY(giro);
         break;
      case 'C':
         elefante->setGiroTrompaZ(giro);
      break;
      case 'D':
         elefante->setGiroTrompaX(giro);
      break;
      case 'E':
         elefante->setGiroTrompaPequeniaX(giro); 
      break;
      case 'F':
         elefante->setGiroTrompaPequeniaZ(giro); 
      break;
      case 'G':
         elefante->setGiroPatas(giro);
      break;
      case 'H':
         elefante->setAgacharse(agachar);
      break;
   
   }
}

void Escena::animarModeloJerarquico(){
   if(parte == 'I'){
      if(abs(elefante->getGiroCabezaY()) >= abs(elefante->getCabezaYMax()/2)){
         cambioSentido*=-1;
      }

      elefante->setGiroCabezaY(0.05*cambioSentido*automatico*auto_cabeza);
      elefante->setGiroTrompaX(0.05*cambioSentido*automatico*auto_trompa);
      elefante->setGiroTrompaPequeniaX(0.05*cambioSentido*automatico*auto_trompita); 
    
   }
  
}


void Escena::habilitar_textura(){
   if(text){
       glEnable(GL_TEXTURE_2D);
       cout << "Textura activada" << endl;
   }else{
       glDisable(GL_TEXTURE_2D);
       cout << "Textura desacticada" << endl;
   }
}


/*-------------------------------------------CÁMARA---------------------------------------*/


void Escena::setMoverse(bool m){
   moverse=m;
}
bool Escena::getMoverse(){
   return moverse;
}
void Escena::ratonMovido(int x, int y){
   if(moverse){
      int x2 = x - this->x;
      int y2 = y - this->y;
      moverEscena(x2, y2);
      this->x = x;
      this->y = y;
   }
}
void Escena::moverEscena(int x, int y){
   camaras[camaraActiva]->rotarXFirstPerson(x);
   camaras[camaraActiva]->rotarYFirstPerson(y);
}

void Escena::dibujarSeleccion(){

}

void Escena::zoom(bool z){
   if(camarasActivadas){
      if(z){
         camaras[camaraActiva]->zoom(1.2);
      }else{
         camaras[camaraActiva]->zoom(0.5);
      }
   }
   
}

void Escena::objetoSeleccionado(int x, int y){
   cout << "Entra " << endl;
   glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, (void *) pixel);
   printf("%f %f %f \n", pixel[0], pixel[1], pixel[2]);
   if(pixel[0] < 1.0 || pixel[1] < 1.0 || pixel[2]<1.0){
      objetoEncontrado = true;
      cout << "Objeto encontrado" << endl;
   }else{
      cout << "Objeto NO seleccionado";
      objetoEncontrado=false;
   }
   if(objetoEncontrado){
      camaras[camaraActiva]->objetoEncontrado(true, x, y);
   }else{
      camaras[camaraActiva]->objetoEncontrado(false, x, y);
   }
 

}
/*-------------------------------------TECLAS ESPECIALES---------------------------------------------*/

//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
        if(camarasActivadas){
				camaras[camaraActiva]->rotarYFirstPerson(-3.0);
				
		 	}
		 	else{
				Observer_angle_y-- ;
		 	}
      break;
	   case GLUT_KEY_RIGHT:
         if(camarasActivadas){
				camaras[camaraActiva]->rotarYFirstPerson(3.0);
				
		 	}
		 	else{
				Observer_angle_y++ ;
		 	}
         
      break;
	   case GLUT_KEY_UP:
         
         if(camarasActivadas){
				camaras[camaraActiva]->rotarXFirstPerson(3.0);
				
		 	}
		 	else{
				Observer_angle_x-- ;
		 	}
         
      break;
	   case GLUT_KEY_DOWN:
         if(camarasActivadas){
				camaras[camaraActiva]->rotarXFirstPerson(-3.0);
				
		 	}
		 	else{
				Observer_angle_x++ ;
		 	}
         
      break;
	   case GLUT_KEY_PAGE_UP:
      cout << "Camaras " << camarasActivadas << endl;
         if(camarasActivadas){
				camaras[camaraActiva]->zoom(1.2);
		 	}
		 	else{
				 Observer_distance *=1.2 ;
		 	}
        
         break;
	   case GLUT_KEY_PAGE_DOWN:
      cout << "Camaras " << camarasActivadas << endl;
         if(camarasActivadas){
				camaras[camaraActiva]->zoom(0.5);
				
		 	}
		 	else{
				Observer_distance /= 1.2 ;
		 	}
         
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

/*------------------------------------VENTANA PRINCIPAL--------------------------------------------*/

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wx = float(Height)*ratio_xy ;
   if(!camarasActivadas){
       glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
   }else{
      camaras[camaraActiva]->setProyeccion();
   }
  }
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   if(!camarasActivadas){
      glTranslatef( 0.0, 0.0, -Observer_distance );
      glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
      glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
   }else{
      camaras[camaraActiva]->setObserver();
   }
   
}
