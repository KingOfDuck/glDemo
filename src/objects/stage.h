#ifndef __STAGE_H
#define __STAGE_H
#endif

#include <vector>
#include <glm/mat4x4.hpp>

class Camera;
class Object;
class Canvas;
class AppWindow;
//stage class, a container of one single scene
/*
A stage is composed of Objects and one canvas, with
which Objects can draw on it. In order to observe the whole
stage, a Camera is also needed.

*/
class Stage {
protected:
	std::vector<Object*> _objects;//Objects, alternative
	Canvas* _canvas;//Canvas, must have one
	Camera* _camera;//Camera, more than one
	glm::mat4 _projection;

	AppWindow* _window;//a stage must be set in a window, this parameter shows
		//its parent window
public:
	Stage(AppWindow* w);
	~Stage();
	
	//Stage is the CONTROLLER of all the objects, including movements, textures, colors
	//and so on.

	//设置透视投影
	void setPerspective(float fieldOfView,float aspectRatio, float Near, float far);
	inline glm::mat4& getProjection() {
		return _projection;
	}
	glm::mat4& getView();

	virtual void step() = 0;
	virtual void draw();
private:
	//banned
	Stage();
	Stage(Stage &);
	Stage(Stage &&);
	Stage(Stage *);

	//Input Process
	virtual void _inputProcess() = 0;
};