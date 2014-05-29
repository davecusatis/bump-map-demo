// #if ( (defined(__MACH__)) && (defined(__APPLE__)) )   
// #include <stdlib.h>
// #include <OpenGL/gl.h>
// #include <GLUT/glut.h>
// #include <OpenGL/glext.h>
// #else
// #include <stdlib.h>
// #include <GL/glew.h>
// #include <GL/gl.h>
// #include <GL/glut.h>
// #include <GL/glext.h>
// #endif
// #include “shader.h”
Shader shader;  
  
GLuint texture;  
GLuint normal_texture; // Our normal map texture  
  
  
GLuint LoadTexture( const char * filename, int width, int height )  
{  
GLuint texture;  
unsigned char * data;  
FILE * file;  
  
//The following code will read in our RAW file  
file = fopen( filename, "rb" );  
  
if ( file == NULL ) return 0;  
data = (unsigned char *)malloc( width * height * 3 );  
fread( data, width * height * 3, 1, file );  
  
fclose( file );  
  
glGenTextures( 1, &texture ); //generate the texture with the loaded data  
glBindTexture( GL_TEXTURE_2D, texture ); //bind the texture to it’s array  
  
glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE ); //set texture environment parameters  
  
//And if you go and use extensions, you can use Anisotropic filtering textures which are of an  
//even better quality, but this will do for now.  
glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  
  
glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  
  
//Here we are setting the parameter to repeat the texture instead of clamping the texture  
//to the edge of our shape.  
glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );  
glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );  
  
//Generate the texture  
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);  
  
free( data ); //free the texture  
  
return texture; //return whether it was successfull  
}  
void FreeTexture( GLuint texture )  
{  
glDeleteTextures( 1, &texture );  
}  
  
void init(void) {  
glEnable(GL_DEPTH_TEST);  
glDepthFunc(GL_LESS);  
  
#if ( (defined(__MACH__)) && (defined(__APPLE__)) )  
#else  
glewInit();  
#endif  
  
shader.init("shader.vert", "shader.frag");  
  
texture = LoadTexture("colour_map.raw", 256, 256);  
normal_texture = LoadTexture("normal_map.raw", 256, 256);  
}  
  
void cube (void) {  
	glActiveTexture(GL_TEXTURE0);  
	glEnable(GL_TEXTURE_2D);  
	int texture_location = glGetUniformLocation(shader.id(), "color_texture");  
	glUniform1i(texture_location, 0);  
	glBindTexture(GL_TEXTURE_2D, texture);  
	  
	glActiveTexture(GL_TEXTURE1);  
	glEnable(GL_TEXTURE_2D);  
	int normal_location = glGetUniformLocation(shader.id(), "normal_texture");  
	glUniform1i(normal_location, 1);  
	glBindTexture(GL_TEXTURE_2D, normal_texture);  
	  
	glBegin(GL_QUADS);  
	glTexCoord2f(0.0f, 0.0f);  
	glVertex3f(-1.0f, -1.0f, 0.0f);  
	  
	glTexCoord2f(1.0f, 0.0f);  
	glVertex3f(1.0f, -1.0f, 0.0f);  
	  
	glTexCoord2f(1.0f, 1.0f);  
	glVertex3f(1.0f, 1.0f, 0.0f);  
	  
	glTexCoord2f(0.0f, 1.0f);  
	glVertex3f(-1.0f, 1.0f, 0.0f);  
	glEnd();  
	  
	glActiveTexture(GL_TEXTURE1);  
	glBindTexture(GL_TEXTURE_2D, 0);  
	glDisable(GL_TEXTURE_2D);  
	  
	glActiveTexture(GL_TEXTURE0);  
	glBindTexture(GL_TEXTURE_2D, 0);  
	glDisable(GL_TEXTURE_2D);  
}  
  
void display (void) {  
glClearColor (0.0,0.0,0.0,1.0);  
glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
glLoadIdentity();  
  
gluLookAt (0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);  
  
shader.bind();  
cube();  
shader.unbind();  
  
glutSwapBuffers();  
}  
  
void reshape (int w, int h) {  
glViewport (0, 0, (GLsizei)w, (GLsizei)h);  
glMatrixMode (GL_PROJECTION);  
glLoadIdentity ();  
gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);  
glMatrixMode (GL_MODELVIEW);  
}  
  
// int main (int argc, char **argv) {  
// glutInit(&argc, argv);  
// glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); //set up the double buffering  
// glutInitWindowSize(500, 500);  
// glutInitWindowPosition(100, 100);  
// glutCreateWindow("A basic OpenGL Window");  
  
// init();  
  
// glutDisplayFunc(display);  
// glutIdleFunc(display);  
  
// glutReshapeFunc(reshape);  
  
// glutMainLoop();  
  
// return 0;  
// }  