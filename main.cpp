//*****************************************************
//
// Exemplo3D.cpp
// Um programa OpenGL simples que abre uma janela GLUT
// e desenha um cubo para exemplificar a visualiza��o
// de objetos 3D utilizando a proje��o perspectiva.
//
// Marcelo Cohen e Isabel H. Manssour
// Este c�digo acompanha o livro
// "OpenGL - Uma Abordagem Pr�tica e Objetiva"
//
//*****************************************************

#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>

using namespace std;

GLfloat fAspect;
GLfloat Obsx = 0,Obsy = 0,Obsz = 0;
int AlteraProjecao = 1;

void CuboColorido(GLfloat tam)
{

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    tam /= 2;

    glBegin(GL_QUADS);
    glColor3f(1.0f,0.0f,0.0f);
    glVertex3f( tam, tam,-tam);
    glVertex3f(-tam, tam,-tam);
    glVertex3f(-tam, tam, tam);
    glVertex3f( tam, tam, tam);

    glColor3f(0.0f,1.0f,0.0f);
    glVertex3f( tam,-tam, tam);
    glVertex3f(-tam,-tam, tam);
    glVertex3f(-tam,-tam,-tam);
    glVertex3f( tam,-tam,-tam);

    glColor3f(0.0f,0.0f,1.0f);
    glVertex3f( tam, tam, tam);
    glVertex3f(-tam, tam, tam);
    glVertex3f(-tam,-tam, tam);
    glVertex3f( tam,-tam, tam);

    glColor3f(1.0f,1.0f,0.0f);
    glVertex3f( tam,-tam,-tam);
    glVertex3f(-tam,-tam,-tam);
    glVertex3f(-tam, tam,-tam);
    glVertex3f( tam, tam,-tam);

    glColor3f(1.0f,0.0f,1.0f);
    glVertex3f(-tam, tam, tam);
    glVertex3f(-tam, tam,-tam);
    glVertex3f(-tam,-tam,-tam);
    glVertex3f(-tam,-tam, tam);

    glColor3f(0.0f,1.0f,1.0f);
    glVertex3f( tam, tam,-tam);
    glVertex3f( tam, tam, tam);
    glVertex3f( tam,-tam, tam);
    glVertex3f( tam,-tam,-tam);

    glEnd();
}

// Fun��o callback de redesenho da janela de visualiza��o
void Desenha(void)
{
    // Limpa a janela de visualiza��o com a cor
    // de fundo definida previamente
    glClear(GL_COLOR_BUFFER_BIT);

    // Altera a cor do desenho para preto
    glColor3f(0.0f, 0.0f, 0.0f);

    // Fun��o da GLUT para fazer o desenho de um cubo
    // com a cor corrente
    CuboColorido(50);

    // Executa os comandos OpenGL
    glFlush();
}

// Fun��o usada para especificar o volume de visualiza��o
void EspecificaParametrosVisualizacao(void)
{
    // Especifica sistema de coordenadas de proje��o
    glMatrixMode(GL_PROJECTION);
    // Inicializa sistema de coordenadas de proje��o
    glLoadIdentity();

    // Especifica a proje��o perspectiva(angulo,aspecto,zMin,zMax)
    //gluPerspective(60,fAspect,0.5,200);
    if(AlteraProjecao == 0)
        glOrtho(-65.0, 65.0, -65.0, 65.0, 1.0, 500.0);
    else
        gluPerspective(60,fAspect,0.5,200);

    // Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);
    // Inicializa sistema de coordenadas do modelo
    glLoadIdentity();

    // Especifica posi��o do observador e do alvo
    gluLookAt(20 + Obsx,40 + Obsy,100 + Obsz, 0,0,0, 0,1,0);

    Desenha();
}

// Fun��o callback chamada quando o tamanho da janela � alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    // Para previnir uma divis�o por zero
    if ( h == 0 )
        h = 1;

    // Especifica as dimens�es da viewport
    glViewport(0, 0, w, h);

    // Calcula a corre��o de aspecto
    fAspect = (GLfloat)w/(GLfloat)h;

    EspecificaParametrosVisualizacao();
}

// Fun��o callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
    if (key == 27)
        exit(0);
    if (key == 'p')
    {
        if(AlteraProjecao == 0)
            AlteraProjecao = 1;
        else
            AlteraProjecao = 0;

        EspecificaParametrosVisualizacao();
    }
    if(key == 'w')
    {
        Obsy = Obsy + 20;
        EspecificaParametrosVisualizacao();
    }
    if(key == 's')
    {
        Obsy = Obsy - 20;
        EspecificaParametrosVisualizacao();
    }
    if(key == 'a')
    {
        Obsx = Obsx  - 20;
        EspecificaParametrosVisualizacao();
    }
    if(key == 'd')
    {
        Obsx = Obsx + 20;
        EspecificaParametrosVisualizacao();

    }
    if(key == 'r')
    {
        Obsz = Obsz  - 20;
        EspecificaParametrosVisualizacao();
    }
    if(key == 'f')
    {
        Obsz = Obsz + 20;
        EspecificaParametrosVisualizacao();

    }

}

// Fun��o respons�vel por inicializar par�metros e vari�veis
void Inicializa (void)
{
    // Define a cor de fundo da janela de visualiza��o como branca
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glLineWidth(2.0);
}

// Programa Principal
int main(void)
{
    // Define do modo de opera��o da GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Especifica a posi��o inicial da janela GLUT
    glutInitWindowPosition(5,5);

    // Especifica o tamanho inicial em pixels da janela GLUT
    glutInitWindowSize(450,450);

    // Cria a janela passando como argumento o t�tulo da mesma
    glutCreateWindow("Desenho de um cubo");

    // Registra a fun��o callback de redesenho da janela de visualiza��o
    glutDisplayFunc(Desenha);

    // Registra a fun��o callback de redimensionamento da janela de visualiza��o
    glutReshapeFunc(AlteraTamanhoJanela);

    // Registra a fun��o callback para tratamento das teclas ASCII
    glutKeyboardFunc (Teclado);

    // Chama a fun��o respons�vel por fazer as inicializa��es
    Inicializa();

    // Inicia o processamento e aguarda intera��es do usu�rio
    glutMainLoop();

    return 0;
}
