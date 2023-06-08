#include "CurrConvFunc.h"
/*
 *
 * RATES ARE FROM 11/4/2022 - 3:12 PM EST
 * https://www.x-rates.com/
 *
 */

int main() {
    char stop = 'Y' ;
    int car = 0 ;





    while (stop == 'Y') {


        car = menuChoice() ;

        switch (car) {

            case 1:
                processCountryName() ;
                std::cout << "Would you like to convert again? (Y or N): " ;
                std::cin >> stop ;
                car = 0 ;

                break ;
            case 2:

                std::cout << "Would you like to convert again? (Y or N): " ;
                std::cin >> stop ;
                break ;

        }


    }

    return 0 ;
}
