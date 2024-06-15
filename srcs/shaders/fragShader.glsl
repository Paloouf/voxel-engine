#version 330 core

in vec2 TexCoord;
//in vec4 vertexColor;
out vec4 FragColor;

uniform sampler2D textureAtlas;

void main() {
    //FragColor = vertexColor;
	FragColor = texture(textureAtlas, TexCoord);
}