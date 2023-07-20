const char* fragmentShaderCode = R"(
#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;


uniform float frame;
uniform int width;
uniform int height;
// Output fragment color
out vec4 finalColor;



void main()
{
    
    vec4 sum = vec4(0, 0,0, 0);

    for (float i = -0.002; i <= 0.002; i+=0.001)
    {
        for (float j = -0.002; j <= 0.002; j+=0.001)
        {
            sum += texture(texture0, vec2(fragTexCoord.x + j, fragTexCoord.y + i));
        }
    }
    
    

    
    finalColor = sum/25;
}
)";