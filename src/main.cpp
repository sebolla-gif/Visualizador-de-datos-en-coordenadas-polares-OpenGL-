#include <iostream>
#include <windows.h>
#include <GL/glut.h>
#include <cmath>

// Definici�n de constantes
#define M_PI 3.1416f

// Estructura para almacenar los datos polares
struct PolarData
{
    unsigned long int* numbers;
    unsigned long count;
    float* vertices;
};

// Variables globales
namespace
{
float zoom = 1.0f;
float offsetX = 0.0f, offsetY = 0.0f;
PolarData* polarData = nullptr;
int screenWidth, screenHeight;
}

// Funci�n para cargar los datos del archivo
PolarData* LoadPolarData()
{
    PolarData* data = new PolarData();
    FILE* f = fopen("400k.bin", "rb");
    if (f)
    {
        fseek(f, 0, SEEK_END);
        long size = ftell(f);
        rewind(f);

        data->count = size / sizeof(unsigned long int);
        data->numbers = new unsigned long int[data->count];
        fread(data->numbers, sizeof(unsigned long int), data->count, f);
        fclose(f);

        // Precalcular v�rtices
        data->vertices = new float[data->count * 2];
        for (unsigned long i = 0; i < data->count; ++i)
        {
            double theta = data->numbers[i];
            double r = data->numbers[i];
            data->vertices[i * 2] = static_cast<float>(r * cos(theta));
            data->vertices[i * 2 + 1] = static_cast<float>(r * sin(theta));
        }

        return data;
    }
    delete data;
    return nullptr;
}

// Funci�n de limpieza
void Cleanup()
{
    if (polarData)
    {
        delete[] polarData->numbers;
        delete[] polarData->vertices;
        delete polarData;
        polarData = nullptr;
    }
}

// Funci�n de renderizado
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    glScalef(zoom, zoom, 1.0);
    glTranslatef(offsetX, offsetY, 0.0);

    // Dibujado de puntos (sin VBOs)
    glColor3f(0, 1, 0);
    glPointSize(0.1f);
    glBegin(GL_POINTS);
    for (unsigned long i = 0; i < polarData->count; ++i)
    {
        glVertex2f(polarData->vertices[i * 2], polarData->vertices[i * 2 + 1]);
    }
    glEnd();

    glPopMatrix();
    glutSwapBuffers();
}

// Funci�n para manejar teclas
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '+': // Aumentar zoom
        zoom *= 1.2f;
        break;
    case '-': // Reducir zoom
        zoom /= 1.2f;
        break;
    case 'w': // Mover hacia arriba
        offsetY += 10.1f / zoom;
        break;
    case 's': // Mover hacia abajo
        offsetY -= 10.1f / zoom;
        break;
    case 'a': // Mover hacia la izquierda
        offsetX -= 10.1f / zoom;
        break;
    case 'd': // Mover hacia la derecha
        offsetX += 10.1f / zoom;
        break;
    case 27: // Esc para salir
        Cleanup();
        exit(0);
        break;
    }
    glutPostRedisplay();
}

// Funci�n para manejar el mouse
void mouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN)
    {
        if (button == GLUT_LEFT_BUTTON)
        {
            zoom *= 1.1f; // Zoom in
        }
        else if (button == GLUT_RIGHT_BUTTON)
        {
            zoom /= 1.1f; // Zoom out
        }
        glutPostRedisplay();
    }
}

// Funci�n principal
int main(int argc, char* argv[])
{
    // Inicializar GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Patron Primo Optimizado");

    // Precargar datos
    polarData = LoadPolarData();
    if (!polarData)
    {
        std::cerr << "Error loading data!" << std::endl;
        return 1;
    }

    // Configuraci�n de proyecci�n
    screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    screenHeight = glutGet(GLUT_SCREEN_HEIGHT);
    gluOrtho2D(-screenWidth / 2, screenWidth / 2, -screenHeight / 2, screenHeight / 2);

    // Configurar callbacks
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    atexit(Cleanup); // Limpieza autom�tica al salir

    // Color de fondo
    glClearColor(0, 0, 0, 0);

    // Iniciar el bucle principal
    glutMainLoop();
    return 0;
}
