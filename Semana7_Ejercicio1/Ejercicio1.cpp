
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h> // para malloc y free

GLuint texturaID[4];

void cargarTextura(const char * archivito, int ind) {

    // Cargar la imagen BMP
    FILE* archivo;
    errno_t err = fopen_s(&archivo, archivito, "rb");
    if (err != 0) {
        printf("Error: no se pudo abrir el archivo BMP\n");
        return;
    }

    // Leer el encabezado del archivo BMP (54 bytes)
    unsigned char encabezado[54];
    fread(encabezado, sizeof(unsigned char), 54, archivo);

    // Extraer ancho, alto y tamaño de la imagen del encabezado BMP
    int ancho = *(int*)&encabezado[18];
    int alto = *(int*)&encabezado[22];
    int tamanoImagen = *(int*)&encabezado[34];

    // Si el tamaño de la imagen no está presente, se calcula
    if (tamanoImagen == 0) tamanoImagen = ancho * alto * 3; // 3 = RGB (24 bits)

    // Leer los datos de la imagen

    unsigned char* data = (unsigned char*)malloc(tamanoImagen);
    fread(data, sizeof(unsigned char), tamanoImagen, archivo);
    fclose(archivo);

    // Generar la textura en OpenGL
    glGenTextures(1, &texturaID[ind]);
    glBindTexture(GL_TEXTURE_2D, texturaID[ind]);

    // Configurar la textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Enviar los datos de la imagen a OpenGL

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
    // Liberar memoria
    free(data);

}

void init() {

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_TEXTURE_2D); // Habilitar las texturas 2D
    cargarTextura("mi_textura.bmp",0);
    cargarTextura("mi_textura1.bmp", 1);
    cargarTextura("mi_textura2.bmp", 2);
    cargarTextura("mi_textura3.bmp", 3);// Cargar la textura
}

void display() {

    glClear(GL_COLOR_BUFFER_BIT);
    // Aplicar la textura (1ra textura)
    glBindTexture(GL_TEXTURE_2D, texturaID[0]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex2f(-1.0, 0.0); // Parte inferior izquierda
    glTexCoord2f(1.0, 0.0); glVertex2f(1.0, 0.0); // Parte inferior derecha
    glTexCoord2f(1.0, 1.0); glVertex2f(0.0, 1.0);  // Parte superior derecha
    glTexCoord2f(0.0, 1.0); glVertex2f(-1.0, 1.0); // Parte superior izquierda
    glEnd();

    //Aplicar la textura(2da textura)
    glBindTexture(GL_TEXTURE_2D, texturaID[1]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex2f(0.0, 0.0); // Parte inferior izquierda
    glTexCoord2f(1.0, 0.0); glVertex2f(1.0, 0.0); // Parte inferior derecha
    glTexCoord2f(1.0, 1.0); glVertex2f(1.0, 1.0);  // Parte superior derecha
    glTexCoord2f(0.0, 1.0); glVertex2f(0.0, 1.0); // Parte superior izquierda
    glEnd();

    //Aplicar la textura(3ra textura)
    glBindTexture(GL_TEXTURE_2D, texturaID[2]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex2f(-1.0, -1.0); // Parte inferior izquierda
    glTexCoord2f(1.0, 0.0); glVertex2f(0.0, -1.0); // Parte inferior derecha
    glTexCoord2f(1.0, 1.0); glVertex2f(0.0, 0.0);  // Parte superior derecha
    glTexCoord2f(0.0, 1.0); glVertex2f(-1.0, 0.0); // Parte superior izquierda
    glEnd();

    //Aplicar textura(4ta textura)
    glBindTexture(GL_TEXTURE_2D, texturaID[3]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex2f(0.0, -1.0); // Parte inferior izquierda
    glTexCoord2f(1.0, 0.0); glVertex2f(1.0, -1.0); // Parte inferior derecha
    glTexCoord2f(1.0, 1.0); glVertex2f(1.0, 0.0);  // Parte superior derecha
    glTexCoord2f(0.0, 1.0); glVertex2f(0.0, 0.0); // Parte superior izquierda
    glEnd();

    glutSwapBuffers();

}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Texturas");
    init();

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}