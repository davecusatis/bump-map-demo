#include<cpuPositionOffset.h>
#include<DSMGL\Framework.h>

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

void computePositionOffsets(float &fxoffset, float &fyoffset)
{
	const float LOOP_DURATION = 5.0f;
	const float SCALE = 3.14159*2.0 / LOOP_DURATION;

	float elapsedTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	float currentLoopTime = fmodf(elapsedTime, LOOP_DURATION);

	fxoffset = cosf(currentLoopTime * SCALE) * 0.5;
	fyoffset = sinf(currentLoopTime * SCALE) * 0.5;
}

void adjustVertexData(float* vertexPositions, GLuint bufferObject, float fxoffset, float fyoffset)
{
	std::vector<float> newData(ARRAY_COUNT(vertexPositions));
	memcpy(&newData[0], vertexPositions, sizeof(vertexPositions));

	for (int i = 0; i < ARRAY_COUNT(vertexPositions); i += 4)
	{
		newData[i] += fxoffset;
		newData[i + 1] += fyoffset;
	}

	glBindBuffer(GL_ARRAY_BUFFER, bufferObject);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexPositions), &newData[0]);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);
}
