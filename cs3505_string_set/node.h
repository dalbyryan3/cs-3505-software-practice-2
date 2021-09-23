/* This node class is used to build drop lists for the
 * string_set class.
 *
 * Peter Jensen
 * September 18, 2020
 *
 * Implementation by Ryan Dalby 
 */

// Guard against double inclusion

#ifndef NODE_H
#define NODE_H

// You will use strings, and you may use vectors.

#include <string>
#include <vector>

namespace cs3505
{
  // We're in a namespace - declarations will be within this CS3505 
  // namespace.  (There are no definitions here, see node.cpp.)

  /* Node class for holding elements. */

  /* Note:  Do not alter the next line of code.  My tester will 
   * re-write the 'class node' to 'class node : private auditor' 
   * so that it inherits from my auditing class (harmlessly). 
   */

  class node
  {
    friend class string_set;   // This allows functions in string_set to access
			       //   private data (and constructor) within this class.
 
    private:
     node(const std::string & data); // this is the default constructor for creating a node with string data
     ~node(); // this is the destructor of a node which recursively deletes nodes which are connected to the node via next
     std::string data; // this holds the data of a node
     std::vector<node *> next; // this is a vector of node pointers which connect this node to other nodes
  };
}
		
#endif 
	
