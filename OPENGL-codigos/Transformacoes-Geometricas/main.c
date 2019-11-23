/* Rafael R. S. 2019 */ 
#include <GL/glut.h>
#include <stdio.h>
// variáveis para posições de translação x e y 
int tx = 0;
int ty = 0; 
int ladoQuadrado = 10;       // quadrado 10x10
int theta = 0; // começa sem rotação 0 graus 

// protótipo das funções
void glutKeyboardFunc(void (*func)(unsigned char key, int x, int y));  // chama a operação realizada
int init(void); 
void translada(int key, int x, int y); 
void rotaciona(int key, int x, int y);
void selecionamodo(unsigned char key, int x, int y); 
void display(void); 
int main(int argc, char** argv); 
 
// implementação 

int init(void){
    glClearColor(1.0, 1.0, 1.0, 0.0);     // define a cor de fundo
    glMatrixMode(GL_PROJECTION);          // carrega a matriz de projeção
    gluOrtho2D(0.0,100.0,0.0,100.0);      // define projeção ortogonal 2D
}
 
// funcao transladar recebe key (dir,esq,cima,baixo) 
// a distancia percorrida é 5. 
void translada(int key, int x, int y){
    switch(key){
    	case GLUT_KEY_RIGHT:
            tx += 5;
            glutPostRedisplay();
    		break;
        case GLUT_KEY_LEFT:
    		tx -= 5;
    		glutPostRedisplay();
    		break;
        case GLUT_KEY_UP:
    		ty += 5;
    		glutPostRedisplay();
    		break;
        case GLUT_KEY_DOWN:
    		ty -= 5;
    		glutPostRedisplay();
    		break;
	}
} 

// funcão para rotacionar o quadrado 
// dir = rotacao sentido horario 
// esq = rotacao anti-horário
void rotaciona(int key, int x, int y){
    switch(key){
        case GLUT_KEY_RIGHT:
            theta -= 10;
            break;
        case GLUT_KEY_LEFT:
            theta += 10;
            break;
    }

    glutPostRedisplay();
} 

// função para definir a operação (translacao e rotação)
void selecionamodo(unsigned char key, int x, int y){
    switch(key){ 
        case 't':
            glutSpecialFunc(translada);        // captura as teclas especiais
            break;
        case 'r':
            glutSpecialFunc(rotaciona);        // captura as teclas especiais
            break;
    }
} 

// display func
void display(void){
    glClear(GL_COLOR_BUFFER_BIT);           // desenha o fundo (limpa a janela)
    glColor3f(1.0,0.0,0.0);                 // altera o atributo de cor
    glMatrixMode(GL_MODELVIEW);             // carrega a matriz de modelo
    glLoadIdentity();                       // carrega a matriz identidade
    // posiciona o objeto para sua respectiva posicao caso ele seja rotacionado    
    glTranslatef(tx+(ladoQuadrado/2), ty+(ladoQuadrado/2), 0);
    glRotatef(theta, 0, 0, 1);
    glTranslatef(-tx-(ladoQuadrado/2), -ty-(ladoQuadrado/2), 0);
    glBegin(GL_POLYGON);                    // desenha uma linha
        glVertex2i(tx, ty);
        glVertex2i(tx, ty + ladoQuadrado);
        glVertex2i(tx + ladoQuadrado, ty + ladoQuadrado);
        glVertex2i(tx + ladoQuadrado, ty);
    glEnd();
     glBegin(GL_POLYGON);                    // desenha uma linha
        glVertex2i(tx, ty);
        glVertex2i(tx, ty + ladoQuadrado);
        glVertex2i(tx + ladoQuadrado, ty + ladoQuadrado);
        glVertex2i(tx + ladoQuadrado, ty);
    glEnd();
    glFlush();                            // desenha os comandos não executados
} 

int main(int argc, char** argv) {

    glutInit(&argc,argv);                                     //inicializa o GLUT
    glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);               //configura o modo de display
    glutInitWindowSize(500,500);                              //configura a largura e altura da janela de exibição
    glutInitWindowPosition(100,100);
    glutCreateWindow("Translacao e rotacao de um quadrado 10x10");           //cria a janela de exibição
    init();                             // executa função de inicialização
    glutSpecialFunc(translada);         // captura as teclas especiais
    glutKeyboardFunc(selecionamodo);    // captura as teclas 'R' e 'T'
    glutDisplayFunc(display);           // estabelece a função "display" como a função callback de exibição.
    glutMainLoop();                     // tela principal
    return 0;
}

