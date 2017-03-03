#pragma once
#include <string>
#include <map>
#include <list>
#include <set>
using namespace std;
class SubsetPermutationSolver {
private:
    //Caches the results of the solve process so we don't have to redo it. 
    map<string, set<string>> _memoizer;

    //Helper function. Returns true if the key has been memoized.
    bool _containsKey(string key) const;

    //Helper function. Turns a string into a list of characters.
    static list<char> _toList(const string& src);

    //Helper function. Turns a list of characters into a string.
    static string _toString(const list<char>& src);

    //Takes the source and the index of the current head of the source and breaks src down
    //into head, the character with which to prefix each subresult, and tail, a list of characters
    //to recurse on. 
    void _reduceStep(const list<char>& src, size_t headIdx, char& head, list<char>& tail);

    //Solves a subproblem and stores the results in currentResults.
    void _solveStep(const list<char>& tail, set<string>& currentResults);

    //merges the results of solveStep into the final results. 
    void _mergeStep(const char& head, const set<string>& currentResults, set<string>& finalResults);

    //Does the actual solving computation recursivly.
    set<string> _solveCore(const list<char>& target);
public:

    //Creates a new SubsetPermutationSolver.
    SubsetPermutationSolver();

    //Creates a new SubsetPermutationSolver with the memoizer set to the given state. 
    //WARNING: The state should be valid.
    SubsetPermutationSolver(const map<string, set<string>> initialMemoizationState);

    //Solves the subset-permutation problem for the given string. 
    //Returns a set of all permutations of all subsets of the given string.
    set<string> solve(const string& string);

    //Resets the memoization. 
    void purge();
};