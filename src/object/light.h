#ifndef __LIGHT_H
#define __LIGHT_H

#include "object.h"
#include <glm/vec3.hpp>
/* Light Class (interface)
 * Light is a drawble object, but you can choose to draw the light source object or not.
 * If no vertices are given, the light source object won't be rendered, you cannot see where the light is.
 * But the light color will still act on objects.
 * @WARNING CANNOT be used directly, implement(PUBLIC) Light class and override the functions
 * @void draw()
 * @void step()
*/ 
class Light : public drawObject{
protected:
	glm::vec3 _lightColor;
	float _ambient;//ambient strength, 0 when the light is NOT used as ambient, 
public:
	Light(float* vertices = NULL, int nvert = 0, Stage *s = NULL);

	//Set the light as Ambient Light
	//@isAmbient false mean this Light is not used as Ambient Light
	//@strength Ambient Light strength, activated when @isAmbient = true
	void setAmbient(bool isAmbient = false, float strength = 0.0f);

	void setColor(float red, float green, float blue);
	//Check if the light is used as Ambient
	inline bool isAmbient() { return _ambient == 0.0f; }
	inline float getAmbientStrength() { return _ambient; }
	inline glm::vec3& getLightColor() { return _lightColor; }

	virtual void step() = 0;
	virtual void paint() = 0;
private:
	Light();
};
#endif