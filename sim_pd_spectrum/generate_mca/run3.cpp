
void run3()
{
  ofstream fo;
  fo.open("run3.mac");

  fo << "/run/initialize" << endl;
  fo << "/tracking/verbose 0" << endl;
  fo << endl;

  int energy = 10;
  while(1){
    if(energy>200) break;  
    if(energy%20 ==0){
      energy += 2;
      continue;
    }

    fo << "/gun/energy " << energy << " keV " << endl;
    fo << "/run/beamOn 1000000" << endl;
    fo << endl;

    energy += 2;
  }

  fo.close();
}
