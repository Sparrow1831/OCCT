#ifndef _BSPLINECURVE_H
#define _BSPLINECURVE_H
#pragma once
#include <IGESControl_Controller.hxx>
#include <IGESControl_Writer.hxx>
#include <Interface_Static.hxx>
#include "geom_bsplinecurve.hxx"
#include "global.h"
#include "OCCHeader.h"
#include "GeomBase.h"
namespace sBase
{
	namespace sCurve
	{
		using namespace sGeomBase;
		class CBSplineCurve
		{
			friend class CPolyLine;
			friend class CBSplineCurve2d;
			friend BOOL InterpolationBSpline(CBSplineCurve& Curve);
		public:
			CBSplineCurve();
			CBSplineCurve(CBSplineCurve& curve);
			CBSplineCurve(CPoint3DAry& CtrlPts, Doubles& Knots, Ints& Multiplicities, int Degree);
			CBSplineCurve(Handle_Geom_BSplineCurve& ahGeomBSpline);
			CBSplineCurve(TopoDS_Shape& aShape);
			CBSplineCurve(CBSplineCurve2d& aCurve2d);
			~CBSplineCurve(void);
		public:
			void PushFitPt(CPoint3D fitpoint);
			void Interpolate();
			void Approximate();
			void From2DCurve(CBSplineCurve2d* pCurve2d);
			void From2DCurve(CBSplineCurve2d& aCurve2d);
			const double GetCurveLength()const;
			double CurvatureAt(const double t)const;
			double FirstParameter()const;
			double LastParameter()const;
			const CVector3D Ders(const double t)const;
			const CVector3D Ders2(const double t)const;
			const CPoint3D  Point(const double t)const;
			const int Degree()const;
			const int SizeOfFitPoints()const;
			const int ControlPointsNumber()const;//控制点个数
			Handle_Geom_BSplineCurve GetCurve()const;
			Handle_AIS_Shape Display()const;
			CPoint3DAry GetControlPoints();
			Doubles GetKnots();
			Ints GetMultiplicities();
			BOOL IsNull()const;//判断是否生成曲线		
			void Discretization();
			void SetControlPoint(int index, CPoint3D pt);
		private:
			void Interpolate(gp_Pnts& DataValues);
			void Approximate(gp_Pnts& DataValues);
			void Knots();
			void ControlPoints();
			void Multiplicities();	
			void KnotsConfigurationEqual(TColStd_Array1OfReal& Knots, TColgp_Array1OfPnt& Poles, Standard_Integer lower, Standard_Integer upper);
		private:
			CPoint3DAry m_FitPoints;//拟合点
			CPoint3DAry m_ControlPoints;//控制点
			Doubles m_Knots;//节点矢量
			Ints m_Multiplicities;//重复度
			Handle_Geom_BSplineCurve m_hGeomBSpline;
		};

    typedef std::vector<shared_ptr<CBSplineCurve>> CBSplineCurves;
		const double GetCurveLength(const CBSplineCurve& Curve,double t = -1);
		BOOL SaveIGES(CBSplineCurve& Curve);
		BOOL SaveIGES(CBSplineCurves Curves);
	}
}
#endif
