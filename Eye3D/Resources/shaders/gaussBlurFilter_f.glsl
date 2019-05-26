uniform sampler2D texture;
varying vec2 coord;
void main()
{
	vec4 color = texture2D(texture,coord);
	gl_FragColor = vec4(1.0,color.gb,1.0);
}