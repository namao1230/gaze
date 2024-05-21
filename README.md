# gaze

-----------------



------------------

        #include <windows.h>
        #include <GL/glut.h>
        #include <cmath>
        
        GLfloat rotationAngleX = 0.0f; // X축 회전 각도
        GLfloat rotationAngleY = 0.0f; // Y축 회전 각도
        GLfloat rotationAngleZ = 0.0f; // Z축 회전 각도
        
        
        void RGBfromHue(float hue, float& r, float& g, float& b) {
            float h = hue * 6.0f;
            int i = (int)floor(h);
            float f = h - i;
            float p = 0.0f;
            float q = 1.0f - f;
            float t = f;
            
            switch (i % 6) {
                case 0: r = 1.0f; g = t; b = p; break;
                case 1: r = q; g = 1.0f; b = p; break;
                case 2: r = p; g = 1.0f; b = t; break;
                case 3: r = p; g = q; b = 1.0f; break;
                case 4: r = t; g = p; b = 1.0f; break;
                case 5: r = 1.0f; g = p; b = q; break;
            }
        }
        
        void display() {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glLoadIdentity();
            gluLookAt(3, 3, 3, 0, 0, 0, 0, 1, 0);
        
            glRotatef(rotationAngleX, 1.0f, 0.0f, 0.0f); // X축 회전
            glRotatef(rotationAngleY, 0.0f, 1.0f, 0.0f); // Y축 회전
            glRotatef(rotationAngleZ, 0.0f, 0.0f, 1.0f); // Z축 회전
        
            // Draw a cylinder with rainbow colors
            glBegin(GL_QUAD_STRIP);
            for (int i = 0; i <= 360; i += 10) {
                float hue = (float)i / 360.0f;
                float r, g, b;
                RGBfromHue(hue, r, g, b);
                
                glColor3f(r, g, b); // Rainbow colors
                glVertex3f(cos(i * 3.1415926 / 180), sin(i * 3.1415926 / 180), 1.0f);
                glVertex3f(cos(i * 3.1415926 / 180), sin(i * 3.1415926 / 180), -1.0f);
            }
            glEnd();
        
            // Draw white outlines
            glLineWidth(2.0f); // Set line width to 2.0
            glColor3f(1.0f, 1.0f, 1.0f); // White color
            glBegin(GL_LINE_LOOP);
            for (int i = 0; i <= 360; i += 10) {
                glVertex3f(cos(i * 3.1415926 / 180), sin(i * 3.1415926 / 180), 1.0f);
            }
            glEnd();
            glBegin(GL_LINE_LOOP);
            for (int i = 0; i <= 360; i += 10) {
                glVertex3f(cos(i * 3.1415926 / 180), sin(i * 3.1415926 / 180), -1.0f);
            }
            glEnd();
        
            // Draw circles at the top and bottom
            glBegin(GL_TRIANGLE_FAN);
            glColor3f(1.0f, 1.0f, 1.0f); // White color
            glVertex3f(0.0f, 0.0f, 1.0f); // Center of top circle
            for (int i = 0; i <= 360; i += 10) {
                float hue = (float)i / 360.0f;
                float r, g, b;
                RGBfromHue(hue, r, g, b);
                glColor3f(r, g, b); // Rainbow colors
                glVertex3f(cos(i * 3.1415926 / 180), sin(i * 3.1415926 / 180), 1.0f);
            }
            glEnd();
        
            glBegin(GL_TRIANGLE_FAN);
            glColor3f(1.0f, 1.0f, 1.0f); // White color
            glVertex3f(0.0f, 0.0f, -1.0f); // Center of bottom circle
            for (int i = 0; i <= 360; i += 10) {
                float hue = (float)i / 360.0f;
                float r, g, b;
                RGBfromHue(hue, r, g, b);
                glColor3f(r, g, b); // Rainbow colors
                glVertex3f(cos(i * 3.1415926 / 180), sin(i * 3.1415926 / 180), -1.0f);
            }
            glEnd();
        
            glutSwapBuffers();
        }
        
        void reshape(int w, int h) {
            glViewport(0, 0, w, h);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(45.0f, (float)w / h, 0.1f, 100.0f);
            glMatrixMode(GL_MODELVIEW);
        }
        
        void init() {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glEnable(GL_DEPTH_TEST);
        }
        
        void update(int value) {
            rotationAngleX += 1.0f; // X축 회전 각도 증가
            rotationAngleY += 1.5f; // Y축 회전 각도 증가
            rotationAngleZ += 2.0f; // Z축 회전 각도 증가
            if (rotationAngleX > 360) {
                rotationAngleX -= 360;
            }
            if (rotationAngleY > 360) {
                rotationAngleY -= 360;
            }
            if (rotationAngleZ > 360) {
                rotationAngleZ -= 360;
            }
            glutPostRedisplay(); // 화면 갱신
            glutTimerFunc(10, update, 0); // 타이머 다시 설정
        }
        
        int main(int argc, char** argv) {
            glutInit(&argc, argv);
            glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
            glutInitWindowSize(520, 520);
            glutCreateWindow("Cylinder Example");
                glutDisplayFunc(display);
            glutReshapeFunc(reshape);
            init();
            glutTimerFunc(10, update, 0); // 타이머 설정
            glutMainLoop();
            return 0;
        }


---------------
