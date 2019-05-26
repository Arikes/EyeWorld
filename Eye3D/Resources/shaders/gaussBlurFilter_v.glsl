attribute vec4 position;
attribute vec2 texcoord;
uniform float screenWidth;
uniform float screenHeight;
uniform int flip;
varying vec2 coord;
void main()
{
    coord = texcoord;
	vec4 pos = position;
	if(flip>0){
	    pos.y = -pos.y;
	}
	gl_Position = pos;
}