#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

vec3 lightColor = vec4(0.529, 0.569, 0.533);
vec3 darkColor = vec4(0.102, 0.098, 0.078);

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