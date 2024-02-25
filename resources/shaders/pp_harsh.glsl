#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

vec4 lightColor = vec3(0.608, 0.78, 0.0);
vec4 darkColor = vec3(0.169, 0.247, 0.035);

// Output fragment color
out vec4 finalColor;

// NOTE: Add here your custom variables

void main()
{
    // Texel color fetching from texture sampler
    vec4 texelColor = texture(texture0, fragTexCoord)*colDiffuse*fragColor;

    // Convert texel color to grayscale using NTSC conversion weights
    if (texelColor.r * 0.2126 + texelColor.g * 0.7152 + texelColor.b * 0.0722 > 0.5) {
        finalColor = vec4(lightColor, texelColor.a);
    } else {
        finalColor = vec4(darkColor, texelColor.a);
    }
}