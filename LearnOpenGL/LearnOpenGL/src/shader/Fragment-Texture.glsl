struct Material {
    sampler2D diffuse;
    lowp vec3 specular;
    lowp float shininess;
};

struct Light {
    lowp vec3 ambient;
    lowp vec3 diffuse;
    lowp vec3 specular;
    lowp vec3 position;
};

uniform Light light;
uniform Material material;

uniform lowp vec3 viewPos;
//入参
varying lowp vec3 Normal;
varying lowp vec3 FragPos;
varying lowp vec2 TextCoord;


void main()
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
    
    //光照物体
    lowp vec3 result = ambient + diffuse + specular;
    
    gl_FragColor = vec4(result, 1.0);
}
