bool isCalibElectron_envelope(MiEvent *Event);
bool isCalibElectron_noEnvelope(MiEvent *Event);
double calculateZenith(MiEvent *Event);
MiVector3D* calculatePosTPPVector(MiEvent *Event);
void populateChain(TChain &ROOTChain, const char *dirPath);
bool isEnergyBetween600_800keV(MiEvent *Event);
void calculateAngles(MiEvent *Event);
void calculateDistTPP(MiEvent *Event, MiVector3D *calibSourceVertexPos);

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

bool isEnergyBetween600_800keV(MiEvent *Event)
{

	double E_OM = 0;
	std::vector<MiCDCaloHit>* caloHitVector = Event->getPTD()->getpart(0)->getcalohitv();

	for(MiCDCaloHit& hit : *caloHitVector)
	{
		E_OM+=hit.getE();
	}

	if(600 < E_OM && E_OM < 800)
	{
		return true;
	}
	
	return false;
}

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

	bool isCalibElectron = false;
	bool didInteractEnvelope= false;
	MiSD *sd = Event->getSD();
    
	if (sd)
        {
        	std::vector<MiSDCaloHit> *ch = sd->getcalohitv();

        	if (ch)
        	{
            		for (auto &hit : *ch)
            		{
            			if(hit.getcategory() == "bi207_calib_source" && hit.getname() == "e-")
            			{
            				isCalibElectron=true;
            				
            				if(hit.getGID()->gettype() == "1066")
            				{
            					didInteractEnvelope=true;
            				}
            			}
            		}
        	}
        }
        
        return (isCalibElectron && !didInteractEnvelope);
}

double calculateZenith(MiEvent *Event)
{
	TVector3 dir = Event->getPTD()->getpart(0)->getdirectionfromfoil();
	double zenith = TMath::ACos(dir.X() / dir.Mag()) * 180.0 / TMath::Pi();
	return zenith;
}

MiVector3D* calculatePosTPPVector(MiEvent *Event)
{

	MiVector3D* posVector = nullptr;
	
	vector<MiVertex>* vertexVector=Event->getPTD()->getpart(0)->getvertexv();
	
	for(MiVertex& vertex : *vertexVector)
	{
		if(vertex.getpos()=="reference source plane")
		{
			posVector=vertex.getr();
		}
	}
	
	return posVector;
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

