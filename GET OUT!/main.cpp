//DEFINES--------------------------------------------

#define TAM_BLOCO 100
#define PASSO	10

#define NORTE  0
#define LESTE  1
#define SUL    2
#define OESTE  3



//GLOBALS--------------------------------------------

GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 50.0 };
GLfloat mat_amarelo[] = {0.8, 0.8, 0.1, 1.0};
GLfloat mat_verde[] = { 0.1, 0.6, 0.1, 1.0 };
GLfloat mat_vermelho[] = { 0.7, 0.1, 0.1, 1.0 };
GLfloat light_position[] = { 0.0, 500.0, 0.0, 1.0 };
GLfloat luz_branca[] = {1.0,1.0,1.0,1.0};
GLfloat lmodel_ambient[] = {0.6,0.6,0.6,1.0};


GLfloat jog_x= 500, jog_z=0;
GLfloat mov_x=PASSO, mov_z=0;
GLint angulo=0;
GLint wire = 0;
GLint inicia = 0;
GLuint texture; 

int id = 0;
glGenTextures(1, &id);
glBindTexture(GL_TEXTURE_2D, id);
lTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData); 
texture_id[];
texture_id[0] = 1;



/*labirinto */
GLint mapa[26][26] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                       1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,
                       1,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,1,1,1,1,0,1,1,1,
                       1,1,0,1,0,0,0,1,0,1,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,1,
                       1,0,0,1,1,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,1,1,1,1,
                       0,1,0,3,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,0,0,1,
                       0,0,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,0,1,
                       1,1,3,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,1,
                       1,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,1,1,
                       1,1,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,1,0,0,0,0,0,1,
                       1,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,1,1,0,1,
                       1,1,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,1,
                       1,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,
                       1,1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1,0,1,
                       1,1,0,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,
                       1,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,1,
                       1,1,1,1,0,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,
                       1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,
                       1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,
                       1,1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,1,0,0,0,1,
                       1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,
                       1,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,1,0,1,0,0,
                       1,1,0,1,1,1,1,1,0,1,0,1,0,1,1,1,1,1,1,1,0,1,0,1,0,1,
                       1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,
                       1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		       1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
                     };

//FUNCOES--------------------------------------------
int pode_mover(float pos_x, float pos_z, float vet_x, float vet_z)
{
    float mundo_x = pos_x + vet_x ;
    float mundo_z = pos_z + vet_z ;

    int ind_x = (int) ((mundo_x + TAM_BLOCO/2) / TAM_BLOCO);
    int ind_z = (int) ((mundo_z + TAM_BLOCO/2) / TAM_BLOCO);

    int casa = mapa[ind_x][ind_z];

    if(casa == 3){
        return 1;
    }else if(casa){
        return 0;
    }else{
        return 1;
    }

}


//---------------------------------------------------------------
unsigned GetTickCount()
{
    struct timeval tv;
    if(gettimeofday(&tv, NULL) != 0)
        return 0;

    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}
//---------------------------------------------------------------
void display(void)
{
    switch(inicia)
    {
    case 0:

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// limpa os pixels da tela

        glLoadIdentity();// Carrega a identidade

        glutSwapBuffers();
        break;
    case 1:
        int x, z;
        int x_mun, z_mun;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// limpa os pixels da tela

        glLoadIdentity();// Carrega a identidade

        gluLookAt(jog_x,25,jog_z, jog_x+mov_x,25,jog_z+mov_z, 0,1,0); // (visão do personagem)

        glPushMatrix(); //

        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_verde);
	
	
	glEnable( GL_TEXTURE_2D ); 
	glBindTexture (GL_TEXTURE_2D, 1);

        glBegin ( GL_QUADS);

	glTexCoord2f(0.0, 0.0);         
	glVertex3f(-10000, -TAM_BLOCO/2, -10000);
	glTexCoord2f(0.0, 1.0); 
        glVertex3f(-10000, -TAM_BLOCO/2, 10000);
	glTexCoord2f(1.0, 1.0); 
        glVertex3f(10000, -TAM_BLOCO/2, 10000);
	glTexCoord2f(1.0, 0.0); 
        glVertex3f(10000, -TAM_BLOCO/2, -10000);

        glEnd();

        glPopMatrix();



        for(x=0; x < 26; x++)
        {
            for(z=0; z < 26; z++)
            {
                if(mapa[x][z]) //tem um bloco
                {
                    x_mun = x * TAM_BLOCO;
                    z_mun = z * TAM_BLOCO;

                    //cubo grande
                    glPushMatrix();

                    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, luz_branca);
                    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
                    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

                    glTranslatef(x_mun, 5,z_mun);

                    int casa = mapa[x][z];

                    if(casa==3)
                    {
                        if(wire) glutWireSphere(10.0, 30,30);
                        else glutSolidSphere(10.0,30,30);
                    }else{
                         if(wire) glutWireCube(TAM_BLOCO);
                         else glutSolidCube(TAM_BLOCO);
                    }

                    glPopMatrix();


                }
            }//for
        }//for

        glutSwapBuffers();
        break;
    case 2:

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// limpa os pixels da tela

        glLoadIdentity();// Carrega a identidade

        glutSolidCube(TAM_BLOCO);

        glutSwapBuffers();
        break;

    }
}

//-----------------------------------------------------------------

void Keyboard_Function(unsigned char key, int x, int y)
{
    switch (key)
    {

    case  27:
        exit(0);
        break; //ESC -> encerra aplicativo...
    case 'w':
    case 'W':
        wire =!wire;
        glutPostRedisplay();
        break;

    case 'h':
    case 'H':
        inicia=2;
        glutPostRedisplay();
        break;

    case 32:
        inicia=1;
        glutPostRedisplay();
        break;
    case 13:
	inicia=1;
	contador=1;
	glutPostRedisplay();
	break;	

    }

}

//-----------------------------------------------------------------

void Special_Function(int key, int x, int y)
{
    float rad;

    switch (key)
    {
    case GLUT_KEY_DOWN:

        if(pode_mover(jog_x, jog_z, - mov_x, -mov_z))
        {
            jog_x -= mov_x;
            jog_z -= mov_z;
        }
        break;


    case GLUT_KEY_UP:

        if(pode_mover(jog_x, jog_z,  mov_x, mov_z))
        {
            jog_x += mov_x;
            jog_z += mov_z;
        }
        break;

    case GLUT_KEY_LEFT:

        angulo -= 10;

        if(angulo < 0) angulo +=360;


        rad =  (float) (3.14159 * angulo / 180.0f);

        mov_x =  cos(rad) * PASSO;
        mov_z =  sin(rad) * PASSO;
        break;


    case GLUT_KEY_RIGHT:

        angulo += 10;

        if(angulo >= 360) angulo -=360;

        rad =  (float) (3.14159 * angulo / 180.0f);

        mov_x = cos(rad) * PASSO;
        mov_z = sin(rad) * PASSO;

        break;

    }//fim do switch

}

//-----------------------------------------------------------------
void Move(void)
{
    glutPostRedisplay();
}

//-----------------------------------------------------------------

void Inicializa(void)
{

    glShadeModel(GL_SMOOTH);

    glClearColor(0.3, 0.6, 0.8, 0.0);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_branca);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luz_branca);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

//Especifica sistema de coordenadas de projecao
    glMatrixMode(GL_PROJECTION);
// Inicializa sistema de coordenadas de projecao
    glLoadIdentity();

//Especifica a projecao perspectiva
    gluPerspective(90,1,0.1,3000);

//Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);

// Inicializa sistema de coordenadas de projecao
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

// inicializa numeros aleatorios
    srand(GetTickCount());
}

//---------------------------------------------------------------
void free_mem(void)
{
    std::clog << "Exiting...\n";
}

//---------------------------------------------------------------
int main(int argc, char **argv)
{
    std::clog << "Begin...\n";

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Labirinto 3D");
    glutFullScreen();

    Inicializa();

    glutDisplayFunc(display);
    glutKeyboardFunc(Keyboard_Function);
    glutSpecialFunc(Special_Function);
    glutIdleFunc(Move);

    glutMainLoop();

    return 0;
}
