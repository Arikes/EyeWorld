attribute vec4 position;
void main()
{
    vec4 pos = position;
	gl_PointSize = 32.0;
	gl_Position = pos;
}