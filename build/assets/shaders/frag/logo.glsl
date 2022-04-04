#version 330 core
out vec4 glFragColor;

in vec2 TexCoord;

uniform vec2 u_resolution;
uniform vec2 u_size;
uniform vec2 u_position;
uniform int u_time;


uniform sampler2D Texture;

#define PI 3.14159265359
void main() {
	// TODO: make so it looks good and also find the reason for crashing and fix it
    // glFragColor = texture(Texture, TexCoord) * vec4(1.0, 1.0, 1.0, 0.5*cos(-PI / 180.0 + PI*u_time/1000.0) + 0.5);
    glFragColor = texture(Texture, TexCoord) * vec4(1.0, 1.0, 1.0, (0.5*cos(-PI + PI*u_time/1500.0) + 0.5) * float(u_time < 3000.0) );
    
}
