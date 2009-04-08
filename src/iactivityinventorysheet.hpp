
#ifndef _IACTIVITYINVENTORYSHEET_HPP_
#define _IACTIVITYINVENTORYSHEET_HPP_
#include "litesql.hpp"
#include "pomotuxdatabase.hpp"
#include <iostream>
#include <string>



//using namespace std;
using namespace litesql;
using namespace pomotuxdatabase;

/**  Interface Class to Activity Inventory Sheet
 *
 * #include "litesql.hpp"
 * #include "pomotuxdatabase.hpp"
 * -llitesql 
 *
 * Interface class to the one automatically generated by LiteSQL.
 *  
 * @see pomotuxdatabase.hpp
 */
class IActivityInventorySheet : public ActivityInventorySheet {
public:

    /** Default constructor.
     * 	@param a reference to the litesql database
     */
    IActivityInventorySheet(const litesql::Database& db);

    /** Destructor.
     */
    ~IActivityInventorySheet();
};



#endif 
