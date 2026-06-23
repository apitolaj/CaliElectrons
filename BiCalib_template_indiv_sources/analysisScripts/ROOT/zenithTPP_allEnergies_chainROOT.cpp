#include "/sps/nemo/scratch/apitolaj/Modules/MiModule/include/MiEvent.h"
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

double zenith;
double distTPP;
int eventNumber;

bool isCalibElectron_envelope(MiEvent *Event)
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

bool isCalibElectron_noEnvelope(MiEvent *Event)
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
                   			return false;
                		}
            		}
        	}
        }
    	return true;
}

void calculateZenith(MiEvent *Event)
{
	TVector3 dir = Event->getPTD()->getpart(0)->getdirectionfromfoil();
	zenith = TMath::ACos(dir.X() / dir.Mag()) * 180.0 / TMath::Pi();
}

void calculateDistTPP(MiEvent *Event, MiVector3D *calibSourceVertexPos)
{

	MiVector3D* refSourceVertexPos = nullptr;
	MiVector3D* diffVector = new MiVector3D();
	
	vector<MiVertex>* vertexVector=Event->getPTD()->getpart(0)->getvertexv();
	
	for(MiVertex& vertex : *vertexVector)
	{
		if(vertex.getpos()=="reference source plane")
		{
			refSourceVertexPos=vertex.getr();
		}
	}
	
	diffVector->setX(0);
	diffVector->setY(refSourceVertexPos->getY()-calibSourceVertexPos->getY());
	diffVector->setZ(refSourceVertexPos->getZ()-calibSourceVertexPos->getZ());
	
	distTPP=diffVector->getModule(); 
	
}

void populateChain(TChain &ROOTChain, const char *dirPath) 
{
	TSystemDirectory dir("dirPath", dirPath);
	TList *files = dir.GetListOfFiles();
	
        if (files) 
	{
		TSystemFile *file;
		TString fname;
		TIter next(files);
		
		while ((file = (TSystemFile*)next())) 
		{
			fname = file->GetName();
			
			if (!file->IsDirectory() && fname.EndsWith(".root")) 
			{
				
				TString fullPath = TString(dirPath) + "/" + fname;
				ROOTChain.Add(fullPath);
		        }
		}
	}
}

void zenithTPP_allEnergies_chainROOT_Source_SOURCE_PLACEHOLDER() 
{
	MiVector3D* calibSourceVertexPos_Source_SOURCE_PLACEHOLDER = new MiVector3D();
	calibSourceVertexPos_Source_SOURCE_PLACEHOLDER->setY(418.5);
	calibSourceVertexPos_Source_SOURCE_PLACEHOLDER->setZ(-418.0);
	
	TChain chain("Event");
	populateChain(chain, "BASE_PLACEHOLDER/../SOURCES/Source_SOURCE_PLACEHOLDER/DATA/ROOTFiles");

	MiEvent *Eve = new MiEvent();
	chain.SetBranchAddress("Eventdata", &Eve);
	
	TFile *outFile_envelope = new TFile("BASE_PLACEHOLDER/DST_PLACEHOLDER/zenithTPP_envelope_allEnergies_Source_SOURCE_PLACEHOLDER.root", "RECREATE");
	TTree *tr_envelope = new TTree("zenith_TPP", "WRITE");

	tr_envelope->Branch("zenith", &zenith, "zenith/f");
	tr_envelope->Branch("distTPP", &distTPP, "distTPP/f");
	tr_envelope->Branch("eventNum", &eventNumber, "eventNumber/I");
	
	TFile *outFile_noEnvelope = new TFile("BASE_PLACEHOLDER/DST_PLACEHOLDER/zenithTPP_noEnvelope_allEnergies_Source_SOURCE_PLACEHOLDER.root", "RECREATE");
	TTree *tr_noEnvelope = new TTree("zenith_TPP", "WRITE");

	tr_noEnvelope->Branch("zenith", &zenith, "zenith/f");
	tr_noEnvelope->Branch("distTPP", &distTPP, "distTPP/f");
	tr_noEnvelope->Branch("eventNum", &eventNumber, "eventNumber/I");

	for (int i = 0; i < chain.GetEntries(); i++)
	{
		chain.GetEntry(i);
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
	
	outFile_envelope->cd();
	tr_envelope->Write();

	outFile_noEnvelope->cd();
	tr_noEnvelope->Write();

    	std::ofstream outFile("BASE_PLACEHOLDER/DST_PLACEHOLDER/zenithTPP_entryCounts_allEnergies_Source_SOURCE_PLACEHOLDER.txt");
    	
    	outFile << "Entry count (all energies)" << std::endl;
	outFile << "Envelope: " << tr_envelope->GetEntries() << std::endl;
	outFile << "No Envelope: " << tr_noEnvelope->GetEntries() << std::endl;
	outFile << "Total: " << chain.GetEntries() << std::endl;
	
	outFile.close();
	outFile_envelope->Close();
	outFile_noEnvelope->Close();
}

































