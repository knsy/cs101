#ifndef WINEPROCESS_H
#define WINEPROCESS_H



#include <string>
#include <vector>

using namespace std;

class Wine //class for storing our wine info
{
private:
    string wineName;
    int vintage;
    int rating;
    double price;
    int upc;
    string location;

 public:
        Wine();
    Wine(double);
    Wine(string setName, int setVintage, int setRating, double setPrice,
         int setWineUpc, string setWineLocation);

    void setWineName(string name);
    string getWineName();

    void setWineVintage(int wineVintage);
    int getWineVintage();

    void setWineRating(int wineRating);
    int getWineRating();

    void setWinePrice(double winePrice);
    double getWinePrice();

    void setWineUpc(int wineUpc);
    int getWineUpc();

    void setWineLocation(string wineLocation);
    string getWineLocation();

    bool operator > (const Wine& wineToCompare) const
    {
        if(rating > wineToCompare.rating) return true;
        else return false;
    }

    bool operator < (const Wine& wineToCompare) const
    {
        if(price < wineToCompare.price) return true;
        else return false;
    }

    bool operator != (const Wine& wineToCompare) const
    {
        if(rating == wineToCompare.rating && price == wineToCompare.price) return true;
        else return false;
    }

    friend const string debugWine(Wine test)
    {
        return test.wineName;
    };



};


class dataProcessing
{
public:
    double string_to_double(string s);
    string double_to_string(double input);
    void readProper_line(string fileLine, Wine& wine);

    void read_line(string fileLine, Wine& wine);


    void processListFile(vector<Wine> &wineList);
    void processProperListFile(vector<Wine> &wineList);
    unsigned int checkFileSize();

};

class Sorter
{
private:
    bool sorted;
    Wine buffer;



public:
    void sortWines(vector<Wine> wineList, vector<Wine>& sortedWines);
    void sortWinesByPrice(vector<Wine> &sortWines);

};




//test function

class function
{
private: int testData;

public: void setTestData(int);
        std::string getTestData();

};






#endif // FUNCTIONS

