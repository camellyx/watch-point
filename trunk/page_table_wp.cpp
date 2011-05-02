#include "page_table_wp.h"
#include <iostream>

#define		PAGE_OFFSET		12		//assuming page size = 4 KB
#define		PAGE_SIZE		(1<<12)

using namespace std;

/*
 * Constructor
 * Initialize the wp system as the whole memory with clean tag
 * As the watchpoint is construct to record memory, the ADDRESS
 * should be unsigned type(which it is in pin.) So we cover the
 * whole memory by setting the end_addr to be max = -1(b1111....1111)
 */
template<class ADDRESS, class FLAGS>
WatchPoint_PT<ADDRESS, FLAGS>::WatchPoint_PT() {
	watchpoint_t<ADDRESS, FLAGS> temp;
	temp.start_addr = 0;
	temp.end_addr = -1;
	temp.flags = 0;
	wp.push_back(temp);
}

template<class ADDRESS, class FLAGS>
WatchPoint_PT<ADDRESS, FLAGS>::~WatchPoint_PT() {
}

/*
 * Below 3 wp fault detector all utilize the general_fault() function,
 * with different detection flags
 */
template<class ADDRESS, class FLAGS>
bool WatchPoint_PT<ADDRESS, FLAGS>::watch_fault(ADDRESS start_addr, ADDRESS end_addr) {
	return general_fault(start_addr, end_addr, WA_READ|WA_WRITE);
}

template<class ADDRESS, class FLAGS>
bool WatchPoint_PT<ADDRESS, FLAGS>::read_fault(ADDRESS start_addr, ADDRESS end_addr) {
	return general_fault(start_addr, end_addr, WA_READ);
}

template<class ADDRESS, class FLAGS>
bool WatchPoint_PT<ADDRESS, FLAGS>::write_fault(ADDRESS start_addr, ADDRESS end_addr) {
	return general_fault(start_addr, end_addr, WA_WRITE);
}

template<class ADDRESS, class FLAGS>
bool WatchPoint_PT<ADDRESS, FLAGS>::general_fault(ADDRESS start_addr, ADDRESS end_addr, FLAGS target_flags) {
	wp_iter = search_address (start_addr, wp);
	while (wp_iter != wp.end() && end_addr > wp_iter->end_addr) {
		if (wp_iter->flags & target_flags)
			return true;
		wp_iter++;
	}
	return ( (wp_iter != wp.end() ) && (wp_iter->flags & target_flags) );
}

template<class ADDRESS, class FLAGS>
void WatchPoint_PT<ADDRESS, FLAGS>::wp_operation(ADDRESS start_addr, ADDRESS end_addr,
		FLAGS target_flags, bool (*flag_test)(FLAGS &x, FLAGS &y),
		FLAGS (*flag_op)(FLAGS &x, FLAGS &y) ) {
	/*
	 * insert_t is used for keeping temp data before being inserted into wp.
	 */
	watchpoint_t<ADDRESS, FLAGS> insert_t;
	/*
	 * The first search must fall into a range either tagged or not.
	 */
	wp_iter = search_address (start_addr, wp);
	
	return;
}
