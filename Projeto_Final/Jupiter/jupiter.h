//Estruturas
typedef struct{
	float Translacao;
	float Rotacao;
	int Faces;
	int TamanhoTranslacao;
	GLuint Texture;
	bool Estado;
}Corpo;

typedef struct{
	int X;
	int Y;
	int Z;
}EixoINT;

typedef struct{
	float X;
	float Y;
	float Z;
}EixoFLOAT;

typedef struct{
	float Largura;
	float Altura;
}Janela;

//Variaveis dos Corpos
Corpo jupiter;
Corpo io;
Corpo europa;
Corpo ganimedes;
Corpo calisto;
Corpo space;

//Variaveis de Luz
float difusa; //luz que espalha em todas as direções
float especular; //luz refletida
float posicional; //a luz é posicional
float global; //luz ambiente
float matrizAD[] = {1.0, 1.0, 1.0, 1.0}; //atenuação da luz
float matrizEspecular[] = {1.0, 1.0, 1,0, 1.0}; //luz branca 
float matrizBrilho[] = {50};
EixoFLOAT luzBranca;

 
//Variaveis de Controle
int horizonteEventos = 1;//Espaço Visivel
EixoINT cursor;
EixoINT mouse;
Janela janela;
bool podeBrilhar = true;
bool podeOrbitar = false;

//Variaveis da Camera
int modoCamera = 1;
float anguloCameraA = 120;
float anguloCameraB = 0;
EixoFLOAT camera;


