void plot(bool dcbFit = true);


void plotECALRawEnergyChecks()
{
 //-----parameters-----//
 //Which plots to plot
 //Double crystal ball fit option (default is Cruijff)
 bool dcbFit = true;

 gSystem->Exec("gmake RegressionTrainerExe -j 8");
 gSystem->Exec("gmake RegressionApplierExe -j 8");

 gROOT->ProcessLine("gROOT->SetBatch(true)");
 gROOT->ProcessLine(".x rootScripts/setupECALRawEnergyChecks.c");

 plot(dcbFit);
}

void plot(bool dcbFit = true)
{
 gROOT->ProcessLine("ResPlotter res");
 if(dcbFit) gROOT->ProcessLine("res.setFitType(ResFitter::FitType::DCB)");

  gROOT->ProcessLine("res.makeHists({treeTL150_Mixed,treeTL150_34Sigma,treeTL150_Ref},\"\",\"mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"abs(sc.seedEta)\",etBinsMC,absEtaBins)");
  gROOT->ProcessLine("res.printFits({0,1,2},\"../plots/ThreshForECALRawEnergyChecks/TL150_\")");

  gROOT->ProcessLine("res.makeHists({treeTL180_Mixed,treeTL180_34Sigma,treeTL180_Ref},\"\",\"mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"abs(sc.seedEta)\",etBinsMC,absEtaBins)");
  gROOT->ProcessLine("res.printFits({0,1,2},\"../plots/ThreshForECALRawEnergyChecks/TL180_\")");

}
