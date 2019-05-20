void main()
{
vec4 color = vec4(1.0,1.0,0.0,1.0);
vec2 p = gl_PointCoord * 2.0 - vec2(1.0);
if(gl_PointCoord.x<0.2)
color = vec4(1.0,0.0,0.0,1.0);
gl_FragColor = color;
}