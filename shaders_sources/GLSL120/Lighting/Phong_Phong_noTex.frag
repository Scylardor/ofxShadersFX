#version 120

varying vec4 ambientGlobal, eyeSpaceVertexPos;
varying vec3 vertex_normal;

vec4 directional_light(in int lightIndex, in vec3 normal) {
    vec3 lightDir;
    vec4 dirLightColor, diffuse, specular, ambient = vec4(0.0);
    float intensity;

    lightDir = normalize(gl_LightSource[lightIndex].position.xyz);
    ambient = gl_FrontMaterial.ambient * gl_LightSource[lightIndex].ambient;
    dirLightColor = ambient;
    intensity = max(dot(normal, lightDir), 0.0);
    if (intensity > 0.0) {
        vec3 reflection;
        vec3 eyeSpaceVertexPos_n = normalize(vec3(eyeSpaceVertexPos));
        vec3 eyeVector = normalize(-eyeSpaceVertexPos_n);

        diffuse = gl_FrontMaterial.diffuse * gl_LightSource[lightIndex].diffuse;
        dirLightColor += diffuse * intensity;
        reflection = normalize((2.0 * dot(lightDir, normal) * normal) - lightDir);
        specular = pow(max(dot(reflection, eyeVector), 0.0), gl_FrontMaterial.shininess) * gl_FrontMaterial.specular * gl_LightSource[lightIndex].specular;
        dirLightColor += specular;
    }
    return dirLightColor;
}

vec4 point_light(in int lightIndex, in vec3 normal) {
    vec3 lightDir;
    vec4 pointLightColor, diffuse, specular, ambient = vec4(0.0);
    float intensity, dist;

    pointLightColor = vec4(0.0);
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
        diffuse = gl_FrontMaterial.diffuse * gl_LightSource[lightIndex].diffuse;
        ambient = gl_FrontMaterial.ambient * gl_LightSource[lightIndex].ambient;
        pointLightColor += att * (diffuse * intensity + ambient);
        reflection = normalize((2.0 * dot(lightDir, normal) * normal) - lightDir);
        specular = pow(max(dot(reflection, eyeVector), 0.0), gl_FrontMaterial.shininess) * gl_FrontMaterial.specular * gl_LightSource[lightIndex].specular;
        pointLightColor += att * specular;
    }
    return pointLightColor;
}

vec4 spot_light(in int lightIndex, in vec3 normal) {
    vec3 lightDir;
    vec4 spotLightColor, diffuse, specular, ambient = vec4(0.0);
    float intensity, dist;

    spotLightColor = vec4(0.0);
    lightDir = vec3(gl_LightSource[lightIndex].position - eyeSpaceVertexPos);
    dist = length(lightDir);
    intensity = max(dot(normal, normalize(lightDir)), 0.0);
    if (intensity > 0.0) {
        float spotEffect;

        spotEffect = dot(normalize(gl_LightSource[lightIndex].spotDirection), normalize(-lightDir));
        if(spotEffect > gl_LightSource[lightIndex].spotCosCutoff) {
            vec3 reflection;
            vec3 eyeSpaceVertexPos_n = normalize(vec3(eyeSpaceVertexPos));
            vec3 eyeVector = normalize(-eyeSpaceVertexPos_n);
            float att, dist;

            spotEffect = pow(spotEffect, gl_LightSource[lightIndex].spotExponent);
            dist = length(lightDir);
            att = spotEffect/(gl_LightSource[lightIndex].constantAttenuation +
                              gl_LightSource[lightIndex].linearAttenuation * dist +
                              gl_LightSource[lightIndex].quadraticAttenuation * dist * dist);
            diffuse = gl_FrontMaterial.diffuse * gl_LightSource[lightIndex].diffuse;
            ambient = gl_FrontMaterial.ambient * gl_LightSource[lightIndex].ambient;
            spotLightColor += att * (diffuse * intensity + ambient);
            reflection = normalize((2.0 * dot(lightDir, normal) * normal) - lightDir);
            specular = pow(max(dot(reflection, eyeVector), 0.0), gl_FrontMaterial.shininess) * gl_FrontMaterial.specular * gl_LightSource[lightIndex].specular;
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
