#version 130

in vec2 a_position;
in vec2 a_texcoord;
uniform mat4 mvp_matrix;

out vec2 v_texcoord;

void main()
{
    gl_Position = mvp_matrix * vec4(a_position.x, a_position.y, 0.0 , 1.0);;
    v_texcoord = a_texcoord;
}
