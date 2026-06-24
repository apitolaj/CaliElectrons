#include "/sps/nemo/scratch/apitolaj/Modules/MiModule/include/MiEvent.h"
#include "UTILS_PLACEHOLDER/functionUtils.h"
#include "TLatex.h"
#include "TVector3.h"
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "TSystemDirectory.h"
#include "TSystemFile.h"
#include "TList.h"

R__LOAD_LIBRARY(/sps/nemo/scratch/apitolaj/Modules/MiModule/lib/libMiModule.so);

void distributionTPP_allEnergies_chainROOT_Source_SOURCE_PLACEHOLDER()
{
	int eventNumber;
			
	double zenith;
	double TPPy;
	double TPPz;
	
	TChain chain("Event");
	populateChain(chain, "BASE_PLACEHOLDER/../SOURCES/Source_SOURCE_PLACEHOLDER/DATA/ROOTFiles");
	
	MiEvent *Eve = new MiEvent();
	chain.SetBranchAddress("Eventdata", &Eve);

	TFile *outFile_envelope_g60 = new TFile("BASE_PLACEHOLDER/DST_PLACEHOLDER/distributionTPP_envelope_allEnergies_zenithg60_Source_SOURCE_PLACEHOLDER.root", "RECREATE");
	TTree *tr_envelope_g60 = new TTree("TPPy_TPPz", "WRITE");

	tr_envelope_g60->Branch("TPPy", &TPPy, "TPPy/f");
	tr_envelope_g60->Branch("TPPz", &TPPz, "TPPz/f");
	tr_envelope_g60->Branch("eventNumber", &eventNumber, "eventNumber/I");
	
	TFile *outFile_envelope_l60 = new TFile("BASE_PLACEHOLDER/DST_PLACEHOLDER/distributionTPP_envelope_allEnergies_zenithl60_Source_SOURCE_PLACEHOLDER.root", "RECREATE");
	TTree *tr_envelope_l60 = new TTree("TPPy_TPPz", "WRITE");

	tr_envelope_l60->Branch("TPPy", &TPPy, "TPPy/f");
	tr_envelope_l60->Branch("TPPz", &TPPz, "TPPz/f");
	tr_envelope_l60->Branch("eventNumber", &eventNumber, "eventNumber/I");
	
	TFile *outFile_noEnvelope_g60 = new TFile("BASE_PLACEHOLDER/DST_PLACEHOLDER/distributionTPP_noEnvelope_allEnergies_zenithg60_Source_SOURCE_PLACEHOLDER.root", "RECREATE");
	TTree *tr_noEnvelope_g60 = new TTree("TPPy_TPPz", "WRITE");

	tr_noEnvelope_g60->Branch("TPPy", &TPPy, "TPPy/f");
	tr_noEnvelope_g60->Branch("TPPz", &TPPz, "TPPz/f");
	tr_noEnvelope_g60->Branch("eventNumber", &eventNumber, "eventNumber/I");
	
	TFile *outFile_noEnvelope_l60 = new TFile("BASE_PLACEHOLDER/DST_PLACEHOLDER/distributionTPP_noEnvelope_allEnergies_zenithl60_Source_SOURCE_PLACEHOLDER.root", "RECREATE");
	TTree *tr_noEnvelope_l60 = new TTree("TPPy_TPPz", "WRITE");

	tr_noEnvelope_l60->Branch("TPPy", &TPPy, "TPPy/f");
	tr_noEnvelope_l60->Branch("TPPz", &TPPz, "TPPz/f");
	tr_noEnvelope_l60->Branch("eventNumber", &eventNumber, "eventNumber/I");
	
	for (int i = 0; i < chain.GetEntries(); i++)
	{
		chain.GetEntry(i);
		eventNumber = i;
		
		if (isCalibElectron_envelope(Eve))
		{
		
			zenith = calculateZenith(Eve);
			MiVector3D* posVector = calculatePosTPPVector(Eve);
			TPPy = posVector->getY();
			TPPz = posVector->getZ();
			
			if (zenith >= 60) 
			{
				tr_envelope_g60->Fill();
			}
			
			else  
			{
				tr_envelope_l60->Fill();
			}
			
		}
		else if (isCalibElectron_noEnvelope(Eve))
		{	
		
			zenith = calculateZenith(Eve);
			MiVector3D* posVector = calculatePosTPPVector(Eve);
			TPPy = posVector->getY();
			TPPz = posVector->getZ();
			
			if (zenith >= 60) 
			{
				tr_noEnvelope_g60->Fill();
			}
			
			else 
			{
				tr_noEnvelope_l60->Fill();
			}
		}

	}
	
	outFile_envelope_g60->cd();
	tr_envelope_g60->Write();

	outFile_envelope_l60->cd();
	tr_envelope_l60->Write();
	
	outFile_noEnvelope_g60->cd();
	tr_noEnvelope_g60->Write();

	outFile_noEnvelope_l60->cd();
	tr_noEnvelope_l60->Write();

    	std::ofstream outFile("BASE_PLACEHOLDER/DST_PLACEHOLDER/zenithTPP_entryCounts_allEnergies_Source_SOURCE_PLACEHOLDER.txt");
    	
    	outFile << "Entry count (all energies)" << std::endl;
	outFile << "Envelope (zenith >= 60): " << tr_envelope_g60->GetEntries() << std::endl;
	outFile << "Envelope  (zenith < 60): " << tr_envelope_l60->GetEntries() << std::endl;
	outFile << "No Envelope  (zenith >= 60): " << tr_noEnvelope_g60->GetEntries() << std::endl;
	outFile << "No Envelope  (zenith < 60): " << tr_noEnvelope_l60->GetEntries() << std::endl;
	outFile << "Total: " << chain.GetEntries() << std::endl;
	
	outFile.close();
	outFile_envelope_g60->Close();
	outFile_envelope_l60->Close();
	outFile_noEnvelope_g60->Close();
	outFile_noEnvelope_l60->Close();
}






































