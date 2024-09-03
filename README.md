# Simulação do Sistema de Júpiter e Suas Luas Galileanas
Este projeto foi desenvolvido como parte da disciplina de Computação Gráfica do curso de Engenharia de Computação na Universidade Federal do Rio Grande do Norte (UFRN). Ele consiste em uma simulação gráfica do planeta Júpiter e suas quatro luas galileanas: Io, Europa, Ganimedes e Calisto, utilizando OpenGL.

## Descrição do Projeto
A simulação visa recriar visualmente Júpiter e suas luas, destacando aspectos como rotação e translação dos corpos celestes, além de aplicar texturas realistas às superfícies. A câmera é configurada para permitir uma visão dinâmica, com modos de visualização que seguem o cursor ou se mantêm estáticos

### Funcionalidades Principais
* Carregamento de Texturas: Utiliza a biblioteca SOIL para carregar texturas de alta qualidade, que são aplicadas aos corpos celestes.
* Renderização de Esferas: A função criaSphere gera as esferas representando Júpiter e suas luas, com mapeamento de textura e suavização de superfície.
* Movimentação Celeste: Implementa a rotação e translação das luas em torno de Júpiter, simulando o movimento orbital.
* Iluminação: Configuração detalhada da iluminação para realçar os efeitos de luz e sombra, criando uma experiência visual mais realista.
Controle de Câmera: A câmera pode ser movida e ajustada em tempo real para explorar o sistema planetário sob diferentes ângulos.

### Tecnologias Utilizadas
* OpenGL: API principal para renderização gráfica em 3D.
* SDL: Para criação e manipulação de janelas e eventos.
* SOIL: Biblioteca para carregamento de texturas.
* GLUT: Utilizada para o gerenciamento de janelas e interação do usuário.

### Como Executar
* Certifique-se de ter as bibliotecas SDL, OpenGL, SOIL e GLUT instaladas.
* Use esse comando no terminal: gcc jupiter.c -o jupiter -lGL -lGLU -lglut -lSOIL -lSDL -lSDLmain -lSDL_image -lSDL_mixer -lm
