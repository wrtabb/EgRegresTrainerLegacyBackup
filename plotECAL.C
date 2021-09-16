
void plot(bool etaPlot, bool puPlot, bool ePlot, bool dcbFit);

void plotECAL()
{
 //-----parameters-----//
 //Which plots to plot
 bool etaPlot = true;
 bool puPlot = true;
 bool ePlot = false;
 //Double crystal ball fit option (default is Cruijff)
 bool dcbFit = true;

 gSystem->Exec("gmake RegressionTrainerExe -j 8");
 gSystem->Exec("gmake RegressionApplierExe -j 8");

 gROOT->ProcessLine("gROOT->SetBatch(true)");
 gROOT->ProcessLine(".x rootScripts/setupECALPlotter.c");

 plot(etaPlot,puPlot,ePlot,dcbFit);
}

void plot(bool etaPlot, bool puPlot, bool ePlot,bool dcbFit)
{
 gROOT->ProcessLine("ResPlotter res");
 if(dcbFit) gROOT->ProcessLine("res.setFitType(ResFitter::FitType::DCB)");
 //Eta
 if(etaPlot){
  gROOT->ProcessLine("res.makeHists({tree,tree2018},\"\",\"mc.energy>0 && sc.rawEnergy>0 && ssFrac.sigmaIEtaIEta>0 && mc.dR<0.1 && ele.et>0 && eventnr%5>=3\",\"mc.pt\",\"abs(sc.seedEta)\",etBins,etaBinsSC)");
  gROOT->ProcessLine("res.printFits({1,3},\"../plots/2018ULVsECALSampleNewSample/DCB_Eta_\")");
 }

 //Pileup
 if(puPlot){
  gROOT->ProcessLine("res.makeHists({tree,tree2018},\"Barrel\",\"abs(sc.seedEta)<1.442 && mc.energy>0 && sc.rawEnergy>0 && ssFrac.sigmaIEtaIEta>0 && mc.dR<0.1 && ele.et>0 && eventnr%5>=3\",\"mc.pt\",\"nrVert\",ptOneBin,puBins)");
  gROOT->ProcessLine("res.printFits({1,3},\"../plots/2018ULVsECALSampleNewSample/DCB_PU_EB_\")");

  gROOT->ProcessLine("res.makeHists({tree,tree2018},\"Endcap\",\"abs(sc.seedEta)>1.566 && mc.energy>0 && sc.rawEnergy>0 && ssFrac.sigmaIEtaIEta>0 && mc.dR<0.1 && ele.et>0 && eventnr%5>=3\",\"mc.pt\",\"nrVert\",ptOneBin,puBins)");
  gROOT->ProcessLine("res.printFits({1,3},\"../plots/2018ULVsECALSampleNewSample/DCB_PU_EE_\")");
 }

 //Et
 if(ePlot){
  gROOT->ProcessLine("res.makeHists({tree,tree2018},\"Barrel\",\"abs(sc.seedEta)<1.442 && mc.energy>0 && sc.rawEnergy>0 && ssFrac.sigmaIEtaIEta>0 && mc.dR<0.1 && ele.et>0 && eventnr%5>=3\",\"mc.pt\",\"mc.pt\",ptOneBin,etBins)");
  gROOT->ProcessLine("res.printFits({1,3},\"../plots/2018ULVsECALSampleNewSample/Et_EB_\")");

  gROOT->ProcessLine("res.makeHists({tree,tree2018},\"Endcap\",\"abs(sc.seedEta)>1.566 && mc.energy>0 && sc.rawEnergy>0 && ssFrac.sigmaIEtaIEta>0 && mc.dR<0.1 && ele.et>0 && eventnr%5>=3\",\"mc.pt\",\"mc.pt\",ptOneBin,etBins)");
  gROOT->ProcessLine("res.printFits({1,3},\"../plots/2018ULVsECALSampleNewSample/Et_EE_\")");
 }
}
