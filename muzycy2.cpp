
#include <iostream>
#include <algorithm>
#include <random>

void printVector(std::vector<int>& v)
{
    for(int i = 0; i != v.size(); ++i)
    {
         std::cout << v.at(i) << " " ;
    }
    std::cout << std::endl;
}


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
    //printVector(v);           
    return v;
}
 


bool isInstrumentFounded(std::vector<int>& v, int index)
{
    for(int currIndex = 0; currIndex != v.size()/2; currIndex++)
    {
        if(v.at(currIndex) == index) // udało się znaleźć!!!  
        {
            //usuwam ten element wektora:
            v.erase(v.begin() + currIndex);
            //dodaję go a końcu
            v.push_back(index);
            
            //wyświetlanie - sprawdzenie, ze erase działa tak jak myślę
            //printVector(v);
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


