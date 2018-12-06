#ifndef OutputFile_H
#define OutputFile_H

#include <string>
#include "TFile.h"
#include "TTree.h"

class OutputFile 
{
    public:
    OutputFile(std::string fileName);
   ~OutputFile();
    void AddEnergy(double energy);

private:
   TFile* outputFile;
   TTree* energyTree;
   double enDep;

};
#endif
