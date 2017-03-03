#include "SubsetPermutationSolver.h"
#include <algorithm>
#include <sstream>
//Helper function. Returns true if the key has been memoized.
bool SubsetPermutationSolver::_containsKey(string key) const {
    return _memoizer.count(key) != 0;
}

//Helper function. Turns a string into a list of characters.
list<char> SubsetPermutationSolver::_toList(const string& src) {
    return list<char>(begin(src), end(src));
}

//Helper function. Turns a list of characters into a string.
string SubsetPermutationSolver::_toString(const list<char>& src) {
    stringstream s;
    for_each(begin(src), end(src), [&s](const char& c) {
        s << c;
    });
    return s.str();
}
//Recursively solves the subset-permutation problem.
set<string> SubsetPermutationSolver::_solveCore(const list<char>& target) {
    string ofStr = _toString(target);

    //If we've already done this before
    if (_containsKey(ofStr)) {

        //Just returned the cached result.
        return _memoizer[ofStr];
    }

    else {
        set<string> finalResults;

        //For each item in the target collection.
        for (size_t cIdx = 0; cIdx < target.size(); cIdx++) {
            char head;
            list<char> tail;
            set<string> currentResults;

            //set it aside from the rest of the collection.
            //this item is the head, The rest of the collection is the tail.
            _reduceStep(target, cIdx, head, tail);

            //Find all subsets of the tail. 
            _solveStep(tail, currentResults);

            //Collect all the calculated subests in the final results.
            //for each subset, also store that subset prepended with the head. 
            _mergeStep(head, currentResults, finalResults);

        }
        //Store the results of this level.
        return _memoizer[ofStr] = finalResults;
    }
}
void SubsetPermutationSolver::_reduceStep(const list<char>& src, size_t headIdx, char& head, list<char>& tail) {
    tail.insert(begin(tail), begin(src), end(src));
    auto tailItr = begin(tail);
    advance(tailItr, headIdx);
    head = *tailItr;
    tail.erase(tailItr);
}

void SubsetPermutationSolver::_mergeStep(const char& head, const set<string>& currentResults, set<string>& finalResults) {
    //merge into the current results.
    finalResults.insert(begin(currentResults), end(currentResults));
    for_each(begin(currentResults), end(currentResults), [&finalResults, head](const string& result) {
        finalResults.emplace(head + result);
    });
}

void SubsetPermutationSolver::_solveStep(const list<char>& tail, set<string>& currentResults) {
    currentResults = _solveCore(tail);
}

SubsetPermutationSolver::SubsetPermutationSolver() {
    _memoizer[""] = set<string>({ "" });
}

SubsetPermutationSolver::SubsetPermutationSolver(const map<string, set<string>> initialMemoizationState) {
    _memoizer.insert(begin(initialMemoizationState), end(initialMemoizationState));

}

set<string> SubsetPermutationSolver::solve(const string& str) {

    return _solveCore(_toList(str));
}

void SubsetPermutationSolver::purge() {
    _memoizer.clear();
}