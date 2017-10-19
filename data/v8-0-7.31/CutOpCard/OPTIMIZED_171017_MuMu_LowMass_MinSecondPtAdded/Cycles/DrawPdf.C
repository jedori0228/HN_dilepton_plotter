#include "canvas_margin.h"

void DrawPdf(){

  gStyle->SetOptStat(0);

  TFile *file = new TFile("pdf.root");

  double y_central = 2062.014;

/*
  KEY: TH1D	hist_Pdf_Replica;1	
  KEY: TH1D	hist_Pdf_Alpha;1	
  KEY: TH1D	hist_Pdf_Scale;1
*/

  TCanvas *c_Replica = new TCanvas("c_Replica", "", 600, 600);
  canvas_margin(c_Replica);
  c_Replica->cd();
  TH1D *hist_Replica = (TH1D *)file->Get("hist_Pdf_Replica");
  hist_Replica->SetLineColor(kBlack);
  hist_Replica->SetLineWidth(3);

  TH1D *hist_Replica_central = (TH1D *)hist_Replica->Clone();
  for(unsigned int i=1; i<=hist_Replica_central->GetXaxis()->GetNbins(); i++){
    hist_Replica_central->SetBinContent(i,y_central);
  }
  hist_Replica_central->SetLineColor(kRed);
  hist_Replica_central->SetLineWidth(3);

  hist_Replica->Draw("hist");
  hist_axis(hist_Replica);
  hist_Replica->GetXaxis()->SetTitle("PDF Replica");
  hist_Replica->GetYaxis()->SetTitle("Signal Yields");
  hist_Replica_central->Draw("histsame");

  c_Replica->SaveAs("Replica.pdf");




  TCanvas *c_Alpha = new TCanvas("c_Alpha", "", 600, 600);
  canvas_margin(c_Alpha);
  c_Alpha->cd();
  TH1D *hist_Alpha = (TH1D *)file->Get("hist_Pdf_Alpha");
  hist_Alpha->SetLineColor(kBlack);
  hist_Alpha->SetLineWidth(3);

  TH1D *hist_Alpha_central = (TH1D *)hist_Alpha->Clone();
  for(unsigned int i=1; i<=hist_Alpha_central->GetXaxis()->GetNbins(); i++){
    hist_Alpha_central->SetBinContent(i,y_central);
  }
  hist_Alpha_central->SetLineColor(kRed);
  hist_Alpha_central->SetLineWidth(3);

  hist_Alpha->Draw("hist");
  hist_axis(hist_Alpha);
  hist_Alpha->GetXaxis()->SetBinLabel(1, "#alpha_{S} = 0.117");
  hist_Alpha->GetXaxis()->SetBinLabel(2, "#alpha_{S} = 0.119");
  hist_Alpha->GetXaxis()->SetLabelSize(0.07);
  hist_Alpha->GetYaxis()->SetTitle("Signal Yields");
  hist_Alpha_central->Draw("histsame");

  c_Alpha->SaveAs("Alpha.pdf");




  TCanvas *c_Scale = new TCanvas("c_Scale", "", 600, 600);
  canvas_margin(c_Scale);
  c_Scale->cd();
  TH1D *hist_Scale = (TH1D *)file->Get("hist_Pdf_Scale");
  hist_Scale->SetLineColor(kBlack);
  hist_Scale->SetLineWidth(3);

  TH1D *hist_Scale_central = (TH1D *)hist_Scale->Clone();
  for(unsigned int i=1; i<=hist_Scale_central->GetXaxis()->GetNbins(); i++){
    hist_Scale_central->SetBinContent(i,y_central);
  }
  hist_Scale_central->SetLineColor(kRed);
  hist_Scale_central->SetLineWidth(3);

  hist_Scale->Draw("hist");
  hist_axis(hist_Scale);
  hist_Scale->GetXaxis()->SetTitle("PDF Scale");
  hist_Scale->GetYaxis()->SetTitle("Signal Yields");
  hist_Scale_central->Draw("histsame");

  c_Scale->SaveAs("Scale.pdf");





}
