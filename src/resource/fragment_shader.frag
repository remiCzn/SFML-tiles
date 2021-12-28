#version 110

uniform vec3 light;
uniform vec2 winSize;
uniform sampler2D texture;
uniform bool hasTexture;
 
void main(void) {
    float dx = gl_FragCoord.x - light.x;
    float dy = winSize.y - gl_FragCoord.y - light.y;
    float distanceCarre = dx * dx + dy * dy;
    float alpha = 1.;
  
    alpha = 1. - sqrt(distanceCarre) / light.z;
    alpha = 1.0 / (1.0 + exp(-(alpha * 7.0 - 3.0)));

    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    vec4 color = vec4(1.0,0.92,0.78,1.);

    if(hasTexture == true) {
        gl_FragColor = color * pixel * alpha;
    } else {
        gl_FragColor = color * pixel;
    }
   
      
}