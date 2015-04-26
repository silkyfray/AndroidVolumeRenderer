// WindowsVolumeRenderer.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include "Common.h"
#include "File.h"
#include "Volume.h"
#include "Camera.h"
#include "Timer.h"
#include "Mesh.h"
#include "ShaderManager.h"
#include "TransferFunction.h"
#include "GLFWRenderer.h"
#include <octree.h>

#pragma region VolumeDeclarations 
Mesh mesh; // gio would be proud of the pragma regions !
Shader *basicShader, *raycastVRShader;
Volume volume;
TransferFunction transferFn;
GLFWRenderer renderer;
#pragma endregion


#pragma region FunctionPrototypes
void updateCallback();
#pragma endregion
Shader* textureBasedVRShader;

int main(int argc, char* argv[])
{


	basicShader = ShaderManager::get().getShader(File("","basicVS.glsl"), File("","basicFS.glsl"));
	raycastVRShader = ShaderManager::get().getShader(File("", "raycastVRShaderVS.glsl"), File("", "raycastVRShaderFS.glsl"));
	textureBasedVRShader = ShaderManager::get().getShader(File("", "textureBasedVRShaderVS.glsl"), File("", "textureBasedVRShaderFS.glsl"));
	mesh.generateCube(raycastVRShader);
	mesh.transform.scaleUniform(MESH_SCALE);

	volume.parseMHD(File("",VOLUME_NAME));
	//volume.parsePVM(File("","Box.pvm"));
	//File temp = File("","Box.pvm");
	//temp.print();
	volume.printProperties();
	volume.generate();

	transferFn.parseVoreenXML(File("",TRANSFER_FN_NAME));
	transferFn.generate();
	

	renderer.setUpdateCallback(updateCallback);
	renderer.mainLoop();


	return 0;
}

void updateCallback()
{
	volume.advance();
	//glm::mat4 MVP = camera.GetProjectionMatrix() * camera.GetViewMatrix() * mesh.transform.getMatrix();
	//glm::vec3 cameraPos = glm::vec3(camera.GetViewMatrix()[3]);
	/* Render here */
	float delta = Timer::get().getLastInterval();
	//mesh.transform.pivotOnLocalAxis(0, 0.02 * delta, 0);
	renderer.renderBasic(basicShader, mesh, renderer.m_camera.GetProjectionMatrix() * renderer.m_camera.GetViewMatrix() * mesh.transform.getMatrix(), true);
	//float delta = Timer::get().getLastInterval();
	//mesh.transform.pivotOnLocalAxis(0,0.001, 0);
	

	//renderer.renderRaycastVR(raycastVRShader, mesh, volume, MAX_RAY_STEPS, RAY_STEP_SIZE, GRADIENT_STEP_SIZE, LIGHT_POS, transferFn);
	renderer.renderTextureBasedVR(textureBasedVRShader, mesh, volume, MAX_RAY_STEPS, transferFn);


}


