# gazeㄹ

-----------------

https://github.com/namao1230/gaze/assets/153504478/e678a35e-b55b-4bc0-a056-5da4708e1359


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

                // MFCApplication6View.cpp 파일
                
                #include "pch.h"
                #include "framework.h"
                #include "MFCApplication6.h"
                #include "MFCApplication6Doc.h"
                #include "MFCApplication6View.h"
                
                #ifdef _DEBUG
                #define new DEBUG_NEW
                #endif
                
                IMPLEMENT_DYNCREATE(CMFCApplication6View, CView)
                
                BEGIN_MESSAGE_MAP(CMFCApplication6View, CView)
                    ON_WM_MOUSEMOVE()
                    ON_WM_LBUTTONDOWN() // 왼쪽 버튼을 누를 때 메시지 핸들러 추가
                END_MESSAGE_MAP()
                
                CMFCApplication6View::CMFCApplication6View() noexcept
                {
                }
                
                CMFCApplication6View::~CMFCApplication6View()
                {
                }
                
                BOOL CMFCApplication6View::PreCreateWindow(CREATESTRUCT& cs)
                {
                    return CView::PreCreateWindow(cs);
                }
                
                void CMFCApplication6View::OnDraw(CDC* pDC)
                {
                    CMFCApplication6Doc* pDoc = (CMFCApplication6Doc*)GetDocument();
                    ASSERT_VALID(pDoc);
                    if (!pDoc)
                        return;
                
                    // 사각형 그리기
                    CBrush redBrush(m_RectColor); // 사각형 색상을 현재 색상으로 설정
                    CBrush* pOldBrush = pDC->SelectObject(&redBrush);
                    pDC->Rectangle(m_MousePos.x - 150, m_MousePos.y - 150, m_MousePos.x + 150, m_MousePos.y + 150);
                    pDC->SelectObject(pOldBrush);
                
                    // 타원 그리기
                    CBrush blueBrush(m_EllipseColor); // 타원 색상을 현재 색상으로 설정
                    pOldBrush = pDC->SelectObject(&blueBrush);
                    pDC->Ellipse(m_MousePos.x - 100, m_MousePos.y - 100, m_MousePos.x + 100, m_MousePos.y + 100);
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
                void CMFCApplication6View::AssertValid() const
                {
                    CView::AssertValid();
                }
                
                void CMFCApplication6View::Dump(CDumpContext& dc) const
                {
                    CView::Dump(dc);
                }
                #endif //_DEBUG
                
                void CMFCApplication6View::OnMouseMove(UINT nFlags, CPoint point)
                {
                    // 마우스 포인터의 위치 저장
                    m_MousePos = point;
                    // 화면 갱신 요청
                    Invalidate();
                    // 기본 핸들러 호출
                    CView::OnMouseMove(nFlags, point);
                }
                
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
                
                class CMFCApplication6View : public CView
                {
                protected:
                    CMFCApplication6View() noexcept;
                    DECLARE_DYNCREATE(CMFCApplication6View)
                
                public:
                    virtual ~CMFCApplication6View();
                #ifdef _DEBUG
                    virtual void AssertValid() const;
                    virtual void Dump(CDumpContext& dc) const;
                #endif
                
                protected:
                    CPoint m_MousePos;
                    COLORREF m_RectColor;
                    COLORREF m_EllipseColor;
                
                public:
                    virtual BOOL PreCreateWindow(CREATESTRUCT& cs) override;
                
                    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
                    afx_msg void OnDraw(CDC* pDC);
                    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
                    DECLARE_MESSAGE_MAP()
                };

--------------
