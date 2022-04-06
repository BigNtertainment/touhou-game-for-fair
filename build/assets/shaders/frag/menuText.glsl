#version 330 core
out vec4 glFragColor;

in vec2 TexCoord;

uniform vec3 u_color;
uniform vec2 u_resolution;
uniform int u_time;

uniform sampler2D Texture;

int pixelSize = 1;
int RGBRange = 256;

#define PI 3.14159265359

vec2 getScreenSpace() {
    vec2 gp, screenSpace;
    gp.x = int(gl_FragCoord.x) % pixelSize;
    gp.y = int(gl_FragCoord.y) % pixelSize;

    gp.x = floor(pixelSize / 2.) - gp.x;
    gp.y = floor(pixelSize / 2.) - gp.y;

    gp.x = gl_FragCoord.x + gp.x;
    gp.y = gl_FragCoord.y + gp.y;

    screenSpace = gp / u_resolution;

    return screenSpace;
}

void main() {
    vec2 screenSpace = getScreenSpace() * 4.;
    vec3 color = vec3(
        0.5 * sin(u_time/1000.0 + screenSpace.x) + 0.5,
        0.5 * sin(u_time/1000.0 + screenSpace.y + PI/2.0) + 0.5,
        0.5 * cos(u_time/1000.0 + (1. - screenSpace.x)) + 0.5
    );
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(Texture, TexCoord).r);
    glFragColor = vec4(color, 1.0) * sampled;
}
