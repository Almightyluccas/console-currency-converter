#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

struct country {
    double rateArr[4]{} ;
    double money[2]{} ;
    std::string nameArr[4] {} ;
    std::string name[2] {} ;
    std::string currency[2] {} ;
} country ;

void printMenuOptions() {
    std::cout << "How would you like to convert: \n"
              << "-Using Currency Name" << std::endl
              << "-Using Country Name\n" ;
}

int menuChoice() {
    std::string menuSelection ;
    int menu ;
    printMenuOptions() ;
    std::cin >> menuSelection ;
    if (menuSelection == "Country") {
        menu = 1 ;
    }
    if (menuSelection == "Currency") {
        menu = 2 ;
    }
    menuSelection.clear() ;
    return menu ;

}                                     //Lets User choose how they will convert (menu option)


void printCountryNames() {
    for (int i = 0; i <= 3; i++) {
        std::cout << country.nameArr[i] << "\n" ;
    }
}                             //Prints out the country names from CountryRates

void printCurrencyNames() {

}                            //Prints out the currencyNames from CountryRates

void retrieveCountryNames(){
    std::ifstream iFile ;
    iFile.open("Countries") ;
    if (iFile.is_open()) {
        for (int i = 0; i <= 3; i++) {
            std::getline(iFile , country.nameArr[i])  ;
        }
    }
    if (!iFile.is_open()) {
        std::cout << "Error! the file did not open" ;
    }
    printCountryNames() ;
    std::cout << "\n" ;
    iFile.close() ;
}                           //Gets all country names from the Countries file

void retrieveCurrencyNames() {

}            //Gets all country names from the Currency file

void askFirstOrSecondCountry(int x){
    if (x == 0) {
        std::cout << "Please choose which country you would like to convert the currency from:\n" ;
    }
    if (x == 1) {
        std::cout << "Please choose which country you would like to convert the currency to:\n" ;
    }
}                   //chooses if it is the first or second country being queried
bool validateCountryInput( int x) {                         //validate country chosen
    if (country.name[x] == "America"  || country.name[x] == "Canada" || country.name[x] == "Brazil"
       || country.name[x] == "England") {
        return true ;
    }                                                       //NEED TO IMPLEMENT ANOTHER IF STATMENT TO
    else {                                                  // MAKE SURE no STRING or CHARACTERS are accepted
        return false ;
    }
}                    //Validates country name

std::string capitalizeFirstLetter(std::string name){
    for(int i = 0 ; i < 1 ; i++){
        name[0] = std::toupper(name[0],std::locale()) ;
    }
    return name ;
}   //Turns first letter of country into a capital

std::string typeOfCurrency(int x) {
    if (country.name[x] == "America") {
        country.currency[x] = "USD";
    }
    if (country.name[x] == "Canada") {
        country.currency[x] = "CAD";
    }
    if (country.name[x] == "Brazil") {
        country.currency[x] = "BRL";
    }
    if (country.name[x] == "England") {
        country.currency[x] = "GBP";
    }
    return country.currency[x] ;
}                    //outputs type of currency based on country selected

std::string queryCountry(int x) {
        do {
            askFirstOrSecondCountry(x);
            retrieveCountryNames();
            std::cin >> country.name[x];
            country.name[x] = capitalizeFirstLetter(country.name[x]);
            if (validateCountryInput(x)) {
                typeOfCurrency(x);
            } else {
                std::cout << "Error! The country you have selected is not available\n\n";
            }
        }
        while (!validateCountryInput(x)) ;
    return country.name[x] ;
}                      //Ask user to enter country with validation

bool validateMoneyInput(int x) {
    if (country.money[x] >= 0) {
        return true ;
    }
    else {
        return false ;                  //STILL NEED TO IMPLEMENT CHARACTER VALIDATION to make sure it isn't a character
    }
}                       //validates if input is a negative num

double queryMoneyInput() { //asks user for total amount of money and returns it
    do {
        if (validateMoneyInput(0)) {
            std::cout << "Please enter the amount of " << typeOfCurrency(0) << ": ";
            std::cin >> country.money[0];
            country.money[0] = floor(country.money[0] * 100) / 100;  // drop all numbers after 2 decimal points
        }
        else {
            std::cout << "Error! Only non-negative numbers allowed \n\n";
        }
    }
    while (!validateMoneyInput(0)) ;
    return country.money[0] ;
}                             //asks user for total amount of money and returns it

std::string getFileName() {
    std::string fileName ;
    typeOfCurrency(0) ;
    if (country.currency[0] == "USD"){
        fileName = "USDConversionRate" ;
    }
    if (country.currency[0] == "CAD"){
        fileName = "CADConversionRate" ;
    }
    if (country.currency[0] == "BRL"){
        fileName = "BRLConversionRate" ;
    }
    if (country.currency[0] == "GBP"){
        fileName = "GBPConversionRate" ;
    }
    return fileName ;
}                            //Chooses which conversion rate to choose based on chosen $

void readRates() {
    std::ifstream iFile ;
    iFile.open(getFileName()) ;
    if (iFile.is_open()) {
        std::string temp ;
        for (int i = 0; i <= 3; i++) {
            iFile >> temp >> country.rateArr[i] ;
            temp.erase() ;
        }
    }
    if (!iFile.is_open()) {
        std::cout << "Error! the file did not open" ;
    }
    iFile.close() ;
}                                     //reads rates from conversion rate files

double calcConvCurr() {
    if (country.currency[1] == "USD") {
        country.money[1] = country.money[0] * country.rateArr[0];
    }
    if (country.currency[1] == "CAD") {
        country.money[1] = country.money[0] * country.rateArr[1];
    }
    if (country.currency[1] == "BRL") {
        country.money[1] = country.money[0] * country.rateArr[2];
    }
    if (country.currency[1] == "GBP") {
        country.money[1] = country.money[0] * country.rateArr[3];
    }
    return country.money[1] ;
}                                //calculates the new converted currency

void printRates(){
    std::cout << "\n" ;
    std::cout << country.money[0] << " " << country.currency[0] << " is equal to:  "
              << calcConvCurr() << " " << country.currency[1] << "\n" ;

}                                     //shows the converted currency

void processCountryName() {
    queryCountry(0) ;                              //Choose country converting from (gives list to choose from)
    queryMoneyInput() ;                               //ask for amount of currency converting
    queryCountry(1) ;                              //choose country converting to
    readRates() ;                                     //reads the rates from file
    calcConvCurr() ;                                  //calculates converted currency based on chosen second currency
    printRates() ;                                    //prints the final converted currency
}                            //entire process for country choice

void processCurrencyName() {
                                                      //choose currency converting from
    queryMoneyInput() ;                               //ask for amount of currency converting

    readRates() ;                                     //reads the rates from file
    calcConvCurr() ;                                  //calculates converted currency based on chosen second currency
    printRates() ;                                    //prints the final converted currency
}                           //entire process for currency choice
