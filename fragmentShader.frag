// simple fragment shader

// 'time' contains seconds since the program was linked.
uniform float time;

varying vec4 V;
varying vec3 N;

void main()
{
	vec4 matEmission, matAmbient, matDiffuse, matSpecular;
	vec4 lightModelAmbient, lightAmbient, lightDiffuse, lightSpecular;
	vec4 L, H;
	float matShininess;

	//Obtenim les dades necessaries
	matEmission = gl_FrontMaterial.emission;
	matAmbient = gl_FrontMaterial.ambient;
	matDiffuse = gl_FrontMaterial.diffuse;
	matSpecular = gl_FrontMaterial.specular;
	lightModelAmbient = gl_LightModel.ambient;
	lightAmbient = gl_LightSource[0].ambient;
	lightDiffuse = gl_LightSource[0].diffuse;
	lightSpecular = gl_LightSource[0].specular;
	matShininess = gl_FrontMaterial.shininess;

	//Calculem N, H i L
	vec3 Nobs = normalize(N);
	L = normalize(gl_LightSource[0].position - V);
	vec4 Vobs = normalize(-V);
	H = normalize(L + Vobs);

	//Formula de Blinn-Phong
	//Ke + Ka*(Ma + Ia) + Kd*Id*(N*L)+ Ks*Is*(N*H)^s
	vec4 color = matEmission+matAmbient*(lightModelAmbient+lightAmbient);
	color += matDiffuse*lightDiffuse*max(0.0, dot(Nobs, L.xyz));
	color += matSpecular*lightSpecular*pow(max(0.0, dot(Nobs,H.xyz)), matShininess);

	gl_FragColor = color;
}