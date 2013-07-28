#version 130

uniform sampler2D texture;
uniform vec4 color;

in vec2 v_texcoord;

void main()
{
    gl_FragColor =color * texture2D(texture, v_texcoord);
}
