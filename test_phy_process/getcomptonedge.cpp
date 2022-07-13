
void getcomptonedge(double e)
{
  double g = e/511.;
  double edge = e*(2*g/(1+2*g));

  cout << "compton edge energy " << edge << " keV" << endl;
}
