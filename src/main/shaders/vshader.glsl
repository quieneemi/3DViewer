attribute vec4 qt_Vertex;
varying vec4 qt_FragColor;

uniform float qt_PointSize;
uniform vec4 qt_Color;
uniform mat4 qt_MVPMatrix;

void main(void) {
    gl_Position = qt_MVPMatrix * qt_Vertex;
    gl_PointSize = qt_PointSize;
    qt_FragColor = qt_Color;
}
