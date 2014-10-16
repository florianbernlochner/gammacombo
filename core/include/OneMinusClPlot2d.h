/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#ifndef OneMinusClPlot2d_h
#define OneMinusClPlot2d_h

#include <TROOT.h>
#include "TMultiGraph.h"
#include "TSystem.h"

#include "OneMinusClPlotAbs.h"
#include "Utils.h"
#include "ColorBuilder.h"

using namespace Utils;
using namespace RooFit;
using namespace std;

class OneMinusClPlot2d : public OneMinusClPlotAbs
{
public:
  OneMinusClPlot2d(OptParser *arg, TString name="c1", TString title="c1");
  
  void            addScanner(MethodAbsScan* s);
  void            addFile(TString fName);
  void            Draw();
  void            DrawFull();
	void						drawCLcontent();
  void            drawMarker(float x, float y, int color=0, int style=3, float size=2.0);
  void            drawLHCb();
  void            drawSolutions();
  void            save();
  inline void     setContoursOnly(){contoursOnly = true;};
  inline void     setXaxisTitle(TString s){xTitle=s;};
  inline void     setYaxisTitle(TString s){yTitle=s;};
  
  vector<TH2F*> histos;
  TString xTitle;
  TString yTitle;
  bool contoursOnly;
  vector<vector<int> > linecolor;   /// defines colors of 1 sigma lines and solutions of different scanners
  vector<vector<int> > fillcolor;   /// defines colors of 1 sigma areas of different scanners
  vector<vector<int> > linestyle;   /// defines the style of 1 sigma line of different scanners
  vector<vector<int> > fillstyle;
  vector<int>          markerstyle; /// defines marker styles of the solutions of different scanners
  vector<float>        markersize;
  
private:
  TGraph*         changePointOrder(TGraph *g, int pointId);
  void            drawContour(TMultiGraph *mg, TList* contour, int linewidth, int linecolor, 
                              int linestyle, int fillcolor, int fillstyle, int linestylelast, bool last, bool plotFilled);
  void            drawLegend();
  void            findClosestPoints(TGraph *g1, TGraph *g2, int &i1, int &i2);
  void            magneticBoundaries(TGraph *g, const TH2F* hCL);
  TGraph*         joinIfInside(TGraph *g1, TGraph *g2);
  TMultiGraph*    makeContours(int hCLid, int nContours, bool plotFilled=true, bool last=false);
  TList*          makeHoles(TList *contour);
  void            makeNewPlotStyle();
};

#endif