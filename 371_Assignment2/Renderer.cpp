#include "Renderer.h"

Renderer *Renderer::instance = 0;


Renderer * Renderer::getInstance() {
	if (!instance) {
		instance = new Renderer();
	}
	return instance;
}

void Renderer::render() {

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(VAO);

	if (renderMode == POINTS) {
		glDrawArrays(GL_POINTS, 0, vertices.size());
	}
	else if (renderMode == LINES) {
		glDrawArrays(GL_LINE_STRIP, 0, vertices.size());
	}

	glBindVertexArray(0);

}

void Renderer::updateBuffer(std::vector<glm::vec3> newVertices) {

	vertices = newVertices;

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Renderer::setRenderMode(RenderMode mode) {
	renderMode = mode;
}

void Renderer::terminate() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	instance = 0;
}

Renderer::Renderer() {

	shader = new Shader("res/shaders/vertex.shader", "res/shaders/fragment.shader");
	shader->use();

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);;
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	renderMode = POINTS;
}