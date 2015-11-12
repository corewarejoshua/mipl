#include "stdafx.h"
#include "MIPL.h"
#include "ChildView.h"
#include "Math.h"
#include "ippi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void CChildView::OnArithmeticAdd()
{
   if(dibData == NULL)
      return;

   short * src = (short *) srcData;
   short * dst = (short *) dstData;
   for(int i=0;i<srcStep * height;i++){
      dst[i] = Clip(src[i] + 200, -32768, 32768);
   }

   Trans16to8();
   Invalidate(FALSE);
}

void CChildView::OnArithmeticSub()
{
   if(dibData == NULL)
      return;

   


   Invalidate(FALSE);
}

void CChildView::OnArithmeticMultiply()
{
   if(dibData == NULL)
      return;


   Invalidate(FALSE);
}

void CChildView::OnArithmeticDivide()
{
   if(dibData == NULL)
      return;


   Invalidate(FALSE);
}

void CChildView::OnArithmeticNegative()
{
   if(dibData == NULL)
      return;


   Invalidate(FALSE);
}

void CChildView::OnGeometricFlipV()
{
   if(dibData == NULL)
      return;


   Invalidate(FALSE);
}

void CChildView::OnGeometricFlipH()
{
   if(dibData == NULL)
      return;

   Invalidate(FALSE);
}

void CChildView::OnGeometricRotateLeft()
{

   Invalidate(FALSE);
}

void CChildView::OnGeometricRotateRight()
{

   Invalidate(FALSE);
}
