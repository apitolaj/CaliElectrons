#include "/sps/nemo/scratch/apitolaj/Modules/MiModule/include/MiEvent.h"
#include "TLatex.h"
#include "TVector3.h"
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

R__LOAD_LIBRARY(/sps/nemo/scratch/apitolaj/Modules/MiModule/lib/libMiModule.so);

float azimuth;
float zenith;
int eventNumber;

// this function comes from Yaroslava's overlay_with_without_carrier.cpp script
bool isCalibElectron(MiEvent *Event, int eventNumber)
{
	MiSD *sd = Event->getSD();
    
	if (sd)
        {
        std::vector<MiSDCaloHit> *ch = sd->getcalohitv();

        	if (ch)
        	{
            		for (auto &hit : *ch)
            		{
                		if (hit.getcategory() == "bi207_calib_source" && hit.getname() == "e-" && hit.getGID()->gettype() == "1066")
              			{
                   			return true;
                		}
            		}
        	}
        }
    	return false;
}

void calculateAngles(MiEvent *Event)
{
	TVector3 dir = Event->getPTD()->getpart(0)->getdirectionfromfoil();
	azimuth = TMath::ATan2(dir.Z() , dir.Y());
	if (azimuth < 0) 
	{
		azimuth += 2.0 * TMath::Pi();  
	}

	azimuth *= 180.0 / TMath::Pi();
	zenith = TMath::ACos(dir.X() / dir.Mag()) * 180.0 / TMath::Pi();
}

void azimuth_zenith_values()
{
	MiEvent *Eve = new MiEvent();
	TFile *f = TFile::Open("/sps/nemo/scratch/apitolaj/YaroFigure/SIMU/brios/SNCUTS/NEW_s_positions/new_testCuts/1/v2_2D_reco_Bi_1-SNCUTS.root");
	TTree *t = (TTree *)f->Get("Event");
	t->SetBranchAddress("Eventdata", &Eve);
	TFile *outFile = new TFile("azimuth_zenith_values.root", "RECREATE");
	TTree *tr = new TTree("azimuth_zenith", "contains the azimuth and zenith angles of fitted 3D direction of electrons");

	tr->Branch("azimuth", &azimuth, "azimuth/f");
	tr->Branch("zenith", &zenith, "zenith/f");
	tr->Branch("Event#", &eventNumber, "eventNumber/I");

	for (int i = 0; i < t->GetEntries(); i++)
	{
		t->GetEntry(i);
		if (isCalibElectron(Eve, i))
		{
		    eventNumber = i;
		    calculateAngles(Eve);
		    tr->Fill();
		}
	}
	tr->Write();
	std::cout << tr->GetEntries() << " entries" << endl;
        tr->Scan("Event #:azimuth:zenith");
    	outFile->Close();
}
