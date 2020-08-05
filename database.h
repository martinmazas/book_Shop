/*
 * ===================================================================
 *
 *       Filename:  database.h
 *
 *    Description:  Declaring MySQL class for using database.
 *
 *        Created:  Friday 22 February 2013 12:48:40  IST
 *       Compiler:  gcc
 *
 *         Author:  Mandeep Kaur, meghasimak@gmail.com
 *        License:  GNU General Public License
 *      Copyright:  Copyright (c) 2013, Great Developers
 *
 * ===================================================================
 */

/**-------------------------------------------------------------------
 *  Include database-detail.h and other files
 *------------------------------------------------------------------*/

#include "header.h"
#include "database-detail.h"


/**
 * ===================================================================
 *        Class:  MySQL
 *  Description:  MySQL class for database accessability
 * ===================================================================
 */

class MySQL
{
    protected:
        /** MySQL connectivity Variables */
        MYSQL *connect;
        MYSQL_RES *res_set;
        MYSQL_ROW row;
        int retQuery(string query)
        {
            char* myNewChar;
            myNewChar = new char[query.size() + 1];
            copy(query.begin(), query.end(), myNewChar);
            myNewChar[query.size()] = '\0';
            mysql_query(connect, myNewChar);
            res_set = mysql_store_result(connect);

            unsigned int numrows = mysql_num_rows(res_set);
            unsigned int colNum = mysql_num_fields(res_set);
            if (((row = mysql_fetch_row(res_set)) == NULL))
            {
                cout << "There is no data to show" << endl;
                return 10;
            }
            else
            {
                mysql_query(connect, myNewChar);
                res_set = mysql_store_result(connect);
                numrows = mysql_num_rows(res_set);
                colNum = mysql_num_fields(res_set);
            }

            while (((row = mysql_fetch_row(res_set)) != NULL))
            {
                
                for (int i = 0; i < colNum; i++) {
                    if (colNum == 1 && row[i] == NULL) {
                        return 10;
                    }
                    else
                        if (row[i] == NULL)
                            cout << "NULL\t" << endl;
                        else
                            cout << row[i] << '\t';
                }
                cout << endl;
            }
            cout << endl;
            delete[] myNewChar;
            return 11;
        }
        void print_query(string query) {
            char* myNewChar;
            myNewChar = new char[query.size() + 1];
            copy(query.begin(), query.end(), myNewChar);
            myNewChar[query.size()] = '\0';
            mysql_query(connect, myNewChar);
            res_set = mysql_store_result(connect);

            unsigned int numrows = mysql_num_rows(res_set);
            unsigned int colNum = mysql_num_fields(res_set);
            if ((row = mysql_fetch_row(res_set)) == NULL)
            {
                cout << "There is no data to show" << endl;
            }
            else
            {
                mysql_query(connect, myNewChar);
                res_set = mysql_store_result(connect);
                numrows = mysql_num_rows(res_set);
                colNum = mysql_num_fields(res_set);
            }
            
            while (((row = mysql_fetch_row(res_set)) != NULL))
            {
                for (int i = 0; i < colNum; i++) {
                    cout << row[i] << '\t';
                }
                cout << endl;
            }
            cout << endl;
            delete[] myNewChar;
        }

    public:
        /** MySQL Constructor */
        MySQL();

        /** Function to show tables in database */
        int getBookId(string title);
        int getCustomerId(string mobile);
        void ShowTables();
        //query 1
        void isBookIninventary();
        //query 2
        void oldestCustomer();
        //query 3
        void oldestBook();
        //query 4
        void currentOrders();
        //query 5
        void countOfSoldBooks();
        //query 6 
        void mostReadAuthor();
        //query 7
        void topThreeCustomer();
        //query 8
        void mostTranslationsBook();
        //query 9
        void buyStoryClient();
        //query 10 
        void orderStoryClient();
        
        //query 12
        void ifCustomerBreakDeliveryShowDetails();
        //query 13
        void deliveryStatus();
        //query 14
        void countOfXpressDeliveryinAMonth();
        //query 15
        void getTotalBitEntry();
        //query 17
        void totalDeliveryInLastYear();
        //query 18
        void deliveryOfTwoOrMoreBookVersion();
        //query 19
        void customerLastBuyBeforeTwoYears();
        //query 20
        void listOfCustomerWithPhoneContactSiceTwoWeeks();
        //query 21
        void numOfBooksInWarehousePerMonth();
        //query 22
        void numOfBooksPurchasedByBookShop();
        //query 23
        void totalProfitInAMonth();
        //query 25
        void monthSalaryOfStaff();
        //query 26
        void bestStaffSeller();
        /** MySQL Destructor */
        ~MySQL();
};


