//------------------------------------------
//--Explanation of plots:
//A: SampleTL150 + ThrTL150 + Regr_STL150_ThrTL150 vs  SampleTL150 + ThrMixed + Regr_STL150_ThrMixed
//B: SampleTL180 + ThrTL180 + Regr_STL180_ThrTL180 vs  SampleTL180 + ThrMixed + Regr_STL150_ThrMixed ( I am adding this one today since the ntuples are existing)
//C: SampleTL150 + ThrTL180 + Regr_STL180_ThrTL180 vs  SampleTL150 + ThrTL150 + Regr_STL150_ThrTL150
//D: SampleTL235 + ThrTL180 + Regr_STL180_ThrTL180 vs  SampleTL235 + ThrTL235 + Regr_STL235_ThrTL235
//E: - SampleTL150 + ThrTL180 + Regr_STL180_ThrTL180 vs SampleTL180 + ThrTL180 + Regr_STL180_ThrTL180 vs SampleTL235 + ThrTL180 + Regr_STL180_ThrTL180
void plot(bool etaPlot, bool puPlot, bool ePlot, bool dcbFit);

void plotThreshForECAL()
{
 //-----parameters-----//
 //Which plots to plot
 bool etaPlot = true;
 bool puPlot = false;
 bool ePlot = true;
 //Double crystal ball fit option (default is Cruijff)
 bool dcbFit = true;

 gSystem->Exec("gmake RegressionTrainerExe -j 8");
 gSystem->Exec("gmake RegressionApplierExe -j 8");

 gROOT->ProcessLine("gROOT->SetBatch(true)");
 gROOT->ProcessLine(".x rootScripts/setupResPlotter.c");

 plot(etaPlot,puPlot,ePlot,dcbFit);
}

void plot(bool etaPlot, bool puPlot, bool ePlot,bool dcbFit)
{
 gROOT->ProcessLine("ResPlotter res");
 if(dcbFit) gROOT->ProcessLine("res.setFitType(ResFitter::FitType::DCB)");
 //Eta
 if(etaPlot){
  gROOT->ProcessLine("res.makeHists({treeTL150_Thr150_RegTL150TL150,treeTL150_ThrMixed_RegTL150Mixed},\"\",\"mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"abs(sc.seedEta)\",ptOneBin,absEtaBins)");
  gROOT->ProcessLine("res.printFits({0,5},\"../plots/ThreshForECAL/A_Eff_Eta_\")");

  gROOT->ProcessLine("res.makeHists({treeTL180_ThrTL180_RegTL180TL180,treeTL180_ThrMixed_RegTL150Mixed},\"\",\"mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"abs(sc.seedEta)\",ptOneBin,absEtaBins)");
  gROOT->ProcessLine("res.printFits({1,6},\"../plots/ThreshForECAL/B_Eff_Eta_\")");

  gROOT->ProcessLine("res.makeHists({treeTL150_ThrTL180_RegTL180TL180,treeTL150_Thr150_RegTL150TL150},\"\",\"mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"abs(sc.seedEta)\",ptOneBin,absEtaBins)");
  gROOT->ProcessLine("res.printFits({2,7},\"../plots/ThreshForECAL/C_Eff_Eta_\")");

  gROOT->ProcessLine("res.makeHists({treeTL235_ThrTL180_RegTL180TL180,treeTL235_ThrTL235_RegTL235TL235},\"\",\"mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"abs(sc.seedEta)\",ptOneBin,absEtaBins)");
  gROOT->ProcessLine("res.printFits({3,8},\"../plots/ThreshForECAL/D_Eff_Eta_\")");

  gROOT->ProcessLine("res.makeHists({treeTL150_ThrTL180_RegTL180TL180,treeTL180_ThrTL180_RegTL180TL180,treeTL235_ThrTL180_RegTL180TL180},\"\",\"mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"abs(sc.seedEta)\",ptOneBin,absEtaBins)");
  gROOT->ProcessLine("res.printFits({2,9,10},\"../plots/ThreshForECAL/E_Eff_Eta_\")");
 }

 //Et
 if(ePlot){
  gROOT->ProcessLine("res.makeHists({treeTL150_Thr150_RegTL150TL150,treeTL150_ThrMixed_RegTL150Mixed},\"Barrel\",\"abs(sc.seedEta)<1.442 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"mc.pt\",ptOneBin,ptOneBin)");
  gROOT->ProcessLine("res.printFits({0,5},\"../plots/ThreshForECAL/A_Eff_Et_EB_\")");

  gROOT->ProcessLine("res.makeHists({treeTL150_Thr150_RegTL150TL150,treeTL150_ThrMixed_RegTL150Mixed},\"Endcap\",\"abs(sc.seedEta)>1.566 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"mc.pt\",ptOneBin,ptOneBin)");
  gROOT->ProcessLine("res.printFits({0,5},\"../plots/ThreshForECAL/A_Eff_Et_EE_\")");


  gROOT->ProcessLine("res.makeHists({treeTL180_ThrTL180_RegTL180TL180,treeTL180_ThrMixed_RegTL150Mixed},\"Barrel\",\"abs(sc.seedEta)<1.442 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"mc.pt\",ptOneBin,ptOneBin)");
  gROOT->ProcessLine("res.printFits({1,6},\"../plots/ThreshForECAL/B_Eff_Et_EB_\")");

  gROOT->ProcessLine("res.makeHists({treeTL180_ThrTL180_RegTL180TL180,treeTL180_ThrMixed_RegTL150Mixed},\"Endcap\",\"abs(sc.seedEta)>1.566 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"mc.pt\",ptOneBin,ptOneBin)");
  gROOT->ProcessLine("res.printFits({1,6},\"../plots/ThreshForECAL/B_Eff_Et_EE_\")");


  gROOT->ProcessLine("res.makeHists({treeTL150_ThrTL180_RegTL180TL180,treeTL150_Thr150_RegTL150TL150},\"Barrel\",\"abs(sc.seedEta)<1.442 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"mc.pt\",ptOneBin,ptOneBin)");
  gROOT->ProcessLine("res.printFits({2,7},\"../plots/ThreshForECAL/C_Eff_Et_EB_\")");

  gROOT->ProcessLine("res.makeHists({treeTL150_ThrTL180_RegTL180TL180,treeTL150_Thr150_RegTL150TL150},\"Endcap\",\"abs(sc.seedEta)>1.566 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"mc.pt\",ptOneBin,ptOneBin)");
  gROOT->ProcessLine("res.printFits({2,7},\"../plots/ThreshForECAL/C_Eff_Et_EE_\")");


  gROOT->ProcessLine("res.makeHists({treeTL235_ThrTL180_RegTL180TL180,treeTL235_ThrTL235_RegTL235TL235},\"Barrel\",\"abs(sc.seedEta)<1.442 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"mc.pt\",ptOneBin,ptOneBin)");
  gROOT->ProcessLine("res.printFits({3,8},\"../plots/ThreshForECAL/D_Eff_Et_EB_\")");

  gROOT->ProcessLine("res.makeHists({treeTL235_ThrTL180_RegTL180TL180,treeTL235_ThrTL235_RegTL235TL235},\"Endcap\",\"abs(sc.seedEta)>1.566 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"mc.pt\",ptOneBin,ptOneBin)");
  gROOT->ProcessLine("res.printFits({3,8},\"../plots/ThreshForECAL/D_Eff_Et_EE_\")");


  gROOT->ProcessLine("res.makeHists({treeTL150_ThrTL180_RegTL180TL180,treeTL180_ThrTL180_RegTL180TL180,treeTL235_ThrTL180_RegTL180TL180},\"Barrel\",\"abs(sc.seedEta)<1.442 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"mc.pt\",ptOneBin,ptOneBin)");
  gROOT->ProcessLine("res.printFits({2,9,10},\"../plots/ThreshForECAL/E_Eff_Et_EB_\")");

  gROOT->ProcessLine("res.makeHists({treeTL150_ThrTL180_RegTL180TL180,treeTL180_ThrTL180_RegTL180TL180,treeTL235_ThrTL180_RegTL180TL180},\"Endcap\",\"abs(sc.seedEta)>1.566 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"mc.pt\",ptOneBin,ptOneBin)");
  gROOT->ProcessLine("res.printFits({2,9,10},\"../plots/ThreshForECAL/E_Eff_Et_EE_\")");
 }

 //Pileup
 if(puPlot){
  gROOT->ProcessLine("res.makeHists({treeTL150_Thr150_RegTL150TL150,treeTL150_ThrMixed_RegTL150Mixed},\"Barrel\",\"abs(sc.seedEta)<1.442 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"nrVert\",ptOneBin,puBins)");
  gROOT->ProcessLine("res.printFits({0,1},\"../plots/ThreshForECAL/A_Eff_PU_EB_\")");

  gROOT->ProcessLine("res.makeHists({treeTL150_Thr150_RegTL150TL150,treeTL150_ThrMixed_RegTL150Mixed},\"Endcap\",\"abs(sc.seedEta)>1.566 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"nrVert\",ptOneBin,puBins)");
  gROOT->ProcessLine("res.printFits({0,1},\"../plots/ThreshForECAL/A_Eff_PU_EE_\")");
 }
}
