#include <sstream>
#include <string>
#include <fstream>
#include "TFile.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TH1.h"
#include "TMath.h"
#include "TRandom3.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TFrame.h"
#include "TPaveLabel.h"
void read_shms()
{
  std::ifstream infile("fall_shms_bcm.txt"); //reads first txtfile
    
  std::string line;// read line by line
  vector <double> run; // define the following quantities which are actually the columns in the shms_eff.txt file, specify which is of int or float or double type
  vector <double> bcm1;
  vector <double> bcm2;
  vector <double> bcm4A;
  vector <double> bcm4B;
   vector <double> bcm4C;
   vector <double>unser;
   // vector <double>runNum;
    
  while (std::getline(infile, line))//while loop to read all the lines , getline is to read all line of the txt file which is stored as infile, and reading all the lines
    {
      std::istringstream iss(line);// to read the whole strings in a line
      double a, b, c, d, e,f,g;// define eun by a, did by b, should by c, eff by d and eff_err by e
      if (!(iss >> a >> b >> c >> d >> e >>f >>g)) // if it could not fine a, b, c, d, e, then not to proceed, so there must be 5 columns in this case.
        {
            
	  break; 
            
        } // error
        
      run.push_back(a);//now run is stored in a
      bcm1.push_back(b);//did is stored in b
      bcm2.push_back(c);//should is stored as c
      bcm4A.push_back(d);//eff = d
      bcm4B.push_back(e);//eff err = e
      bcm4C.push_back(f);//eff err = e
      unser.push_back(g);//eff err = e
      //  runNum.push_back(a);//now run is stored in a


    }




  // for (int i =0; i< run.size(); i++)// for cout you have to have elements equal to in one column or column with maximum elements 
  //   {
  //     cout <<" run : "<<run[i]<<"\t"<<" bcm1 : " <<bcm1[i]<< "  bcm4A :"<<bcm4A[i]<< "    bcm4B : "  <<bcm4B[i]<<endl;//you have to cout each elements , so need i
  //   }
   auto c3 = new TCanvas("c3","c3",1600, 1200);
   c3->cd();gPad->SetGridy();
   // TMultiGraph *mg1 = new TMultiGraph("mg1", "BCM current vs Run Num March 5-17, 2019");
  TMultiGraph *mg1 = new TMultiGraph("mg1", "BCM current vs Run Num Nov 7-28, 2018");

  auto gr1 = new TGraph(run.size(), &run[0], &bcm1[0]);

  gr1->SetName("gr1");
  gr1->SetMarkerStyle(21);
  gr1->SetTitle("BCM1");
  gr1->SetMarkerColor(kRed);
  auto gr2 = new TGraph(run.size(), &run[0],&bcm2[0]);
  gr2->SetName("gr2");
  gr2->SetMarkerStyle(22);
  gr2->SetTitle("BCM2");
  gr2->SetMarkerColor(kBlue);
  auto gr3 = new TGraph(run.size(), &run[0],&bcm4A[0]);
  gr3->SetName("gr3");
  gr3->SetTitle("BCM4A");
  gr3->SetMarkerStyle(23);
  gr3->SetMarkerColor(1);

 auto gr4 = new TGraph(run.size(), &run[0],&bcm4B[0]);
  gr4->SetName("gr3");
  gr4->SetTitle("BCM4B");
  gr4->SetMarkerStyle(120);
  gr4->SetMarkerColor(3);




  mg1->Add(gr1);
  mg1->Add(gr2);
  mg1->Add(gr3);
  mg1->Add(gr4);
  gr4->Draw("AP");
  mg1->Draw("AP");

 auto legend = new TLegend(0.1,0.7,0.48,0.9);


 c3->BuildLegend();

 mg1->GetXaxis()->SetTitle("Run Num Fall");
 mg1->GetYaxis()->SetTitle("Current (mA)");
 mg1->SetTitle("Comparision of current by various BCMs");
 mg1->GetXaxis()->CenterTitle();
 mg1->GetYaxis()->CenterTitle();
    
}
