#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;


// Output fragment color
out vec4 finalColor;

// NOTE: Add here your custom variables

void main()
{
    vec4 lightColor = vec4(0.78, 0.941, 0.847, 1.0);
    vec4 darkColor = vec4(0.263, 0.322, 0.239, 1.0);
    // Texel color fetching from texture sampler
    vec4 texelColor = texture(texture0, fragTexCoord)*colDiffuse*fragColor;

    // Convert texel color to grayscale using NTSC conversion weights
    if (texelColor.r * 0.2126 + texelColor.g * 0.7152 + texelColor.b * 0.0722 > 0.5) {
        finalColor = vec4(lightColor.r, lightColor.g, lightColor.b, texelColor.a);
    } else {
        finalColor = vec4(darkColor.r, darkColor.g, darkColor.b, texelColor.a);
    }
}