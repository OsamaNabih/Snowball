#ifndef SCENE_H
#define SCENE_H

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
	//glm::mat4 Extra;
	Model Object;
	Shader ourShader;
public:
	virtual bool CheckCollision(SceneObject* object)
	{
		return false;
	}
	SceneObject::SceneObject(string ObjectPath, Shader Shader) : Object(FileSystem::getPath(ObjectPath)), ourShader(Shader)
	{
	}

	void setTranslation(glm::vec3 trans)
	{
		glm::mat4 Identity;
		Translation = glm::translate(Identity, trans);
	}

	void setRotation(float angle, glm::vec3 Axes)
	{
		glm::mat4 Identity;
		Rotation = glm::rotate(Identity, angle, Axes);
	}

	void addRotation(float angle, glm::vec3 Axes)
	{
		Rotation = glm::rotate(Rotation, angle, Axes);
	}


	void setScaling(glm::vec3 Scales)
	{
		glm::mat4 Identity;
		Scaling = glm::scale(Identity, Scales);
	}

	//void setExtra(glm::mat4 Ex)
	//{
	//	Extra = Ex;
	//}

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

	//glm::mat4 getExtra()
	//{
	//	return Extra;
	//}

	void ResetRotation()
	{
		Rotation = glm::mat4();
	}

	void Draw()
	{
		sendModelToShader();
		Object.Draw(ourShader);
	}

	void sendModelToShader()
	{
		ourShader.use();
		glm::mat4 model = Translation * Scaling * Rotation;
		ourShader.setMat4("model", model);
		Object.Draw(ourShader);
	}

	SceneObject::~SceneObject()
	{
	}

};

#endif