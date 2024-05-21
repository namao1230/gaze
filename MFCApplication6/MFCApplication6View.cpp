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
