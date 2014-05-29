varying float diffuse_value;

void main()
{
	gl_FragColor = gl_Color * diffuse_value;
}