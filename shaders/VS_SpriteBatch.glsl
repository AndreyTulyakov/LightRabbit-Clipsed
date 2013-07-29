#version 130

uniform mat4 mvp_matrix;

in vec2 a_position;
in vec2 a_texcoord;
in vec4 a_color;

out vec2 v_texcoord;
out vec4 v_color;

void main()
{
    gl_Position = mvp_matrix * vec4(a_position.x, a_position.y, 0.0 , 1.0);

    v_texcoord = a_texcoord;
    v_color = a_color;
}
