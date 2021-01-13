struct Material {
    sampler2D diffuse;
    lowp vec3 specular;
    lowp float shininess;
};

struct Light {
    lowp vec3 ambient;
    lowp vec3 diffuse;
    lowp vec3 specular;
    
    lowp vec3 direction;
    lowp vec3 position;
    
    lowp float constant;
    lowp float linear;
    lowp float quadratic;
    lowp float cutoff;
};

uniform Light light;
uniform Material material;

uniform lowp vec3 viewPos;
//入参
varying lowp vec3 Normal;
varying lowp vec3 FragPos;
varying lowp vec2 TextCoord;

//平行光
lowp vec3 main_dir_light()
{
    //环境光
    lowp vec3 ambient = light.ambient * texture2D(material.diffuse, TextCoord).rgb;
    //法线
    lowp vec3 norm = normalize(Normal);
    
    //漫反射
    lowp vec3 lDirection = normalize(-light.direction);
    lowp float diff = max(dot(norm, lDirection), 0.0);
    lowp vec3 diffuse = light.diffuse * diff * texture2D(material.diffuse, TextCoord).rgb;
    
    //镜面反射
    lowp vec3 viewDirection = normalize(viewPos - FragPos);
    lowp vec3 reflectDirection = reflect(-lDirection, norm);
    lowp float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
    lowp vec3 specular = light.specular * (spec * material.specular);
    
    //光照物体
    lowp vec3 result = ambient + diffuse + specular;
    return result;
}


//点光
lowp vec3 main_point_light()
{
    //环境光
    lowp vec3 ambient = light.ambient * texture2D(material.diffuse, TextCoord).rgb;
    //法线
    lowp vec3 norm = normalize(Normal);
    
    //漫反射
    lowp vec3 lDirection = normalize(light.position - FragPos);
    lowp float diff = max(dot(norm, lDirection), 0.0);
    lowp vec3 diffuse = light.diffuse * diff * texture2D(material.diffuse, TextCoord).rgb;
    
    //镜面反射
    lowp vec3 viewDirection = normalize(viewPos - FragPos);
    lowp vec3 reflectDirection = reflect(-lDirection, norm);
    lowp float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
    lowp vec3 specular = light.specular * (spec * material.specular);
    
    //衰减 Fatt = 1.0 / (Kc + Kl * d + Kq * d2)
    lowp float dis = length(light.position - FragPos);
    lowp float attenuation = 1.0 / (light.constant + light.linear * dis + light.quadratic * dis * dis);
    
    //光照物体
    lowp vec3 result = (ambient * attenuation) + (diffuse * attenuation) + (specular * attenuation);
    return result;
}

//聚光 (手电筒)
lowp vec3 main_flash_light()
{
    lowp vec3 lDirection = normalize(light.position - FragPos);
    lowp float theta = dot(lDirection, normalize(-light.direction));
    
    if (theta > light.cutoff) {
        //环境光
        lowp vec3 ambient = light.ambient * texture2D(material.diffuse, TextCoord).rgb;
        //法线
        lowp vec3 norm = normalize(Normal);
        
        //漫反射
        lowp float diff = max(dot(norm, lDirection), 0.0);
        lowp vec3 diffuse = light.diffuse * diff * texture2D(material.diffuse, TextCoord).rgb;
        
        //镜面反射
        lowp vec3 viewDirection = normalize(viewPos - FragPos);
        lowp vec3 reflectDirection = reflect(-lDirection, norm);
        lowp float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
        lowp vec3 specular = light.specular * (spec * material.specular);
        
        //衰减 Fatt = 1.0 / (Kc + Kl * d + Kq * d2)
        lowp float dis = length(light.position - FragPos);
        lowp float attenuation = 1.0 / (light.constant + light.linear * dis + light.quadratic * dis * dis);
        
        //光照物体
        lowp vec3 result = ambient + (diffuse * attenuation) + (specular * attenuation);
        return result;
    }
    
    lowp vec3 otherresult = vec3(light.ambient * texture2D(material.diffuse, TextCoord).rgb);
    return otherresult;
}

void main()
{
    //光照物体
    lowp vec3 result = main_flash_light();
    
    gl_FragColor = vec4(result, 1.0);
}
