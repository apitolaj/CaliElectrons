void th2dHisto_TPPDistribution_ENERGY_PLACEHOLDER1_Source_SOURCE_PLACEHOLDER(const char* file1, const char* file2,const char* file3, const char* file4)
{
	TFile *f1 = new TFile(file1);
	if (!f1 || f1->IsZombie()) 
	{ 
		std::cerr << "Error: cannot open " << file1 << std::endl; 
		return; 
	}
	
	TFile *f2 = new TFile(file2);
	if (!f2 || f2->IsZombie()) 
	{ 
		std::cerr << "Error: cannot open " << file2 << std::endl;
		f1->Close(); 
		return; 
	}
	
	TFile *f3 = new TFile(file3);
	if (!f3 || f3->IsZombie()) 
	{ 
		std::cerr << "Error: cannot open " << file3 << std::endl; 
		f1->Close(); 
                f2->Close();
		return; 
	}
	
	TFile *f4 = new TFile(file4);
	if (!f4 || f4->IsZombie()) 
	{ 
		std::cerr << "Error: cannot open " << file4 << std::endl;
		f1->Close(); 
                f2->Close();  
                f3->Close();  
		return; 
	}

	TTree *t1 = (TTree*)f1->Get("TPPy_TPPz");
	TTree *t2 = (TTree*)f2->Get("TPPy_TPPz");
	TTree *t3 = (TTree*)f3->Get("TPPy_TPPz");
	TTree *t4 = (TTree*)f4->Get("TPPy_TPPz");
	if (!t1 || !t2 || !t3 || !t4) 
	{ 
		std::cerr << "Error: cannot find TTree TPPy_TPPz" << std::endl;
		f1->Close(); f2->Close(); f3->Close(); f4->Close();  
		return; 
	}

	// Create canvas with 2x2 grid
	TCanvas *c = new TCanvas("c", "Comparison", 1600, 1000);
	c->Divide(2, 2);

	// --- Top Left ---
	c->cd(1);
	TH2D *h1 = new TH2D("h1",
		"Source_SOURCE_PLACEHOLDER: TPP Distribution for Zenith >= 60 (Env., ENERGY_PLACEHOLDER2);Y [mm];Z [mm]",
		180, -2500, 2500, 180, -1500, 1500);
	h1->SetStats(0);
	t1->Draw("TPPz:TPPy >> h1", "", "COLZ");

	// --- Top Right ---
	c->cd(2);
	TH2D *h2 = new TH2D("h2",
		"Source_SOURCE_PLACEHOLDER: TPP Distribution for Zenith < 60 (Env., ENERGY_PLACEHOLDER2);Y [mm];Z [mm]",
		180, -2500, 2500, 180, -1500, 1500);
	h2->SetStats(0);
	t2->Draw("TPPz:TPPy >> h2", "", "COLZ");

	// --- Bottom Left ---
	c->cd(3);
	TH2D *h3 = new TH2D("h3",
		"Source_SOURCE_PLACEHOLDER: TPP Distribution for Zenith >= 60 (No env., ENERGY_PLACEHOLDER2);Y [mm];Z [mm]",
		180, -2500, 2500, 180, -1500, 1500);
	h3->SetStats(0);
	t3->Draw("TPPz:TPPy >> h3", "", "COLZ");

	// --- Bottom Right ---
	c->cd(4);
	TH2D *h4 = new TH2D("h4",
		"Source_SOURCE_PLACEHOLDER: TPP Distribution for Zenith < 60 (No env., ENERGY_PLACEHOLDER2);Y [mm];Z [mm]",
		 180, -2500, 2500, 180, -1500, 1500);
	h4->SetStats(0);t4->Draw("TPPz:TPPy >> h4", "", "COLZ");
	    
	c->SaveAs("th2dHisto_TPPDistribution_ENERGY_PLACEHOLDER1_Source_SOURCE_PLACEHOLDER.png");
	f1->Close();
	f2->Close();
	f3->Close();
	f4->Close();
}

