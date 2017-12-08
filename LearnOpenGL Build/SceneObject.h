#ifndef SCENE_H
#define SCENE_H

//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <learnopengl/filesystem.h>
#include <learnopengl/model.h>

class SceneObject
{
	glm::mat4 Translation;
	glm::mat4 Scaling;
	glm::mat4 Rotation;
	glm::mat4 Extra;
public:
	virtual bool CheckCollision(SceneObject* object)
	{
		return false;
	}
	SceneObject::SceneObject(string ObjectPath)
	{
		Model Object(FileSystem::getPath(ObjectPath));
	}

	void setTranslation(glm::mat4 Trans)
	{
		Translation = Trans;
	}

	void setRotation(glm::mat4 Rot)
	{
		Rotation = Rot;
	}

	void setScaling(glm::mat4 Scal)
	{
		Scaling = Scal;
	}

	void setExtra(glm::mat4 Ex)
	{
		Extra = Ex;
	}

	glm::mat4 getTranslation()
	{
		return Translation;
	}

	glm::mat4 getRotation()
	{
		return Rotation;
	}

	glm::mat4 getScaling()
	{
		return Scaling;
	}

	glm::mat4 getExtra()
	{
		return Extra;
	}

	SceneObject::~SceneObject()
	{
	}

};

#endif