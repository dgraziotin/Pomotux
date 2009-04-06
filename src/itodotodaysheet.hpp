
#ifndef _ITODOTODAYSHEET_HPP_
#define _ITODOTODAYSHEET_HPP_
#include "litesql.hpp"
#include "pomotuxdatabase.hpp"
#include <iostream>
#include <string>

//using namespace std;
using namespace litesql;
using namespace pomotuxdatabase;

/**  Interface Class to Todo Today Sheet
 *
 * #include "litesql.hpp"
 * #include "pomotuxdatabase.hpp"
 * -llitesql 
 *
 * Interface class to the obejct table Todo Today Sheet automatically generated by 
 * litesql framework
 *  
 * @see pomotuxdatabase.hpp
 */
class ITodoTodaySheet : public TodoTodaySheet
{
	public:
	
	/** Default constructor.
	 * 	@param a reference to the litesql database
	 */
	ITodoTodaySheet(const litesql::Database& db);
	
	/** A method to set the activity order of an activity already picked up in the todo today sheet
	 * 	@param an Integer representing the Order of the activity in the TDTS
	 */
	void set_mActivityOrder(int activityOrder);
	
	/** A method that returns the activity order of an activity already picked up in the todo today sheet
	 * 	@return activity order as integer
	 */
	int get_mActivityOrder();
	
	/** Deconstructor
	 * 	
	 */
	~ITodoTodaySheet();
};
#endif
