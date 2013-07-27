#version 130

in vec2 a_position;
uniform mat4 mvp_matrix;

void main()
{
    gl_Position = mvp_matrix * vec4(a_position.x, a_position.y, 0.0 , 1.0);
}
