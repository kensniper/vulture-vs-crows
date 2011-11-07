uniform float sigma0=6.;
uniform float blurSize=1/(16.);
uniform sampler2D blurSampler;
const float pi = 3.14159265f;
const float numBlurPixelsPerSide = 4.0f;

const float saturation0 = 0.85;

uniform vec2 mousepos=vec2(0.5,0.5);
uniform float mouserange=0.4;
varying vec4 verpos;

void main() {

  // Incremental Gaussian Coefficent Calculation (See GPU Gems 3 pp. 877 - 889)
  float r=dot((mousepos-verpos.xy),(mousepos-verpos.xy));
  if(r!=0)
  {
      r=(mouserange*mouserange)/r;
  }

  if(r<1.)
  {
      float sigma=sigma0*(1-r);
      vec3 incrementalGaussian;
      incrementalGaussian.x = 1.0f / (sqrt(2.0f * pi) * sigma);
      incrementalGaussian.y = exp(-0.5f / (sigma * sigma));
      incrementalGaussian.z = incrementalGaussian.y * incrementalGaussian.y;

      vec4 avgValue = vec4(0.0f, 0.0f, 0.0f, 0.0f);
      float coefficientSum = 0.0f;

      // Take the central sample first...
      avgValue += texture2D(blurSampler, gl_TexCoord[0].xy) * incrementalGaussian.x;
      coefficientSum += incrementalGaussian.x;
      incrementalGaussian.xy *= incrementalGaussian.yz;

      // Go through the remaining 8 vertical samples (4 on each side of the center)
      vec2  blurMultiplyVec      = vec2(1.0f, 0.0f);
      for (float i = 1.0f; i <= numBlurPixelsPerSide; i++) {
        avgValue += texture2D(blurSampler, gl_TexCoord[0].xy - i * blurSize *
                              blurMultiplyVec) * incrementalGaussian.x;
        avgValue += texture2D(blurSampler, gl_TexCoord[0].xy + i * blurSize *
                              blurMultiplyVec) * incrementalGaussian.x;
        coefficientSum += 2 * incrementalGaussian.x;
        incrementalGaussian.xy *= incrementalGaussian.yz;
      }
      blurMultiplyVec      = vec2(0.0f, 1.0f);
      for (float i = 1.0f; i <= numBlurPixelsPerSide; i++) {
        avgValue += texture2D(blurSampler, gl_TexCoord[0].xy - i * blurSize *
                              blurMultiplyVec) * incrementalGaussian.x;
        avgValue += texture2D(blurSampler, gl_TexCoord[0].xy + i * blurSize *
                              blurMultiplyVec) * incrementalGaussian.x;
        coefficientSum += 2 * incrementalGaussian.x;
        incrementalGaussian.xy *= incrementalGaussian.yz;
      }

      float  saturation = saturation0*(1-r);
      vec4 tmpcolor=avgValue / coefficientSum*gl_Color;
      float avg= (tmpcolor.x+tmpcolor.y+tmpcolor.z)/3;
      tmpcolor.x=tmpcolor.x+(avg-tmpcolor.x)*saturation;
      tmpcolor.y=tmpcolor.y+(avg-tmpcolor.y)*saturation;
      tmpcolor.z=tmpcolor.z+(avg-tmpcolor.z)*saturation;



      gl_FragColor = tmpcolor;
  }
  else
  {
        gl_FragColor=texture2D(blurSampler, gl_TexCoord[0].xy)*gl_Color;
  }

}
