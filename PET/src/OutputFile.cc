#include "OutputFile.hh"
#include <iostream>


OutputFile::OutputFile(std::string filename)
{
   //stworzenie i otwarcie pliku
   outputFile = new TFile(filename.c_str(), "recreate");
   //stworzenie drzewa (może być wiecej niż jedno)
   energyTree = new TTree("energyTree", "energyTree");
  //stworzenie gałęzi i przepisanie im adresów
   energyTree->Branch("enDep", &enDep);

}
//w destruktorze zapisujemy i zamykamy plik
//jeśli obiekt jest singletonem warto stworzyć medotę do
//zamykania, aby destruktor pozostał prywatny
OutputFile::~OutputFile()
{
   outputFile->Write();
   outputFile->Close();
   delete outputFile;
}

void OutputFile::AddEnergy(double energy)
{
   enDep = energy;
   energyTree->Fill();
}

