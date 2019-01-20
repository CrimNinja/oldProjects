// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <utility>
#include <limits>
#include <set>
#include <map>
#include <unordered_map>

// Type for town IDs
using TownID = std::string;

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
    std::set<TownID> connections;
};

class revPriority
{
public:
  bool operator() (const TownID& town1, const TownID& town2) const
  {
    return town1 > town2;
  }
};

//struct weightedSort
//{
//    bool operator () (const std::pair<std::pair<TownID, TownID>, int>& road1,
//                      const std::pair<std::pair<TownID, TownID>, int>& road2) {
//        return road1.second < road2.second;
//    }
//} weightedObject;

inline bool roadSort(const std::pair<std::pair<TownID, TownID>, int>& road1,
              const std::pair<std::pair<TownID, TownID>, int>& road2) {
    return road1.second < road2.second;
}

// Return value for cases where required town was not found
TownID const NO_ID = "----------";

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Return value for cases where name values were not found
std::string const NO_NAME = "-- unknown --";

// Type for a coordinate (x, y)
using Coord = std::pair<int, int>;

// Return value for cases where coordinates were not found
Coord const NO_COORD{NO_VALUE, NO_VALUE};

// Type for distance
using Dist = int;

// Return value for cases where distance is unknown
Dist const NO_DIST = NO_VALUE;


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
    Coord get_coordinates(TownID id);

    // Estimate of performance: O(1) on average and O(n) in worst case
    // Short rationale for estimate: unordered maps have an average find and access
    // of constant time while their worst case would be linear in size.
    int get_tax(TownID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: unordered maps have an average find and access
    // of constant time while their worst case would be linear in size. The vassals
    // are always maintained in a sorted fashion so no sorting required.
    std::vector<TownID> get_vassals(TownID id);

    // Estimate of performance: O(n)
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

    // Estimate of performance: O(n)
    // Short rationale for estimate: Returns vector if present, else makes one by
    // iterating through the map which is already sorted.
    std::vector<TownID> towns_alphabetically();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Returns vector if present, else makes one by
    // iterating through the map which is already sorted.
    std::vector<TownID> towns_distance_increasing();

    // Estimate of performance: O(nlogn), O(n) if low number of towns with such name
    // Short rationale for estimate: If the number of towns with the said name is high,
    // the towns get added in a vector and are sorted. Which results in a O(nlogn)
    // situation where n is the number of towns of such name. It is logarthmic otherwise.
    // but returning a vector is linear, so linear in the end.
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

    // Estimate of performance: O(n)
    // Short rationale for estimate: Iterating through the roadmap is a linear
    // operation.
    std::vector<std::pair<TownID, TownID>> all_roads();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Returns by iterating though a vector in the main map.
    std::vector<TownID> get_roads_from(TownID id);

    // Estimate of performance: O(logn)
    // Short rationale for estimate: Adding to maps are logarthmic
    bool add_road(TownID town1, TownID town2);

    // Estimate of performance: O(n)
    // Short rationale for estimate: erasing from vector is linear, map is logarithmic
    bool remove_road(TownID town1, TownID town2);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Clearing vectors and maps are linear
    void clear_roads();

    // Estimate of performance: O(V + E)
    // Short rationale for estimate: BFS is used to find a route, and it has a complexity of
    // V + E where V is the number of vertices and E is the number of edges.
    std::vector<TownID> any_route(TownID fromid, TownID toid);

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

    // Estimate of performance: O(V + E)
    // Short rationale for estimate: BFS is used to find a route, and it has a complexity of
    // V + E where V is the number of vertices and E is the number of edges.
    std::vector<TownID> least_towns_route(TownID fromid, TownID toid);

    // Estimate of performance: O(E logV)
    // Short rationale for estimate: Dijkstra's algorithm was used to find the shortest path. But,
    // since we did not use a Matrix and used adjacent list to traverse the graph through BFS, the
    // complexity of the algorithm was reduced to O(E log V) instead of O(n^2)
    std::vector<TownID> shortest_route(TownID fromid, TownID toid);

    // Estimate of performance: O(V + E)
    // Short rationale for estimate: DFS is used to find the cycle, and it has a complexity of
    // V + E where V is the number of vertices and E is the number of edges.
    std::vector<TownID> road_cycle_route(TownID startid);

    // Estimate of performance: O(E logV)
    // Short rationale for estimate: Kruskal's algorithm was implemented to create a minimum spanning
    // tree, and since this operation has a higher complexity than the other operations (which are
    // linear), the final complexity is O(E logV)
    Dist trim_road_network();

private:
    // Add stuff needed for your class implementation here
    bool alphalistUpdated = false;
    bool distlistUpdated = false;

    unsigned int dist;
    int tempo = 0;
    int tempo2 = 0;

    TownID tempID;
    TownID start;

    std::map<TownID, std::set<TownID>> roadmap;

    std::unordered_map<TownID, TownData> townmap;
    std::multimap<std::string, TownID> alphamap;
    std::multimap<int, TownID> distmap;
    std::vector<std::vector<TownID>> idception;
    std::vector<TownID> alphalist;
    std::vector<TownID> distlist;
    std::vector<TownID> vlist;
    std::unordered_map<TownID, TownData>::iterator mapIter;
    std::multimap<std::string, TownID>::iterator iter;
    std::multimap<int, TownID>::iterator iter2;

    std::map<TownID, TownID> parentT;

    int counter;

    void add_vassal_vectors(const TownID &id);
    int vassal_taxes(const TownID &id);

    TownID findSet(const TownID& town);
    void UnionSet(const TownID& town1, const TownID& town2);

    bool isCyclic(TownID id, std::map<TownID, bool>& visited,
                  TownID parent, TownID *routeUtil);

};

#endif // DATASTRUCTURES_HH
