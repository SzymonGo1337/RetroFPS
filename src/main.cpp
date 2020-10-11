#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <bits/stdc++.h>

void drawCube(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength) {
    GLfloat halfSideLength = edgeLength * 0.5;

    GLfloat vertices[] = {
        // front face
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom right
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom left

        // back face
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top left
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom left

        // left face
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom left

        // right face
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom left

        // top face
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // bottom right
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // bottom left

        // bottom face
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // top left
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // top right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom left
    };

    GLfloat color[] = {
        // front face
        255, 0, 0,
        0, 255, 0,
        0, 255, 255,
        0, 0, 0,

        // back face
        255, 0, 0,
        0, 255, 0,
        0, 255, 255,
        0, 0, 0,

        // left face
        255, 0, 0,
        0, 255, 0,
        0, 255, 255,
        0, 0, 0,

        // right face
        255, 0, 0,
        0, 255, 0,
        0, 255, 255,
        0, 0, 0,

        // top face
        255, 0, 0,
        0, 255, 0,
        0, 255, 255,
        0, 0, 0,

        // bottom face
        255, 0, 0,
        0, 255, 0,
        0, 255, 255,
        0, 0, 0,
    };

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, color);
    glDrawArrays(GL_QUADS, 0, 24);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;

int main() {
    sf::ContextSettings context;
    //context.antialiasingLevel = 8.0f;

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Retro FPS", sf::Style::Titlebar | sf::Style::Close, context);
    window.setFramerateLimit(60);
    window.setActive(true);

    glViewport(0.0f, 0.0f, 1280.0f, 720.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, 1280, 0, 720, 0, 1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

    GLfloat halfScreenWidth = 1280 / 2;
    GLfloat halfScreenHeight = 720 / 2;

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            rotationX -= 10.0f;
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            rotationX += 10.0f;
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            rotationY += 10.0f;
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            rotationY -= 10.0f;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glPushMatrix();
        glTranslatef(halfScreenWidth, halfScreenHeight, -500);
        glRotatef(rotationX, 1, 0, 0);
        glRotatef(rotationY, 0, 1, 0);
        glTranslatef(-halfScreenWidth, -halfScreenHeight, 500);

        drawCube(halfScreenWidth, halfScreenHeight, -500, 200);
        
        glPopMatrix();

        window.display();
    }
}