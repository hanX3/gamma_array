#include "GammaSource.hh"

#include "GammaDecay.hh"
#include "G4ProcessManager.hh"
#include "G4IonTable.hh"
#include "G4Decay.hh"
#include "G4DecayTable.hh"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4PhysicalConstants.hh"

//
GammaSource::GammaSource()
{
  messenger = new GammaSourceMessenger(this);

  source_energy = -1.0 * MeV;
  GSS = 0.;
  file_name = "";
}

//
GammaSource::~GammaSource()
{
  delete messenger;
}

//
void GammaSource::BuildLevelScheme()
{
  if(source_energy>0.0*MeV){
    G4cout << "\nSimple isotropic gamma-ray of " << source_energy/keV << " keV will be emitted each event" << G4endl;
    return;
  }

  G4IonTable *table = (G4IonTable*)(G4ParticleTable::GetParticleTable()->GetIonTable());

  G4ParticleDefinition *ground_state = table->GetIon(28, 60, 0.0*MeV);

  ground_state->SetPDGLifeTime(-1.0);
  ground_state->DumpTable();

  PolarizedParticle *pol_gs = new PolarizedParticle(ground_state, 28, 60, GSS, 0.0*MeV);
  levels.push_back(pol_gs);

  std::ifstream file;
  file.open(file_name.c_str(), std::ios::in);
  if(!file.is_open()){
    G4cout << "\n\033[1;31mCould not open source level scheme file " << file_name << "! The simulation won't do anything...\033[m" << G4endl;
    return;
  }

  G4cout << "\nBuilding source level scheme from " << file_name << G4endl;

  std::string line, word;
  while(std::getline(file,line)){
    std::stringstream linestream1(line);

    linestream1 >> word;
    G4int state_index;
    std::stringstream ss0(word);
    ss0 >> state_index;

    linestream1 >> word;
    G4double energy;
    std::stringstream ss1(word);
    ss1 >> energy;
    energy *= keV;

    linestream1 >> word;
    G4double spin;
    std::stringstream ss2(word);
    ss2 >> spin;

    linestream1 >> word;
    G4double lifetime;
    std::stringstream ss3(word);
    ss3 >> lifetime;
    lifetime *= ps;

    linestream1 >> word;
    G4double prob;
    std::stringstream ss4(word);
    ss4 >> prob;
    probs.push_back(prob);

    linestream1 >> word;
    G4int nbr;
    std::stringstream ss5(word);
    ss5 >> nbr;

    G4ParticleDefinition *part = table->GetIon(28, 60, energy);
    if(nbr){
      part->SetPDGLifeTime(lifetime);
      part->SetDecayTable(new G4DecayTable());
      part->GetProcessManager()->SetParticleType(part);
      part->GetProcessManager()->AddProcess(new G4Decay(), 0, -1, 0);
    }
    else{
      part->SetPDGLifeTime(-1.0);
    }

    G4cout << " " << state_index << " " << energy/keV << " " << spin << " " << lifetime/ps << " " << prob << " " << nbr << G4endl;
    part->DumpTable();

    if(nbr==0){
      G4cout << " \033[1;36m Warning: State " << state_index << " has no decay branches.\033[m" << G4endl;
    }

    PolarizedParticle *ppart = new PolarizedParticle(part, 28, 60, spin, energy);
    for(int i=0;i<nbr;i++){
      std::getline(file, line);
      std::stringstream linestream2(line);

      linestream2 >> word;
      G4int index;
      std::stringstream ss6(word);
      ss6 >> index;

      linestream2 >> word;
      G4double br;
      std::stringstream ss7(word);
      ss7 >> br;

      linestream2 >> word;
      G4int l0;
      std::stringstream ss8(word);
      ss8 >> l0;

      linestream2 >> word;
      G4int lp;
      std::stringstream ss9(word);
      ss9 >> lp;

      linestream2 >> word;
      G4double del;
      std::stringstream ss10(word);
      ss10 >> del;

      linestream2 >> word;
      G4double cc;
      std::stringstream ss11(word);
      ss11 >> cc;

      G4cout << "  " << index << " " << br << " " << l0 << " " << lp << " " << del << " " << cc << G4endl;

      part->GetDecayTable()->Insert(new GammaDecay(ppart,levels.at(index), br, l0, lp, del, cc));
    }

    if((unsigned int)state_index != levels.size()){
      G4cout << "States are out of order in source level scheme file " << file_name << "!" << G4endl;
    }

    levels.push_back(ppart);
  }

  if(levels.size()-1 == probs.size()){
    G4cout << levels.size()-1  << " excited states built for the source!" << G4endl;
  }
  else{
    G4cout << "There are " << levels.size()-1 << " excited states but " << probs.size() << " population probabilities!" << G4endl;
  }

  G4double sum = 0.0;
  for(unsigned int i=0;i<probs.size();i++){
    sum += probs.at(i);
  }
  for(unsigned int i=0;i<probs.size();i++){
    probs.at(i) /= sum;
  }



  return;
}

//
void GammaSource::Unpolarize()
{
  for(auto lvl:levels){
    lvl->Unpolarize();
  }

  return;
}

//
G4int GammaSource::ChooseState()
{
  G4double sum_br = 0.0;

  G4double num = G4UniformRand();

  G4cout << "prob.size = " << probs.size() << G4endl;
  G4cout << "num = " << num << " " << G4endl;
  for(unsigned int i=0;i<probs.size();i++){
    sum_br += probs.at(i);
    G4cout << "prob. " << i << "  = " << probs.at(i) << G4endl;
    if(num<sum_br){
      return i+1;
    }
  }

  return 0;
}