/*
 * ===================================================================
 *
 *       Filename:  database.cc
 *
 *    Description:  Definition of MySQL Class for accessing database
 *
 *        Created:  Friday 22 February 2013 02:07:49  IST
 *       Compiler:  gcc
 *
 *         Author:  Mandeep Kaur, meghasimak@gmail.com
 *        License:  GNU General Public License
 *      Copyright:  Copyright (c) 2013, Great Developers
 *
 * ===================================================================
 */

/**-------------------------------------------------------------------
 *  Include mysql.h file local header file(declaration of class)
 *------------------------------------------------------------------*/

#include "database.h"
#include <iostream>
#include <string>
#include<time.h>

/**
 *--------------------------------------------------------------------
 *       Class:  MySQL
 *      Method:  MySQL :: MySQL()
 * Description:  Constructor to initialize database conectivity
 *--------------------------------------------------------------------
 */

MySQL :: MySQL()
{
    connect = mysql_init(NULL);
    if ( !connect )
    {
        cout << "MySQL Initialization Failed";
    }   

    connect = mysql_real_connect(connect, SERVER, USER, PASSWORD, DATABASE, 0,NULL,0);
    
    if ( connect )
    {
        cout << "Connection Succeeded\n";
    }
    
    else
    {
        cout << "Connection Failed\n";
    }
}

/**
 *--------------------------------------------------------------------
 *       Class:  MySQL
 *      Method:  MySQL :: ShowTables()
 * Description:  Show tables in database
 *--------------------------------------------------------------------
 */

void MySQL :: ShowTables()
{
  
    /** Add MySQL Query */
    //mysql_query (connect,"show tables");                              
    mysql_query(connect, "show tables");

                                                                         
    res_set = mysql_store_result(connect);                              
                                                                    
    unsigned int numrows = mysql_num_rows(res_set);                   
  
    cout << " Tables in " << DATABASE << " database " << endl;        
                                                                         
    while (((row=mysql_fetch_row(res_set)) != NULL))
    {   
    
        cout << row[0] << endl;
      
      
    }
}
int MySQL::getBookId(string title)
{
    int det;
    char* details;
    string query = "select details_id from inventary join book_details using(details_id) join book using(book_id) where title ='";
    query += title + "'";
    char* tit;
    tit = new char[query.size() + 1];
    copy(query.begin(), query.end(), tit);
    tit[query.size()] = '\0';
    mysql_query(connect, tit);
    res_set = mysql_store_result(connect);

    unsigned int numrows = mysql_num_rows(res_set);

    if (((row = mysql_fetch_row(res_set)) != NULL)) {
        details = row[0];
        det = atoi(details);
    }
    else {
        cout << "There is no book with that title in the inventary" << endl;
        return 0;
    }
    delete[] tit;

    return det;
}

int MySQL::getCustomerId(string mobile)
{
    int id = 0;
    char* identify;
    string query = "select customer_id from customer where mobile_phone='";
    query += mobile + "'";
    char* cust;
    cust = new char[query.size() + 1];
    copy(query.begin(), query.end(), cust);
    cust[query.size()] = '\0';
    mysql_query(connect, cust);
    res_set = mysql_store_result(connect);

    unsigned int numrows = mysql_num_rows(res_set);
    if (((row = mysql_fetch_row(res_set)) != NULL)) {
        identify = row[0];
        id = atoi(identify);
    }
    delete[] cust;
    return id;
}

//1 query
void MySQL::isBookIninventary() 
{   
        string query = "SELECT distinct(inventary_id), concept FROM inventary join book_details using(details_id) join book_author using(book_id) join book using(book_id) join author using(author_id) join stock using(stock_id)";
        int option,myQuery;
        string title, author,selected_option;
        string first_name, last_name;
        cout << "Choose 1 to search a book by title or choose 2 to search a book by author" << endl;
        cin >> option;
        if (option == 1)
        {
            cout << "Insert the title:" << endl;
            cin.ignore();
            getline(cin, title);
            query += " where title='" + title + "'";
        }
        else
        {
            cout << "Insert author's first name:" << endl;
            cin.ignore();
            getline(cin, first_name);
            cout << "Insert author's last name:" << endl;
            getline(cin, last_name);
            remove_if(first_name.begin(), first_name.end(), isspace);
            remove_if(last_name.begin(), last_name.end(), isspace);
            query += "where first_name='" + first_name + "' and last_name='" + last_name + "'";
        }
        myQuery = retQuery(query);
        if (myQuery == 10) {
            cout << "There is a mistake with the name you choose" << endl;
        }

}

//2 query
void MySQL :: oldestCustomer() {
    string query = "Select customer_id,first_name,last_name from customer order by customerEntryDate limit 1";
    cout << "The oldest customer is:" << endl;
    print_query(query);
}
// 3 query
void MySQL::oldestBook()
{
    string query = "Select title from inventary join book_details using(details_id) join book using(book_id) where stock_id!=3 order by purchase_date limit 1";
    cout << "The oldest book in the inventary is:" << endl;
    print_query(query);
}
//4 query
void MySQL::currentOrders() 
{
    string query = "Select order_id,customer_id,order_date,details_id from orders join detail_order using(order_id) where orderBookStatus_id=1 order by order_date";
    cout << "Current active orders are:" << endl;
    int ans = retQuery(query);
    if (ans == 10) {
        cout << "There are not current orders" << endl;
    }
}
// 5 query
void MySQL::countOfSoldBooks() 
{
    string title;
    cout << "Insert book's name:";
    cin.ignore();
    getline(cin, title);
    int details = getBookId(title);
    string query = "Select count(*) from orders join detail_order using(order_id) join book_details using(details_id) where orderBookStatus_id=3 and details_id='";
    query += to_string(details) + "'";
    cout << "Count of sold " + title + " book is: " << endl;
    print_query(query);
}

//query 6
void MySQL::mostReadAuthor()
{
    string date1, date2;
    cout << "Insert 1st date:"<<endl;
    cin >> date1;
    cout << "Insert 2nd date:" << endl;
    cin >> date2;
    string query = "Select first_name,last_name,COUNT(author_id) AS MaxAuthor from orders join detail_order using(order_id) join book_details USING(details_id) join book_author USING(book_id) JOIN author USING(author_id) WHERE orderBookStatus_id =3 and order_date between '";
    query += date1 + "' and '" + date2 + "'and orderBookStatus_id = 3 group by author_id order by MaxAuthor DESC limit 1";
    cout << "The most read author between " + date1 + " and " + date2 + " is:" << endl;
    int myQuery = retQuery(query);
    if (myQuery == 10)
        cout << "We don't sold books between this days." << endl;
}

//query 7
void MySQL::topThreeCustomer()
{
    string query = "Select customer_id,first_name,last_name,COUNT(customer_id) As MaxCustomer from orders join detail_order using(order_id) join customer USING(customer_id) where orderBookStatus_id = 3 GROUP BY customer_id ORDER BY MAXCUSTOMER DESC LIMIT 3";
    cout << "The top 3 customers is:" << endl;
    print_query(query);
}
//query 8
void MySQL::mostTranslationsBook() 
{
    string query = "SELECT title, COUNT(DISTINCT translator_id) NumOfTranslations FROM inventary JOIN book_details USING(details_id) join book using(book_id) WHERE stock_id != 3 AND translator_id IS NOT NULL GROUP BY book_id ORDER BY NumOfTranslations DESC LIMIT 1";
    cout << "The book with more translations is: " << endl;
    print_query(query);

}
//query 9
void MySQL::buyStoryClient()
{
    string phone;
    cout << "Insert client's mobile phone:" << endl;
    cin >> phone;
    string query= "SELECT book_id, title takenBooks, order_date purchaseDate, price FROM orders JOIN detail_order USING(order_id) JOIN book_details USING(details_id) JOIN book_author USING(book_id) JOIN book USING(book_id) JOIN sale_price USING(details_id) WHERE customer_id ='";
    query += to_string(getCustomerId(phone)) + "' and orderBookStatus_id = 3 order by order_date";
    cout << "The buy story of customer number " << getCustomerId(phone) << " is:" << endl;
    int myQuery = retQuery(query);
    if (myQuery == 10)
        cout << "The phone number is wrong, please try again" << endl;
}
//query 10
void MySQL::orderStoryClient()
{
    string phone;
    cout << "Insert client's mobile phone:" << endl;
    cin >> phone;
    string query = "select title,order_date,IF(orderBookStatus_id=1,'No','Yes') isInInventary,IF(orderBookStatus_id=3,'Yes','No') getTheBook from orders join detail_order using(order_id) join book_details using(details_id) join book using(book_id) where customer_id ='";
    query += to_string(getCustomerId(phone)) + "'order by order_date";
    cout << "The order story of customer number " << getCustomerId(phone) << " is:" << endl;
    int myQuery = retQuery(query);
    if (myQuery == 10)
        cout << "The phone number is wrong, please try again" << endl;
}


//query 12
void MySQL::ifCustomerBreakDeliveryShowDetails() 
{
    string phone;
    cout << "Enter customer mobile's phone" << endl;
    cin >> phone;
    string query = "select order_id,order_date,concept,title from delivery join detail_order using(detailOrder_id) join orders using(order_id) join delivery_types using(deliveryType_id) join book_details using(details_id) join book using(book_id) join customer using(customer_id) where order_id in(select order_id from delivery join detail_order using(detailOrder_id) join orders using(order_id) join customer using(customer_id) where customer_id ='";
    query += to_string(getCustomerId(phone)) + "'group by order_id having(count(distinct(deliveryType_id)) > 1) order by order_id)";
    cout << "Customer number " << getCustomerId(phone) << " break a delivery?" << endl;
    int myQuery = retQuery(query);
    if (myQuery == 10)
        cout << "Phone number is wrong or maybe the customer doesnt break any delivery" << endl;
}
//query 13
void MySQL::deliveryStatus()
{
    string phone, order, myconcept;
    cout << "Enter customer mobile's phone" << endl;
    cin >> phone;
    cout << "Insert order's date:" << endl;
    cin >> order;
    cout << "Insert name of delivery(Doar Rashum, Doar Mishloaj, Doar FMishloaj, Xp Pick up or Xp Sheliaj)" << endl;
    cin.ignore();
    getline(cin, myconcept);
    string query = "select deliverState from delivery join detail_order using(detailOrder_id) join orders using(order_id) join delivery_status using(deliveryStatus_id) join delivery_types using(deliveryType_id) where customer_id ='";
    query += to_string(getCustomerId(phone)) + "' and order_date='" + order + "' and concept='" + myconcept + "' group by deliveryType_id, order_id";
    cout << "delivery status is:" << endl;
    int myQuery = retQuery(query);
    if (myQuery == 10)
        cout << "Check again the data" << endl;
     
}
//query 14
void MySQL::countOfXpressDeliveryinAMonth()
{
    int month, year;
    cout << "Insert the month" << endl;
    cin >> month;
    cout << "Insert the year" << endl;
    cin >> year;
    string query = "Select COUNT(*) from delivery join delivery_types using(deliveryType_id) join detail_order using(detailOrder_id) join orders using(order_id) WHERE concept LIKE 'Xp%' AND month(order_date) ='";
    query += to_string(month) + "'and year(order_date)='";
    query+=to_string(year) + "'";
    cout << "Total Xpress delivery in "<<month<< "/"<< year<< " is:" << endl;
    print_query(query);
}
//query 15
void MySQL::getTotalBitEntry()
{
    int month,year;
    cout << "Insert a month:"<<endl;
    cin >> month;
    cout << "Insert a year:" << endl;
    cin >> year;
    string query = "Select SUM(price+weight*pricePerKg) totalBitEntry from payment join payment_method using(paymentMethod_id) join orders using(order_id) join detail_order using(order_id) join sale_price using(details_id) join delivery using(detailOrder_id) join delivery_types using(deliveryType_id) WHERE payment_concept = 'bit' AND month(order_date)='";
    query += to_string(month) + "' and year(order_date)='";
    query += to_string(year) + "'"; 
    int ans = retQuery(query);
    cout<<"Total bit entry in " << month << "/" << year << " is:" << endl;
    if (ans == 10) {
        cout << "There are not bit entry in "<<month << "/" << year << endl;
    }
}
//query 17
void MySQL::totalDeliveryInLastYear() {
    string query = "select COUNT(CASE WHEN concept LIKE 'Doar%' THEN 1 END) AS Doar, COUNT(CASE WHEN concept LIKE 'XP%' THEN 1 END) AS Xpress from delivery join delivery_types using(deliveryType_id) join detail_order using(detailOrder_id) join orders using(order_id)WHERE order_date > DATE_SUB(now(), INTERVAL 12 month)";
    cout << "Doar\t" << "Xpress" << endl;
    print_query(query);
}
//query 18
void MySQL::deliveryOfTwoOrMoreBookVersion()
{
    string query = "select delivery_id,deliveryStatus_id,order_id,inventary_id from delivery join detail_order using(detailOrder_id) join book_details using(details_id) join book using(book_id) where title in(select title from delivery join detail_order using(detailOrder_id) join book_details using(details_id) join book using(book_id) group by title having(count(distinct(details_id)) > 1) order by title)";
    cout << "Showing delivery of two or more version of same book title:" << endl;
    print_query(query);
}
//query 19
void MySQL::customerLastBuyBeforeTwoYears()
{
    string query = "SELECT * FROM orders JOIN customer USING(customer_id) WHERE LAST_DAY(order_date) < DATE_SUB(now(), INTERVAL 24 month) GROUP BY customer_id ORDER BY customer_id";
    cout << "Showing data:" << endl;
    print_query(query);
}
//query 20
void MySQL::listOfCustomerWithPhoneContactSiceTwoWeeks() 
{
    string query = "select customer_id,first_name,last_name from detail_order join orders using(order_id) join customer using(customer_id) join inventary using(inventary_id) where orderBookStatus_id = 2 and (purchase_date) < DATE_SUB(now(), INTERVAL 14 day)";
    cout << "Customers that we call them two or more weeks ago and didnt came:" << endl;
    print_query(query);
}
//query 21
void MySQL::numOfBooksInWarehousePerMonth()
{
    string query = "select month(purchase_date),year(purchase_date),count(*) from inventary where stock_id=2 group by year(purchase_date),month(purchase_date) order by year(purchase_date)";
    cout << "Total warehouse books per month:" << endl;
    print_query(query);
}
//query 22
void MySQL::numOfBooksPurchasedByBookShop()
{
    string date1, date2;
    cout << "Insert 1st date" << endl;
    cin >> date1;
    cout << "Insert 2nd date" << endl;
    cin >> date2;
    string query = "SELECT COUNT(*) totalBooks,SUM(purchase_price) totalSum FROM inventary WHERE purchase_date BETWEEN '";
    query += date1 + "' and '" + date2 + "'";
    cout << "Total books\t" << "totalSum\t" << "between " << date1 << " and " << date2 << endl;
    int ans = retQuery(query);
    if (ans == 10) {
        cout << "There are not bit entry between " << date1 << " and " << date2 << endl;
    }
}
//query 23
void MySQL::totalProfitInAMonth()
{
    int month, year;
    cout << "Insert a month:" << endl;
    cin >> month;
    cout << "Insert a year:" << endl;
    cin >> year;
    string query = "select MonthRef,YearRef,SUM(Earn-PaidPrice) totalWin from transaction where MonthRef='";
    query += to_string(month) + "' and YearRef='" + to_string(year);
    query+= "' group by MonthRef, YearRef order by YearRef, MonthRef ";
    cout << "Total profit is:" << endl;
    print_query(query);

}
//query 25
void MySQL::monthSalaryOfStaff()
{
    int id,month,year;
    cout << "Insert id's staff:" << endl;
    cin >> id;
    cout << "Insert the month:" << endl;
    cin >> month;
    cout << "Insert the year:" << endl;
    cin >> year;
    string query = "SELECT salaryPerHour* hours salary FROM staff JOIN hours_staff USING(staff_id) WHERE staff_id ='";
    query += to_string(id) + "'and month_id='" + to_string(month) + "' and year_id='"+ to_string(year) + "'";
    cout << "Total salary of staff number " << id << " on "<<month<<"/"<<year<<" is: " << endl;
    print_query(query);
}
//query 26
void MySQL::bestStaffSeller() {
    int month;
    cout << "Insert a month" << endl;
    cin >> month;
    string query = "SELECT staff_id, COUNT(staff_id) AS bestSeller FROM orders WHERE Month(order_date)='";
    query += to_string(month) + "' group by staff_id order by bestSeller DESC limit 1";
    print_query(query);
}



/**
 *--------------------------------------------------------------------
 *       Class:  MySQL
 *      Method:  MySQL :: ~MySQL()
 * Description:  Destructor of MySQL class for closing mysql
 *               connection
 *--------------------------------------------------------------------
 */

MySQL :: ~MySQL()
{
    mysql_close (connect);
}


