/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#ifndef Utils_h
#define Utils_h

#include "TMath.h"
#include "TString.h"
#include "TH2F.h"
#include "TStyle.h"
#include "RooAbsPdf.h"
#include "RooWorkspace.h"
#include "TCanvas.h"
#include "rdtsc.h"
#include "TMatrixDSym.h"
#include "RooRealVar.h"
#include "RooFitResult.h"
#include "RooSlimFitResult.h"
#include "RooDataSet.h"
#include "RooMinuit.h"
#include "TTree.h"
#include "TMatrixDSymEigen.h"
#include "TVectorD.h"
#include <sys/stat.h>
#include "boost/algorithm/string.hpp"

#include "UtilsConfig.h"

using namespace std;
using namespace RooFit;

namespace Utils
{
    extern int countFitBringBackAngle;      ///< counts how many times an angle needed to be brought back
    extern int countAllFitBringBackAngle;   ///< counts how many times fitBringBackAngle() was called
        
		// used to fix parameters in the combination, see e.g. Combiner::combine()
		struct FixPar
		{
			TString name; 
			float value;
			bool useValue;
		};
	
    inline double sq(double x){return x*x;}
    inline double RadToDeg(double rad){return rad/TMath::Pi()*180.;}
    inline double DegToRad(double deg){return deg/180.*TMath::Pi();}
    inline double Max(double v1, double v2){return v1>v2 ? v1 : v2;}
    int           calcNsubdigits(double value, int sigdigits=2);
    float         Round(double value, int digits);
    double        bringBackAngle(double angle);
    bool          isPosDef(TMatrixDSym* c);
    bool          isAngle(RooRealVar* v);
    
    RooFitResult*   fitToMin(RooAbsPdf *pdf, bool thorough, int printLevel);
    RooFitResult*   fitToMinBringBackAngles(RooAbsPdf *pdf, bool thorough, int printLevel);
    RooFitResult*   fitToMinForce(RooWorkspace *w, TString name, TString forceVariables="");
    RooFitResult*   fitToMinImprove(RooWorkspace *w, TString name);
    double          getChi2(RooAbsPdf *pdf);
    TH1F*           histHardCopy(const TH1F* h, bool copyContent=true, bool uniqueName=true);
    TH2F*           histHardCopy(const TH2F* h, bool copyContent=true, bool uniqueName=true);
    
    TString combine(RooWorkspace *w, TString pdf1, TString pdf2);
    TString combine(RooWorkspace *w, TString pdf1, TString pdf2, TString pdf3);
    TString combine(RooWorkspace *w, TString pdf1, TString pdf2, TString pdf3, TString pdf4);
    TString combine(RooWorkspace *w, TString pdf1, TString pdf2, TString pdf3, TString pdf4, TString pdf5);
    TString combine(RooWorkspace *w, TString pdf1, TString pdf2, TString pdf3, TString pdf4, TString pdf5, TString pdf6);
    TString combine(RooWorkspace *w, TString pdf1, TString pdf2, TString pdf3, TString pdf4, TString pdf5, TString pdf6, TString pdf7);
    
    TTree*  convertRooDatasetToTTree(RooDataSet *d);
    
    void mergeNamedSets(RooWorkspace *w, TString mergedSet, TString set1, TString set2);
		void printNuisanceCode(TString par, float val);
		void randomizeParameters(RooWorkspace* w, TString setname);
    void setParameters(const RooAbsCollection* setMe, const RooAbsCollection* values);
    void setParameters(RooWorkspace* w, TString parname, const RooAbsCollection* set);
    void setParameters(RooWorkspace* w, TString parname, RooFitResult* r, bool constAndFloat=false);
    void setParameters(RooWorkspace* w, TString parname, RooSlimFitResult* r, bool constAndFloat=false);
    void setParameters(RooWorkspace* w, TString parname, RooDataSet* d);
    void setParameters(RooWorkspace* w, RooFitResult* values);
    void setParametersFloating(const RooAbsCollection* setMe, const RooAbsCollection* values);
    void setParametersFloating(RooWorkspace* w, TString parname, const RooAbsCollection* set);
    void setParametersFloating(RooWorkspace* w, TString parname, RooFitResult* r);
    void setParametersFloating(RooWorkspace* w, TString parname, RooDataSet* d);
    void fixParameters(const RooAbsCollection* set);
    void fixParameters(RooWorkspace* w, TString parname);
    void floatParameters(const RooAbsCollection* set);
    void floatParameters(RooWorkspace* w, TString parname);
    void setLimit(RooRealVar* v, TString limitname);
    void setLimit(RooWorkspace* w, TString parname, TString limitname);
    void setLimit(const RooAbsCollection* set, TString limitname);
    
    void buildCorMatrix(TMatrixDSym &cor);
    TMatrixDSym* buildCovMatrix(TMatrixDSym &cor, float *err);
    TMatrixDSym* buildCovMatrix(TMatrixDSym &cor, vector<double> &err);
    
    void savePlot(TCanvas *c1, TString name);
    bool FileExists( TString strFilename );
    template<class T> inline bool isIn(vector<T> vec, T var){return (find(vec.begin(), vec.end(), var) != vec.end());};
    
    RooWorkspace* makeWorkspace(TString name="w", config cCoords=usePolarCoords);
    
    static int uniqueRootNameId = 0;
    inline TString          getUniqueRootName(){return (TString)Form("UID%i", ++        uniqueRootNameId);}
    void                    fillArgList(RooArgList* list, RooWorkspace* w, std::vector<TString> names);
    void                    getParameters(const RooFitResult &result, std::vector<TString> &names);
    std::vector<TString>    getParsWithName(const TString& subString, const RooArgSet& set);
    bool                    checkBoundary(const RooSlimFitResult& r, std::vector<TString> lowProb, std::vector<TString> highProb);
    void                    setParsConstToBound(RooWorkspace* w, std::vector<TString> names, bool low);
    void                    setParsConstToBound(RooWorkspace* w, std::vector<TString> namesLow, std::vector<TString> namesHigh);
    void                    setParametersFloating(RooWorkspace* w, std::vector<TString> names);
    void                    setParametersFloating(RooWorkspace* w, std::vector<TString> names, std::vector<TString> names2);

	  void dump_vector(const std::vector<int>& l);
	  void dump_vector(const std::vector<float>& l);
	  void dump_map(const std::map<int, std::vector<int> >& map);
}

#endif