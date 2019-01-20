// Datastructures.cc

// Remove the numberOfTowns and rechect the performance?

#include "datastructures.hh"

//#include <iostream>
#include <utility>
#include <cmath>
#include <random>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

//template <class S> void Swap(S& name1, S& name2) {
//    // Basic swapping of two values.
//    S temp_ = name1;
//    name1 = name2;
//    name2 = temp_;
//}



Datastructures::Datastructures()
{

}

Datastructures::~Datastructures()
{
    for (unsigned int i = 0; i < towns.size(); ++i) {
        delete towns[i];
    }

    towns.clear();
    distlist.clear();
    alphalist.clear();
    distlistUpdated = false;
    alphalistUpdated = false;
    //    delete pivot;
}

unsigned int Datastructures::size()
{
    return towns.size();
}

void Datastructures::clear()
{
    for (unsigned int i = 0; i < towns.size(); ++i) {
        delete towns[i];
    }

    towns.clear();
    distlist.clear();
    alphalist.clear();
    alphalistUpdated = false;
    distlistUpdated = false;
}

std::vector<TownData*> Datastructures::all_towns()
{
    return towns;
}

TownData* Datastructures::add_town(const std::string& name, int x, int y)
{
    TownData* town = new TownData;

    town->name = name;
    town->x = x;
    town->y = y;

    towns.push_back(town);
    //    distlistUpdated = false;
    if (distlist.size() > 0) {
        unsigned int n = binSearch(x, y);
        if (n == distlist.size() - 1)
            distlist.push_back(town);
        else
            distlist.insert(distlist.begin() + n, town);
    }

    if (alphalist.size() > 0) {
        unsigned int n = binSearch(x, y, true, name);
        if (n == alphalist.size() - 1)
            alphalist.push_back(town);
        else
            alphalist.insert(alphalist.begin() + n, town);
    }
    return town;
}

std::vector<TownData*> Datastructures::towns_alphabetically()
{
    if (towns.size() == 0)
        return {};

    if (alphalistUpdated)
        return alphalist;

    alphalistUpdated = true;
    alphalist = mysort(towns, true, 0, towns.size() - 1);

    return alphalist;
}

std::vector<TownData*> Datastructures::towns_distance_increasing()
{
    if (towns.size() == 0)
        return {};

    if (distlistUpdated)
        return distlist;

    distlistUpdated = true;
    distlist = mysort(towns, false, 0, towns.size() - 1);

    return  distlist;
}

TownData* Datastructures::find_town(std::string const& name)
{
    if (alphalistUpdated) {
        unsigned int n = binSearch(0, 0, true, name);
        if (alphalist[n]->name == name)
            return alphalist[n];
    } else {
        for (unsigned int i = 0; i < towns.size(); ++i) {
            if (towns[i]->name == name)
                return towns[i];
        }
    }

    return nullptr;
}

TownData* Datastructures::min_distance()
{

    if (towns.size() == 0)
        return nullptr;
    else if (distlistUpdated || distlist.size() == 1)
        return distlist[0];
    else {
        distlist = mysort(towns, false, 0, towns.size() - 1);
        distlistUpdated = true;
        return distlist[0];
    }
}

TownData* Datastructures::max_distance()
{

    if (towns.size() == 0)
        return nullptr;
    else if (distlistUpdated || distlist.size() == 1)
        return distlist[towns.size() - 1];
    else {
        distlist = mysort(towns, false, 0, towns.size() - 1);
        distlistUpdated = true;
        return distlist[distlist.size() - 1];
    }
}

TownData* Datastructures::nth_distance(unsigned int n)
{
    if (towns.size() < n || n == 0)
        return nullptr;
    else if (distlistUpdated)
        return distlist[n - 1];
    else {
        distlist = mysort(towns, false, 0, towns.size() - 1);
        distlistUpdated = true;
        return distlist[n - 1];
    }
}

void Datastructures::remove_town(const std::string& town_name)
{
    for (unsigned int i = 0; i < towns.size(); ++i) {
        if (towns[i]->name == town_name) {
            delete towns[i];
            towns.erase(towns.begin() + i);
            distlistUpdated = false;
            alphalistUpdated = false;
        }
    }
}

std::vector<TownData*> Datastructures::towns_distance_increasing_from(int x, int y)
{
    return mysort(towns, false, 0, towns.size() - 1, x, y);
}



std::vector<TownData*> Datastructures::mysort(std::vector<TownData *> towns, const bool& alpha,
                                              const int& left, const int& right,
                                              const int& x, const int& y) {
    unsigned int maxDepth = 2*log2(towns.size());
    introsort(towns, maxDepth, left, right, alpha, x, y);
    return towns;
}

void Datastructures::introsort(std::vector<TownData *> &towns, unsigned int maxDepth,
                               const int& left, const int& right, const bool& alpha,
                               const int& x, const int& y) {
    if (right - left <= 16) {
        insertionsort(towns, alpha, left, right, x, y);
    } else if (maxDepth == 0) {
        heapsort(towns, alpha, left, right, x, y);
    } else {
        if (left < right) {
            unsigned int p = part(towns, left, right, alpha, x, y);
            introsort(towns, maxDepth - 1, left, p - 1, alpha, x, y);
            introsort(towns, maxDepth - 1, p + 1, right, alpha, x, y);
        }
    }
}

void Datastructures::maxHeapify(std::vector<TownData *> &towns, const int &left,
                                const int &right, const bool& alpha, const int &x,
                                const int &y, const int& i, const int &n) {

    int largest;
    int l = 2*i;
    int r = 2*i + 1;

    if (alpha) {
        if (l <= n && towns[l]->name > towns[i]->name)
            largest = l;
        else
            largest = i;
        if (r <= n && towns[r]->name > towns[largest]->name)
            largest = r;
    } else {
        if (l <= n && abs(towns[l]->x - x) + abs(towns[l]->y - y) >
                abs(towns[i]->x - x) + abs(towns[i]->y - y))
            largest = l;
        else
            largest = i;
        if (r <= n && abs(towns[r]->x - x) + abs(towns[r]->y - y) >
                abs(towns[largest]->x - x) + abs(towns[largest]->y - y))
            largest = r;
    }
    if (largest != i) {
        std::swap(towns[i], towns[largest]);
        maxHeapify(towns, left, right, alpha, x, y, largest, n);
    }
}

void Datastructures::buildMaxHeap(std::vector<TownData *> &towns, const int &left,
                                  const int &right, const bool& alpha, const int &x,
                                  const int &y) {
    int n = right - left;
    for (int i = (right - left)/2; i >= 1; --i) {
        maxHeapify(towns, left, right, alpha, x, y, i, n);
    }
}

void Datastructures::heapsort(std::vector<TownData *> &towns, const bool& alpha,
                              const int& left, const int& right,
                              const int& x, const int& y) {
    int n = right - left;
    buildMaxHeap(towns, left, right, alpha, x, y);
    for (int i = n; i >= left + 1; --i) {
        std::swap(towns[i], towns[1]);
        n -= 1;
        maxHeapify(towns, left, right, alpha, x, y, 1, n);
    }
}

void Datastructures::insertionsort(std::vector<TownData *> &towns, const bool& alpha,
                                   const int& left, const int& right,
                                   const int& x, const int& y) {
    int j;

    for (int i = left; i <= right; ++i) {
        j = i;
        if (alpha) {
            while (j > 0 && towns[j]->name < towns[j-1]->name){
                std::swap(towns[j], towns[j-1]);
                --j;
            }
        } else {
            while (j > 0 && abs(towns[j]->x - x) + abs(towns[j]->y - y) <
                   abs(towns[j - 1]->x - x) + abs(towns[j - 1]->y - y)){
                std::swap(towns[j], towns[j-1]);
                --j;
            }
        }
    }
}

unsigned int Datastructures::part(std::vector<TownData *> &towns, const int &left,
                                  const int &right, const bool& alpha, const int& x,
                                  const int& y) {

    //    int pt = random_in_range(left, right);
    int pt = left + (right - left)/2;
    pivot = towns[pt];
    std::swap(towns[left], towns[pt]);
    int i = left + 1;
    int j = right;

    if (alpha) {
        while (i <= j) {
            while (i <= j && towns[i]->name <= pivot->name) {
                ++i;
            }
            while (i <= j && towns[j]->name > pivot->name) {
                --j;
            }
            if (i < j) {
                std::swap(towns[i], towns[j]);
            }
        }
    } else {
        while (i <= j) {
            while (i <= j && abs(towns[i]->x - x) + abs(towns[i]->y - y) <=
                   abs(pivot->x - x) + abs(pivot->y - y)) {
                ++i;
            }
            while (i <= j && abs(towns[j]->x - x) + abs(towns[j]->y - y) >
                   abs(pivot->x - x) + abs(pivot->y - y)) {
                --j;
            }
            if (i < j) {
                std::swap(towns[i], towns[j]);
            }
        }
    }
    std::swap(towns[left], towns[i-1]);
    return i - 1;
}

//TownData* Datastructures::myselect(std::vector<TownData *> towns, const int &left,
//                                   const int &right, unsigned int n) {
//    n -= 1;
//    if (left == right) {
//        return towns[right];
//    } else {
//        unsigned int maxDepth = 2*log2(right - left);
//        return introselect(towns, left, right, n, maxDepth);
//    }
//}

//TownData* Datastructures::introselect(std::vector<TownData *> towns, unsigned int left,
//                                      unsigned int right, const unsigned int &n, unsigned int maxDepth) {
//    while (right - left > 3) {
//        if (maxDepth == 0) {
//            return heapselect(towns, left, right, n);
//        }
//        --maxDepth;

//        unsigned int pt = part(towns, left, right, false);
//        if (pt <= n) {
//            left = pt;
//        } else {
//            right = pt;
//        }
//    }
//    insertionsort(towns, false, left, right);
//    return towns[n];
//}

//TownData* Datastructures::heapselect(std::vector<TownData *> towns, unsigned int left,
//                                     unsigned int right, unsigned int n) {
//    unsigned int p = (right - left)/2;
//    for (int i = p; i >= 0; --i){
//        heapMove(towns, i, right);
//    }

//    unsigned int limit = right - n + 1;
//    for (unsigned int i = right; i > limit; --i) {
//        if (abs(towns[0]->x) + abs(towns[0]->y) > abs(towns[i]->x) + abs(towns[i]->y)) {
//            std::swap(towns[0], towns[i]);
//            heapMove(towns, 0, i - 1);
//        }
//    }
//    return towns[0];
//}

//void Datastructures::heapMove(std::vector<TownData *> towns, unsigned int first, unsigned int last) {
//    unsigned int largest = 2*first + 1;

//    while (largest <= last) {
//        if (largest < last && abs(towns[largest]->x) + abs(towns[largest]->y) >
//                abs(towns[largest + 1]->x) + abs(towns[largest + 1]->y)) {
//            ++largest;
//        }
//        if (abs(towns[first]->x) + abs(towns[first]->y) <
//                abs(towns[largest]->x) + abs(towns[largest]->y)) {
//            std::swap(towns[first], towns[largest]);
//            first = largest;
//            largest = 2*first + 1;
//        } else
//            return;
//    }
//}

unsigned int Datastructures::binSearch(const int &x, const int &y, const bool &alpha,
                                       const std::string &townName) {
    int low = 0, high = distlist.size() - 1;
    int mid;

    if (alpha) {
        while (low < high) {
            mid = low + (high - low)/2;
            if (alphalist[mid]->name == townName)
                return mid;
            else if (alphalist[mid]->name > townName)
                high = mid;
            else
                low = mid + 1;
        }
    } else {
        while (low < high) {
            mid = low + (high - low)/2;
            if (abs(distlist[mid]->x) + abs(distlist[mid]->y) ==
                    abs(x) + abs(y))
                return mid;
            else if (abs(distlist[mid]->x) + abs(distlist[mid]->y) >
                     abs(x) + abs(y))
                high = mid;
            else
                low = mid + 1;
        }
    }

    return low;
}
