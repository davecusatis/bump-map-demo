float rand(vec2 n)
{
	return 0.5 + 0.5 *
			fract(sin(dot(n.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

void main()
{
	vec3 v;
	float x = rand(v.xz);
	gl_FragColor = vec4(x, x, x, 1.0);
}