#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;


//Atrybuty
in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
in vec4 color; //kolor związany z wierzchołkiem
in vec4 normal; //wektor normalny w przestrzeni modelu
in vec2 texCoord0;
in vec4 C1;
in vec4 C2;
in vec4 C3;

//Zmienne interpolowane
out vec4 ic;
out vec4 l;
out vec4 v;
out vec2 iTexCoord0;


void main(void) {
    vec4 lp = vec4(0, 0, -6, 1); //przestrzeń świata

    mat4 MTBN = mat4(C1,C2,C3,vec4(0,0,0,1));

    l = normalize(MTBN*inverse(M)*lp - MTBN*vertex); //wektor do światła w przestrzeni oka
    v = normalize(MTBN*inverse(V*M)*vec4(0, 0, 0, 1) - MTBN*vertex); //wektor do obserwatora w przestrzeni oka

    iTexCoord0 = texCoord0;
    
    ic = color;
    
    gl_Position=P*V*M*vertex;
}
