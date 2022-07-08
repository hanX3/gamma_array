
void test_fit()
{
  TGraph *gr = new TGraph("eff.dat");

  TF1 *tf = new TF1("tf", "[0]+[1]/([2]-pow(x,[3]))", 50, 2000);
  tf->SetParameters(1, 1, 1, 3);
  
  gr->Draw("AP*");
  gr->Fit("tf");
}