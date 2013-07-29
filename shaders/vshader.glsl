#version 130

uniform mat4 mvp_matrix;

in vec2 a_position;
in vec2 a_texcoord;

out vec2 v_texcoord;

void main()
{
    v_texcoord = a_texcoord;
    gl_Position = mvp_matrix * vec4(a_position.x, a_position.y, 0.0 , 1.0);
}
