#include "wineProcess.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <sstream>
#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>

using namespace std;

/**
   default constructor for a Wine object. Sets all values to 0.
*/
Wine::Wine()
{
    wineName = "";
    vintage = 0;
    rating = 0;
    price = 0;
    upc = 0;
    location = "";
}

/**
   overloaded constructor for a Wine object. Sets wine price to the passed price.
   @param setPrice a double used to set the price of a Wine object
*/
Wine::Wine(double setPrice)
{
    wineName = "";
    vintage = 0;
    rating = 0;
    price = setPrice;
    upc = 0;
    location = "";
}

/**
   overloaded constructor. Sets all wine parameters.
   @param setPrice a double used to set the price of a Wine object
*/
Wine::Wine(string setName,int setVintage,int setRating, double setPrice,
           int setWineUpc, string setWineLocation)
{
    wineName = setName;
    vintage = setVintage;
    rating = setRating;
    price = setPrice;
    upc = setWineUpc;
    location = setWineLocation;

}

void Wine::setWineName(string name)
{
    wineName = name;
}

string Wine::getWineName()
{
    return wineName;
}


void Wine::setWineVintage(int wineVintage)
{
    vintage = wineVintage;
}

int Wine::getWineVintage()
{
    return vintage;
}


void Wine::setWineRating(int wineRating)
{
    rating = wineRating;
}

int Wine::getWineRating()
{
    return rating;
}

void Wine::setWinePrice(double winePrice)
{
    price = winePrice;
}

double Wine::getWinePrice()
{
    return price;
}

void Wine::setWineUpc(int wineUpc)
{
    upc = wineUpc;
}

int Wine::getWineUpc()
{
    return upc;
}

void Wine::setWineLocation(string wineLocation)
{
    location = wineLocation;
}

string Wine::getWineLocation()
{
    return location;
}

/**
   Converts a string to a floating-point number, e.g. "3.14" -> 3.14.
   @param s a string representing a floating-point number
   @return the equivalent floating-point number
*/
double dataProcessing::string_to_double(string s)
{
   istringstream stream;
   stream.str(s);
   double x = 0;
   stream >> x;
   return x;
}

/**
   Converts a double to a string, e.g. 3.14 -> "3.14".
   @param input is a double to be processed
   @return string equivalent of the floating-point number
*/
string dataProcessing::double_to_string(double input)
{

    stringstream out;
    out << input;

    return out.str();
}


/**
   Processes the lines Delimited by ';' and including 4 fields
   @param fileLine is the string to be processed
   @param wineName is the name to record from the string
   @param vintage is the year to record from the string
   @param rating is the rating to record from the string
   @param price is the price to record from the string
*/
void dataProcessing::readProper_line(string fileLine, Wine& wine)
   {

    int i = 0;
    int j = 0;



    while (fileLine[i] != ';') { i++; };
    wine.setWineName(fileLine.substr(j, i-j));
    j=i+2;
    i++;


    while (fileLine[i] != ';') { i++; };
    wine.setWineVintage(string_to_double(fileLine.substr(j, i-j)));
    j=i+2;
    i++;

    while (fileLine[i] != ';') { i++; };
    wine.setWineRating(string_to_double(fileLine.substr(j, i-j)));
    j=i+2;
    i++;

    while (fileLine[i] != ';') { i++; };
    wine.setWinePrice(string_to_double(fileLine.substr(j, i-j)));
    j=i+2;
    i++;

    while (fileLine[i] != ';') { i++; };
    wine.setWineUpc(string_to_double(fileLine.substr(j, i-j)));
    j=i+2;
    i++;


    while (fileLine[i] != ';') { i++; };
    wine.setWineLocation(fileLine.substr(j, i-j ));


}

void dataProcessing::read_line(string fileLine, Wine& wine)
{

   int i = 0;
   while (fileLine[i] != ';') { i++; }//parsing to get the first field

   int j = i + 1;//parsing to get the second field marked
   while (isalnum(fileLine[j]) || isspace(fileLine[j])) { j++; }

   int k = j + 1;//third field
   //because the second field is sometimes missing, work around:
   if(string_to_double(fileLine.substr(i + 1, j - 1)) < 1000)
   {
       wine.setWineVintage(666);//just a random number to substitute into missing field
       k = i + 1;

    }
   else{wine.setWineVintage(string_to_double(fileLine.substr(i + 1, j - 1))); }
   while (isalnum(fileLine[k]) || isspace(fileLine[k])) { k++; }


   int l = k + 1; //marking the fourth filed
   while (isalnum(fileLine[l])) { l++; }


   //cutting out the values and pasting them into the object
   wine.setWineName(fileLine.substr(0, i - 2));
   wine.setWineRating(string_to_double(fileLine.substr(j + 1, k - 1)));
   wine.setWinePrice(string_to_double(fileLine.substr(k + 1, l - 1)));
   wine.setWineLocation("Canadia");

}


/**
   Processes the file by cutting it up and feeding separate lines  to the
   read_line processor
   @param wineList[] structure for wine descriptions/rating/price

*/

void dataProcessing::processListFile(vector<Wine> &wineList)
{
    int lineNum = 0;
    ifstream inList;
    inList.open("winelist.txt");//open file

    string fileLine;//will store cut out lines from a file in this





    while(getline(inList, fileLine))//read file, send onto processing
    {


        read_line(fileLine, wineList[lineNum]);
        wineList[lineNum].setWineUpc(100000+lineNum);

        lineNum ++;

    }
    inList.close();


}

/**
   Processes the properly saved file by cutting it up and feeding separate lines  to the
   read_line processor
   @param wineList[] structure for wine descriptions/rating/price

*/
void dataProcessing::processProperListFile(vector<Wine> &wineList)
{
    unsigned int lineNum = 0;
    ifstream inList;
    inList.open("winelistsave.txt");//open file

    string fileLine;//will store cut out lines from a file in this



    while(getline(inList, fileLine))//read file, send onto processing

    {

        if(wineList.size() > (lineNum)){

            readProper_line(fileLine, wineList[lineNum]);
            lineNum++;



       }else{



           //readProper_line(fileLine, wineList[lineNum]);
           //lineNum++;
        }



    }

    inList.close();


}

/**
   Processes the properly saved file by cutting it up and feeding separate lines  to the
   read_line processor
   @param wineList[] structure for wine descriptions/rating/price

*/
unsigned int dataProcessing::checkFileSize()
{
    unsigned int lineNum = 0;
    ifstream inList;
    inList.open("winelistsave.txt");//open file

    string fileLine;//will store cut out lines from a file in this



    while(getline(inList, fileLine))//read file, send onto processing

    {

            lineNum++;

    }

    inList.close();

    return lineNum;


}



/**
   Sorts Wine objects
   @param wineList[] vector of Wine objects to be sorted and
   @param sortedWines[] to store the sorted vector

*/
void Sorter::sortWines(vector<Wine> wineList, vector<Wine> &sortedWines)
{
    bool sorted = false;
    Wine buffer;
    while(!sorted)
    {
        for(unsigned int i=0; i < (wineList.size()-1); i++)
        {
              if(wineList[i+1] > wineList[i])
              {

                  buffer = wineList[i];
                  wineList[i]=wineList[i+1];
                  wineList[i+1]=buffer;
                  i=0;
              }
                else{sorted = true;};
        }
    }

    for(unsigned int i=0; i < wineList.size(); i++)
            {sortedWines[i] = wineList[i];
            };

}


/**
   Sorts Wine objects according to price
   @param wineList[] vector of Wine objects to be sorted and
   @param sortedWines[] to store the sorted vector

*/
void Sorter::sortWinesByPrice(vector<Wine> &sortWines)
{
    sort(sortWines.begin(), sortWines.end());

}
