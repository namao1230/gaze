# 국립안동대학교 컴퓨턱공학과 20210817 신현진

-----------------
# Dev-CPP 사각형 큐브 대신 다른 도형 넣기


https://github.com/namao1230/gaze/assets/153504478/e678a35e-b55b-4bc0-a056-5da4708e1359


------------------

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

---------------
# MFC에서 사각형, 타원, 글씨에 다른 3가지 추가하기 를 구현


https://github.com/namao1230/gaze/assets/153504478/f9ea3d2b-d2c5-4b17-b3f6-3f8fdfbf6fe0

---------------

                // MFCApplication6View.cpp 파일
                
                #include "pch.h"
                #include "framework.h"
                #include "MFCApplication6.h"
                #include "MFCApplication6Doc.h"
                #include "MFCApplication6View.h"
                
                #ifdef _DEBUG
                #define new DEBUG_NEW
                #endif
                
                // CMFCApplication6View 클래스의 생성을 선언합니다.
                IMPLEMENT_DYNCREATE(CMFCApplication6View, CView)
                
                BEGIN_MESSAGE_MAP(CMFCApplication6View, CView)
                    ON_WM_MOUSEMOVE() // 마우스 이동 이벤트 핸들러 매핑
                    ON_WM_LBUTTONDOWN() // 마우스 왼쪽 버튼 클릭 이벤트 핸들러 매핑
                END_MESSAGE_MAP()
                
                // 생성자: 초기화 리스트에서는 멤버 변수의 초기값을 설정합니다.
                CMFCApplication6View::CMFCApplication6View() noexcept
                {
                }
                
                // 소멸자: 추가 정리 작업을 수행합니다.
                CMFCApplication6View::~CMFCApplication6View()
                {
                }
                
                // 창을 생성하기 전에 호출되며, 창의 특성을 설정합니다.
                BOOL CMFCApplication6View::PreCreateWindow(CREATESTRUCT& cs)
                {
                    return CView::PreCreateWindow(cs);
                }
                
                // 그리기 이벤트 핸들러: 화면을 그립니다.
                void CMFCApplication6View::OnDraw(CDC* pDC)
                {
                    CMFCApplication6Doc* pDoc = (CMFCApplication6Doc*)GetDocument();
                    ASSERT_VALID(pDoc);
                    if (!pDoc)
                        return;
                
                    // 사각형 그리기
                    CBrush redBrush(m_RectColor); // 현재 색상으로 사각형 브러시 생성
                    CBrush* pOldBrush = pDC->SelectObject(&redBrush);
                    pDC->Rectangle(m_MousePos.x - 150, m_MousePos.y - 150, m_MousePos.x + 150, m_MousePos.y + 150);
                    pDC->SelectObject(pOldBrush);
                
                    // 타원 그리기
                    CBrush blueBrush(m_EllipseColor); // 현재 색상으로 타원 브러시 생성
                    pOldBrush = pDC->SelectObject(&blueBrush);
                    pDC->Ellipse(m_MousePos.x - 100, m_MousePos.y - 100, m_MousePos.x + 100, m_MousePos.y + 100);
                    pDC->SelectObject(pOldBrush);
                
                    // 삼각형 그리기
                    CBrush greenBrush(RGB(0, 255, 0)); // 녹색으로 삼각형 브러시 생성
                    pOldBrush = pDC->SelectObject(&greenBrush);
                    POINT trianglePoints[3];
                    trianglePoints[0] = CPoint(m_MousePos.x, m_MousePos.y - 200); // 삼각형의 꼭짓점 1
                    trianglePoints[1] = CPoint(m_MousePos.x - 100, m_MousePos.y - 50); // 삼각형의 꼭짓점 2
                    trianglePoints[2] = CPoint(m_MousePos.x + 100, m_MousePos.y - 50); // 삼각형의 꼭짓점 3
                    pDC->Polygon(trianglePoints, 3);
                    pDC->SelectObject(pOldBrush);
                
                    // 삼각형 내부에 원 그리기
                    CBrush yellowBrush(RGB(255, 255, 0)); // 노란색으로 원 브러시 생성
                    pOldBrush = pDC->SelectObject(&yellowBrush);
                    pDC->Ellipse(m_MousePos.x - 25, m_MousePos.y - 125, m_MousePos.x + 25, m_MousePos.y - 75);
                    pDC->SelectObject(pOldBrush);
                
                    // 텍스트 출력
                    CString text = L"가야할때를 알고가는 이의 뒷모습은 얼마나 아름다운가";
                    CRect rect;
                    pDC->DrawTextW(text, rect, DT_CALCRECT | DT_CENTER | DT_SINGLELINE);
                    int width = rect.Width();
                    int height = rect.Height();
                    pDC->TextOutW(m_MousePos.x - width / 2, m_MousePos.y - height / 2, text);
                }
                
                #ifdef _DEBUG
                // 디버그 모드에서 객체의 유효성을 검사합니다.
                void CMFCApplication6View::AssertValid() const
                {
                    CView::AssertValid();
                }
                
                // 디버그 모드에서 객체의 상태를 덤프합니다.
                void CMFCApplication6View::Dump(CDumpContext& dc) const
                {
                    CView::Dump(dc);
                }
                #endif //_DEBUG
                
                // 마우스 이동 이벤트 핸들러: 마우스 위치를 업데이트하고 화면을 다시 그립니다.
                void CMFCApplication6View::OnMouseMove(UINT nFlags, CPoint point)
                {
                    // 마우스 포인터의 위치 저장
                    m_MousePos = point;
                    // 화면 갱신 요청
                    Invalidate();
                    // 기본 핸들러 호출
                    CView::OnMouseMove(nFlags, point);
                }
                
                // 마우스 왼쪽 버튼 클릭 이벤트 핸들러: 사각형과 타원의 색상을 랜덤하게 변경하고 화면을 다시 그립니다.
                void CMFCApplication6View::OnLButtonDown(UINT nFlags, CPoint point)
                {
                    // 랜덤한 RGB 값을 생성하여 사각형과 타원의 색상으로 설정
                    m_RectColor = RGB(rand() % 256, rand() % 256, rand() % 256);
                    m_EllipseColor = RGB(rand() % 256, rand() % 256, rand() % 256);
                    // 화면 갱신 요청
                    Invalidate();
                    // 기본 핸들러 호출
                    CView::OnLButtonDown(nFlags, point);
                }

--------------

                #pragma once
                
                // CMFCApplication6View 클래스는 CView를 상속받아 MFC 응용 프로그램의 뷰를 구현합니다.
                class CMFCApplication6View : public CView
                {
                protected:
                    // 생성자: serialization에서만 호출됩니다.
                    CMFCApplication6View() noexcept;
                    DECLARE_DYNCREATE(CMFCApplication6View)
                
                public:
                    // 소멸자
                    virtual ~CMFCApplication6View();
                
                #ifdef _DEBUG
                    // 디버그 모드에서 객체의 유효성을 검사합니다.
                    virtual void AssertValid() const;
                
                    // 디버그 모드에서 객체의 상태를 덤프합니다.
                    virtual void Dump(CDumpContext& dc) const;
                #endif
                
                protected:
                    // 마우스 위치를 저장하는 멤버 변수
                    CPoint m_MousePos;
                
                    // 사각형 색상을 저장하는 멤버 변수
                    COLORREF m_RectColor;
                
                    // 타원 색상을 저장하는 멤버 변수
                    COLORREF m_EllipseColor;
                
                    // 삼각형 색상을 저장하는 멤버 변수
                    COLORREF m_TriangleColor;
                
                    // 삼각형 안의 원 색상을 저장하는 멤버 변수
                    COLORREF m_CircleInTriangleColor;
                
                public:
                    // 창을 생성하기 전에 호출되며, 창의 특성을 설정합니다.
                    virtual BOOL PreCreateWindow(CREATESTRUCT& cs) override;
                
                    // 마우스 이동 이벤트 핸들러
                    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
                
                    // 그리기 이벤트 핸들러
                    afx_msg void OnDraw(CDC* pDC);
                
                    // 마우스 왼쪽 버튼 클릭 이벤트 핸들러
                    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
                
                    // 메시지 맵을 선언합니다.
                    DECLARE_MESSAGE_MAP()
                };
                

--------------
# 소감문


이번에 dev c++ 에서 처음으로 3D 도형을 구현해 본거같은데 생각보다 많이 어려웠습니다. p5.js는 원통형이나 이런것들을 간단하게 만들어주는 라이브러리가 있어서 함수만집어넣어주면 바로 만들어 주지만 이거는 하나하나 뭔가 만들어가는 느낌이 매우 크다는 것을 받았습니다. 그리고 p5.js랑 코드도 많이달라서 완전히 새로운 무언가를 배우는데 생각보다 많이 힘들었습니다. 하지만 끈질기게 하면서 완성을했고 조금은 openGL에 한발자국 딛었다는 느낌을 받았습니다. 그리고 두번째 과제를 하면서 MFC라는 것을 처음 알게되었습니다. 이것은 p5.js 랑 또 다르게 C++로 만들고 이벤트 처리를 포함한 GUI 요소를 만들고 관리할 수 있는 클래스들을 제공해주기 때문에 많이 편한느낌을 받았습니다. 하지만 C++를 처음 접해봤기때문에 마찬가지로 많이 어렵게 느껴졌습니다. 하지만 처음이 힘들지 계속해서 하면 늘기도 하고 또 편안하게 p5.js 처럼 많은 클래스를 제공해줘서 익숙해진다면 더욱 쉽게 많고 다양한것들을 구현할수 있겠다는 생각을 했습니다. 이번기회로 많은 디자인 그래픽에 대한 길을 넓혔다고 생각하고 더욱 증진해서 더많은 그래픽을 구현하기위해 노력하겠습니다. 
