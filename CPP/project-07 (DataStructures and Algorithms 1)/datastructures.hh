// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>

struct TownData
{
    std::string name;
    int x;
    int y;
};

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();


    // Estimate of performance: constant.

    // Short rationale for estimate: uses the std::vector::size function which is
    // of constant complexity.
    unsigned int size();

    // Estimate of performance: O(n).

    // Short rationale for estimate: Goes through elements one by one and removes the
    // pointers which is linear, and then clears the vectors, which is also linear.
    void clear();

    // Estimate of performance: constant.

    // Short rationale for estimate: just returns the towns list.
    std::vector<TownData*> all_towns();

    // Estimate of performance: constant time when adding for the first time and
    // O(log(n)) when adding after calling for sorted lists.

    // Short rationale for estimate: Smart adding procedure maintains the sorted
    // list if the sorted list exists through binary search for finding the index
    // to insert the element at.
    TownData* add_town(std::string const& name, int x, int y);

    // Estimate of performance: theta(n.log(n)) in the best and worst case, constant
    // if sorted list exists.

    // Short rationale for estimate: The sort function used is a variant of intro sort
    // similar to the C++ std lib implementation. It uses a modified quick sorting
    // algorithm to maintain the worst case condition at n.log(n).
    std::vector<TownData*> towns_alphabetically();

    // Estimate of performance: theta(n.log(n)) if sorted list doesn't exist, constant
    // if sorted list exists.

    // Short rationale for estimate: The sort function used is a variant of intro sort
    // similar to the C++ std lib implementation. It uses a modified quick sorting
    // algorithm to maintain the worst case condition at n.log(n).
    std::vector<TownData*> towns_distance_increasing();

    // Estimate of performance: O(n) if sorted list is unavailable and O(log(n))
    // if the sorted list is available.

    // Short rationale for estimate: If the alphabatically sorted list is available,
    // implements binary search to find the town.
    TownData* find_town(std::string const& name);

    // Estimate of performance: constant if sorted list exists, O(n.log(n)) otherwise.

    // Short rationale for estimate: Removed the introselect implementation
    // to maintain a sorted list as it is more efficient in the overall scenario.
    TownData* min_distance();

    // Estimate of performance: constant if sorted list exists, O(n.log(n)) otherwise.

    // Short rationale for estimate: Removed the introselect implementation to
    // maintain a sorted list as it is more efficient in the overall scenario.
    TownData* max_distance();

    // Estimate of performance: constant if sorted list exists, O(n.log(n)) otherwise.

    // Short rationale for estimate: Removed the introselect implementation
    // to maintain a sorted list as it is more efficient in the overall scenario.
    TownData* nth_distance(unsigned int n);

    // Non-compulsory operations

    // Estimate of performance: O(n).

    // Short rationale for estimate: Finding the element and erasing uses linear time.
    void remove_town(std::string const& town_name);

    // Estimate of performance: theta(n.log(n)) in the best and worst case.

    // Short rationale for estimate: The sort function used is a variant of
    // intro sort similar to the C++ std lib implementation. It uses a modified
    // quick sorting algorithm to maintain the worst case condition at n.log(n).
    std::vector<TownData*> towns_distance_increasing_from(int x, int y);

private:
    // Add stuff needed for your class implementation here
    std::vector<TownData*> towns;
    std::vector<TownData*> alphalist;
    std::vector<TownData*> distlist;

    bool distlistUpdated = false;
    bool alphalistUpdated = false;
    TownData* pivot;

    std::vector<TownData*> mysort(std::vector<TownData*> towns, const bool& alpha,
                                  const int& left, const int& right,
                                  const int& x = 0, const int& y = 0);
    void introsort(std::vector<TownData*> &towns, unsigned int maxDepth,
                   const int& left, const int& right, const bool& alpha,
                   const int& x = 0, const int& y = 0);
    void heapsort(std::vector<TownData*> &towns, const bool& alpha,
                  const int& left, const int& right,
                  const int& x = 0, const int& y = 0);
    void buildMaxHeap(std::vector<TownData*> &towns, const int& left,
                      const int& right, const bool& alpha, const int& x,
                      const int& y);
    void maxHeapify(std::vector<TownData*> &towns, const int& left,
                    const int& right, const bool& alpha, const int& x,
                    const int& y, const int& i, const int& n);
    void insertionsort(std::vector<TownData*> &towns, const bool& alpha,
                       const int& left, const int& right,
                       const int& x = 0, const int& y = 0);
    unsigned int part(std::vector<TownData*> &towns, const int& left,
                      const int& right, const bool& alpha, const int& x = 0,
                      const int& y = 0);
//    TownData* myselect(std::vector<TownData*> towns, const int& left,
//                       const int& right, unsigned int n);
//    TownData* introselect(std::vector<TownData*> towns, unsigned int left,
//                     unsigned int right, const unsigned int& n, unsigned int maxDepth);
//    TownData* heapselect(std::vector<TownData*> towns, unsigned int left,
//                         unsigned int right, unsigned int n);
//    void heapMove(std::vector<TownData*> towns,
//                  unsigned int first, unsigned int last);
    unsigned int binSearch(const int& x, const int& y, const bool& alpha = false,
                           std::string const& townName = "");

};

#endif // DATASTRUCTURES_HH
