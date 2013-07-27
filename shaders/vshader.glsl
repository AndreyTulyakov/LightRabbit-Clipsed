#version 130

uniform mat4 mvp_matrix;

in vec3 a_position;
in vec2 a_texcoord;

out vec2 v_texcoord;

void main()
{
    v_texcoord = a_texcoord;
    gl_Position = mvp_matrix * vec4(a_position.x, a_position.y, a_position.z , 1.0);
}
