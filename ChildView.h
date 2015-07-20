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
   int               imageWidth;
   int               imageHeight;
   int               imageStep;
   
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
};

