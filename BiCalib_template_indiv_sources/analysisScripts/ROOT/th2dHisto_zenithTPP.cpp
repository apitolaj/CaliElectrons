void th2dHisto_zenithTPP_Source_SOURCE_PLACEHOLDER(const char* envelopeFile, const char* noEnvelopeFile)
{
    TFile *f1 = new TFile(envelopeFile);
    TFile *f2 = new TFile(noEnvelopeFile);
    TTree *t1 = (TTree*)f1->Get("zenith_TPP");
    TTree *t2 = (TTree*)f2->Get("zenith_TPP");

    TCanvas *c = new TCanvas("c", "Comparison", 800, 1000);
    c->Divide(1, 2);

    // --- top ---
    c->cd(1);
    TH2D *h1 = new TH2D("h1", "Ref. Source Plane Vertex Dist. to Cali. Source vs. Zenith Angle (Env, ENERGY_PLACEHOLDER2);Zenith Angle [deg];Distance [mm]",
                         180, 0, 180, 100, 0, 100);
    
    h1->SetStats(0);
    t1->Draw("distTPP:zenith >> h1", "", "COLZ");

    // --- bottom ---
    c->cd(2);
    TH2D *h2 = new TH2D("h2", "Ref. Source Plane Vertex Dist. to Cali. Source vs. Zenith Angle (Env, ENERGY_PLACEHOLDER2);Zenith Angle [deg];Distance [mm]",
                         180, 0, 180, 100, 0, 100);

    h2->SetStats(0);
    t2->Draw("distTPP:zenith >> h2", "", "COLZ");

    c->SaveAs("th2dHisto_ENERGY_PLACEHOLDER1_Source_SOURCE_PLACEHOLDER.png");
}


