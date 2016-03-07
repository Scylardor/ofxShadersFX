// The MIT License (MIT)
// Copyright (c) 2016 Alexandre Baron (Scylardor)

// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#version 120
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect tex;

varying vec4 ambientGlobal,  eyeSpaceVertexPos;
varying vec3 vertex_normal;

vec4 directional_light(in int lightIndex,  in vec3 normal) {
    vec3 lightDir;
    vec4 dirLightColor,  diffuse,  specular,  ambient = vec4(0.0);
    float intensity;

    lightDir = normalize(gl_LightSource[lightIndex].position.xyz);
    ambient = gl_FrontMaterial.ambient  *  gl_LightSource[lightIndex].ambient  *  texture2DRect(tex,  gl_TexCoord[0].st);
    dirLightColor = ambient;
    intensity = max(dot(normal,  lightDir),  0.0);
    if (intensity > 0.0) {
        vec3 halfVector_n = normalize(gl_LightSource[lightIndex].halfVector.xyz);
       float NdotHV;

       diffuse = gl_FrontMaterial.diffuse  *  gl_LightSource[lightIndex].diffuse;
        dirLightColor += diffuse  *  intensity  *  texture2DRect(tex,  gl_TexCoord[0].st);
        NdotHV = max(dot(normal,  halfVector_n),  0.0);
        specular = pow(NdotHV,  gl_FrontMaterial.shininess)  *  gl_FrontMaterial.specular  *  gl_LightSource[lightIndex].specular;
        dirLightColor += specular;
    }
    return dirLightColor;
}

vec4 point_light(in int lightIndex,  in vec3 normal) {
    vec3 lightDir;
    vec4 pointLightColor;
    float intensity,  dist;

    pointLightColor = vec4(0.0);
    lightDir = vec3(gl_LightSource[lightIndex].position - eyeSpaceVertexPos);
    dist = length(lightDir);
    intensity = max(dot(normal,  normalize(lightDir)),  0.0);
    if (intensity > 0.0) {
        float att,  NdotHV;
        vec4 diffuse,  specular,  ambient = vec4(0.0);
        vec3 halfVector;

        att = 1.0 / (gl_LightSource[lightIndex].constantAttenuation +
                     gl_LightSource[lightIndex].linearAttenuation  *  dist +
                     gl_LightSource[lightIndex].quadraticAttenuation  *  dist  *  dist);
        diffuse = gl_FrontMaterial.diffuse  *  gl_LightSource[lightIndex].diffuse  *  texture2DRect(tex,  gl_TexCoord[0].st);
        ambient = gl_FrontMaterial.ambient  *  gl_LightSource[lightIndex].ambient  *  texture2DRect(tex,  gl_TexCoord[0].st);
        pointLightColor += att  *  (diffuse  *  intensity + ambient);
        halfVector = normalize(lightDir - vec3(eyeSpaceVertexPos));
        NdotHV = max(dot(normal,  halfVector),  0.0);
        specular = pow(NdotHV,  gl_FrontMaterial.shininess)  *  gl_FrontMaterial.specular  *  gl_LightSource[lightIndex].specular;
        pointLightColor += att  *  specular;
    }
    return pointLightColor;
}

vec4 spot_light(in int lightIndex,  in vec3 normal) {
    vec3 lightDir;
    vec4 spotLightColor;
    float intensity,  dist;

    spotLightColor = vec4(0.0);
    lightDir = vec3(gl_LightSource[lightIndex].position - eyeSpaceVertexPos);
    dist = length(lightDir);
    intensity = max(dot(normal,  normalize(lightDir)),  0.0);
    if (intensity > 0.0) {
        float spotEffect,  att,  NdotHV;
        vec4 diffuse,  specular,  ambient = vec4(0.0);
        vec3 halfVector;

        spotEffect = dot(normalize(gl_LightSource[lightIndex].spotDirection),  normalize(-lightDir));
        if (spotEffect > gl_LightSource[lightIndex].spotCosCutoff) {
            spotEffect = pow(spotEffect,  gl_LightSource[lightIndex].spotExponent);
            att = spotEffect / (gl_LightSource[lightIndex].constantAttenuation +
                                gl_LightSource[lightIndex].linearAttenuation  *  dist +
                                gl_LightSource[lightIndex].quadraticAttenuation  *  dist  *  dist);
            diffuse = gl_FrontMaterial.diffuse * gl_LightSource[lightIndex].diffuse  *  texture2DRect(tex, gl_TexCoord[0].st);
            ambient = gl_FrontMaterial.ambient * gl_LightSource[lightIndex].ambient * texture2DRect(tex, gl_TexCoord[0].st);
            spotLightColor += att * (diffuse * intensity+ambient);
            halfVector = normalize(lightDir - vec3(eyeSpaceVertexPos));
            NdotHV = max(dot(normal, halfVector), 0.0);
            specular = pow(NdotHV, gl_FrontMaterial.shininess) * gl_FrontMaterial.specular * gl_LightSource[lightIndex].specular;
            spotLightColor += att * specular;
        }
    }
    return spotLightColor;
}

vec4 calc_lighting_color(in vec3 normal) {
    vec4 lightingColor = vec4(0.0);

    for(int i = 0; i < 8; i++) {
        if (gl_LightSource[i].position.w == 0.0) {
            lightingColor += directional_light(i, normal);
        } else {
            if (gl_LightSource[i].spotCutoff <= 90.0) {
                lightingColor += spot_light(i, normal);
            } else {
                lightingColor += point_light(i, normal);
            }
        }

    }
    return lightingColor;
}

void main() {
    vec3 n;
    vec4 color = ambientGlobal;

    n = normalize(vertex_normal);
    color += calc_lighting_color(n);
    color.w = 1.0;
    gl_FragColor = color;
}
