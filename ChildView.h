#pragma once

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:
   BITMAPINFO *      bitmapInfo;
   unsigned char *   dibData;
   unsigned char *   srcData;
   unsigned char *   dstData;

   int               samplePerPixel;
   int               width;
   int               height;
   int               step;
   
   int               GetRealWidth(int width);
   unsigned char     Clip(int value, int low, int high);

   CScrollBar        scrollBar;

   void              GammaCorrection(double gamma);

   void              SpatialFilter3x3(double * mask);

   BOOL              m_bDown;
   CPoint            m_ptDown;

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	DECLARE_MESSAGE_MAP()
public:
   afx_msg void OnFileOpen();

   afx_msg void OnArithmeticAdd();
   afx_msg void OnArithmeticSub();
   afx_msg void OnArithmeticMultiply();
   afx_msg void OnArithmeticDivide();
   afx_msg void OnArithmeticNegative();

   afx_msg void OnGeometricFlipV();
   afx_msg void OnGeometricFlipH();
   afx_msg void OnGeometricRotateLeft();
   afx_msg void OnGeometricRotateRight();

   afx_msg void OnLUTAdd();
   afx_msg void OnLUTNegative();
   afx_msg void OnLUTGamma();
   afx_msg void OnUpdateLutAdd(CCmdUI *pCmdUI);
   afx_msg void OnUpdateLutNegative(CCmdUI *pCmdUI);
   afx_msg void OnUpdateLutGamma(CCmdUI *pCmdUI);
   
   afx_msg void OnFilterBlur();
   afx_msg void OnFilterSharpen();
   afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
   afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
   afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

