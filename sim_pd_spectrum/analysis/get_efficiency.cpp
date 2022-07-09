
void get_efficiency_pd()
{
  TString str_fi_path;
  str_fi_path = TString::Format("../data_pd/");

  stringstream ss;
  ss.str("");
  ss << str_fi_path.Data() << "cata.dat";
  cout << ss.str() << endl;

  ifstream fi;
  fi.open(ss.str().c_str());
  if(!fi){
    cout << "can not open " << ss.str() << endl;
    return ;
  }

  vector<int> v_e;
  vector<int> v_nevt;

  TString str;
  double e;
  int k;
  int nevt;
  while(1){
    str.Clear();
    e = 0.;
    k = 0;
    nevt = 0;
    ss.str("");

    fi >> str >> e >> k;
    // cout << str << " " << e << " " << k << endl;
    if(!fi.good()) break;

    ss << str_fi_path << str << ".root";
    TFile *fi_root = TFile::Open(ss.str().c_str());
    if(!fi_root){
      cout << "can not open " << ss.str() << endl;
      return;
    }

    Int_t si_hit_num;
    Int_t si_id[si_hit_num];
    Double_t si_e[si_hit_num];

    TTree *tr = (TTree*)fi_root->Get("tr");
    tr->SetBranchAddress("si_hit_num", &si_hit_num);
    tr->SetBranchAddress("si_id", si_id);
    tr->SetBranchAddress("si_e", si_e);

    Double_t si_e_all = 0.;
    for(int i=0;i<tr->GetEntries();i++){
      tr->GetEntry(i);
      if(si_hit_num==0){
        continue;
      }

      if(si_hit_num>0){
        nevt++;
      }
    }

    v_e.push_back(1000*e);
    v_nevt.push_back(nevt);
    delete tr;
    fi_root->Close();
  }
  fi.close();

  ofstream fo;
  fo.open("pd_eff.txt");

  for(int i=0;i<v_e.size();i++){
    fo << v_e[i] << " " << v_nevt[i] << endl;
  }
   fo.close();
}

//
void get_efficiency_csi_pd()
{
  TString str_fi_path;
  str_fi_path = TString::Format("../data_csi_pd/");

  stringstream ss;
  ss.str("");
  ss << str_fi_path.Data() << "cata.dat";
  cout << ss.str() << endl;

  ifstream fi;
  fi.open(ss.str().c_str());
  if(!fi){
    cout << "can not open " << ss.str() << endl;
    return ;
  }

  vector<int> v_e;
  vector<int> v_nevt_csi;
  vector<int> v_nevt_pd;

  TString str;
  double e;
  int k;
  int nevt_csi;
  int nevt_pd;
  while(1){
    str.Clear();
    e = 0.;
    k = 0;
    nevt_csi = 0;
    nevt_pd = 0;
    ss.str("");

    fi >> str >> e >> k;
    // cout << str << " " << e << " " << k << endl;
    if(!fi.good()) break;

    ss << str_fi_path << str << ".root";
    TFile *fi_root = TFile::Open(ss.str().c_str());
    if(!fi_root){
      cout << "can not open " << ss.str() << endl;
      return;
    }

    Int_t csi_hit_num;
    Int_t csi_id[csi_hit_num];
    Double_t csi_e[csi_hit_num];
    Int_t si_hit_num;
    Int_t si_id[si_hit_num];
    Double_t si_e[si_hit_num];

    TTree *tr = (TTree*)fi_root->Get("tr");
    tr->SetBranchAddress("csi_hit_num", &csi_hit_num);
    tr->SetBranchAddress("csi_id", csi_id);
    tr->SetBranchAddress("csi_e", csi_e);
    tr->SetBranchAddress("si_hit_num", &si_hit_num);
    tr->SetBranchAddress("si_id", si_id);
    tr->SetBranchAddress("si_e", si_e);

    for(int i=0;i<tr->GetEntries();i++){
      tr->GetEntry(i);

      if(csi_hit_num>0){
        nevt_csi++;
      }

      if(si_hit_num>0){
        nevt_pd++;
      }
    }

    v_e.push_back(1000*e);
    v_nevt_csi.push_back(nevt_csi);
    v_nevt_pd.push_back(nevt_pd);
    delete tr;
    fi_root->Close();
  }
  fi.close();

  ofstream fo;
  fo.open("csi_pd_eff.txt");

  for(int i=0;i<v_e.size();i++){
    fo << v_e[i] << " " << v_nevt_csi[i] << " " << v_nevt_pd[i] << endl;
  }
   fo.close();
}