/*
Simple program that draws health and armor near the map (like in Grand Theft Auto 5).

Use A and D to decrease / increase health.
Use Z and C to decrease / increase armor.
*/

#include <GL/glut.h>
#include <iostream>

//screen constants
const int SCREEN_WIDTH = 300;
const int SCREEN_HEIGHT = 250;

//map constants
const float MAP_WIDTH = 280;
const float MAP_HEIGHT = 220;

//health constants
const float MAX_HEALTH = 100.f;
const float HEALTH_HEIGHT = 20;
const float MAX_HEALTH_WIDTH = MAP_WIDTH / 2.f;

//armor constants
const float MAX_ARMOR = MAX_HEALTH;
const float ARMOR_HEIGHT = HEALTH_HEIGHT;
const float MAX_ARMOR_WIDTH = MAX_HEALTH_WIDTH;

//health and armor variables
float health, armor;
float healthWidth, armorWidth;

void refreshData()
{
    healthWidth = (health  / 100.f) * MAX_HEALTH_WIDTH;
    armorWidth = (armor / 100.f) * MAX_ARMOR_WIDTH;
}

static void display(void)
{
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT);

    std::cout << "------------" << std::endl;
    std::cout << "health: " << health << std::endl;
    std::cout << "armor: " << armor << std::endl;

    //draw map bounds
    glLineWidth(1);
	glBegin(GL_LINES);
        glColor3f(0, 0, 0);

		glVertex2f(0, 0);
		glVertex2f(0, MAP_HEIGHT);

		glVertex2f(0, MAP_HEIGHT);
		glVertex2f(MAP_WIDTH, MAP_HEIGHT);

		glVertex2f(MAP_WIDTH, MAP_HEIGHT);
		glVertex2f(MAP_WIDTH, 0);

		glVertex2f(MAP_WIDTH, 0);
		glVertex2f(0, 0);
	glEnd();

	//draw health
	if(health > MAX_HEALTH / 3.f)
    {
        glColor3f(0, 0.8, 0);
    }
    else
    {
        glColor3f(0.8, 0, 0);
    }

	glRectf(0, 0, healthWidth, HEALTH_HEIGHT);

	//draw armor
	glColor3f(0.2, 0.2, 1);
	glRectf(MAX_HEALTH_WIDTH, 0, MAX_HEALTH_WIDTH + armorWidth, ARMOR_HEIGHT);

	glFlush();
}

void changeHealthBy(float amount)
{
    health += amount;

    if(health < 0)
        health = 0;

    if(health > MAX_HEALTH)
        health = MAX_HEALTH;
}

void changeArmorBy(float amount)
{
    armor += amount;

    if(armor < 0)
        armor = 0;

    if(armor > MAX_ARMOR)
        armor = MAX_ARMOR;
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'a':
        case 'A':
            changeHealthBy(-5.f);
            break;
        case 'd':
        case 'D':
            changeHealthBy(5.f);
            break;
        case 'z':
        case 'Z':
            changeArmorBy(-5.f);
            break;
        case 'c':
        case 'C':
            changeArmorBy(5.f);
            break;
    }

    refreshData();
    glutPostRedisplay();
}

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-10, SCREEN_WIDTH - 10, -10, SCREEN_HEIGHT - 10);

	health = 100.f;
	armor = 100.f;

	refreshData();
}

/* Program entry point */
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition(10,10);
    glutCreateWindow("GTA 5 Map Logic");
    init();
    //glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    //glClearColor(1,1,1,1);
    glutMainLoop();

    return EXIT_SUCCESS;
}
