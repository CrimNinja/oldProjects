// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <utility>
#include <limits>

// Type for town IDs
using TownID = std::string;
using Towns = std::vector<TownID>;

struct TownData
{
    TownData() {}
    TownData(const TownID& nID, const std::string& nName, const int& nX,
             const int& nY, const int& nTax) {
        id = nID;
        name = nName;
        x = nX;
        y = nY;
        tax = nTax;
    }
    TownID id;
    std::string name;
    int x;
    int y;
    int tax;
    TownID master;
    std::vector<TownID> vassal;
};

// Return value for cases where required town was not found
TownID const NO_ID = "----------";

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Return value for cases where name values were not found
std::string const NO_NAME = "-- unknown --";

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance: O(1)
    // Short rationale for estimate: size of a vector is a constant time operation.
    unsigned int size();

    // Estimate of performance: O(n)
    // Short rationale for estimate: clear operation in maps and vectors are linear
    void clear();

    // Estimate of performance: O(1) on average and O(n) in worst case
    // Short rationale for estimate: unordered maps have an average find and access
    // of constant time while their worst case would be linear in size.
    std::string get_name(TownID id);

    // Estimate of performance: O(1) on average and O(n) in worst case
    // Short rationale for estimate: unordered maps have an average find and access
    // of constant time while their worst case would be linear in size.
    std::pair<int, int> get_coordinates(TownID id);

    // Estimate of performance: O(1) on average and O(n) in worst case
    // Short rationale for estimate: unordered maps have an average find and access
    // of constant time while their worst case would be linear in size.
    int get_tax(TownID id);

    // Estimate of performance: O(1) on average and O(n) in worst case
    // Short rationale for estimate: unordered maps have an average find and access
    // of constant time while their worst case would be linear in size. The vassals
    // are always maintained in a sorted fashion so no sorting required.
    std::vector<TownID> get_vassals(TownID id);

    // Estimate of performance: O(1)
    // Short rationale for estimate: Just returns a vector.
    std::vector<TownID> all_towns();

    // Estimate of performance: O(logn) on average, O(n) in worst case
    // Short rationale for estimate: Adding to maps are logarthmic and adding to
    // unordered maps are linear in worst case.
    bool add_town(TownID id, std::string const& name, int x, int y, int tax);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Iterating through the alphamap is a linear
    // operation.
    bool change_town_name(TownID id, std::string const& newname);

    // Estimate of performance: O(n), O(1) if sorted order available
    // Short rationale for estimate: If a sorted list is not available, costs O(n),
    // but O(1) if there is a sorted list that is maintained. A sorted list is formed
    // once a sort function is called atleast once and no serious change is made.
    std::vector<TownID> towns_alphabetically();

    // Estimate of performance: O(n), O(1) if sorted order available
    // Short rationale for estimate: If a sorted list is not available, costs O(n),
    // but O(1) if there is a sorted list that is maintained. A sorted list is formed
    // once a sort function is called atleast once and no addition is made.
    std::vector<TownID> towns_distance_increasing();

    // Estimate of performance: O(nlogn), O(logn) if low number of towns with such name
    // Short rationale for estimate: If the number of towns with the said name is high,
    // the towns get added in a vector and are sorted. Which results in a O(nlogn)
    // situation where n is the number of towns of such name. It is logarthmic otherwise.
    std::vector<TownID> find_towns(std::string const& name);

    // Estimate of performance: O(n), O(1) if sorted order available
    // Short rationale for estimate: If a sorted list is not available, costs O(n),
    // but O(1) if there is a sorted list that is maintained. A sorted list is formed
    // once a sort function is called atleast once and no addition is made.
    TownID min_distance();

    // Estimate of performance: O(n), O(1) if sorted order available
    // Short rationale for estimate: If a sorted list is not available, costs O(n),
    // but O(1) if there is a sorted list that is maintained. A sorted list is formed
    // once a sort function is called atleast once and no addition is made.
    TownID max_distance();

    // Estimate of performance: O(n), O(1) if sorted order available
    // Short rationale for estimate: If a sorted list is not available, costs O(n),
    // but O(1) if there is a sorted list that is maintained. A sorted list is formed
    // once a sort function is called atleast once and no addition is made.
    TownID nth_distance(unsigned int n);

    // Estimate of performance: O(n), O(logn) if low number of vassals
    // Short rationale for estimate: Linear as it inserts the vassals in the
    // vector without compromising the order. If number of vassals is low, it
    // goes down to a logarthmic complexity.
    bool add_vassalship(TownID vassalid, TownID masterid);

    // Estimate of performance: O(logn), O(nlogn) in the worst case
    // Short rationale for estimate: if all the town masters are in a single chain,
    // the whole towns list have to be returned, resulting in an O(nlogn) situation.
    std::vector<TownID> taxer_path(TownID id);

    // Non-compulsory operations

    // Estimate of performance: O(n), O(nlogn) in the worst case
    // Short rationale for estimate: If in the odd case that the town has a master
    // and also a large amount of vassals, they are pushed to a vector and sorted
    bool remove_town(TownID id);

    // Estimate of performance: O(nlogn)
    // Short rationale for estimate: A list is made from scratch by inserting n
    // elements in a map.
    std::vector<TownID> towns_distance_increasing_from(int x, int y);

    // Estimate of performance: O(nlogn)
    // Short rationale for estimate: Depends on the amount of vassals and their vassals
    // But the functionality should be O(nlogn) on average.
    std::vector<TownID> longest_vassal_path(TownID id);

    // Estimate of performance: O(nlogn)
    // Short rationale for estimate: Depends on the amount of vassals and their vassals
    // But the functionality should be O(nlogn) on average.
    int total_net_tax(TownID id);

private:
    // Add stuff needed for your class implementation here
    bool alphalistUpdated = false;
    bool distlistUpdated = false;

    std::vector<TownID> townlist;
    unsigned int dist, tempn, tempn2;

    TownID tempID;

    std::unordered_map<TownID, TownData> townmap;
    std::multimap<std::string, TownID> alphamap;
    std::multimap<int, TownID> distmap;
    std::multimap<int, TownID> distmapxy;
    std::vector<std::vector<TownID>> idception;
    std::vector<TownID> alphalist;
    std::vector<TownID> distlist;
    std::vector<TownID> tlist;
    std::vector<TownID> vlist;
    std::unordered_map<TownID, TownData>::iterator mapIter;
    std::multimap<std::string, TownID>::iterator iter;
    std::multimap<int, TownID>::iterator iter2;

    void add_vassal_vectors(const TownID &id);
    int vassal_taxes(const TownID &id);
};

#endif // DATASTRUCTURES_HH
