
#include <iostream>
#include <algorithm>
#include <random>

std::vector<int> makeRandomVector(int size)
{
    std::vector<int> v;
    for(int i = 0; i!= size; ++i)
        v.push_back(i);
 
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::shuffle(v.begin(), v.end(), generator);
    
    //for(int i = 0; i < v.size(); ++i)
    //std::cout << v.at(i) << " ";
               
    return v;
}
 
bool isInstrumentFounded(std::vector<int>& v, int index)
{
    int currIndex = index;
    for(int nrOfTries = 0; nrOfTries != v.size()/2; nrOfTries++)
    {
        currIndex = v.at(currIndex);
        if(currIndex == index)  
        {
            //std::cout << currIndex << " " << index << std::endl;
            return true; 
        }
    
    }
    return false;
}

bool isAllInstrumentsFounded(std::vector<int>& v)
{
    bool isAllInstrFounded = true;
    for(int instrumentNr = 0; instrumentNr != v.size(); instrumentNr++)
    {
        isAllInstrFounded *= isInstrumentFounded(v, instrumentNr);    
    }
    return isAllInstrFounded;
}


int main()
{
    
    int nrOfFalses = 0;
    int nrOfSuccesses = 0;
    int nrOfTries = 10000;
    int size = 100;
    for(int i = 0; i != nrOfTries; ++i)
    {
        std::vector<int> randVec = makeRandomVector(size);
        if(isAllInstrumentsFounded(randVec))
            nrOfSuccesses++;
        else
            nrOfFalses++;    
    }
    std::cout << "sukcesy: " << (double) nrOfSuccesses*100./nrOfTries 
              << " porażki: " << (double) nrOfFalses*100./nrOfTries << std::endl;
}


