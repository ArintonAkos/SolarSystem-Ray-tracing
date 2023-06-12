#include "SolarSystemSkyBox.h"

SolarSystemSkyBox::SolarSystemSkyBox() : SkyBox(
{
	"Textures/SkyBox/right.jpg",
	"Textures/SkyBox/left.jpg",
	"Textures/SkyBox/top.jpg",
	"Textures/SkyBox/bottom.jpg",
	"Textures/SkyBox/front.jpg",
	"Textures/SkyBox/back.jpg"
})
{
}

void SolarSystemSkyBox::draw(const Camera* camera)
{
	glDepthMask(GL_FALSE);

	CubeMesh::draw(shader, camera);

	glDepthMask(GL_TRUE);
}