// The MIT License (MIT)
// Copyright (c) 2016 Alexandre Baron (Scylardor)

// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#version 120

varying vec4 ambientGlobal, diffuse, ambient, specular;

vec4 eyeSpaceVertexPos;

void directional_light(in int lightIndex, in vec3 normal) {
    vec3 lightDir;
    float intensity;

    lightDir = normalize(gl_LightSource[lightIndex].position.xyz);
    ambient += gl_FrontMaterial.ambient * gl_LightSource[lightIndex].ambient;
    intensity = max(dot(normal, lightDir), 0.0);
    if (intensity > 0.0) {
        vec3 reflection;
        vec3 eyeSpaceVertexPos_n = normalize(vec3(eyeSpaceVertexPos));
        vec3 eyeVector = normalize(-eyeSpaceVertexPos_n);
        diffuse += gl_FrontMaterial.diffuse * gl_LightSource[lightIndex].diffuse * intensity;
        reflection = normalize((2.0 * dot(lightDir, normal) * normal) - lightDir);
        specular += pow(max(dot(reflection, eyeVector), 0.0), gl_FrontMaterial.shininess) * gl_FrontMaterial.specular * gl_LightSource[lightIndex].specular;
    }
}

void point_light(in int lightIndex,in vec3 normal) {
    vec3 lightDir;
    float intensity, dist;

    lightDir = vec3(gl_LightSource[lightIndex].position - eyeSpaceVertexPos);
    dist = length(lightDir);
    intensity = max(dot(normal, normalize(lightDir)), 0.0);
    if (intensity > 0.0) {
        vec3 reflection;
        vec3 eyeSpaceVertexPos_n = normalize(vec3(eyeSpaceVertexPos));
        vec3 eyeVector = normalize(-eyeSpaceVertexPos_n);
        float att, dist;
        dist = length(lightDir);
        att = 1.0 / (gl_LightSource[lightIndex].constantAttenuation +
                     gl_LightSource[lightIndex].linearAttenuation * dist +
                     gl_LightSource[lightIndex].quadraticAttenuation * dist * dist);
        diffuse += att * gl_FrontMaterial.diffuse * gl_LightSource[lightIndex].diffuse * intensity;
        ambient += att * gl_FrontMaterial.ambient * gl_LightSource[lightIndex].ambient;
        reflection = normalize((2.0 * dot(lightDir, normal) * normal) - lightDir);
        specular += att * pow(max(dot(reflection, eyeVector), 0.0), gl_FrontMaterial.shininess) * gl_FrontMaterial.specular * gl_LightSource[lightIndex].specular;
    }
}

void spot_light(in int lightIndex,in vec3 normal) {
    vec3 lightDir;
    float intensity, dist;

    lightDir = vec3(gl_LightSource[lightIndex].position - eyeSpaceVertexPos);
    dist = length(lightDir);
    intensity = max(dot(normal, normalize(lightDir)), 0.0);
    if (intensity > 0.0) {
        float spotEffect;
        spotEffect = dot(normalize(gl_LightSource[lightIndex].spotDirection), normalize(-lightDir));
        if (spotEffect > gl_LightSource[lightIndex].spotCosCutoff) {
            vec3 reflection;
            vec3 eyeSpaceVertexPos_n = normalize(vec3(eyeSpaceVertexPos));
            vec3 eyeVector = normalize(-eyeSpaceVertexPos_n);
            float att, dist;

            spotEffect = pow(spotEffect, gl_LightSource[lightIndex].spotExponent);
            dist = length(lightDir);
            att = spotEffect / (gl_LightSource[lightIndex].constantAttenuation +
                                gl_LightSource[lightIndex].linearAttenuation * dist +
                                gl_LightSource[lightIndex].quadraticAttenuation * dist * dist);
            diffuse += att * gl_FrontMaterial.diffuse * gl_LightSource[lightIndex].diffuse * intensity;
            ambient += att * gl_FrontMaterial.ambient * gl_LightSource[lightIndex].ambient;
            reflection = normalize((2.0 * dot(lightDir,normal) * normal) - lightDir);
            specular += att * pow(max(dot(reflection, eyeVector), 0.0), gl_FrontMaterial.shininess) * gl_FrontMaterial.specular * gl_LightSource[lightIndex].specular;
        }
    }
}

void calc_lighting_color(in vec3 normal) {
    for(int i = 0; i < 8; i++) {
        if (gl_LightSource[i].position.w == 0.0) {
            directional_light(i, normal);
        } else {
            if (gl_LightSource[i].spotCutoff <= 90.0) {
                spot_light(i, normal);
            } else {
                point_light(i, normal);
            }
        }
    }
}

void main() {
    vec3 vertex_normal;
    vec4 color;

    diffuse = vec4(0.0);
    ambient = vec4(0.0);
    specular = vec4(0.0);
    vertex_normal = normalize(gl_NormalMatrix * gl_Normal);
    eyeSpaceVertexPos = gl_ModelViewMatrix * gl_Vertex;
    ambientGlobal = gl_LightModel.ambient * gl_FrontMaterial.ambient + gl_FrontMaterial.emission;
    calc_lighting_color(vertex_normal);
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    gl_Position = ftransform();
}
