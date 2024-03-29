/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 20:19:19 by donglee           #+#    #+#             */
/*   Updated: 2021/06/22 20:27:30 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_HPP
# define TEST_HPP

# include <iostream>
# include <cmath>

# ifdef STD

#  include <list>
#  include <vector>
#  include <map>
#  include <stack>
#  include <queue>
#  include <set>

#  define LIST std::list
#  define VECTOR std::vector
#  define MAP std::map
#  define STACK std::stack
#  define QUEUE std::queue
#  define SET std::set
#  define MULTIMAP std::multimap
#  define MULTISET std::multiset

#  define MSG " ** std containers result! ** "

# else

#  include "../list.hpp"
#  include "../vector.hpp"
#  include "../map.hpp"
#  include "../stack.hpp"
#  include "../queue.hpp"

#  define LIST ft::list
#  define VECTOR ft::vector
#  define MAP ft::map
#  define STACK ft::stack
#  define QUEUE ft::queue
#  define SET ft::set
#  define MULTIMAP ft::multimap
#  define MULTISET ft::multiset

#  define MSG " ** my containers result! ** "

# endif

void test_list(void);
void test_vector(void);
void test_map(void);
void test_stack(void);
void test_queue(void);

#endif
