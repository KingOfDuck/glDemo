/** @filename drawer.cpp
* @brief Graphics tools
* @created 2018/09/25
*/
#include "drawer.h"
#include "shader.h"
#include "../Model.h"
#include "../object.h"
#include "../../stage/stage.h"
#include "../../glDemo.h"

Drawer::Drawer(Entity *obj):_obj(obj){
}

Drawer* Drawer::CreateDrawer(Entity* obj) {
	switch (glDemoApp::APP_GRAPHICS_MODE) {
	case OPENGL_3_0:
		return new GLDrawer(obj);
	default:
		//TODO: LOG ERROR GRAPHICS MODE
		return NULL;
	}
}

GLDrawer::GLDrawer(Entity *_obj) : Drawer(_obj),_shader(NULL) {
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	_ebo = -1;
}

GLDrawer::~GLDrawer() {
	glDeleteBuffers(1, &_vbo);
	glDeleteVertexArrays(1, &_vao);
	if (_ebo != -1) {
		glDeleteBuffers(1, &_ebo);
	}
	if (_shader)
		free(_shader);
}

void GLDrawer::draw() {
	if (!_shader) {
		//TODO: Log Object do not have a shader?
		return;
	}
	glBindVertexArray(_vao);
	_shader->use();
	_obj->paint();//调用Object的paint方法，由用户自定义绘图参数和方式
	glBindVertexArray(0);
}

void GLDrawer::gl_setFormat(void* vertices, GLsizeiptr vsize, std::vector<int> oneLineFormat,
	unsigned int* indices, GLsizeiptr isize){
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, vsize, vertices, GL_STATIC_DRAW);

	int sum = 0;
	for (int i = 0; i < oneLineFormat.size(); ++i) {
		sum += oneLineFormat[i];
	}

	int total = 0;
	for (int i = 0; i < oneLineFormat.size(); ++i) {
		glVertexAttribPointer(i, oneLineFormat[i], GL_FLOAT, GL_FALSE, sum * sizeof(float), (void*)(total * sizeof(float)));
		total += oneLineFormat[i];
		glEnableVertexAttribArray(i);
	}

	if (indices) {
		if (_ebo == -1) {
			glGenBuffers(1, &_ebo);
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, isize, indices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	glBindVertexArray(0);
}

void GLDrawer::gl_setShader(const char* vertshader, const char* fragshader) {
	_shader = Shader::LoadFromFile(vertshader, fragshader);
}

void GLDrawer::gl_drawMesh(Mesh* mesh) {
	if (!_shader) {
		//TODO: Log Object do not have a shader?
		return;
	}
	glBindVertexArray(_vao);
	_shader->use();
	/*
	uniform DirLight dirLight;//环境光
	uniform PointLight pointLights[MAX_POINTLIGHT];//预先开辟点光源空间
	uniform SpotLight spotLights[MAX_SPOTLIGHT];//预先开辟聚光空间

	uniform int npointlight;//点光源数目
	uniform int nspotlight;//聚光数目
	uniform int hasdirlight;//是否有环境光
	*/
	//views
	_shader->setParameter(STAGE_NAME_VIEWPOS, mesh->_pModel->_stage->getViewPoint());
	_shader->setParameter(STAGE_NAME_VIEWDIR, mesh->_pModel->_stage->getViewDir());
	//Materials
	unsigned int diffuseNr = 0;
	unsigned int specularNr = 0;

	for (unsigned int i = 0; i < mesh->_textures->size(); ++i) {
		(*(mesh->_textures))[i].use(GL_TEXTURE0 + i);
		if ((*(mesh->_textures))[i].getType() == Texture::type::diffuse) {
			_shader->setParameter((std::string(OBJECT_NAME_MATERIAL) + OBJECT_ATTR_DIFFTEX
				+ '[' + std::to_string(diffuseNr++) + ']'), (int)i);
		}
		else if ((*(mesh->_textures))[i].getType() == Texture::type::specular) {
			_shader->setParameter((std::string(OBJECT_NAME_MATERIAL) + OBJECT_ATTR_SPECTEX +
				'[' + std::to_string(specularNr++) + ']'), (int)i);
		}
	}
	//glActiveTexture(GL_TEXTURE0);

	_shader->setParameter(std::string(OBJECT_NAME_MATERIAL) + OBJECT_ATTR_USETEXTURE, true);
	_shader->setParameter(std::string(OBJECT_NAME_MATERIAL) + OBJECT_ATTR_NUMDIFFTEX, (int)diffuseNr);
	_shader->setParameter(std::string(OBJECT_NAME_MATERIAL) + OBJECT_ATTR_NUMSPECTEX, (int)specularNr);
	_shader->setParameter(std::string(OBJECT_NAME_MATERIAL) + OBJECT_ATTR_SHININESS, 16.0f);

	//matrix
	_shader->setParameter(STAGE_NAME_PROJECTION, mesh->_pModel->_stage->getProjection());
	_shader->setParameter(STAGE_NAME_VIEW, mesh->_pModel->_stage->getView());
	_shader->setParameter(OBJCET_NAME_MODEL, mesh->_pModel->_model);
	//lights

	_shader->setAmbientLight(mesh->_pModel->_stage->manageLights().getAmbientLight());
	_shader->setPointLight(mesh->_pModel->_stage->manageLights().getPointLight());
	_shader->setSpotLight(mesh->_pModel->_stage->manageLights().getSpotLight());

	// 绘制网格
	glDrawElements(GL_TRIANGLES, (int)(*(mesh->_indices)).size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}
