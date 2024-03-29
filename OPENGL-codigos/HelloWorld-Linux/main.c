#include <GL/glut.h>

int init(void){
    glClearColor(1.0, 1.0, 1.0, 0.0);     //define a cor de fundo

    glMatrixMode(GL_PROJECTION);          //carrega a matriz de projeção
    gluOrtho2D(0.0,200.0,0.0,150.0);      //define projeção ortogonal 2D

}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);         //desenha o fundo (limpa a janela)

    glColor3f(1.0,0.0,0.0);               //altera o atributo de cor
    glBegin(GL_LINES);                    //desenha uma linha
        glVertex2i(180,15);
        glVertex2i(10,145);
    glEnd();

    glFlush();                            //desenha os comandos não executados
}

int main(int argc, char** argv) {

    glutInit(&argc,argv);                                     //inicializa o GLUT
    glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);               //configura o modo de display
    glutInitWindowSize(400,300);                              //configura a largura e altura da janela de exibição
    glutInitWindowPosition(200,0);
    glutCreateWindow("Um programa OpenGL Exemplo");           //cria a janela de exibição

    init();                          //executa função de inicialização
    glutDisplayFunc(display);        //estabelece a função "display" como a função callback de exibição.
    glutMainLoop();                  //mostre tudo e espere
    return 0;
}

