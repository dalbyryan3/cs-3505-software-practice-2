/* A 'string set' is defined as a set of strings stored
 * in sorted order in a drop list.  See the class video
 * for details.
 *
 * For lists that do not exceed 2 ^ (max_width + 1)
 * elements, the add, remove, and contains functions are 
 * O(lg size) on average.  The operator= and get_elements 
 * functions are O(size).   
 * 
 * Peter Jensen
 * September 18, 2020
 *
 * Implementation by Ryan Dalby 
 */

#include "string_set.h"
#include <iostream>  // For debugging, if needed.
#include <stdlib.h> // srand and rand 

namespace cs3505
{
  /*******************************************************
   * string_set member function definitions
   ***************************************************** */
  
  /** Constructor:  The parameter indicates the maximum
    * width of the next pointers in the drop list nodes.
    * max_width must at least be 1
    */
  string_set::string_set(int max_width):
    max_width(max_width),size(0)
  {
    // Initialize head, its data value doesn't matter so just set to "" 
    this->head = new node("");


    // Set head to have a max_width next vector of node pointers, set to NULL, will point to something once values are added to the string_set. 
    this->head->next = std::vector<node *>(max_width, NULL);
  
  }

  
  /** Copy constructor:  Initialize this set
    * to contain exactly the same elements as
    * another set.
    */
  string_set::string_set(const string_set & other)
  {
    // Use overloaded =
    this->head = NULL;
    *this = other;
  }


  /** Destructor:  Release any memory allocated
    * for this object.
    */
  string_set::~string_set()
  {
    this->clean();
  }


  void string_set::add(const std::string & target)
  {
    // Declare prior vector to help do insertions or deletions
    // Set initial prior to point to the head node in each spot
    std::vector<node *> prior = std::vector<node *>(this->max_width, this->head);


    // Traverse to potential location
    for(int width = ((this->max_width)-1); width >= 0; width--)
    {
      // If we are not on the outermost width, start at the last prior end location 
      if (width != (this->max_width-1))
      {
        prior.at(width) = prior.at(width+1);
      }
      // Check if the next node is at end of list or past target
      while((prior.at(width)->next.at(width) != NULL) && (target.compare(prior.at(width)->next.at(width)->data) > 0))
      {
        prior.at(width) = prior.at(width)->next.at(width); 
      }
    }

    // We are now either just infront of the target and the next node will be the target
    // Exit method if next node is same as target 
    if ((prior.at(0)->next.at(0) != NULL) && (target.compare(prior.at(0)->next.at(0)->data) == 0))
    {
      return;
    }

    // Create new node with value
    node * node_to_add = new node(target); 
    // Randomly generate width of node
    int node_to_add_width = 1; // May want to move this to a global place and use random seed (like time)
    // Approx 50% chance of increasing width of this node by 1
    while(((rand()%10) < 5) && (node_to_add_width < this->max_width))  
    {
      node_to_add_width++;
    }
    // Set prior nodes to properly link to new node and have new node link properly to next nodes
    for(int i = 0; i < node_to_add_width; i++)
    {
      // Correctly set next pointers for added node
      node_to_add->next.push_back(prior.at(i)->next.at(i));
      
      // Correctly set prior nodes to point to added node
      prior.at(i)->next.at(i) = node_to_add;
    }

    // Increase size of string_set
    this->size++;

  }

  void string_set::remove(const std::string & target)
  {
    // Declare prior vector to help do insertions or deletions
    // Set initial prior to point to the head node in each spot
    std::vector<node *> prior = std::vector<node *>(this->max_width, this->head);


    // Traverse to potential location
    for(int width = ((this->max_width)-1); width >= 0; width--)
    {
      // If we are not on the outermost width, start at the last prior end location 
      if (width != (this->max_width-1))
      {
        prior.at(width) = prior.at(width+1);
      }
      // Check if the next node is at end of list or past target
      while((prior.at(width)->next.at(width) != NULL) && (target.compare(prior.at(width)->next.at(width)->data) > 0))
      {
        prior.at(width) = prior.at(width)->next.at(width); 
      }
    }

    // We are now either just infront of the target and the next node will be the target
    // Exit method if the target does not exit (also make sure that we are not looking at null before comparing to target) 
    if ((prior.at(0)->next.at(0) == NULL) || (target.compare(prior.at(0)->next.at(0)->data) != 0))
    {
      return;
    }

    // Current is the node to remove
    node * node_to_remove = prior.at(0)->next.at(0);
    int node_to_remove_width = node_to_remove->next.size();

    // Set prior nodes to properly link to the next nodes  and have new node link properly to next nodes
    for(int i = 0; i < node_to_remove_width; i++)
    {
      prior.at(i)->next.at(i) = node_to_remove->next.at(i);
      node_to_remove->next.at(i) = NULL;
    }

    // Decrease size of string_set
    this->size--;

    // Trigger deletion of node
    delete node_to_remove;

  }

  bool string_set::contains(const std::string & target) const
  {
    // Declare traversal helper variable current
    // Set initial current to the head node, begin traversal here
    node * current = this->head;

    // Traverse to potential location
    for(int width = ((this->max_width)-1); width >= 0; width--)
    {
      // Check if the next node is at end of list or past target
      while((current->next.at(width) != NULL) && (target.compare(current->next.at(width)->data) >= 0))
      {
        current = current->next.at(width);
      }
    }

    if(target.compare(current->data) == 0)
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  int string_set::get_size() const
  {
    return this->size;
  }

  string_set & string_set::operator= (const string_set & rhs)
  {
    // Avoid self assignment
    if (this == &rhs)
    {
      return *this;
    }

    // Clean out existing data
    clean();

    // Set member variables of this to rhs
    this->max_width = rhs.max_width;
    // Initialize head, its data value doesn't matter so just set to "" 
    this->head = new node("");
    // Set head to have a max_width next vector of node pointers, set to NULL, will point to something once values are added to the string_set. 
    this->head->next = std::vector<node *>(rhs.max_width, NULL);

    // Traverse all values of other and add to this
    node * rhs_current = rhs.head;
    while(rhs_current != NULL)
    {
      // Only add if we are not at head node
      if(rhs_current != rhs.head)
      {
        this->add(rhs_current->data);
      }
      rhs_current = rhs_current->next.at(0);
    } 
  }

  std::vector<std::string> string_set::get_elements()
  {
    // Declare traversal helper variable current
    // Set initial current to the head node, begin traversal here
    node * current = this->head;
    std::vector<std::string> elements= std::vector<std::string>();
    while(current->next.at(0) != NULL)
    {
      current = current->next.at(0);
      elements.push_back(current->data);
    } 
    return elements;
  }


  void string_set::clean()
  {
    // Tigger cleaning of all nodes, node destructor will clean subseqent nodes
    if (this->head != NULL)
    {
      delete this->head;
    }

    //Set default values 
    this->size = 0;
    this->max_width = 0;
    this->head = NULL;
  }
}

