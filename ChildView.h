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
};

