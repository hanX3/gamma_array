
void run2()
{
  ofstream fo;
  fo.open("run2.mac");

  fo << "/run/initialize" << endl;
  fo << "/tracking/verbose 0" << endl;
  fo << endl;

  int energy = 40;
  while(1){
    if(energy>2000) break;  

    fo << "/gun/energy " << energy << " keV " << endl;
    fo << "/run/beamOn 1000000" << endl;
    fo << endl;

    energy += 20;
  }

  fo.close();
}
