//------------------------------------------
//--Explanation of plots:
//A: SampleTL150 + ThrTL150 + Regr_STL150_ThrTL150 vs  SampleTL150 + ThrMixed + Regr_STL150_ThrMixed
//B: SampleTL180 + ThrTL180 + Regr_STL180_ThrTL180 vs  SampleTL180 + ThrMixed + Regr_STL150_ThrMixed ( I am adding this one today since the ntuples are existing)
//C: SampleTL150 + ThrTL180 + Regr_STL180_ThrTL180 vs  SampleTL150 + ThrTL150 + Regr_STL150_ThrTL150
//D: SampleTL235 + ThrTL180 + Regr_STL180_ThrTL180 vs  SampleTL235 + ThrTL235 + Regr_STL235_ThrTL235
//E: - SampleTL150 + ThrTL180 + Regr_STL180_ThrTL180 vs SampleTL180 + ThrTL180 + Regr_STL180_ThrTL180 vs SampleTL235 + ThrTL180 + Regr_STL180_ThrTL180
void plot(bool etaPlot, bool puPlot, bool ePlot, bool dcbFit,bool plotVsRaw);

void plotThreshForECAL()
{
 //-----parameters-----//
 //Which plots to plot
 bool etaPlot = false;
 bool puPlot = false;
 bool ePlot = false;
 bool plotVsRaw = true;
 //Double crystal ball fit option (default is Cruijff)
 bool dcbFit = true;

 gSystem->Exec("gmake RegressionTrainerExe -j 8");
 gSystem->Exec("gmake RegressionApplierExe -j 8");

 gROOT->ProcessLine("gROOT->SetBatch(true)");
 gROOT->ProcessLine(".x rootScripts/setupResPlotter.c");

 plot(etaPlot,puPlot,ePlot,dcbFit,plotVsRaw);
}

void plot(bool etaPlot, bool puPlot, bool ePlot,bool dcbFit,bool plotVsRaw)
{
 gROOT->ProcessLine("ResPlotter res");
 if(dcbFit) gROOT->ProcessLine("res.setFitType(ResFitter::FitType::DCB)");

 //Plot corrected versus raw
 if(plotVsRaw){
  gROOT->ProcessLine("res.makeHists({treeTL150_ThrTL180_RegTL180TL180,nullptr},\"\",\"mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"abs(sc.seedEta)\",etBinsMC,absEtaBins)");
  gROOT->ProcessLine("res.printFits({0,1},\"../plots/ThreshForECALVsRaw_TL150_180/Eta_\")");

  gROOT->ProcessLine("res.makeHists({treeTL150_ThrTL180_RegTL180TL180,nullptr},\"Barrel\",\"abs(sc.seedEta)<1.442 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"mc.pt\",ptOneBin,etBinsMC)");
  gROOT->ProcessLine("res.printFits({0,1},\"../plots/ThreshForECALVsRaw_TL150_180/Et_EB_\")");

  gROOT->ProcessLine("res.makeHists({treeTL150_ThrTL180_RegTL180TL180,nullptr},\"Endcap\",\"abs(sc.seedEta)>1.566 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"mc.pt\",ptOneBin,etBinsMC)");
  gROOT->ProcessLine("res.printFits({0,1},\"../plots/ThreshForECALVsRaw_TL150_180/Et_EE_\")");

  gROOT->ProcessLine("res.makeHists({treeTL150_ThrTL180_RegTL180TL180,nullptr},\"2.5 < |#eta| < 3.0, 80 GeV < E^{gen}_{T} < 100 GeV\",\"mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3 && abs(sc.seedEta) > 2.5 && abs(sc.seedEta) < 3.0\",\"mc.pt\",\"nrVert\",ptHighBin,puBinsCoarse)");
  gROOT->ProcessLine("res.printFits({0,1},\"../plots/ThreshForECALVsRaw_TL150_180/PU_\")");


  gROOT->ProcessLine("res.makeHists({treeTL150_Thr150_RegTL150TL150,nullptr},\"\",\"mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"abs(sc.seedEta)\",etBinsMC,absEtaBins)");
  gROOT->ProcessLine("res.printFits({0,1},\"../plots/ThreshForECALVsRaw_TL150_150/Eta_\")");

  gROOT->ProcessLine("res.makeHists({treeTL150_Thr150_RegTL150TL150,nullptr},\"Barrel\",\"abs(sc.seedEta)<1.442 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"mc.pt\",ptOneBin,etBinsMC)");
  gROOT->ProcessLine("res.printFits({0,1},\"../plots/ThreshForECALVsRaw_TL150_150/Et_EB_\")");

  gROOT->ProcessLine("res.makeHists({treeTL150_Thr150_RegTL150TL150,nullptr},\"Endcap\",\"abs(sc.seedEta)>1.566 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"mc.pt\",ptOneBin,etBinsMC)");
  gROOT->ProcessLine("res.printFits({0,1},\"../plots/ThreshForECALVsRaw_TL150_150/Et_EE_\")");

  gROOT->ProcessLine("res.makeHists({treeTL150_Thr150_RegTL150TL150,nullptr},\"2.5 < |#eta| < 3.0, 80 GeV < E^{gen}_{T} < 100 GeV\",\"mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3 && abs(sc.seedEta) > 2.5 && abs(sc.seedEta) < 3.0\",\"mc.pt\",\"nrVert\",ptHighBin,puBinsCoarse)");
  gROOT->ProcessLine("res.printFits({0,1},\"../plots/ThreshForECALVsRaw_TL150_150/PU_\")");
 }

 //Eta
 if(etaPlot){
  //gROOT->ProcessLine("res.makeHists({treeTL150_Thr150_RegTL150TL150,treeTL150_ThrMixed_RegTL150Mixed},\"\",\"mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"abs(sc.seedEta)\",etBinsMC,absEtaBins)");
  //gROOT->ProcessLine("res.printFits({0,5},\"../plots/ThreshForECAL_v2/A_Eta_\")");

  //gROOT->ProcessLine("res.makeHists({treeTL180_ThrTL180_RegTL180TL180,treeTL180_ThrMixed_RegTL150Mixed},\"\",\"mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"abs(sc.seedEta)\",etBinsMC,absEtaBins)");
  //gROOT->ProcessLine("res.printFits({1,6},\"../plots/ThreshForECAL_v2/B_Eta_\")");

  gROOT->ProcessLine("res.makeHists({treeTL150_ThrTL180_RegTL180TL180,treeTL150_Thr150_RegTL150TL150},\"\",\"mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"abs(sc.seedEta)\",etBinsMC,absEtaBins)");
  gROOT->ProcessLine("res.printFits({2,7},\"../plots/ThreshForECAL_v2/C_Eta_\")");

  //gROOT->ProcessLine("res.makeHists({treeTL235_ThrTL180_RegTL180TL180,treeTL235_ThrTL235_RegTL235TL235},\"\",\"mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"abs(sc.seedEta)\",etBinsMC,absEtaBins)");
  //gROOT->ProcessLine("res.printFits({3,8},\"../plots/ThreshForECAL_v2/D_Eta_\")");

  //gROOT->ProcessLine("res.makeHists({treeTL150_ThrTL180_RegTL180TL180,treeTL180_ThrTL180_RegTL180TL180,treeTL235_ThrTL180_RegTL180TL180},\"\",\"mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"abs(sc.seedEta)\",etBinsMC,absEtaBins)");
  //gROOT->ProcessLine("res.printFits({2,9,10},\"../plots/ThreshForECAL_v2/E_Eta_\")");
 }

 //Et
 if(ePlot){
  gROOT->ProcessLine("res.makeHists({treeTL150_Thr150_RegTL150TL150,treeTL150_ThrMixed_RegTL150Mixed},\"Barrel\",\"abs(sc.seedEta)<1.442 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"mc.pt\",ptOneBin,etBinsMC)");
  gROOT->ProcessLine("res.printFits({0,5},\"../plots/ThreshForECAL_v2/A_Et_EB_\")");

  gROOT->ProcessLine("res.makeHists({treeTL150_Thr150_RegTL150TL150,treeTL150_ThrMixed_RegTL150Mixed},\"Endcap\",\"abs(sc.seedEta)>1.566 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"mc.pt\",ptOneBin,etBinsMC)");
  gROOT->ProcessLine("res.printFits({0,5},\"../plots/ThreshForECAL_v2/A_Et_EE_\")");


  gROOT->ProcessLine("res.makeHists({treeTL180_ThrTL180_RegTL180TL180,treeTL180_ThrMixed_RegTL150Mixed},\"Barrel\",\"abs(sc.seedEta)<1.442 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"mc.pt\",ptOneBin,etBinsMC)");
  gROOT->ProcessLine("res.printFits({1,6},\"../plots/ThreshForECAL_v2/B_Et_EB_\")");

  gROOT->ProcessLine("res.makeHists({treeTL180_ThrTL180_RegTL180TL180,treeTL180_ThrMixed_RegTL150Mixed},\"Endcap\",\"abs(sc.seedEta)>1.566 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"mc.pt\",ptOneBin,etBinsMC)");
  gROOT->ProcessLine("res.printFits({1,6},\"../plots/ThreshForECAL_v2/B_Et_EE_\")");


  gROOT->ProcessLine("res.makeHists({treeTL150_ThrTL180_RegTL180TL180,treeTL150_Thr150_RegTL150TL150},\"Barrel\",\"abs(sc.seedEta)<1.442 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"mc.pt\",ptOneBin,etBinsMC)");
  gROOT->ProcessLine("res.printFits({2,7},\"../plots/ThreshForECAL_v2/C_Et_EB_\")");

  gROOT->ProcessLine("res.makeHists({treeTL150_ThrTL180_RegTL180TL180,treeTL150_Thr150_RegTL150TL150},\"Endcap\",\"abs(sc.seedEta)>1.566 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"mc.pt\",ptOneBin,etBinsMC)");
  gROOT->ProcessLine("res.printFits({2,7},\"../plots/ThreshForECAL_v2/C_Et_EE_\")");


  gROOT->ProcessLine("res.makeHists({treeTL235_ThrTL180_RegTL180TL180,treeTL235_ThrTL235_RegTL235TL235},\"Barrel\",\"abs(sc.seedEta)<1.442 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"mc.pt\",ptOneBin,etBinsMC)");
  gROOT->ProcessLine("res.printFits({3,8},\"../plots/ThreshForECAL_v2/D_Et_EB_\")");

  gROOT->ProcessLine("res.makeHists({treeTL235_ThrTL180_RegTL180TL180,treeTL235_ThrTL235_RegTL235TL235},\"Endcap\",\"abs(sc.seedEta)>1.566 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"mc.pt\",ptOneBin,etBinsMC)");
  gROOT->ProcessLine("res.printFits({3,8},\"../plots/ThreshForECAL_v2/D_Et_EE_\")");


  gROOT->ProcessLine("res.makeHists({treeTL150_ThrTL180_RegTL180TL180,treeTL180_ThrTL180_RegTL180TL180,treeTL235_ThrTL180_RegTL180TL180},\"Barrel\",\"abs(sc.seedEta)<1.442 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"mc.pt\",ptOneBin,etBinsMC)");
  gROOT->ProcessLine("res.printFits({2,9,10},\"../plots/ThreshForECAL_v2/E_Et_EB_\")");

  gROOT->ProcessLine("res.makeHists({treeTL150_ThrTL180_RegTL180TL180,treeTL180_ThrTL180_RegTL180TL180,treeTL235_ThrTL180_RegTL180TL180},\"Endcap\",\"abs(sc.seedEta)>1.566 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"mc.pt\",ptOneBin,etBinsMC)");
  gROOT->ProcessLine("res.printFits({2,9,10},\"../plots/ThreshForECAL_v2/E_Et_EE_\")");
 }

 //Pileup
 if(puPlot){
  gROOT->ProcessLine("res.makeHists({treeTL150_Thr150_RegTL150TL150,treeTL150_ThrMixed_RegTL150Mixed},\"Barrel\",\"abs(sc.seedEta)<1.442 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"nrVert\",ptOneBin,puBins)");
  gROOT->ProcessLine("res.printFits({0,1},\"../plots/ThreshForECAL_v2/A_PU_EB_\")");

  gROOT->ProcessLine("res.makeHists({treeTL150_Thr150_RegTL150TL150,treeTL150_ThrMixed_RegTL150Mixed},\"Endcap\",\"abs(sc.seedEta)>1.566 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"nrVert\",ptOneBin,puBins)");
  gROOT->ProcessLine("res.printFits({0,1},\"../plots/ThreshForECAL_v2/A_PU_EE_\")");
 }
}
