void PlotHisto()
{
    //nazwa pliku:
    TFile* file = new TFile("build/file.root");
    //nazwa frzewa 
    TTree* tree=(TTree*)file->Get("treeName");
 
    //zakres histogramu
    double xMin = 0;
    double xMax = 5000;//do ustalenia 
    //liczba binów
    double xNBins = (xMax-xMin);    
    
       
    TH1F* histo = new TH1F("histo0","histo0",xNBins,xMin,xMax);
    //nazwaLiscia >> nazwaHistogramu
    tree->Draw("leafName>>histo0");
    
    int lowBin = 100;//threshold
    int highBin = (int) xNBins;//ostani bin
    double calka = histo->Integral(lowBin, highBin);
    std::cout << "l. zliczen powyzej progu: " << calka << std::endl;
    //rysowanie histogramu
    histo->Draw();
    
}
