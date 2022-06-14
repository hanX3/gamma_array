
void get_fit_data()
{
  ifstream fi;
  fi.open("eff.dat");

  TGraph *gr_2mm = new TGraph();
  TGraph *gr_5mm = new TGraph();
  TGraph *gr_10mm = new TGraph();

  int i = 0;
  double e, eff_2mm, eff_5mm, eff_10mm;
  while(1){
    fi >> e >> eff_2mm >> eff_5mm >> eff_10mm;
    cout << e << " " << eff_2mm << " " << eff_5mm << " " << eff_10mm << endl;

    if(!fi.good()) break;
    gr_2mm->SetPoint(i, e, eff_2mm);
    gr_5mm->SetPoint(i, e, eff_5mm);
    gr_10mm->SetPoint(i, e, eff_10mm);
    i++;
  }
  fi.close();

  TCanvas *c_2mm = new TCanvas("c_2mm");
  c_2mm->cd();
  gr_2mm->Draw();
  TF1 *tf_2mm = new TF1("tf_2mm", "[0]+[1]/([2]-pow(x,[3]))", 10, 2000);
  tf_2mm->SetParameters(1, 1, 1, 3);
  gr_2mm->Fit("tf_2mm");

  TCanvas *c_5mm = new TCanvas("c_5mm");
  c_5mm->cd();
  gr_5mm->Draw();
  TF1 *tf_5mm = new TF1("tf_5mm", "[0]+[1]/([2]-pow(x,[3]))", 60, 2000);
  tf_5mm->SetParameters(1, 1, 1, 3);
  gr_5mm->Fit("tf_5mm");

  TCanvas *c_10mm = new TCanvas("c_10mm");
  c_10mm->cd();
  gr_10mm->Draw();
  TF1 *tf_10mm = new TF1("tf_10mm", "[0]+[1]/([2]-pow(x,[3]))", 60, 2000);
  tf_10mm->SetParameters(1, 1, 1, 3);
  gr_10mm->Fit("tf_10mm");

  ofstream fo;
  fo.open("fit_data.txt");
  for(int i=60;i<=2000;i++){
    fo << i << " " << tf_2mm->Eval(i) << " " << tf_5mm->Eval(i) << " " << tf_10mm->Eval(i) << endl;
  }

  fo.close();
}