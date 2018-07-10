#ifndef __STAGE_H
#define __STAGE_H
#endif

#include <vector>

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
private:
	std::vector<Object*> _objects;
	Canvas* _canvas;
	Camera* _camera;
	AppWindow* _window;//a stage must be set in a window, this parameter shows
		//its parent window
public:
	Stage(AppWindow* w);
	~Stage();
	
	virtual void step()=0;
private:
	//banned
	Stage();
	Stage(Stage &);
	Stage(Stage &&);
	Stage(Stage *);
};