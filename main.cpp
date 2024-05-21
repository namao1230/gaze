#include <windows.h>
#include <GL/glut.h>
#include <cmath>

// 회전 각도 변수 초기화
GLfloat rotationAngleX = 0.0f; // X축 회전 각도
GLfloat rotationAngleY = 0.0f; // Y축 회전 각도
GLfloat rotationAngleZ = 0.0f; // Z축 회전 각도

// 색상 변환 함수
void RGBfromHue(float hue, float& r, float& g, float& b) {
    // 색상 값을 RGB로 변환하는 함수
    float h = hue * 6.0f; // 색상 값을 0부터 6까지로 스케일링
    int i = (int)floor(h); // 정수부분 색상 값
    float f = h - i; // 소수부분 색상 값
    float p = 0.0f; // 보조 변수 p 초기화
    float q = 1.0f - f; // 보조 변수 q 초기화
    float t = f; // 보조 변수 t 초기화
    
    // 색상 값을 RGB로 변환하는 계산식
    switch (i % 6) {
        case 0: r = 1.0f; g = t; b = p; break; // 빨간색에서 노란색으로
        case 1: r = q; g = 1.0f; b = p; break; // 노란색에서 초록색으로
        case 2: r = p; g = 1.0f; b = t; break; // 초록색에서 청록색으로
        case 3: r = p; g = q; b = 1.0f; break; // 청록색에서 파란색으로
        case 4: r = t; g = p; b = 1.0f; break; // 파란색에서 자주색으로
        case 5: r = 1.0f; g = p; b = q; break; // 자주색에서 빨간색으로
    }
}

// 디스플레이 함수
void display() {
    // 화면 지우기
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity(); // 모델뷰 행렬 초기화
    gluLookAt(3, 3, 3, 0, 0, 0, 0, 1, 0); // 카메라 위치 및 방향 설정

    // 회전 적용
    glRotatef(rotationAngleX, 1.0f, 0.0f, 0.0f); // X축 회전
    glRotatef(rotationAngleY, 0.0f, 1.0f, 0.0f); // Y축 회전
    glRotatef(rotationAngleZ, 0.0f, 0.0f, 1.0f); // Z축 회전

    // 원기둥을 무지개 색상으로 그리기
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= 360; i += 10) {
        float hue = (float)i / 360.0f; // 색상 값 계산
        float r, g, b; // 색상 변수 초기화
        RGBfromHue(hue, r, g, b); // 색상 값 계산
        glColor3f(r, g, b); // 무지개 색상 설정
        glVertex3f(cos(i * 3.1415926 / 180), sin(i * 3.1415926 / 180), 1.0f); // 상단 점
        glVertex3f(cos(i * 3.1415926 / 180), sin(i * 3.1415926 / 180), -1.0f); // 하단 점
    }
    glEnd();

    // 흰색 외곽선 그리기
    glLineWidth(2.0f); // 선 두께 설정
    glColor3f(1.0f, 1.0f, 1.0f); // 흰색 설정
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= 360; i += 10) {
        glVertex3f(cos(i * 3.1415926 / 180), sin(i * 3.1415926 / 180), 1.0f); // 상단 외곽선
    }
    glEnd();
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= 360; i += 10) {
        glVertex3f(cos(i * 3.1415926 / 180), sin(i * 3.1415926 / 180), -1.0f); // 하단 외곽선
    }
    glEnd();

    // 상단과 하단에 원 그리기
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 1.0f, 1.0f); // 흰색 설정
    glVertex3f(0.0f, 0.0f, 1.0f); // 상단 원의 중심
    for (int i = 0; i <= 360; i += 10) {
        float hue = (float)i / 360.0f; // 색상 값 계산
        float r, g, b; // 색상 변수 초기화
        RGBfromHue(hue, r, g, b); // 색상 값 계산
        glColor3f(r, g, b); // 무지개 색상 설정
        glVertex3f(cos(i * 3.1415926 / 180), sin(i * 3.1415926 / 180), 1.0f); // 상단 원의 점
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 1.0f, 1.0f); // 흰색 설정
    glVertex3f(0.0f, 0.0f, -1.0f); // 하단 원의 중심
    for (int i = 0; i <= 360; i += 10) {
        float hue = (float)i / 360.0f; // 색상 값 계산
        float r, g, b; // 색상 변수 초기화
        RGBfromHue(hue, r, g, b); // 색상 값 계산
        glColor3f(r, g, b); // 무지개 색상 설정
        glVertex3f(cos(i * 3.1415926 / 180), sin(i * 3.1415926 / 180), -1.0f); // 하단 원의 점
    }
    glEnd();

    glutSwapBuffers(); // 더블 버퍼링 사용하여 화면 표시
}

// 창 크기 변경 시 호출되는 함수
void reshape(int w, int h) {
    glViewport(0, 0, w, h); // 뷰포트 설정
    glMatrixMode(GL_PROJECTION); // 투영 행렬 모드 설정
    glLoadIdentity(); // 투영 행렬 초기화
    gluPerspective(45.0f, (float)w / h, 0.1f, 100.0f); // 원근 투영 설정
    glMatrixMode(GL_MODELVIEW); // 모델뷰 행렬 모드 설정
}

// 초기화 함수
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 배경색 설정
    glEnable(GL_DEPTH_TEST); // 깊이 테스트 활성화
}

// 회전 각도 업데이트 함수
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

// 메인 함수
int main(int argc, char** argv) {
    glutInit(&argc, argv); // GLUT 초기화
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // 디스플레이 모드 설정
    glutInitWindowSize(520, 520); // 창 크기 설정
    glutCreateWindow("Cylinder Example"); // 창 생성
    glutDisplayFunc(display); // 디스플레이 콜백 함수 설정
    glutReshapeFunc(reshape); // 창 크기 변경 콜백 함수 설정
    init(); // 초기화 함수 호출
    glutTimerFunc(10, update, 0); // 타이머 설정
    glutMainLoop(); // 메인 루프 실행
    return 0; // 프로그램 종료
}
