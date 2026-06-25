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

void zenithTPP_600_800keV_chainROOT_Source_SOURCE_PLACEHOLDER() 
{
	double zenith;
	double distTPP;
	int eventNumber;
	
	MiVector3D* calibSourceVertexPos_Source_SOURCE_PLACEHOLDER = new MiVector3D();
	
	if(sourcePositions.count("Source_SOURCE_PLACEHOLDER"))
	{
		auto [Y, Z] = sourcePositions.at("Source_SOURCE_PLACEHOLDER");
		calibSourceVertexPos_Source_SOURCE_PLACEHOLDER->setY(Y);
		calibSourceVertexPos_Source_SOURCE_PLACEHOLDER->setZ(Z);
	}
	
	TChain chain("Event");
	populateChain(chain, "BASE_PLACEHOLDER/../SOURCES/Source_SOURCE_PLACEHOLDER/DATA/ROOTFiles");

	MiEvent *Eve = new MiEvent();
	chain.SetBranchAddress("Eventdata", &Eve);
	
	TFile *outFile_envelope = new TFile("BASE_PLACEHOLDER/DST_PLACEHOLDER/zenithTPP_envelope_600_800keV_Source_SOURCE_PLACEHOLDER.root", "RECREATE");
	TTree *tr_envelope = new TTree("zenith_TPP", "WRITE");

	tr_envelope->Branch("zenith", &zenith, "zenith/D");
	tr_envelope->Branch("distTPP", &distTPP, "distTPP/D");
	tr_envelope->Branch("eventNum", &eventNumber, "eventNumber/I");
	
	TFile *outFile_noEnvelope = new TFile("BASE_PLACEHOLDER/DST_PLACEHOLDER/zenithTPP_noEnvelope_600_800keV_Source_SOURCE_PLACEHOLDER.root", "RECREATE");
	TTree *tr_noEnvelope = new TTree("zenith_TPP", "WRITE");

	tr_noEnvelope->Branch("zenith", &zenith, "zenith/D");
	tr_noEnvelope->Branch("distTPP", &distTPP, "distTPP/D");
	tr_noEnvelope->Branch("eventNum", &eventNumber, "eventNumber/I");

	for (int i = 0; i < chain.GetEntries(); i++)
	{
		chain.GetEntry(i);
		
		if(isEnergyBetween600_800keV(Eve))
		{
			if (isCalibElectron_envelope(Eve))
			{
			    eventNumber = i;
			    calculateZenith(Eve);
			    calculateDistTPP(Eve, calibSourceVertexPos_Source_SOURCE_PLACEHOLDER);
			    tr_envelope->Fill();
			}
			else if (isCalibElectron_noEnvelope(Eve))
			{
			    eventNumber = i;
			    calculateZenith(Eve);
			    calculateDistTPP(Eve, calibSourceVertexPos_Source_SOURCE_PLACEHOLDER);
			    tr_noEnvelope->Fill();
			}
		}
	}
	outFile_envelope->cd();
	tr_envelope->Write();

	outFile_noEnvelope->cd();
	tr_noEnvelope->Write();

    	std::ofstream outFile("BASE_PLACEHOLDER/DST_PLACEHOLDER/zenithTPP_entryCounts_600_800keV_Source_SOURCE_PLACEHOLDER.txt");
    	
    	outFile << "Entry count (all energies)" << std::endl;
	outFile << "Envelope: " << tr_envelope->GetEntries() << std::endl;
	outFile << "No Envelope: " << tr_noEnvelope->GetEntries() << std::endl;
	outFile << "Total: " << chain.GetEntries() << std::endl;
	
	outFile.close();
	outFile_envelope->Close();
	outFile_noEnvelope->Close();
}

