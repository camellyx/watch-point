/*
 * page_table_wp.h
 *
 *  Created on: May 1, 2011
 *      Author: luoyixin
 */

#ifndef PAGE_TABLE_WP_H_
#define PAGE_TABLE_WP_H_

#include "auto_wp.h"

template<class ADDRESS, class FLAGS>
class WatchPoint_PT:public WatchPoint<ADDRESS, FLAGS> {
public:
	WatchPoint_PT();
	~WatchPoint_PT();
	
	std::deque< watchpoint_t<ADDRESS, FLAGS> > wp;
	typename std::deque< watchpoint_t<ADDRESS, FLAGS> >::iterator wp_iter;
	typename std::deque< watchpoint_t<ADDRESS, FLAGS> >::iterator pre_iter;
	typename std::deque< watchpoint_t<ADDRESS, FLAGS> >::iterator aft_iter;
};

#include "page_table_wp.cpp"
#endif /* PAGE_TABLE_WP_H_ */
