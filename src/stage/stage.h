#ifndef __STAGE_H
#define __STAGE_H
#endif

#include <vector>
#include <glm/mat4x4.hpp>
#include "../object/manager/LightManager.h"

#define STAGE_NAME_VIEWPOS "viewPos"
#define STAGE_NAME_VIEWDIR "viewDir"
#define STAGE_NAME_PROJECTION "projection"
#define STAGE_NAME_VIEW "view"

class Camera;
class Object;
class Canvas;
class AppWindow;
class Light;
/** @class Stage
* @brief a conatiner of objects
* 1. Stage
A stage is composed of Objects and one canvas, with which Objects can draw on it.
In order to observe the whole stage, a Camera is also needed.

* 2. Lights managing
User(coder) can use the interfaces of LightManager to manage lights, LightManager
gives out the interfaces of controlling lights, and also the interfaces of getting
light informations.
There are three kind of lights defined, which are ambient(dir), point as well as
spotlight. Only one dir light is allowed in one stage, and up-to 16 point lights and
sopt lights are allowed. Also no light is allowed.
Use Stage->manageLights()->... to control the lights of this stage.

* @exaplmples
   class TS: public Stage{
   public: 
		TS(AppWindow *w):Stage(w){
		_canvas = new Canvas(0.0f, 0.0f, 0.0f);
		_camera = new Camera();
		setPerspective(45.0f, (float)w->getClientWidth() / (float)w->getClientHeight(), 0.1f, 100.0f);
		//Add Lights
		_lightmanager.addLight(..., "ambient");
		//Add Objects
		...
		}
		void paint(){...}//draw objects here
		void loop(){...]//loop here
	}
*/
class Stage {
	friend class AppWindow;
protected:
	std::vector<Object*> _objects;//Objects, alternative
	Canvas* _canvas;//Canvas, must have one
	Camera* _camera;//Camera, more than one
	LightManager _lightmanager;//Light Manager提供光照管理接口
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

	inline glm::mat4& getProjection() { return _projection; }
	const glm::mat4& getView();
	
	//获取当前视点
	const glm::vec3& getViewPoint();
	
	//获取当前视角
	const glm::vec3& getViewDir();

	//获得光照管理器
	LightManager& manageLights() { return _lightmanager; }

	virtual void paint() = 0;
	virtual void loop() = 0;
private:
	//banned
	Stage();
	Stage(Stage &);
	Stage(Stage &&);
	Stage(Stage *);

	//Input Process
	virtual void _inputProcess() = 0;
	void draw();
	void step();
};