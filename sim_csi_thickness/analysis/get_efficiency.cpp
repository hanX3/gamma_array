
void get_efficiency(int thick)
{
  TString str_fi_path;
  if(thick==0){
    str_fi_path = TString::Format("./build/data/");
  }
  else{
    str_fi_path = TString::Format("./build_%dmm/data/", thick);
  }

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
    double ge_e;
    TTree *tr = (TTree*)fi_root->Get("tr");
    tr->SetBranchAddress("ge_e", &ge_e);
    for(int i=0;i<tr->GetEntries();i++){
      tr->GetEntry(i);
      if(ge_e>950.*e){
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
  if(thick==0){
    fo.open("no_csi_eff.txt");
  }
  else{
    fo.open(TString::Format("%dmm_csi_eff.txt",thick).Data());
  }

  for(int i=0;i<v_e.size();i++){
    fo << v_e[i] << " " << v_nevt[i] << endl;
  }
   fo.close();
}
