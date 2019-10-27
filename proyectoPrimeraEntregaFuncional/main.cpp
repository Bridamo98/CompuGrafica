/*
 * Maze Generator:
 *   Made by Jaden Peterson in 2016
 */

/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <deque>
#include <GL/glut.h>
#include <sstream>
#include <iostream>

// A macro for unused variables (to bypass those pesky G++ warnings)
#define UNUSED(param) (void)(param)

// Snake direction macros
#define UP    1//ESTO VA
#define DOWN  2//ESTO VA
#define LEFT  3//ESTO VA
#define RIGHT 4//ESTO VA

using namespace std;



const float map_half_length = 30.0f;//ESTO VA
GLUquadricObj* fillObject = nullptr;


GLsizei w, h;

int direction = DOWN;
bool moved = false;
const int move_speed = 500;

float xCam, yCam, zCam = 30.0f; 
std::deque< std::deque<float> > part_coords;

bool food_available = false;
int food_coords[2];

int score = 0;

int growth_stage = 0;
const int growth = 2;

void drawFood(){
    glPushMatrix();
    glTranslatef(food_coords[0], food_coords[1], -40.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    /*glScalef(1.0,1.0,5.0);
    glBegin(GL_POLYGON);
        glVertex2d( 1.0f,  1.0f);
        glVertex2d( 1.0f, -1.0f);
        glVertex2d(-1.0f, -1.0f);
        glVertex2d(-1.0f,  1.0f);
    glEnd();*/
    glutSolidCube(2.0f);
    glPopMatrix();
}

void spawnFood(){
    if(food_available){
        return;
    }

    int temp_food_coords[2];
    bool collides;

    do {
        collides = false;

        // Produce a temporary random coordinate
        temp_food_coords[0] = 2 * (rand() % ((int) map_half_length + 1)) - (int) map_half_length;
        temp_food_coords[1] = 2 * (rand() % ((int) map_half_length + 1)) - (int) map_half_length;

        // Does it collide with the snake?
        for(unsigned int a = 0; a < part_coords.size(); a++){
            if(temp_food_coords[0] == part_coords[a][0] &&
               temp_food_coords[1] == part_coords[a][1]){
                collides = true;
            }
        }
    } while(collides);

    food_coords[0] = temp_food_coords[0];
    food_coords[1] = temp_food_coords[1];

    food_available = true;
}

void drawBitmapText(char* text, float x, float y, float z) {
    char* c;

    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos3f(x, y, z);

    for(c = text; *c != '\0'; c++){
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
    }
    glPopMatrix();
}

void drawControls(){
    char* move_message = (char*) "Use las flechas izquierda y derecha";
    char* exit_message = (char*) "Presiones ESC para salir";

    drawBitmapText(move_message, map_half_length - 32.0f, map_half_length - 2.0f, -39.5f);
    drawBitmapText(exit_message, map_half_length - 21.0f, map_half_length - 4.0f, -39.5f);
}

void drawScore(){
    const char* score_message = (char*) "Puntos: ";
    const char* length_message = (char*) "Longitud: ";
    std::stringstream score_string;
    std::stringstream length_string;

    score_string << score_message << score;
    length_string << length_message << part_coords.size();

    drawBitmapText((char*) score_string.str().c_str(), -map_half_length + 1.0f, map_half_length - 2.0f, -39.5f);
    drawBitmapText((char*) length_string.str().c_str(), -map_half_length + 1.0f, map_half_length - 4.0f, -39.5f);
}

void drawSnake(){
     // Loop over snake size and draw each part at it's respective coordinates
    for(unsigned int a = 0; a < part_coords.size(); a++){
        glPushMatrix();
        glTranslatef(part_coords[a][0], part_coords[a][1], -40.0f);
        glColor3f(0.0f, 1.0f, 0.0f);
        //glScalef(1.0,1.0,5.0);
        /*glBegin(GL_POLYGON);
            glVertex3f( 1.0f,  1.0f, 0.0f);
            glVertex3f( 1.0f, -1.0f, 0.0f);
            glVertex3f(-1.0f, -1.0f, 0.0f);
            glVertex3f(-1.0f,  1.0f, 0.0f);
        glEnd();*/
        glutSolidCube(2.0f);
        glPopMatrix();
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    


    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    glViewport( 0, h*0.8, w, h);
    gluPerspective(76.0f, 1.0f, 0.0f, 80.0f);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity( );

    gluLookAt( 0, map_half_length+20, 0,0, map_half_length+20, -40, 0, 1, 0);
    
    glPushMatrix();
    drawScore();
    glPopMatrix();

    glPushMatrix();
    drawControls();
    glPopMatrix();



    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    glViewport( 0, 0, w, h*0.8 );
    gluPerspective(76.0f, 1.0f, 0.0f, 80.0f);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity( );

    gluLookAt( part_coords[0][0], part_coords[0][1], -20,xCam, yCam, -40, 0, 0, 1 );
    cout<<part_coords[0][0]<<" "<<part_coords[0][1]<<" "<<zCam<<" "<<xCam<<" "<<yCam<<" "<<zCam<<endl;

    glPushMatrix();
        glColor3f(1.0f,1.0f,1.0f);
        glLineWidth(2.0);
        for (float i = -31.0f; i <= 31.0f; i = i + 2.0f)
        {
            glBegin(GL_LINE_LOOP);
                glVertex3f(i, 31.0f, -40.0f);
                glVertex3f(i, -31.0f, -40.0f);
            glEnd();
        }
        for (float j = -31.0f; j <= 31.0f; j = j + 2.0f)
        {
            glBegin(GL_LINE_LOOP);
                glVertex3f(31.0f, j, -40.0f);
                glVertex3f(-31.0f, j, -40.0f);
            glEnd();
        }
    glPopMatrix();


    glPushMatrix();
    drawSnake();
    glPopMatrix();

    glPushMatrix();
    spawnFood();
    glPopMatrix();

    glPushMatrix();
    drawFood();
    glPopMatrix();




    glutSwapBuffers();
}

void moveSnake(int new_direction){
    direction = new_direction;

    int last_part = part_coords.size() - 1;
    std::deque<float> new_head = part_coords[last_part];

    float delta_x = 0.0f;
    float delta_y = 0.0f;

    float map_edge = 0.0f;

    int snake_part_axis = 0;

    switch (direction){
        case UP:{
            delta_y = 2.0f;
            map_edge = map_half_length;
            snake_part_axis = 1;

            break;
        }

        case DOWN:{
            delta_y = -2.0f;
            map_edge = -map_half_length;
            snake_part_axis = 1;

            break;
        }

        case RIGHT:{
            delta_x = 2.0f;
            map_edge = map_half_length;
            snake_part_axis = 0;

            break;
        }

        case LEFT:{
            delta_x = -2.0f;
            map_edge = -map_half_length;
            snake_part_axis = 0;

            break;
        }
    }

    // Did we slither into ourself?{

    for(unsigned int a = 0; a < part_coords.size(); a++){
        if(part_coords[0][0] + delta_x == part_coords[a][0] &&
           part_coords[0][1] + delta_y == part_coords[a][1]){
            exit(0);
        }
    }

    // Did we slither into a wall?
    if(part_coords[0][snake_part_axis] == map_edge){
        exit(0);
    }

    // Did we get food?
    if(part_coords[0][0] + delta_x == food_coords[0] &&
       part_coords[0][1] + delta_y == food_coords[1]){
        score += 50;
        growth_stage++;
        food_available = false;
    }

    new_head[0] = part_coords[0][0] + delta_x;
    new_head[1] = part_coords[0][1] + delta_y;

    part_coords.push_front(new_head);

    if(!growth_stage){
        part_coords.pop_back();
    } else if(growth_stage == growth){
        growth_stage = 0;
    } else {
        growth_stage++;
    }

    glutPostRedisplay();
}

void moveSnakeAuto(int value){
    if(!moved){
        UNUSED(value);

        moveSnake(direction);
    } else {
        moved = false;
    }

    glutTimerFunc(move_speed, moveSnakeAuto, 0);
}

void initGL(){
    //glMatrixMode(GL_PROJECTION);
    fillObject = gluNewQuadric( );
    gluQuadricDrawStyle( fillObject, GLU_FILL);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void keyboard(unsigned char key, int x, int y){
    UNUSED(x);
    UNUSED(y);

    switch(key){
       /* case 'w':{
            if(direction == LEFT || direction == RIGHT){
                moved = true;

                moveSnake(UP);
            }

            break;
        }

        case 's':{
            if(direction == LEFT || direction == RIGHT){
                moved = true;

                moveSnake(DOWN);
            }

            break;
        }

        case 'a':{
            if(direction == UP || direction == DOWN){
                moved = true;

                moveSnake(LEFT);
            }

            break;
        }

        case 'd':{
            if(direction == UP || direction == DOWN){
                moved = true;

                moveSnake(RIGHT);
            }

            break;
        }
    */
        // Escape key
        case 27:
        case 'q':{
            exit(0);
        }
    }
}

void special(int key, int x, int y){
    UNUSED(x);
    UNUSED(y);

    switch(key){
        case GLUT_KEY_LEFT:{
            if(direction == UP){
                moved = true;

                moveSnake(LEFT);
                xCam = -map_half_length;
                yCam = part_coords[0][1];
                break;
            }
            if(direction == DOWN){
                moved = true;

                moveSnake(RIGHT);

                xCam = map_half_length;
                yCam = part_coords[0][1];
                break;   
            }
            if(direction == LEFT){
                moved = true;

                moveSnake(DOWN);
                yCam = -map_half_length;
                xCam = part_coords[0][0];
                break;      
            }
            if(direction == RIGHT){
                moved = true;

                moveSnake(UP); 

                yCam = map_half_length;
                xCam = part_coords[0][0];
                break;     
            }
        }

        case GLUT_KEY_RIGHT:{
            if(direction == UP){
                moved = true;

                moveSnake(RIGHT);
                xCam = map_half_length;
                yCam = part_coords[0][1];
                
                break;
            }
            if(direction == DOWN){
                moved = true;

                moveSnake(LEFT);
                xCam = -map_half_length;
                yCam = part_coords[0][1];
                break;   
            }
            if(direction == LEFT){
                moved = true;

                moveSnake(UP);
                yCam = map_half_length;
                xCam = part_coords[0][0];
                break;      
            }
            if(direction == RIGHT){
                moved = true;

                moveSnake(DOWN);
                yCam = -map_half_length;
                xCam = part_coords[0][0];
                break;      
            }
        }
    }
}

void reshape(GLsizei width, GLsizei height){
    

    // Make the window non-resizable so we don't have to worry about size changes
    //glutReshapeWindow(600, 600);
    /*gluPerspective(
    50,
    float( width ) / float( height ),
    0.01, 400
    );*/

    w = width;
    h = height;


    /*glMatrixMode( GL_PROJECTION );
  glLoadIdentity( );
  glViewport( 0, 0, width, height );

    gluPerspective(76.0f, 1.0f, 0.0f, 80.0f);*/
  

}

int main(int argc, char** argv){
    glutInit(&argc, argv);

    glutInitWindowSize(800, 800);
    glutCreateWindow("Snake 3D");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutSpecialFunc(special);
    glutTimerFunc(move_speed, moveSnakeAuto, 0);

    const int initSize = 3;

    // Specify the coordinates to each part of the snake
    for(int a = 1; a <= initSize; a++){
        std::deque<float> row;

        row.push_back(0.0f);
        row.push_back((map_half_length + 2.0f + (initSize * 2)) - (a * 2));
        cout<<(map_half_length + 2.0f + (initSize * 2)) - (a * 2)<<endl;

        part_coords.push_front(row);
    }
    xCam = part_coords[0][0];
    yCam = -map_half_length;

    srand(time(NULL));

    initGL();
    glutMainLoop();

    return 0;
}
