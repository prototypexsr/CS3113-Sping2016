#include "Projectile.h"
#include "Matrix.h"
#include "ShaderProgram.h"
#include "Vector.h"



Projectile::Projectile(Matrix& modelMatrix, Matrix& projectionMatrix, Matrix& viewMatrix){
	model = modelMatrix;
	projection = projectionMatrix;
	view = viewMatrix;
	YPos = -1.5;
	remove = false;

	position.x = 0.0;
	position.y = -1.5;
	position.z = 0.0;
	
	acceleration.x = 0.5;
	acceleration.y = 0.5;
	acceleration.z = 0.0;
	velocity.x = 1.0;
	velocity.y = 1.0;
	velocity.z = 0.0;
	/*float vertices[] = { -0.04, -0.04,
		0.04, -0.04,
		0.04, 0.04,
		-0.04, -0.04,
		0.04, 0.04,
		-0.04, 0.04 };*/

}
Projectile::Projectile(){
	YPos = -1.5;
	remove = false;
	visible = false;
	position.x = 0.0;
	position.y = -1.5;
	position.z = 0.0;
	
	acceleration.x = 0.5;
	acceleration.y = 0.5;
	acceleration.z = 0.0;
	velocity.x = 1.0;
	velocity.y = 1.0;
	velocity.z = 0.0;

	direction.x = 1.0;
	direction.y = 1.0;
	direction.z = 0.0;

	damage = 10;
	/*float vertices[] = { -0.04, -0.04,
		0.04, -0.04,
		0.04, 0.04,
		-0.04, -0.04,
		0.04, 0.04,
		-0.04, 0.04 };*/



}

void Projectile::setMatrices(ShaderProgram program){
	program.setModelMatrix(model); program.setProjectionMatrix(projection); program.setViewMatrix(view);
}

void Projectile::setOrthoProjection(){
	projection.setOrthoProjection(-2.777f, 2.777f, -2.0f, 2.0f, -1.0f, 1.0f);
}

void Projectile::identityMatrix(){

	model.identity();
}

void Projectile::moveMatrix(float x_value, float y_value, float z_value){
	model.Translate(x_value, y_value, z_value);
}

void Projectile::renderWithNoTexture(ShaderProgram program, float vertices[]){

	glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
	glEnableVertexAttribArray(program.positionAttribute);


	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(program.positionAttribute);
}

void Projectile::incrementYPos(float value){
	position.y += value;
	//YPos += value;
}
void Projectile::incrementXPos(float value){
	position.x += value;
	//XPos += value;
}

void Projectile::BlendSprite(GLuint& texture) {

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture); //Disabling this will result in the most recent image loaded to take over everything

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisable(GL_TEXTURE_2D);

}

void Projectile::setupAndRender(ShaderProgram& program, float vertices[], float texCoords[], GLuint& texture){
	BlendSprite(texture); //Blend first? Why?
	glUseProgram(program.programID);



	glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
	glEnableVertexAttribArray(program.positionAttribute);

	glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
	glEnableVertexAttribArray(program.texCoordAttribute);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(program.positionAttribute);
	glDisableVertexAttribArray(program.texCoordAttribute);

}
void Projectile::scaleMatrix(float x_value, float y_value, float z_value){
	model.Scale(x_value, y_value, z_value);
}

