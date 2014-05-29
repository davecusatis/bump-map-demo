#include<DSMGL\Framework.h>
#include<DSMGL\Graphics.h>
#include<DSMGL\Input.h>
#include<DSMGL\Shader.h>

Graphics engine;
Shader   noiseShader;
Shader   lightShader;
Shader	 bumpShader;
Shader	 putsShader;
Texture	 mopTex;
Texture  background;
Texture	 bonesTex;
Texture  bonesNMTex;


GLfloat diffuseValues[] = { 1.0, 1.0, 1.0 };
GLfloat	ambientValues[] = { 0.0, 0.0, 0.0 };
GLfloat lightingPos[]	= { 1.0, 1.5, 1.5, 0.0 };

int texture_location;
int normal_location;

int i = 0;

const float vertexData[] = {
	0.25f, 0.25f, -1.25f, 1.0f,
	0.25f, -0.25f, -1.25f, 1.0f,
	-0.25f, 0.25f, -1.25f, 1.0f,

	0.25f, -0.25f, -1.25f, 1.0f,
	-0.25f, -0.25f, -1.25f, 1.0f,
	-0.25f, 0.25f, -1.25f, 1.0f,

	0.25f, 0.25f, -2.75f, 1.0f,
	-0.25f, 0.25f, -2.75f, 1.0f,
	0.25f, -0.25f, -2.75f, 1.0f,

	0.25f, -0.25f, -2.75f, 1.0f,
	-0.25f, 0.25f, -2.75f, 1.0f,
	-0.25f, -0.25f, -2.75f, 1.0f,

	-0.25f, 0.25f, -1.25f, 1.0f,
	-0.25f, -0.25f, -1.25f, 1.0f,
	-0.25f, -0.25f, -2.75f, 1.0f,

	-0.25f, 0.25f, -1.25f, 1.0f,
	-0.25f, -0.25f, -2.75f, 1.0f,
	-0.25f, 0.25f, -2.75f, 1.0f,

	0.25f, 0.25f, -1.25f, 1.0f,
	0.25f, -0.25f, -2.75f, 1.0f,
	0.25f, -0.25f, -1.25f, 1.0f,

	0.25f, 0.25f, -1.25f, 1.0f,
	0.25f, 0.25f, -2.75f, 1.0f,
	0.25f, -0.25f, -2.75f, 1.0f,

	0.25f, 0.25f, -2.75f, 1.0f,
	0.25f, 0.25f, -1.25f, 1.0f,
	-0.25f, 0.25f, -1.25f, 1.0f,

	0.25f, 0.25f, -2.75f, 1.0f,
	-0.25f, 0.25f, -1.25f, 1.0f,
	-0.25f, 0.25f, -2.75f, 1.0f,

	0.25f, -0.25f, -2.75f, 1.0f,
	-0.25f, -0.25f, -1.25f, 1.0f,
	0.25f, -0.25f, -1.25f, 1.0f,

	0.25f, -0.25f, -2.75f, 1.0f,
	-0.25f, -0.25f, -2.75f, 1.0f,
	-0.25f, -0.25f, -1.25f, 1.0f,




	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,

	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,

	0.8f, 0.8f, 0.8f, 1.0f,
	0.8f, 0.8f, 0.8f, 1.0f,
	0.8f, 0.8f, 0.8f, 1.0f,

	0.8f, 0.8f, 0.8f, 1.0f,
	0.8f, 0.8f, 0.8f, 1.0f,
	0.8f, 0.8f, 0.8f, 1.0f,

	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,

	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,

	0.5f, 0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f,

	0.5f, 0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f,

	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,

	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,

	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,

	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,

};

void resize(int w, int h)
{
	engine.resize(w, h);
}
void genBuffer(GLuint bufferRef, GLuint BUFFER_TYPE_ENUM, float* vertexData, GLuint GL_DRAW_TYPE_ENUM)
{
	glGenBuffers(1, &bufferRef);
	glBindBuffer(BUFFER_TYPE_ENUM, bufferRef);
	glBufferData(BUFFER_TYPE_ENUM, sizeof(vertexData), vertexData, GL_DRAW_TYPE_ENUM);
	glBindBuffer(BUFFER_TYPE_ENUM, NULL);
}

//void somethingNeat(void)
//{
//	GLuint	 vertices;
//	int textureLocation;
//	float vertexPos[] = {
//		0.75, 0.75, 0.0, 1.0,
//		0.75, -0.75, 0.0, 1.0,
//		-0.75, -0.75, 0.0, 1.0
//	};
//
//	genBuffer(vertices, GL_ARRAY_BUFFER, vertexPos, GL_STATIC_DRAW);
//}
// for puts action
//void testDisplay(void)
//{
//	//engine.putS(bonesTex, { 0, 0, 0 }, 0, 1);
//	GLuint vertices;
//	int textureLocation;
//	float vertexPos[] = {
//		0.75, 0.75, 0.0, 1.0,
//		0.75, -0.75, 0.0, 1.0,
//		-0.75, -0.75, 0.0, 1.0
//	};
//
//	genBuffer(vertices, GL_ARRAY_BUFFER, vertexPos, GL_STATIC_DRAW);
//
//	
//
//	putsShader.bind();
//	glActiveTexture(GL_TEXTURE0);
//	glEnable(GL_TEXTURE_2D);
//	bonesTex.bindTexture();
//
//	textureLocation = glGetUniformLocation(putsShader.id(), "color_texture");
//	glUniform1i(textureLocation, 0);
//	
//
//	glMatrixMode(GL_PROJECTION);
//		glPushMatrix();
//		glLoadIdentity();
//		gluOrtho2D(0, engine.getWindowWidth(), engine.getWindowHeight(), 0);
//
//		glMatrixMode(GL_MODELVIEW);
//		glLoadIdentity();
//
//		glBegin(GL_QUADS);
//			glTexCoord2f(0, 0);	glVertex3f(-1, -1, 0);
//			glTexCoord2f(1, 0); glVertex3f(1, -1, 0);
//			glTexCoord2f(1, 1);	glVertex3f(1, 1, 0);
//			glTexCoord2f(0, 1);	glVertex3f(-1, 1, 0);
//		glEnd();
//
//		glPopMatrix();
//	glPopMatrix();
//
//	bonesTex.unbindTexture();
//	putsShader.unbind();
//}

void bumpDisplay(void)
{
	engine.clearDisplay();
	glLoadIdentity();
	glLightfv(GL_LIGHT0, GL_POSITION, lightingPos);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	/*noiseShader.bind();
	glBindBuffer(GL_ARRAY_BUFFER, vertices);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
	noiseShader.unbind();*/

	bumpShader.bind();

	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	texture_location = glGetUniformLocation(bumpShader.id(), "color_texture");
	glUniform1i(texture_location, 0);
	glBindTexture(GL_TEXTURE_2D, bonesTex.getTextureID());

	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);
	normal_location = glGetUniformLocation(bumpShader.id(), "normal_texture");
	glUniform1i(normal_location, 1);
	glBindTexture(GL_TEXTURE_2D, bonesNMTex.getTextureID());


	glBegin(GL_QUADS);
		glTexCoord2f(0, 0);	glVertex3f(-1, -1, 0);
		glTexCoord2f(1, 0); glVertex3f( 1, -1, 0);
		glTexCoord2f(1, 1);	glVertex3f( 1,  1, 0);
		glTexCoord2f(0, 1);	glVertex3f(-1,  1, 0);
	glEnd();

	// for noise -- refresh screen on interval for realism
	/*if (i % 50 == 0 || i == 0)
		engine.flushAndSwapBuffers();*/

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	bumpShader.unbind();
	
	engine.flushAndSwapBuffers();
}

void motionHandler(int x, int y)
{
	float temp[] = { x/(float)engine.getWindowWidth(), y/(float)engine.getWindowHeight(), 1.5, 0 };
	memcpy(lightingPos, temp, 4);
	printf("%f, %f\n", x / (float)engine.getWindowWidth(), y / (float)engine.getWindowHeight());
}

void main(int argc, char** argv)
{
	engine.initEngine(argc, argv, 600, 600, 0, 0, "SHADER ACTION");
	engine.initGlutFuncs(bumpDisplay, resize, Input::MouseButtonClick, Input::MouseDrag, Input::MopControls);
	glutIdleFunc(bumpDisplay);
	glutPassiveMotionFunc(motionHandler);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	
	// init shaders
	bumpShader.init("bumpShader.vert", "bumpShader.frag");
	// textures
	bonesTex.loadTexture("Resources/Images/Bones1 (2).jpg", 1024, 768);
	bonesNMTex.loadTexture("Resources/Images/Bones.jpg_normalmap1.jpg", 1024, 768);
	
	engine.startMainLoop();
	
}