#include "OptParser.h"

///
/// Organize command line options.
/// The strategy is to have one object of this class present in the
/// main program, which then gets passed down to all other objects.
/// The command line options are made available through data members
/// of this class.
/// Options can be booked, either in blocks using the respective functions,
/// or individually. Only booked options get parsed from the command line.
///
/// To add a new option,
/// - add a data member
/// - add its initializer to the constructor (vectors don't need initializers).
/// - add its name to defineOptions()
/// - add its definition and parsing to parseArguments()
///
OptParser::OptParser()
{
  defineOptions();

  // always book these options
  bookedOptions.push_back("debug");
  bookedOptions.push_back("interactive");
  bookedOptions.push_back("usage");
  bookedOptions.push_back("var");
  bookedOptions.push_back("verbose");

  // Initialize the variables.
	// For more complex arguments these are also the default values.
	cacheStartingValues = false;
  controlplot = false;
	coverageCorrectionID = 0;
	coverageCorrectionPoint = 0;
  debug = false;
  digits = -99;
  enforcePhysRange = false;
  id = -99;
  importance = false;
  interactive = false;
  jobdir = ".";
  largest = false;
  lightfiles = false;
  nBBpoints = -99;
  ndiv = 407;
  ndivy = 407;
  nosyst = false;
  npoints1d = -99;
  npoints2dx = -99;
  npoints2dy = -99;
  npointstoy = -99;
  nrun = -99;
  ntoys = -99;
	parsavefile = "";
  parevol = false;
  plotid = -99;
	plotlegend = true;
  plotlegx = -99;
  plotlegy = -99;
  plotlhcbx = -99;
  plotlhcby = -99;
  plotlog = false;
  plotmagnetic = false;
  plotnsigmacont = 2;
  plotpluginonly = false;
  plotprelim = false;
  plotpulls = false;
  plotsolutions = -99;
  plotunoff = false;
  pluginPlotRangeMax = -99;
  pluginPlotRangeMin = -99;
  pluginext = false;
  probforce = false;
  probimprove = false;
	printcor = false;
  scanforce = false;
  scanrangeMax = -99;
  scanrangeMin = -99;
  scanrangeyMax = -99;
  scanrangeyMin = -99;
  usage = false;
  verbose = false;
}

///
/// Define the names of all available command line options.
/// Other places of the code will check against this list.
///
void OptParser::defineOptions()
{
  availableOptions.push_back("action");
  availableOptions.push_back("addpdf");
  availableOptions.push_back("asimov");
	availableOptions.push_back("cacheStartingValues");
  availableOptions.push_back("combid");
	availableOptions.push_back("color");
  availableOptions.push_back("controlplots");
	availableOptions.push_back("covCorrect");
	availableOptions.push_back("covCorrectPoint");
  availableOptions.push_back("debug");
  availableOptions.push_back("delpdf");
  availableOptions.push_back("digits");
  availableOptions.push_back("evol");
	availableOptions.push_back("fix");
  availableOptions.push_back("id");
  availableOptions.push_back("importance");
  availableOptions.push_back("interactive");
  availableOptions.push_back("jobdir");
  availableOptions.push_back("jobs");
  availableOptions.push_back("largest");
  availableOptions.push_back("leg");
  availableOptions.push_back("lhcb");
  availableOptions.push_back("lightfiles");
	availableOptions.push_back("loadParamsFile");
  availableOptions.push_back("log");
  availableOptions.push_back("magnetic");
  availableOptions.push_back("nBBpoints");
  availableOptions.push_back("nosyst");
  availableOptions.push_back("npoints");
  availableOptions.push_back("npoints2d");
  availableOptions.push_back("npoints2dx");
  availableOptions.push_back("npoints2dy");
  availableOptions.push_back("npointstoy");
  availableOptions.push_back("nrun");
  availableOptions.push_back("ntoys");
	availableOptions.push_back("parsavefile");
  availableOptions.push_back("pevid");
  availableOptions.push_back("physrange");
  availableOptions.push_back("plotid");
  availableOptions.push_back("pluginext");
  availableOptions.push_back("pn");
  availableOptions.push_back("pn2d");
  availableOptions.push_back("po");
  availableOptions.push_back("prelim");
  availableOptions.push_back("probforce");
  availableOptions.push_back("probimprove");
  availableOptions.push_back("ps");
  availableOptions.push_back("pulls");
  availableOptions.push_back("qh");
	availableOptions.push_back("sn");
	availableOptions.push_back("sn2d");
  availableOptions.push_back("scanforce");
  availableOptions.push_back("scanrange");
  availableOptions.push_back("scanrangey");
  availableOptions.push_back("title");
  availableOptions.push_back("usage");
  availableOptions.push_back("unoff");
  availableOptions.push_back("var");
  availableOptions.push_back("verbose");
  availableOptions.push_back("relation");
  availableOptions.push_back("pluginplotrange");
  availableOptions.push_back("plotnsigmacont");
  availableOptions.push_back("plot2dcl");
  availableOptions.push_back("ndiv");
  availableOptions.push_back("ndivy");
	availableOptions.push_back("printcor");
}

///
/// Book all available options, if you are lazy.
///
void OptParser::bookAllOptions()
{
  for ( int i=0; i<availableOptions.size(); i++ )
    bookedOptions.push_back(availableOptions[i]);
}

///
/// Book options associated to plotting.
///
void OptParser::bookPlottingOptions()
{
	bookedOptions.push_back("color");
  bookedOptions.push_back("digits");
  bookedOptions.push_back("leg");
  bookedOptions.push_back("lhcb");
  bookedOptions.push_back("log");
  bookedOptions.push_back("magnetic");
  bookedOptions.push_back("prelim");
  bookedOptions.push_back("ps");
  bookedOptions.push_back("plotnsigmacont");
  bookedOptions.push_back("plot2dcl");
  bookedOptions.push_back("ndiv");
  bookedOptions.push_back("ndivy");
  bookedOptions.push_back("title");
  bookedOptions.push_back("unoff");
}

///
/// Book options associated to the Plugin method
/// and the Berger-Boos method (batch job handling,
/// control plots).
///
void OptParser::bookPluginOptions()
{
  bookedOptions.push_back("controlplots");
  bookedOptions.push_back("id");
  bookedOptions.push_back("importance");
  bookedOptions.push_back("jobs");
  bookedOptions.push_back("lightfiles");
  bookedOptions.push_back("nBBpoints");
  bookedOptions.push_back("npointstoy");
  bookedOptions.push_back("nrun");
  bookedOptions.push_back("ntoys");
  bookedOptions.push_back("pevid");
  bookedOptions.push_back("physrange");
  bookedOptions.push_back("pluginext");
  bookedOptions.push_back("po");
  bookedOptions.push_back("pluginplotrange");
}

///
/// Book options associated to the Prob method.
///
void OptParser::bookProbOptions()
{
  bookedOptions.push_back("asimov");
  bookedOptions.push_back("evol");
  bookedOptions.push_back("npoints");
  bookedOptions.push_back("npoints2d");
  bookedOptions.push_back("npoints2dx");
  bookedOptions.push_back("npoints2dy");
  bookedOptions.push_back("physrange");
  bookedOptions.push_back("pn");
  bookedOptions.push_back("pn2d");
  bookedOptions.push_back("sn");
  bookedOptions.push_back("sn2d");
  bookedOptions.push_back("probforce");
  bookedOptions.push_back("probimprove");
  bookedOptions.push_back("pulls");
  bookedOptions.push_back("scanforce");
	bookedOptions.push_back("scanforce");
}

///
/// Book options associated to the flow control.
///
void OptParser::bookFlowcontrolOptions()
{
  bookedOptions.push_back("action");
  bookedOptions.push_back("addpdf");
  bookedOptions.push_back("combid");
	bookedOptions.push_back("fix");
  bookedOptions.push_back("delpdf");
  bookedOptions.push_back("jobdir");
  bookedOptions.push_back("nosyst");
}

///
/// Book the given option. Checks if it is available.
/// \param opt Book this option.
///
void OptParser::bookOption(TString opt)
{
  if ( !isIn<TString>(availableOptions, opt) ){
    cout << "OptParser::bookOption() : ERROR : No such option! Check OptParser::defineOptions()." << endl;
    return;
  }
  bookedOptions.push_back(opt);
}

///
/// Check the --action argument. Was action 's' given?
///
bool OptParser::isAction(TString s)
{
  return isIn<TString>(action, s);
}

///
/// Check the --quickhack argument. Was hack 'id' given?
///
bool OptParser::isQuickhack(int id)
{
  return isIn<int>(qh, id);
}

///
/// Parse the command line for booked options. Then apply some
/// post-processing and checks, where necessary. Save the parsed
/// values into the datamembers. If an option was not given or not booked,
/// it will assume the default value given here.
///
void OptParser::parseArguments(int argc, char* argv[])
{
	CmdLine cmd("Calculate CL intervals.", ' ', "v2");

  // --------------- arguments that take a value
	TCLAP::ValueArg<string> scanrangeArg("", "scanrange", "Restrict the scan range to a given range. "
    "In 2D scans, this corresponds to the x variable. "
    "Format: --scanrange min:max.", false, "default", "string");
  TCLAP::ValueArg<string> scanrangeyArg("", "scanrangey", "For 2D plots, restrict the scan range "
    "of the y variable to a given range. "
    "Format: --scanrangey min:max.", false, "default", "string");
  TCLAP::ValueArg<int> ndivArg("", "ndiv", "Set the number of axis divisions (x axis in 1d and 2d plots): "
		"ndiv=N1 + 100*N2 + 10000*N3, "
	  "N1 = number of 1st divisions (N2 = 2nd, N3 = 3rd). Default is 407. To enable bin optimization, pre-pend "
	  "a '-'.", false, -1, "int");
	TCLAP::ValueArg<int> coverageCorrectionIDArg("","covCorrect","Correct for the coverage given a flat transformation of the pvalue distribution. You can also pass a coverage correction point (see --covCorrectPoint)\n"
			"0: no correction (default)\n"
			"1: linear correction\n"
			"2: linear + exponential correction\n"
			"3: linear + 1/x correction\n",
			false, 0, "int");
	TCLAP::ValueArg<int> coverageCorrectionPointArg("","covCorrectPoint","Point to use for coverage correction",false,0,"int");
  TCLAP::ValueArg<int> ndivyArg("", "ndivy", "Set the number of axis divisions (y axis in 2d plots): "
		"ndivy=N1 + 100*N2 + 10000*N3, "
	  "N1 = number of 1st divisions (N2 = 2nd, N3 = 3rd). Default is 407. To enable bin optimization, pre-pend "
	  "a '-'.", false, -1, "int");
	TCLAP::ValueArg<int> plotidArg("p", "plotid", "Make plot with given ID. When plotting control plots "
	  "(--controlplots), the IDs 1-6 are available. If not given, all control plots are made.", false, 0, "int");
	TCLAP::ValueArg<int> digitsArg("s", "digits", "Set the number of printed"
	  " digits right of the decimal point. Default is automatic.", false, -1, "int");
	TCLAP::ValueArg<int> plotsolutionsArg("", "ps", "Include solutions in the plots.\n"
  	"1d plots: the numerical value and 1sigma errors are plotted.\n"
  	" 0: don't plot\n"
  	" 1: at central value\n"
  	" 2: at left interval boundary\n"
  	" 3: at right interval boundary.\n"
  	" 4: a little more left of the left interval boundary.\n"
  	"2d plots: markers are plotted at the position of the solution.\n"
  	" 0: don't plot\n"
  	" 1: plot markers at local minima\n"
  	" 2: plot markers only at best-fit point.",
  	false, 0, "int");
  TCLAP::ValueArg<string> plotlegArg("", "leg", "Adjust the plot legend.\n"
		"Disable the legend with --leg off .\n"
		"2d plots: set the position of the legend. "
    "Format: --leg xmin:ymin in normalized coordinates [0,1]. Default: 0.17:0.75", false, "default", "string");
  TCLAP::ValueArg<string> pluginplotrangeArg("", "pluginplotrange", "Restrict the Plugin plot to a given range to "
    "rejcet low-statistics outliers. Format: --pluginplotrange min-max.", false, "default", "string");
  TCLAP::ValueArg<int> plotnsigmacontArg("", "ncontours", "plot this many sigma contours in 2d plots (max 5)", false, 2, "int");
  TCLAP::ValueArg<string> plotlhcbArg("", "lhcb", "Set the position of the LHCb logo. "
    "Format: --lhcb xmin:ymin in normalized coordinates [0,1]. To use default values "
    "for one coordinate use -1: -1:y. Use '--lhcb off' to disable the logo.", false, "default", "string");
  TCLAP::ValueArg<int> nBBpointsArg("", "nBBpoints", "number of BergerBoos points per scanpoint", false, 1, "int");
  TCLAP::ValueArg<int> idArg("", "id", "When making controlplots (--controlplots), only consider the "
    "point with this ID. This can be used to plot a certain Berger-Boos point only, "
    "or to plot a certain coverage test toy only.", false, -1, "int");
	TCLAP::ValueArg<int> ntoysArg("", "ntoys", "number of toy experiments per job. Default: 25", false, 25, "int");
	TCLAP::ValueArg<int> nrunArg("", "nrun", "Number of toy run. To be used with --action pluginbatch.", false, 1, "int");
	TCLAP::ValueArg<int> npointsArg("", "npoints", "Number of scan points used by the 1d prob method. Default: 100", false, 100, "int");
	TCLAP::ValueArg<int> npoints2dArg("", "npoints2d", "Number of scan points used by the 2d prob method. "
	  "Uses same number for both dimensions. See also --npoints2dx, --npoints2dy.", false, -1, "int");
	TCLAP::ValueArg<int> npoints2dxArg("", "npoints2dx", "Number of 2D scan points, x axis. Default: 50", false, 50, "int");
	TCLAP::ValueArg<int> npoints2dyArg("", "npoints2dy", "Number of 2D scan points, y axis. Default: 50", false, 50, "int");
	TCLAP::ValueArg<int> npointstoyArg("", "npointstoy", "Number of scan points used by the plugin method. Default: 100", false, 100, "int");
  TCLAP::MultiArg<string> jobsArg("j", "jobs", "Range of toy job ids to be considered. "
    "To be used with --action plugin. "
    "Can be given multiple times when plotting more than one combinations. Give in same "
    "order as the -c options. Format: -j min-max", false, "string");
  TCLAP::ValueArg<string> jobdirArg("", "jobdir", "Give absolute job-directory if working on batch systems.", false, "default", "string");

  // --------------- switch arguments
	TCLAP::SwitchArg plotpluginonlyArg("", "po", "Make a 1-CL plot just showing the plugin curves.", false);
  TCLAP::SwitchArg interactiveArg("i", "interactive", "Enables interactive mode (requires X11 session).", false);
	TCLAP::SwitchArg pluginextArg("", "pluginext", "Use the external (=Prob) chi2min histogram"
	  " instead of chi2min from the toys", false);
	TCLAP::SwitchArg parevolArg("e", "evol", "Plots the parameter evolution of the profile likelihood.", false);
	TCLAP::SwitchArg controlplotArg("", "controlplots", "Make controlplots analysing the generated toys.", false);
	TCLAP::SwitchArg plotmagneticArg("", "magnetic", "In 2d plots, enable magnetic plot borders which will "
	  "attract the 2sigma curves.", false);
	TCLAP::SwitchArg verboseArg("v", "verbose", "Enables verbose output.", false);
	TCLAP::SwitchArg debugArg("d", "debug", "Enables debug level output.", false);
	TCLAP::SwitchArg usageArg("u", "usage", "Prints usage information and exits.", false);
	TCLAP::SwitchArg scanforceArg("f", "scanforce", "Use stronger minimum finding for the Plugin method.", false);
	TCLAP::SwitchArg probforceArg("", "probforce", "Use stronger minimum finding for the Prob method.", false);
	TCLAP::SwitchArg probimproveArg("", "probimprove", "Use IMPROVE minimum finding for the Prob method.", false);
	TCLAP::SwitchArg largestArg("", "largest", "Report largest CL interval: lowest boundary of "
  	"all intervals to highest boundary of all intervals. Useful if two intervals are very "
  	"close together.", false);
	TCLAP::SwitchArg plotlogArg("", "log", "make logarithmic 1-CL plots", false);
	TCLAP::SwitchArg plotpullsArg("", "pulls", "Make a pull plot illustrating the consistency "
	  "of the best solution with the observables.", false);
	TCLAP::SwitchArg lightfilesArg("", "lightfiles", "Produce only light weight root files for the plugin toys."
	  " They cannot be used for control plots but save disk space.", false);
	TCLAP::SwitchArg plotprelimArg("", "prelim", "Plot 'Preliminiary' into the plots. See also --unoff .", false);
	TCLAP::SwitchArg plotunoffArg("", "unoff", "Plot 'Unofficial' into the plots. See also --prelim .", false);
	TCLAP::SwitchArg plot2dclArg("", "2dcl", "Plot '2d' confidence level contours in 2d plots.", false);
	TCLAP::SwitchArg physrangeArg("", "pr", "Enforce the physical range on all parameters (needed to reproduce "
	  "the standard Feldman-Cousins with boundary example). If set, no nuisance will be allowed outside the "
	  "'phys' limit. However, toy generation of observables is not affected.", false);
	TCLAP::SwitchArg importanceArg("", "importance", "Enable importance sampling for plugin toys.", false);
	TCLAP::SwitchArg nosystArg("", "nosyst", "Sets all systematic errors to zero.", false);
	TCLAP::SwitchArg printcorArg("", "printcor", "Print correlations of each solution found.", false);

  // --------------- aruments that can be given multiple times
  vector<string> vAction;
	vAction.push_back("bb");
	vAction.push_back("bbbatch");
	vAction.push_back("plot");
	vAction.push_back("plot2d");
	vAction.push_back("plugin");
	vAction.push_back("pluginbatch");
	vAction.push_back("prob");
	vAction.push_back("runtoys");
	vAction.push_back("scantree");
	vAction.push_back("test");
	ValuesConstraint<string> cAction(vAction);
	TCLAP::MultiArg<string> actionArg("a", "action", "Perform action", false, &cAction);
	TCLAP::MultiArg<string> varArg("", "var", "Scan variable (default: g). Can be given twice, in which case "
	  "2D scans are performed.", false, "string");
	TCLAP::MultiArg<string> relationArg("", "relation", "Provide the truth relation of the PDF family PDF_GenericGaus, "
  	"that connects an observable to the parameters. "
  	"Example: --relation 'x+y'. Default: idendity.", false, "string");
  TCLAP::MultiArg<int> combidArg("c", "combid", "ID of combination to be computed. "
	  "Use -u to get a list of available combinations.", false, "int");
	TCLAP::MultiArg<int> colorArg("", "color", "ID of color to be used for the combination. "
	  "Default: 0 for first scanner, 1 for second, etc.", false, "int");
	TCLAP::MultiArg<string> addpdfArg("", "addpdf", "Create a new combination by adding PDFs to an existing one. "
	  "Use -u to get a list of available PDFs.\n"
	  "Syntax: --addpdf combinerId:pdfId1,pdfId2,...\n"
	  "Example: -c 10 --addpdf 10:5. This will perform two scans, one for combination "
	  "10, one for combination 10 with added PDF 5.", false, "int");
  TCLAP::MultiArg<string> delpdfArg("", "delpdf", "PDF ID to be deleted from the selected combination. "
	  "Use -u to get a list of available PDFs.\n"
	  "Syntax: --delpdf combinerId:pdfId1,pdfId2,...\n"
	  "Example: -c 10 --delpdf 10:5. This will perform two scans, one for combination "
	  "10, one for combination 10 without PDF 5.", false, "int");
	TCLAP::MultiArg<int> pevidArg("", "pevid", "ID of combination used for the profile likelihood"
  	"that determines the parameter evolution for the Plugin toy generation. If not given, "
  	"the --combid will be used. Use -u to get a list of possible choices.", false, "int");
	TCLAP::MultiArg<float> pnArg("", "pn", "--pn x. Print nuisances at certain points in C++ format after a "
  	"1d scan was performed. This can be used with the force method to obtain suitable start "
  	"parameters for further scans. "
  	"Parameters will be printed for scan point bin that contains x. "
  	"Angles have to be given in radians.", false, "float");
	TCLAP::MultiArg<string> pn2dArg("", "pn2d", "Print nuisances during 2d scans at the given points. "
	  "Format: x:y", false, "string");
	TCLAP::MultiArg<int> qhArg("", "qh", "Quick hacks. \n"
  	"1: Move up the printed solutions in 1d log plots such that they don't clash with the 95% clabel. \n"
  	"2: Move the CL labels to the middle of the 1d plots. \n"
  	"3: add 180 deg to the d_dpi axis and solution in the 1d plot. \n"
  	"4: move plotted numbers a bit to the left to not cover 1d plot axis. \n"
		"5: Test toy generation in the 1d plugin method. At each scan point, 10 toys are printed out- but nothing is fit.\n"
		"6: Scale down LHCb errors in the full and robust combinations by a factor 10.\n"
		"7: Remove 'addedPdf' and 'delPdf' strings from plot file name to get shorter filenames.\n"
		"8: Switch on the new CL interval maker output.\n"
  	, false, "int");
	TCLAP::MultiArg<string> titleArg("", "title", "Override the title of a combination. "
  	"If 'default' is given, the default title for that combination is used. "
  	"Example: --title 'This is the 1. combination.' --title 'And this the second.'", false, "string");
	TCLAP::MultiArg<string> fixArg("", "fix", "Fix one or more parameters in a combination. "
  	"If 'none' is given, all parameters are floated (default). "
		"If given multiple times, the first --fix argument refers to the first combination, "
		"the second one to the second and so on. "
		"If given a single time, it is applied to all combinations. \n"
  	"Example: --fix 'g=1.7,r_dk-0.09' \n"
		"To fix just the parameters in the second combination, do\n"
  	"Example: --fix 'none' --fix 'g=1.7,r_dk-0.09' \n"
		, false, "string");
	TCLAP::MultiArg<float> snArg("", "sn", "--sn x. Save nuisances to parameter cache file at certain points after a "
  	"1d scan was performed. This can be used to set these as starting points "
  	"for further scans. "
  	"Parameters will be saved for scan point bin that contains x. "
  	"Angles have to be given in radians.", false, "float");
	TCLAP::MultiArg<string> sn2dArg("", "sn2d", "Save nuisances as for --sn (1d case) but for 2d scans at the given points. "
	  "Format: x:y", false, "string");
	TCLAP::MultiArg<string> loadParamsFileArg("", "parfile", "Load starting parameters for the corresponding "
		"combination from this particular file. "
  	"If 'default' is given, the default file for that combination is used, which is found in "
		"plots/par/*_RO.dat ."
  	"Example: --parfile parsForFirstCombination.dat --parfile parsForSecondCombination.dat", false, "string");
	TCLAP::MultiArg<int> asimovArg("", "asimov", "Run an Asimov toy, in which all observables are set to "
		"truth values defined in a parameter .dat file. This can be the default one, or a configured one "
		"using --parfile.\n"
		"The given value selects the parameter point from the .dat file: first=1, second=2, ...\n"
		"Can be given once per combination. "
  	"Example: --asimov 2 --asimov 1\n"
		"This will run an Asimov toy for the first combination at point 2, and another one "
		"for the second combination at point 1. If you only want to run an Asimov for the second "
		"combination, select asimov point 0 for the first one.", false, "int");

	//
	// let TCLAP parse the command line
	// The order is alphabetical - this order defines how the options
	// are ordered on the command line, unfortunately in reverse.
	//
  if ( isIn<TString>(bookedOptions, "verbose" ) ) cmd.add( verboseArg );
  if ( isIn<TString>(bookedOptions, "var" ) ) cmd.add(varArg);
  if ( isIn<TString>(bookedOptions, "usage" ) ) cmd.add( usageArg );
  if ( isIn<TString>(bookedOptions, "unoff" ) ) cmd.add( plotunoffArg );
  if ( isIn<TString>(bookedOptions, "title" ) ) cmd.add( titleArg );
  if ( isIn<TString>(bookedOptions, "sn2d" ) ) cmd.add(sn2dArg);
  if ( isIn<TString>(bookedOptions, "sn" ) ) cmd.add(snArg);
  if ( isIn<TString>(bookedOptions, "scanrange" ) ) cmd.add( scanrangeArg );
  if ( isIn<TString>(bookedOptions, "scanrangey" ) ) cmd.add( scanrangeyArg );
  if ( isIn<TString>(bookedOptions, "scanforce" ) ) cmd.add( scanforceArg );
  if ( isIn<TString>(bookedOptions, "relation" ) ) cmd.add(relationArg);
  if ( isIn<TString>(bookedOptions, "qh" ) ) cmd.add(qhArg);
  if ( isIn<TString>(bookedOptions, "pulls" ) ) cmd.add( plotpullsArg );
  if ( isIn<TString>(bookedOptions, "ps" ) ) cmd.add( plotsolutionsArg );
  if ( isIn<TString>(bookedOptions, "probimprove" ) ) cmd.add( probimproveArg );
  if ( isIn<TString>(bookedOptions, "probforce" ) ) cmd.add( probforceArg );
  if ( isIn<TString>(bookedOptions, "prelim" ) ) cmd.add( plotprelimArg );
  if ( isIn<TString>(bookedOptions, "po" ) ) cmd.add( plotpluginonlyArg );
  if ( isIn<TString>(bookedOptions, "pn2d" ) ) cmd.add(pn2dArg);
  if ( isIn<TString>(bookedOptions, "pn" ) ) cmd.add(pnArg);
  if ( isIn<TString>(bookedOptions, "pluginplotrange" ) ) cmd.add( pluginplotrangeArg );
  if ( isIn<TString>(bookedOptions, "pluginext" ) ) cmd.add( pluginextArg );
  if ( isIn<TString>(bookedOptions, "plotnsigmacont" ) ) cmd.add(plotnsigmacontArg);
  if ( isIn<TString>(bookedOptions, "plotid" ) ) cmd.add(plotidArg);
  if ( isIn<TString>(bookedOptions, "plot2dcl" ) ) cmd.add( plot2dclArg );
  if ( isIn<TString>(bookedOptions, "physrange" ) ) cmd.add( physrangeArg );
  if ( isIn<TString>(bookedOptions, "pevid" ) ) cmd.add( pevidArg );
	if ( isIn<TString>(bookedOptions, "printcor" ) ) cmd.add( printcorArg );
  if ( isIn<TString>(bookedOptions, "ntoys" ) ) cmd.add(ntoysArg);
  if ( isIn<TString>(bookedOptions, "nrun" ) ) cmd.add(nrunArg);
  if ( isIn<TString>(bookedOptions, "npointstoy" ) ) cmd.add(npointstoyArg);
  if ( isIn<TString>(bookedOptions, "npoints2dy" ) ) cmd.add(npoints2dyArg);
  if ( isIn<TString>(bookedOptions, "npoints2dx" ) ) cmd.add(npoints2dxArg);
  if ( isIn<TString>(bookedOptions, "npoints2d" ) ) cmd.add(npoints2dArg);
  if ( isIn<TString>(bookedOptions, "npoints" ) ) cmd.add(npointsArg);
  if ( isIn<TString>(bookedOptions, "nosyst" ) ) cmd.add( nosystArg );
  if ( isIn<TString>(bookedOptions, "ndiv" ) ) cmd.add(ndivArg);
  if ( isIn<TString>(bookedOptions, "ndivy" ) ) cmd.add(ndivyArg);
  if ( isIn<TString>(bookedOptions, "nBBpoints" ) ) cmd.add(nBBpointsArg);
  if ( isIn<TString>(bookedOptions, "magnetic" ) ) cmd.add( plotmagneticArg );
  if ( isIn<TString>(bookedOptions, "log" ) ) cmd.add( plotlogArg );
	if ( isIn<TString>(bookedOptions, "loadParamsFile" ) ) cmd.add( loadParamsFileArg );
  if ( isIn<TString>(bookedOptions, "lightfiles" ) ) cmd.add( lightfilesArg );
  if ( isIn<TString>(bookedOptions, "lhcb" ) ) cmd.add( plotlhcbArg );
  if ( isIn<TString>(bookedOptions, "leg" ) ) cmd.add( plotlegArg );
  if ( isIn<TString>(bookedOptions, "largest" ) ) cmd.add( largestArg );
  if ( isIn<TString>(bookedOptions, "jobs" ) ) cmd.add(jobsArg);
  if ( isIn<TString>(bookedOptions, "jobdir" ) ) cmd.add( jobdirArg );
  if ( isIn<TString>(bookedOptions, "interactive" ) ) cmd.add( interactiveArg );
  if ( isIn<TString>(bookedOptions, "importance" ) ) cmd.add( importanceArg );
  if ( isIn<TString>(bookedOptions, "id" ) ) cmd.add(idArg);
	if ( isIn<TString>(bookedOptions, "fix" ) ) cmd.add(fixArg);
  if ( isIn<TString>(bookedOptions, "evol" ) ) cmd.add(parevolArg);
  if ( isIn<TString>(bookedOptions, "digits" ) ) cmd.add(digitsArg);
  if ( isIn<TString>(bookedOptions, "delpdf") ) cmd.add(delpdfArg);
  if ( isIn<TString>(bookedOptions, "debug" ) ) cmd.add(debugArg);
	if ( isIn<TString>(bookedOptions, "covCorrect" ) ) cmd.add(coverageCorrectionIDArg);
	if ( isIn<TString>(bookedOptions, "covCorrectPoint" ) ) cmd.add(coverageCorrectionPointArg);
  if ( isIn<TString>(bookedOptions, "controlplots" ) ) cmd.add(controlplotArg);
  if ( isIn<TString>(bookedOptions, "color" ) ) cmd.add(colorArg);
	if ( isIn<TString>(bookedOptions, "combid" ) ) cmd.add(combidArg);
  if ( isIn<TString>(bookedOptions, "addpdf") ) cmd.add(addpdfArg);
  if ( isIn<TString>(bookedOptions, "action") ) cmd.add(actionArg);
  if ( isIn<TString>(bookedOptions, "asimov") ) cmd.add(asimovArg);
	cmd.parse( argc, argv );

	//
	// copy over parsed values into data members
	//
	asimov            = asimovArg.getValue();
	controlplot       = controlplotArg.getValue();
	digits            = digitsArg.getValue();
	enforcePhysRange  = physrangeArg.getValue();
	interactive       = interactiveArg.getValue();
	npoints1d         = npointsArg.getValue();
	npoints2dx        = npoints2dArg.getValue()==-1 ? npoints2dxArg.getValue() : npoints2dArg.getValue();
	npoints2dy        = npoints2dArg.getValue()==-1 ? npoints2dyArg.getValue() : npoints2dArg.getValue();
	npointstoy        = npointstoyArg.getValue();
	nrun	            = nrunArg.getValue();
	ntoys	            = ntoysArg.getValue();
	parevol           = parevolArg.getValue();
	pevid             = pevidArg.getValue();
	plotid            = plotidArg.getValue();
	plotlog           = plotlogArg.getValue();
	plotmagnetic      = plotmagneticArg.getValue();
	plotnsigmacont    = plotnsigmacontArg.getValue();
	plotpluginonly    = plotpluginonlyArg.getValue();
	plotpulls         = plotpullsArg.getValue();
	plotsolutions     = plotsolutionsArg.getValue();
	pluginext         = pluginextArg.getValue();
	probforce         = probforceArg.getValue();
	probimprove       = probimproveArg.getValue();
	printcor          = printcorArg.getValue();
	scanforce         = scanforceArg.getValue();
	usage             = usageArg.getValue();
	color             = colorArg.getValue();
  combid            = combidArg.getValue();
  id                = idArg.getValue();
  importance        = importanceArg.getValue();
  jobdir            = TString(jobdirArg.getValue());
  largest           = largestArg.getValue();
  lightfiles        = lightfilesArg.getValue();
  nBBpoints         = nBBpointsArg.getValue();
  ndiv              = ndivArg.getValue();
  ndivy             = ndivyArg.getValue();
  nosyst            = nosystArg.getValue();
  plot2dcl          = plot2dclArg.getValue();
  plotprelim        = plotprelimArg.getValue();
  plotunoff         = plotunoffArg.getValue();
  printnuisances1d  = pnArg.getValue();
	savenuisances1d 	= snArg.getValue();
  qh                = qhArg.getValue();
  verbose           = verboseArg.getValue();

  //
  // The following options need some post-processing to
  // check for allowed values and set sensible things.
  //

  // --action
	vector<string> tmp = actionArg.getValue();  ///< can't assign directly because of TString cast
	for ( int i = 0; i < tmp.size(); i++ ) action.push_back(tmp[i]);

	// --var
	tmp = varArg.getValue();
	for ( int i = 0; i < tmp.size(); i++ ) var.push_back(tmp[i]);
	if ( tmp.size()==0 ) var.push_back("g");

	// --relation
	tmp = relationArg.getValue();
	for ( int i = 0; i < tmp.size(); i++ ) relation.push_back(tmp[i]);
	if ( tmp.size()==0 ) relation.push_back("NoDefaultEquation");

	// --title
	tmp = titleArg.getValue();
	for ( int i = 0; i < tmp.size(); i++ ) title.push_back(tmp[i]);
	if ( tmp.size()==0 ) title.push_back("default");

	// --loadParamsFile
	tmp = loadParamsFileArg.getValue();
	for ( int i = 0; i < tmp.size(); i++ ) loadParamsFile.push_back(tmp[i]);
	if ( tmp.size()==0 ) loadParamsFile.push_back("default");

  // --debug
  debug = debugArg.getValue();
  if ( debug ) verbose = true;

	// --covCorrect
	coverageCorrectionID = coverageCorrectionIDArg.getValue();
	if (coverageCorrectionID < 0 || coverageCorrectionID > 3){
		cout << "Argument error: covCorrect has to be in the range [0,3]" << endl;
		exit(1);
	}
	coverageCorrectionPoint = coverageCorrectionPointArg.getValue();

  // --pn2d
  for ( int i = 0; i < pn2dArg.getValue().size(); i++ ){
    TString parseMe = pn2dArg.getValue()[i];
    TString x = parseMe;
    TString y = parseMe;
    x.Replace(x.Index(":"), x.Sizeof(), "");
    y.Replace(0, y.Index(":")+1, "");
    printnuisances2dx.push_back(x.Atof());
    printnuisances2dy.push_back(y.Atof());
  }

	// --sn2d
  for ( int i = 0; i < sn2dArg.getValue().size(); i++ ){
    TString parseMe = sn2dArg.getValue()[i];
    TString x = parseMe;
    TString y = parseMe;
    x.Replace(x.Index(":"), x.Sizeof(), "");
    y.Replace(0, y.Index(":")+1, "");
    savenuisances2dx.push_back(x.Atof());
    savenuisances2dy.push_back(y.Atof());
  }

	// --addpdf, --delpdf
  parseCombinerPdfList(addpdfArg, addpdf);
  parseCombinerPdfList(delpdfArg, delpdf);

	// --jobs
	if ( jobsArg.getValue().size()>1 && jobsArg.getValue().size()!=(combid.size()+addpdf.size()+delpdf.size()) ){
    cout << "Argument error: Please give as many job ranges (-j) as combinations (-c)." << endl;
    exit(1);
  }
  if ( jobsArg.getValue().size()==0 ){
    jmin.push_back(1);
    jmax.push_back(1);
  }
  for ( int i=0; i<jobsArg.getValue().size(); i++ ){
    TString parseMe = jobsArg.getValue()[i];
    TString x = parseMe;
    TString y = parseMe;
    x.Replace(x.Index("-"), x.Sizeof(), "");
    y.Replace(0, y.Index("-")+1, "");
    int min = x.Atoi();
    int max = y.Atoi();
    if ( min>max ){
      cout << "Argument error: job range min>max." << endl;
      exit(1);
    }
    jmin.push_back(min);
    jmax.push_back(max);
  }

  // --leg
	if ( TString(plotlegArg.getValue())==TString("off") ){
		plotlegend = false;
	}
	else{
		plotlegend = true;
  	parsePosition(plotlegArg.getValue(), plotlegx, plotlegy);
	}

  // --lhcb
  lhcb = plotlhcbArg.getValue();
  parsePosition(plotlhcbArg.getValue(), plotlhcbx, plotlhcby);

  // --pluginplotrange
  parseRange(pluginplotrangeArg.getValue(), pluginPlotRangeMin, pluginPlotRangeMax);

  // --scanrange
  parseRange(scanrangeArg.getValue(), scanrangeMin, scanrangeMax);
  parseRange(scanrangeyArg.getValue(), scanrangeyMin, scanrangeyMax);

	// --fix
	tmp = fixArg.getValue();
	for ( int i = 0; i < tmp.size(); i++ ){ // loop over instances of --fix
		vector<FixPar> assignments;
		// parse 'none' default string
		if ( TString(tmp[i])==TString("none") ){
			fixParameters.push_back(assignments);
			continue;
		}
		// parse list of fixed parameters: "foopar=5,barpar=7"
    TObjArray *assignmentArray = TString(tmp[i]).Tokenize(","); // split string at ","
    for ( int j=0; j<assignmentArray->GetEntries(); j++ ){ // loop over assignments
			TString assignmentString = ((TObjString*)assignmentArray->At(j))->GetString();
			FixPar p;
			if ( parseAssignment(assignmentString, p.name, p.value) ){
				assignments.push_back(p);
			}
			else{
				cout << "ERROR : parse error in --fix argument: " << assignmentString << endl << endl;
			}
    }
		fixParameters.push_back(assignments);
	}
	// // test code for --fix
	// for ( int i = 0; i < fixParameters.size(); i++ ){
	// 	cout << "combination " << i << endl;
	// 	for ( int j = 0; j < fixParameters[i].size(); j++ ){
	// 		cout << fixParameters[i][j].name << " = " << fixParameters[i][j].value << endl;
	// 	}
	// }
	// exit(0);

	// check --po argument
	if ( plotpluginonly && !isAction("plugin") ){
		cout << "ERROR : --po can only be given when -a plugin is set." << endl;
		exit(1);
	}
}

///
/// Parse the position arguments, which define the position of
/// the legend and logo in the plots.
///
void OptParser::parsePosition(TString parseMe, float &x, float &y)
{
  if ( parseMe==TString("default") ){
    x = -1.;
    y = -1.;
    return;
  }
  if ( parseMe==TString("off") ){
    return;
  }
  TString xStr = parseMe;
  TString yStr = parseMe;
  xStr.Replace(xStr.Index(":"), xStr.Sizeof(), "");
  yStr.Replace(0, yStr.Index(":")+1, "");
  x = xStr.Atof();
  y = yStr.Atof();
  if ( ! ( (x==-1 || (0.0<=x && x<=1.0))
        && (y==-1 || (0.0<=y && y<=1.0)) )){
    cout << "Argument error: coordinates out of range: x=" << x << ", y=" << y << endl;
    cout << "They need to be in  [0,1], or equal to -1 to set the default value." << endl;
    exit(1);
  }
}

///
/// Parse the range arguments.
/// \param parseMe Format: "min-max", e.g. "3.28:7.34"
/// \param min return value
/// \param max return value
///
void OptParser::parseRange(TString parseMe, float &min, float &max)
{
  if ( parseMe==TString("default") ){
    min = -99;
    max = -99;
  }
  else {
    TString minStr = parseMe;
    TString maxStr = parseMe;
    minStr.Replace(minStr.Index(":"), minStr.Sizeof(), "");
    maxStr.Replace(0, maxStr.Index(":")+1, "");
    min = minStr.Atof();
    max = maxStr.Atof();
  }
  if ( min>max ){
    cout << "Argument error: plugin plot range min>max." << endl;
    exit(1);
  }
}

///
/// Parse a variable assignment string.
/// \param parseMe Format: "foovar=3.14"
/// \param name return string
/// \param value return value
///
bool OptParser::parseAssignment(TString parseMe, TString &name, float &value)
{
	TString nameStr = parseMe;
	TString valueStr = parseMe;
	if ( parseMe.Index("=") == -1 ) return false; // parse error: '=' not found
	nameStr.Replace(nameStr.Index("="), nameStr.Sizeof(), "");
	valueStr.Replace(0, valueStr.Index("=")+1, "");
	name = nameStr;
	value = valueStr.Atof();
	return true;
}

///
/// Parse --addpdf and --delpdf
/// the string to parse looks sth like "combinerId:pdfId1,pdfId2"
/// e.g. "26:12,23"
///
void OptParser::parseCombinerPdfList(TCLAP::MultiArg<string> &arg, vector<vector<int> > &output)
{
  for ( int i=0; i<arg.getValue().size(); i++ ){
    TString parseMe = arg.getValue()[i]; // "26:12,23"
    // parse leading combiner ID
    TObjArray *array = parseMe.Tokenize(":"); // split string at ":"
    if ( array->GetEntries()!=2 ){
      cout << "ERROR: could not parse argument. Required format: 'combinerId:pdfId1,pdfId2,...'" << endl;
      return;
    }
    TString combinerIdStr = ((TObjString*)array->At(0))->GetString();
    vector<int> outputRow;
    outputRow.push_back(combinerIdStr.Atoi());
    // parse list of PDF IDs
    TString pdfIdsListStr = ((TObjString*)array->At(1))->GetString();
    TObjArray *array1 = pdfIdsListStr.Tokenize(","); // split string at ","
    for ( int j=0; j<array1->GetEntries(); j++ ){
      TString pdfId = ((TObjString*)array1->At(j))->GetString();
      outputRow.push_back(pdfId.Atoi());
    }
    // fill into output
    output.push_back(outputRow);
  }
}