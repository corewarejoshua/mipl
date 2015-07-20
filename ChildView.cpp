#include "stdafx.h"
#include "MIPL.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CChildView::CChildView()
{
   dibData      = NULL;
   dstData      = NULL;
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
   ON_COMMAND(ID_FILE_OPEN,               OnFileOpen)
   ON_COMMAND(ID_ARITHMETIC_ADD,          OnArithmeticAdd)
   ON_COMMAND(ID_ARITHMETIC_SUB,          OnArithmeticSub)
   ON_COMMAND(ID_ARITHMETIC_MULTIPLY,     OnArithmeticMultiply)
   ON_COMMAND(ID_ARITHMETIC_DIVIDE,       OnArithmeticDivide)
   ON_COMMAND(ID_ARITHMETIC_NEGATIVE,     OnArithmeticNegative)
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

void CChildView::OnPaint() 
{
	CPaintDC dc(this);

   if(dibData == NULL)
      return;

   ::SetDIBitsToDevice(dc.m_hDC,
      0, 0, imageWidth, imageHeight,   // Destination
      0, 0, 0, imageHeight,            // Source
      dstData, bitmapInfo, DIB_RGB_COLORS);	
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
   imageWidth     = bitmapInfo->bmiHeader.biWidth;
   imageHeight    = bitmapInfo->bmiHeader.biHeight;
   imageStep      = GetRealWidth(imageWidth);
   srcData        = dibData + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * bitmapInfo->bmiHeader.biClrUsed;

   // Allocate destination memory
   if(dstData)
      delete[] dstData;
   dstData  = new unsigned char[imageStep * imageHeight];

   // copy src to dst
   memcpy(dstData, srcData, imageStep * imageHeight);

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

   for(int i=0;i<imageWidth * imageHeight;i++){
      dstData[i] = Clip(srcData[i] + 100, 0, 255);
   }

   Invalidate(FALSE);
}

void CChildView::OnArithmeticSub()
{
   if(dibData == NULL)
      return;

   for(int i=0;i<imageWidth * imageHeight;i++){
      dstData[i] = Clip(srcData[i] - 100, 0, 255);
   }

   Invalidate(FALSE);
}

void CChildView::OnArithmeticMultiply()
{
   if(dibData == NULL)
      return;

   for(int i=0;i<imageWidth * imageHeight;i++){
      dstData[i] = Clip(srcData[i] * 2, 0, 255);
   }

   Invalidate(FALSE);
}

void CChildView::OnArithmeticDivide()
{
   if(dibData == NULL)
      return;

   for(int i=0;i<imageWidth * imageHeight;i++){
      dstData[i] = Clip(srcData[i] / 2, 0, 255);
   }

   Invalidate(FALSE);
}

void CChildView::OnArithmeticNegative()
{
   if(dibData == NULL)
      return;

   for(int i=0;i<imageWidth * imageHeight;i++){
      dstData[i] = 255 - srcData[i];
   }

   Invalidate(FALSE);
}
