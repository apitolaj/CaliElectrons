void th2dHisto_TPPDistribution_Source_SOURCE_PLACEHOLDER(
    const char* file1, const char* file2,
    const char* file3, const char* file4)
{
    // Open files
    TFile *f1 = new TFile(file1);
    TFile *f2 = new TFile(file2);
    TFile *f3 = new TFile(file3);
    TFile *f4 = new TFile(file4);

    // Get trees
    TTree *t1 = (TTree*)f1->Get("TPPy_TPPz");
    TTree *t2 = (TTree*)f2->Get("TPPy_TPPz");
    TTree *t3 = (TTree*)f3->Get("TPPy_TPPz");
    TTree *t4 = (TTree*)f4->Get("TPPy_TPPz");

    // Create canvas with 2x2 grid
    TCanvas *c = new TCanvas("c", "Comparison", 1600, 1000);
    c->Divide(2, 2);

    // --- Top Left ---
    c->cd(1);
    TH2D *h1 = new TH2D("h1",
        "Source_SOURCE_PLACEHOLDER: TPP Distribution for Zenith >= 60 (Env., ENERGY_PLACEHOLDER2);Y [mm];Z [mm]",
        180, -1500, 1500, 180, -2500, 2500);
    h1->SetStats(0);
    t1->Draw("TPPy:TPPz >> h1", "", "COLZ");

    // --- Top Right ---
    c->cd(2);
    TH2D *h2 = new TH2D("h2",
        "Source_SOURCE_PLACEHOLDER: TPP Distribution for Zenith < 60 (Env., ENERGY_PLACEHOLDER2);Y [mm];Z [mm]",
        180, -1500, 1500, 180, -2500, 2500);
    h2->SetStats(0);
    t2->Draw("TPPy:TPPz >> h2", "", "COLZ");

    // --- Bottom Left ---
    c->cd(3);
    TH2D *h3 = new TH2D("h3",
        "Source_SOURCE_PLACEHOLDER: TPP Distribution for Zenith >= 60 (No env., ENERGY_PLACEHOLDER2);Y [mm];Z [mm]",
        180, -1500, 1500, 180, -2500, 2500);
    h3->SetStats(0);
    t3->Draw("TPPy:TPPz >> h3", "", "COLZ");

    // --- Bottom Right ---
    c->cd(4);
    TH2D *h4 = new TH2D("h4",
        "Source_SOURCE_PLACEHOLDER: TPP Distribution for Zenith < 60 (No env., ENERGY_PLACEHOLDER2);Y [mm];Z [mm]",
         180, -1500, 1500, 180, -2500, 2500);
    h4->SetStats(0);
    t4->Draw("TPPy:TPPz >> h4", "", "COLZ");

    c->SaveAs("th2dHisto_TPPDistribution_ENERGY_PLACEHOLDER1_Source_SOURCE_PLACEHOLDER.png");
}

