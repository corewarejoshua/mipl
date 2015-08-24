#include "stdafx.h"
#include "MIPL.h"
#include "ChildView.h"
#include "Math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CChildView::CChildView()
{
   dibData     = NULL;
   dstData     = NULL;
   m_bDown     = FALSE;
}

CChildView::~CChildView()
{
   if(dibData)
      delete[] dibData;
   if(dstData)
      delete[] dstData;
}

BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
   ON_WM_CREATE()
   ON_WM_HSCROLL()
   ON_COMMAND(ID_FILE_OPEN,               OnFileOpen)
   ON_COMMAND(ID_ARITHMETIC_ADD,          OnArithmeticAdd)
   ON_COMMAND(ID_ARITHMETIC_SUB,          OnArithmeticSub)
   ON_COMMAND(ID_ARITHMETIC_MULTIPLY,     OnArithmeticMultiply)
   ON_COMMAND(ID_ARITHMETIC_DIVIDE,       OnArithmeticDivide)
   ON_COMMAND(ID_ARITHMETIC_NEGATIVE,     OnArithmeticNegative)
   ON_COMMAND(ID_GEOMETRIC_FLIPV,         OnGeometricFlipV)
   ON_COMMAND(ID_GEOMETRIC_FLIPH,         OnGeometricFlipH)
   ON_COMMAND(ID_GEOMETRIC_ROTATELEFT,    OnGeometricRotateLeft)
   ON_COMMAND(ID_GEOMETRIC_ROTATERIGHT,   OnGeometricRotateRight)
   ON_COMMAND(ID_LUT_ADD,                 OnLUTAdd)
   ON_COMMAND(ID_LUT_NEGATIVE,            OnLUTNegative)
   ON_COMMAND(ID_LUT_GAMMA,               OnLUTGamma)
   ON_UPDATE_COMMAND_UI(ID_LUT_ADD,       OnUpdateLutAdd)
   ON_UPDATE_COMMAND_UI(ID_LUT_NEGATIVE,  OnUpdateLutNegative)
   ON_UPDATE_COMMAND_UI(ID_LUT_GAMMA,     OnUpdateLutGamma)
   ON_COMMAND(ID_FILTER_BLUR,             OnFilterBlur)
   ON_COMMAND(ID_FILTER_SHARPEN,          OnFilterSharpen)
   ON_WM_LBUTTONDOWN()
   ON_WM_LBUTTONUP()
   ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   if (CWnd::OnCreate(lpCreateStruct) == -1)
      return -1;

   scrollBar.Create(SBS_HORZ | WS_VISIBLE | WS_CHILD, CRect(0, 600, 600, 600+20), this, 9999);
   scrollBar.SetScrollRange(0, 100);
   scrollBar.SetScrollPos(0);

   return 0;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this);

   if(dibData == NULL)
      return;

   // Draw Image
   ::SetDIBitsToDevice(dc.m_hDC,
      0, 0, width, height,    // Destination
      0, 0, 0, height,        // Source
      dstData, bitmapInfo, DIB_RGB_COLORS);	

   // Draw GDI Object
   CPen Pen;
   CPen * pOldPen;
   Pen.CreatePen(PS_SOLID, 1, RGB(255,0,0));
   pOldPen = dc.SelectObject(&Pen);

   CBrush Brush;
   CBrush * pOldBrush;
   Brush.CreateSolidBrush(RGB(0,255,0));
   pOldBrush = dc.SelectObject(&Brush);
   {
      dc.MoveTo(100, 100);
      dc.LineTo(200, 200);

      dc.Rectangle(10, 10, 50, 50);
   }
   dc.SelectObject(pOldBrush);
   Brush.DeleteObject();

   dc.SelectObject(pOldPen);
   Pen.DeleteObject();
}

void CChildView::OnFileOpen()
{
   // Show File Dialog Box
   CString szFilter = _T("bitmap Files (*.bmp)|*.bmp|All Files (*.*)|*.*|");
   CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT, szFilter,this);
   if(dlg.DoModal() == IDCANCEL)
      return;

   // Open File
   FILE * file;
   _wfopen_s(&file, dlg.GetPathName(), L"rb");

   // Read File Header
   BITMAPFILEHEADER bitmapFileHeader;
   fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, file);

   // Calculate DIB size
   int dibSize = bitmapFileHeader.bfSize - sizeof(BITMAPFILEHEADER);

   // Allocate DIB memory
   if(dibData)
      delete[] dibData;
   dibData = new unsigned char[dibSize];

   // Read DIB
   fread(dibData, dibSize, 1, file);

   // Important Variables
   bitmapInfo     = (BITMAPINFO *) dibData;
   samplePerPixel = bitmapInfo->bmiHeader.biBitCount / 8;
   width          = bitmapInfo->bmiHeader.biWidth;
   height         = bitmapInfo->bmiHeader.biHeight;
   step           = GetRealWidth(width);
   srcData        = dibData + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * bitmapInfo->bmiHeader.biClrUsed;

   // Allocate destination memory
   if(dstData)
      delete[] dstData;
   dstData  = new unsigned char[step * height];

   // copy src to dst
   memcpy(dstData, srcData, step * height);

   // Close file
   fclose(file);

   // Repaint client area
   Invalidate(FALSE);
}

int CChildView::GetRealWidth(int width)
{
   int real_width;
   div_t r;
   r = div(width,4);
   if(r.rem != 0){
      real_width = ((r.quot + 1) * 4);
      return real_width;
   }
   else
      return width;
}

unsigned char CChildView::Clip(int value, int low, int high)
{
   if(value < low)
      return (unsigned char) low;
   else if(value > high)
      return (unsigned char) high;
   else 
      return (unsigned char) value;
}

void CChildView::OnArithmeticAdd()
{
   if(dibData == NULL)
      return;

   for(int i=0;i<width * height;i++){
      dstData[i] = Clip(srcData[i] + 100, 0, 255);
   }

   Invalidate(FALSE);
}

void CChildView::OnArithmeticSub()
{
   if(dibData == NULL)
      return;

   for(int i=0;i<width * height;i++){
      dstData[i] = Clip(srcData[i] - 100, 0, 255);
   }

   Invalidate(FALSE);
}

void CChildView::OnArithmeticMultiply()
{
   if(dibData == NULL)
      return;

   for(int i=0;i<width * height;i++){
      dstData[i] = Clip(srcData[i] * 2, 0, 255);
   }

   Invalidate(FALSE);
}

void CChildView::OnArithmeticDivide()
{
   if(dibData == NULL)
      return;

   for(int i=0;i<width * height;i++){
      dstData[i] = Clip(srcData[i] / 2, 0, 255);
   }

   Invalidate(FALSE);
}

void CChildView::OnArithmeticNegative()
{
   if(dibData == NULL)
      return;

   for(int i=0;i<width * height;i++){
      dstData[i] = 255 - srcData[i];
   }

   Invalidate(FALSE);
}

void CChildView::OnGeometricFlipV()
{
   for(int i=0;i<height;i++){
      memcpy(dstData + i*step, srcData + (height-1-i)*step, step);
   }
   Invalidate(FALSE);
}

void CChildView::OnGeometricFlipH()
{
   for(int i=0;i<height;i++){
      for(int j=0;j<width;j++){
         dstData[i*step + j] = srcData[i*step + (width-j-1)];
      }
   }
   Invalidate(FALSE);
}

void CChildView::OnGeometricRotateLeft()
{
   for(int i=0;i<height;i++){
      for(int j=0;j<width;j++){
         dstData[j*step + (height-i-1)] = srcData[i*step + j];
      }
   }
   Invalidate(FALSE);
}

void CChildView::OnGeometricRotateRight()
{
   for(int i=0;i<height;i++){
      for(int j=0;j<width;j++){
         dstData[i*step + j] = srcData[j*step + (height-i-1)];
      }
   }
   Invalidate(FALSE);
}

void CChildView::OnLUTAdd()
{
   unsigned char lut[256];

   for(int i=0;i<255;i++){
      lut[i] = Clip(i+50, 0, 255);
   }

   for(int i=0;i<width * height;i++){
      dstData[i] = lut[srcData[i]];
   }

   Invalidate(FALSE);
}

void CChildView::OnLUTNegative()
{
   unsigned char lut[256];

   for(int i=0;i<255;i++){
      lut[i] = 255 - i;
   }

   for(int i=0;i<width * height;i++){
      dstData[i] = lut[srcData[i]];
   }

   Invalidate(FALSE);
}

void CChildView::OnLUTGamma()
{
   GammaCorrection(0.8);
}

void CChildView::GammaCorrection(double gamma)
{
   double exp = 1. / gamma;

   unsigned char lut[256];

   for(int i=0;i<255;i++){
      lut[i] = unsigned char( pow(i / 255., exp) * 255 );
   }

   for(int i=0;i<width * height;i++){
      dstData[i] = lut[srcData[i]];
//    dstData[i] = unsigned char( pow(srcData[i]/ 255., exp) * 255 );
   }

   Invalidate(FALSE);
}

void CChildView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
   double gamma = 1. - nPos / 200.;
   GammaCorrection(gamma);

   CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CChildView::OnUpdateLutAdd(CCmdUI *pCmdUI)
{
   if(dibData == NULL)
      pCmdUI->Enable(FALSE);
}

void CChildView::OnUpdateLutNegative(CCmdUI *pCmdUI)
{
   if(dibData == NULL)
      pCmdUI->Enable(FALSE);
}

void CChildView::OnUpdateLutGamma(CCmdUI *pCmdUI)
{
   if(dibData == NULL)
      pCmdUI->Enable(FALSE);
}

void CChildView::OnFilterBlur()
{
   double mask[9] = {1/9., 1/9., 1/9.,
                     1/9., 1/9., 1/9.,
                     1/9., 1/9., 1/9.};
   SpatialFilter3x3(mask);
}

void CChildView::OnFilterSharpen()
{
   double mask[9] = {0, -1, 0,
                     -1, 5, -1,
                     0, -1, 0};
   SpatialFilter3x3(mask);
}

void CChildView::SpatialFilter3x3(double * mask)
{
   double sum;
   for(int i=1;i<height-1;i++){
      for(int j=1;j<width-1;j++){
         sum = 0;
         for(int k=0;k<3;k++){
            for(int l=0;l<3;l++){
               sum += srcData[(i+k-1)*step+ (j+l-1)] * mask[k*3+l];
            }
         }
         dstData[i*step+j] = Clip(int(sum), 0, 255);
      }
   }

   Invalidate(FALSE);
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
   m_bDown = TRUE;
   m_ptDown = point;

   CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
   m_bDown = FALSE;

   CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
   if(m_bDown){

      int diff = m_ptDown.y - point.y;

      unsigned char lut[256];

      for(int i=0;i<255;i++){
         lut[i] = Clip(i+diff, 0, 255);
      }

      for(int i=0;i<width * height;i++){
         dstData[i] = lut[srcData[i]];
      }

      Invalidate(FALSE);
   }  

   CWnd::OnMouseMove(nFlags, point);
}
