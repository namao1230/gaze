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
