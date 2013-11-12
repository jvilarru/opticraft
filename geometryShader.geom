// simple geometry shader

// these lines enable the geometry shader support.
#version 120
#extension GL_EXT_geometry_shader4 : enable

void main( void )
{
	for( int i = 0 ; i < gl_VerticesIn ; i++ )
	{
		gl_FrontColor  = gl_FrontColorIn[ i ];
	}

	float x = gl_PositionIn[0].x, y = gl_PositionIn[0].y, z = gl_PositionIn[0].z;
	//TOP vertices
	vec4 pos1 = gl_ModelViewProjectionMatrix * vec4(x-0.5, y+0.5, z+0.5, 1.0);
	vec4 pos2 = gl_ModelViewProjectionMatrix * vec4(x+0.5, y+0.5, z+0.5, 1.0);
	vec4 pos3 = gl_ModelViewProjectionMatrix * vec4(x+0.5, y+0.5, z-0.5, 1.0);
	vec4 pos4 = gl_ModelViewProjectionMatrix * vec4(x-0.5, y+0.5, z-0.5, 1.0);
	//BOTTOM vertices
	vec4 pos5 = gl_ModelViewProjectionMatrix * vec4(x-0.5, y-0.5, z+0.5, 1.0);
	vec4 pos6 = gl_ModelViewProjectionMatrix * vec4(x-0.5, y-0.5, z-0.5, 1.0);
	vec4 pos7 = gl_ModelViewProjectionMatrix * vec4(x+0.5, y-0.5, z-0.5, 1.0);
	vec4 pos8 = gl_ModelViewProjectionMatrix * vec4(x+0.5, y-0.5, z+0.5, 1.0);

	//TOP face (1-2-3, 3-4-1)
	gl_Position = pos1;
	EmitVertex();
	gl_Position = pos2;
	EmitVertex();
	gl_Position = pos3;
	EmitVertex();
	EndPrimitive();
	gl_Position = pos3;
	EmitVertex();
	gl_Position = pos4;
	EmitVertex();
	gl_Position = pos1;
	EmitVertex();
	EndPrimitive();
	//BOTTOM face (5-6-7, 7-8-6)
	gl_Position = pos5;
	EmitVertex();
	gl_Position = pos6;
	EmitVertex();
	gl_Position = pos7;
	EmitVertex();
	EndPrimitive();
	gl_Position = pos7;
	EmitVertex();
	gl_Position = pos8;
	EmitVertex();
	gl_Position = pos6;
	EmitVertex();
	EndPrimitive();
	//FRONT face (5-8-2, 2-1-5)
	gl_Position = pos5;
	EmitVertex();
	gl_Position = pos8;
	EmitVertex();
	gl_Position = pos2;
	EmitVertex();
	EndPrimitive();
	gl_Position = pos2;
	EmitVertex();
	gl_Position = pos1;
	EmitVertex();
	gl_Position = pos5;
	EmitVertex();
	EndPrimitive();
	//BACK face (7-6-4, 4-3-7)
	gl_Position = pos7;
	EmitVertex();
	gl_Position = pos6;
	EmitVertex();
	gl_Position = pos4;
	EmitVertex();
	EndPrimitive();
	gl_Position = pos4;
	EmitVertex();
	gl_Position = pos3;
	EmitVertex();
	gl_Position = pos7;
	EmitVertex();
	EndPrimitive();
	//LEFT face (6-5-1, 1-4-6)
	gl_Position = pos6;
	EmitVertex();
	gl_Position = pos5;
	EmitVertex();
	gl_Position = pos1;
	EmitVertex();
	EndPrimitive();
	gl_Position = pos1;
	EmitVertex();
	gl_Position = pos4;
	EmitVertex();
	gl_Position = pos6;
	EmitVertex();
	EndPrimitive();
	//RIGHT face (7-3-2, 2-8-7)
	gl_Position = pos7;
	EmitVertex();
	gl_Position = pos3;
	EmitVertex();
	gl_Position = pos2;
	EmitVertex();
	EndPrimitive();
	gl_Position = pos2;
	EmitVertex();
	gl_Position = pos8;
	EmitVertex();
	gl_Position = pos7;
	EmitVertex();
	EndPrimitive();
}
