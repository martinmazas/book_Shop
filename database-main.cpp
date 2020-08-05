/*
 * ===================================================================
 *
 *       Filename:  database-main.cpp
 *
 *    Description:  Main Method
 *
 *        Created:  Thursday 28 February 2013 10:53:59  IST
 *       Compiler:  gcc
 *
 *         Author:  Mandeep Kaur, meghasimak@gmail.com
 *        License:  GNU General Public License
 *      Copyright:  Copyright (c) 2013, Great Developers
 *
 * ===================================================================
 */

/**-------------------------------------------------------------------
 *  \mainpage MySQL Connectivity with C++
 *
 *  This is a working code example of using C++ to interface with MySQL.
 *  Steps:                                                                
 *                                                                                                                        
 *  \li Download this code \n
 *      $ git clone https://github.com/megha55/mysql-with-cpp.git
 *
 *  \li For installing MySQL Connector for C++ \n                     
 *      $ make install 
 *
 *  \li Change database details in database-detail.h file.
 *                                                                         
 *  \li To run example \n                                              
 *      $ make 
 * 
 *------------------------------------------------------------------*/

/**-------------------------------------------------------------------
 *  Include required header files
 *------------------------------------------------------------------*/
 
#include "database.h"

int main(void)
{
    MySQL Mysql;
    int staff,option,id;
    cout << "Hi choose 1 for manager, choose 2 for staff" << endl;
    cin >> staff;
    while(staff < 1 || staff>2) {
        cout << staff << " is not a possible option please try again with 1(manager) or 2(employee)" << endl;
        cin >> staff;
    }
    if (staff == 1) {
        cout << "Insert your id's staff:" << endl;
        cin >> id;
        while(id != 999) {
            cout << "wrong number,try again" << endl;
            cin >> id;
        }
    }
    cout << "Choose one of the following actions:\n"
        "1. Search a book on inventary by title or by author\n"
        "2. Who's the oldest customer?\n"
        "3. What is the oldest book in the inventary?\n"
        "4. Current order list\n"
        "5. How many copies of Y book we sold?\n"
        "6. Who's the most read author between two dates\n"
        "7. Top 3 customers with more purchases\n"
        "8. Book in inventary with more translations\n"
        "9. Purchase history of a customer X\n"
        "10. Order history of a customer X\n"
        "11. Delivery calculation\n"
        "12. See if customer X break a purchase in many deliveries\n"
        "13. Delivery status\n"
        "14. Number of Xpress's delivery in a month\n"
        "15. How much money we get from Bit\n"
        "16. Last 12 month transactions\n"
        "17. Total Xpress's delivery in last year\n"
        "18. Deliveries that we do of different editions of same book\n"
        "19. Customers that buyed in the past and last buy was since two years ago\n"
        "20. Customer that we purchased the book they didnt came to the store since 14 days\n"
        "21. Number of books in the warehouse at X month\n"
        "22. Bookshop's purchased book between two dates\n"
        "23. Store win a month\n"
        "24. Average transactions per month\n"
        "25. Gross salary of a employee in a month\n"
        "26. Employee with more sales in a month\n"
        "0. Exit"<< endl;
    cin >> option;

    while (option != 0) {
        if (staff == 2 && (option == 26 || option==25 || option==24 || option==23))
        {
            cout << "You dont have access to this action" << endl;
            goto CHOOSE_OPTION;
        }
        switch (option) {
        case 1:
            Mysql.isBookIninventary();
            break;
        case 2:
            Mysql.oldestCustomer();
            break;
        case 3:
            Mysql.oldestBook();
            break;
        case 4:
            Mysql.currentOrders();
            break;
        case 5:
            Mysql.countOfSoldBooks();
            break;
        case 6:
            Mysql.mostReadAuthor();
            break;
        case 7:
            Mysql.topThreeCustomer();
            break;
        case 8:
            Mysql.mostTranslationsBook();
            break;
        case 9:
            Mysql.buyStoryClient();
            break;
        case 10:
            Mysql.orderStoryClient();
            break;
        case 11:
            cout << "Temporary not available" << endl;
            break;
        case 12:
            Mysql.ifCustomerBreakDeliveryShowDetails();
            break;
        case 13:
            Mysql.deliveryStatus();
            break;
        case 14:
            Mysql.countOfXpressDeliveryinAMonth();
            break;
        case 15:
            Mysql.getTotalBitEntry();
            break;
        case 16:
            cout << "Temporary not available" << endl;
            break;
        case 17:
            Mysql.totalDeliveryInLastYear();
            break;
        case 18:
            Mysql.deliveryOfTwoOrMoreBookVersion();
            break;
        case 19:
            Mysql.customerLastBuyBeforeTwoYears();
            break;
        case 20:
            Mysql.listOfCustomerWithPhoneContactSiceTwoWeeks();
            break;
        case 21:
            Mysql.numOfBooksInWarehousePerMonth();
            break;
        case 22:
            Mysql.numOfBooksPurchasedByBookShop();
            break;
        case 23:
            Mysql.totalProfitInAMonth();
            break;
        case 24:
            cout << "Temporary not available" << endl;
            break;
        case 25:
            Mysql.monthSalaryOfStaff();
            break;
        case 26:
            Mysql.bestStaffSeller();
            break;
        default:
            cout << "wrong option, please choose a correct option" << endl;  
        }
        CHOOSE_OPTION:cout << "Choose another option" << endl;
        cin >> option;
        

    }
    
    return 0;
}
