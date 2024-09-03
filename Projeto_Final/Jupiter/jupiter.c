#include <SDL/SDL.h>               //manipulação de janelas e eventos no SDL.
#include "SDL/SDL_opengl.h"         //Extensão do SDL para suporte a OpenGL.
#include "SDL/SDL_image.h"          //carregar imagens em várias formatos.
#include <stdio.h>                  
#include <stdbool.h>                
#include <stdlib.h>                 
#include <string.h>                 
#include <SOIL/SOIL.h>              //carregar texturas em OpenGL.
#include <GL/gl.h>                  //API padrão de gráficos em 3D em OpenGL.
#include <GL/glu.h>                 //Biblioteca utilitária OpenGL.
#include <GL/freeglut.h>            //Biblioteca gratuita para GLUT
#include <math.h>                   
#include "jupiter.h"                


//---------------------------------------------------- Carregamento de Texturas ------------------------------------------------------------
GLuint carregaTextura(const char* arquivo) {
  GLuint idTextura = SOIL_load_OGL_texture(
                     arquivo,
                     SOIL_LOAD_AUTO,
                     SOIL_CREATE_NEW_ID,
                     SOIL_FLAG_INVERT_Y
                    );

  if (idTextura == 0) {
    printf("Erro do SOIL: '%s' - '%s'\n", arquivo, SOIL_last_result());
  }

  return idTextura;
} 

//---------------------------------------------------- Renderização ------------------------------------------------------------
void criaSphere(float radius, int stacks, int columns){
    GLUquadric* quadObj = gluNewQuadric();
    gluQuadricDrawStyle(quadObj, GLU_FILL);
    gluQuadricNormals(quadObj, GLU_SMOOTH);
    gluQuadricTexture(quadObj, GL_TRUE);
    gluSphere(quadObj, radius, stacks, columns);
    gluDeleteQuadric(quadObj);
}
void renderizaAstroRei(){
	glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, jupiter.Texture);
    	glPushMatrix();
	        glRotatef(jupiter.Translacao, 0, 1, 0);
	        glRotatef(90, 1, 0, 0);
	        criaSphere(100 , jupiter.Faces, jupiter.Faces);
   		 glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}
void renderizaCorpos(){
	glEnable(GL_TEXTURE_2D);
		//Espaço
		glBindTexture(GL_TEXTURE_2D, space.Texture);
	    glPushMatrix();
	       glTranslatef(cursor.X, cursor.Y, cursor.Z); 
	        criaSphere(7000, jupiter.Faces, jupiter.Faces);
	    glPopMatrix();
	    /*luas*/
		//Io
		glBindTexture(GL_TEXTURE_2D, io.Texture);
		glPushMatrix();
	        glRotatef(io.Translacao, 0, 1, 0);
	        glTranslatef(io.TamanhoTranslacao, 0.0, 0);
	        glRotatef(io.Rotacao, 0, 1, 0);
	        glRotatef(97, 1, 0, 0); 
	        criaSphere(20 * horizonteEventos, io.Faces, io.Faces);
	    glPopMatrix();
	    //europa
	    glBindTexture(GL_TEXTURE_2D, europa.Texture);   
	    glPushMatrix();
	        glRotatef(europa.Translacao, 0, 1, 0);
	        glTranslatef(europa.TamanhoTranslacao, 0.0, 0);
	        glRotatef(europa.Rotacao, 0, 1, 0);
	        glRotatef(-267, 1, 0, 0);        
	        criaSphere(10 * horizonteEventos, europa.Faces, europa.Faces);
	    glPopMatrix();
	    //Ganimedes
	    glBindTexture(GL_TEXTURE_2D, ganimedes.Texture);   
	    glPushMatrix();
	        glRotatef(ganimedes.Translacao, 0, 1, 0);
	        glTranslatef(ganimedes.TamanhoTranslacao, 0.0, 0);
	        glRotatef(ganimedes.Rotacao, 0, 1, 0);
	        glRotatef(-133.5, 1, 0, 0);        
	        criaSphere(40 * horizonteEventos, ganimedes.Faces, ganimedes.Faces);
	    glPopMatrix();
	    //Calisto
	    glBindTexture(GL_TEXTURE_2D, calisto.Texture);   
	    glPushMatrix();
	        glRotatef(calisto.Translacao, 0, 1, 0);
	        glTranslatef(calisto.TamanhoTranslacao, 0.0, 0);
	        glRotatef(calisto.Rotacao, 0, 1, 0);
	        glRotatef(115, 1, 0, 0);        
	        criaSphere(30 * horizonteEventos, calisto.Faces, calisto.Faces);
	    glPopMatrix();
	    
	    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void Luz(){
    if(podeBrilhar){
        // Configuração das propriedades da luz ambiente
        float luzAmbiente[] = {0.0, 0.0, 0.0, 1.0};
        float luzDifusa0[] = {difusa, difusa, difusa, 1.0};
        float luzEpecular0[] = {especular, especular, especular, 1.0};
        float luzPosicional0[] = {0.0, 0.0, 3.0, posicional};
        float luzDE[] = {0.0, 1.0, 0.0, 1.0};
        float luzPosicional1[] = {1.0, 2.0, 0.0, 1.0};
        float luzGlobal[] = {global, global, global, 1.0};

        // Configuração das luzes
        glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa0);
        glLightfv(GL_LIGHT0, GL_SPECULAR, luzEpecular0);

        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobal);
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, false);
        glEnable(GL_LIGHT0);
        glDisable(GL_LIGHTING);

        // Configuração da posição da luz posicional e renderização de um objeto iluminado por ela
        glPushMatrix();
            glRotatef(luzBranca.X, 1.0, 0.0, 0.0);
            glRotatef(luzBranca.Y, 0.0, 1.0, 0.0);
            glLightfv(GL_LIGHT0, GL_POSITION, luzPosicional0);
            glTranslatef(luzPosicional0[0], luzPosicional0[1], luzPosicional0[2]);
            glColor3f(difusa, difusa, difusa);
            renderizaAstroRei();
        glPopMatrix();
    } else {
        // Desabilita a luz se não puder brilhar
        glDisable(GL_LIGHT0);
    }

    // Habilita a iluminação geral
    glEnable(GL_LIGHTING);
}


void exibeCamera(){
    // Cálculo das coordenadas da câmera com base nos ângulos da câmera
    camera.X = 800 * sin(anguloCameraA) * cos(anguloCameraB);
    camera.Y = 800 * sin(anguloCameraA);
    camera.Z = 800 * cos(anguloCameraA) * sin(anguloCameraB);

    // Seleção do modo de câmera
    switch(modoCamera){
        case 1:
            // Configuração da câmera no modo de seguir o cursor
            gluLookAt(cursor.X+camera.X, camera.Y, cursor.Z+camera.Z, cursor.X+0, 0, cursor.Z+0, 0, 1, 0);
        break;
        case 2:
            // Configuração da câmera no modo estático
            gluLookAt(0, 0, 1080, 0, 0, 0, 0, 1, 0);
        break;
    }
}


//---------------------------------------------------- Estado de Execução ------------------------------------------------------------

void estadoExecucao(){
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity(); //redefine a posição e orientação da camera
    exibeCamera();
   	glMaterialfv(GL_FRONT, GL_SHININESS, matrizBrilho);
    glColor3f(1, 1, 1);
    Luz();
    renderizaCorpos();
    
    glutSwapBuffers();
}

void estadoAtualizacao(int time){
	glutPostRedisplay();
    glutTimerFunc(time, estadoAtualizacao, time);
}

//---------------------------------------------------- Processos de Execução ------------------------------------------------------------
void estadoRotacao(){
	jupiter.Rotacao = jupiter.Rotacao + 0.1f;
	io.Rotacao = io.Rotacao + 0.04f;
	europa.Rotacao = europa.Rotacao + 0.01f;
	ganimedes.Rotacao = ganimedes.Rotacao + 2.4f;
	calisto.Rotacao = calisto.Rotacao + 2.3f;
	
	glutPostRedisplay();
}

void estadoTranslacao(){
	io.Translacao = io.Translacao + 0.16f;
	europa.Translacao = europa.Translacao + 0.12f;
	ganimedes.Translacao = ganimedes.Translacao + 0.1f;
	calisto.Translacao = calisto.Translacao + 0.08f;
	
	estadoRotacao();
	glutPostRedisplay();
}

void estadoTeclado(unsigned char key, int x, int y){
	switch(key){
		case '1':
			modoCamera = 1;
		break;
		case '2':
			modoCamera = 2;
		break;
		
		case 'a':
			cursor.X -= 5;
		break;
		
		case 'd':
			cursor.X += 5;
		break;
		
		case 'w':
			cursor.Z -= 5;
		break;
		
		case 's':
			cursor.Z += 5;
		break;
		
	}
	
}

//---------------------------------------------------- Configurações da Aplicação ------------------------------------------------------------
/*Define as configurações da janela*/
void confJanela(int w, int h){
	janela.Largura = w;
	janela.Altura = h;

	glEnable(GL_DEPTH_TEST); //ativa o teste de profundidade
    glViewport (0, 0, w, h); //área da janela onde é renderizada
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    
    //campo de visão vertical em graus, relação de aspecto, distância do observador parao plano proximo, distancia do observador parao plano distante
    gluPerspective(60.0, (float)w/(float)h, 0.2, 2147483647.0);
    glMatrixMode(GL_MODELVIEW);
}
/*Define as configurações da camera*/
//chamada sempre que há um movimento no mouse
void confCamera(int x, int y){
	float altX = x - mouse.X;
	float altY = y - mouse.Y;

	anguloCameraA = anguloCameraA + altX/150; //ajuste para controlar a velocidade rotação da camera
	anguloCameraB = anguloCameraB + altY/150;

	mouse.X = x;
	mouse.Y = y;
}

/*Define estado inicial dos componentes*/
void defineBase(){
	glClearColor(0,0,0, 0.0); //preto e transparente
    glEnable(GL_BLEND); //ativa mesclagem de cores
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    	/*Configurações da Luz*/
    	difusa = 1;
	especular = 1;
	posicional = 1;
	global = 0.2;
	luzBranca.X = 0;
	luzBranca.Y = 0;

	/*Configurações do Cursor*/
	cursor.X = 0;
	cursor.Y = 0;
	cursor.Z = 0;

	/*Configurações do Mouse*/
	mouse.X = 0;
	mouse.Y = 0;
	mouse.Z = 0;

    /*Configurações das luas*/
    //JUPITER
	jupiter.Texture = carregaTextura("resources/textures/jupiter.jpg");
	jupiter.Translacao = 0;
	jupiter.Faces = 200;
	jupiter.Estado = true;
	jupiter.Rotacao = 0;

	//IO
	io.Texture = carregaTextura("resources/textures/io2.png");
	io.Translacao = 10;
	io.Rotacao = 10;
	io.TamanhoTranslacao = 150;
	io.Faces = 200;
	io.Estado = true;

	//EUROPA
	europa.Texture = carregaTextura("resources/textures/europa2.png");
	europa.Translacao = 30;
	europa.Rotacao = 10;
	europa.TamanhoTranslacao = 200;
	europa.Faces = 200;
	europa.Estado = true;

	//GANIMEDES
	ganimedes.Texture = carregaTextura("resources/textures/ganimedes2.png");
	ganimedes.Translacao = 90;
	ganimedes.Rotacao = 90;
	ganimedes.TamanhoTranslacao = 250;
	ganimedes.Faces = 200;
	ganimedes.Estado = true;

	//CALISTO
	calisto.Texture = carregaTextura("resources/textures/calisto2.png");
	calisto.Translacao = 10;
	calisto.Rotacao = 10;
	calisto.TamanhoTranslacao = 300;
	calisto.Faces = 200;
	calisto.Estado = true;

	//Espaço
	space.Texture = carregaTextura("resources/textures/space.jpg");

	/*Configurações do Material*/
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matrizAD);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matrizEspecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matrizBrilho);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}




int main(int argc, char* args[]){ 
	
	SDL_Init(SDL_INIT_EVERYTHING); //Inicia o SDL
	glutInit(&argc, args);
	glutInitContextVersion(1, 1);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
    //Configurações da Janela
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); //Modo
    glutInitWindowSize(1400, 840);//Dimensão
    glutInitWindowPosition (0, 0);//Posição
    glutCreateWindow("Jupiter e suas luas galileanas"); //Nome     

	//Chama funções principais
	glutDisplayFunc(estadoExecucao);//Execução
	glutReshapeFunc(confJanela);
	glutTimerFunc(10, estadoAtualizacao, 10); //Taxa de Atualização
	glutKeyboardFunc(estadoTeclado);
	glutPassiveMotionFunc(confCamera);
	glutIdleFunc(estadoTranslacao);
	defineBase(); //Processos Iniciais
	glutMainLoop();//Loop
	SDL_Quit();	//Encerra o SDL

	return 0;
}
