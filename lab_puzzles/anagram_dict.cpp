/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;
using std::sort;
using std::pair;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
	ifstream wordsFile(filename);
	if (wordsFile.is_open()) 	
	{
		string theWord;
      /* Reads a line from `wordsFile` into `word` until the file ends. */
		while (getline(wordsFile, theWord)) 
		{
        		string sortedWord(theWord);
        		sort(sortedWord.begin(), sortedWord.end());
        		dict[sortedWord].push_back(theWord);
      		}
    	}
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
	for (string theWord : words)
	{
		string sortedWord(theWord);
		sort(sortedWord.begin(), sortedWord.end());
		dict[sortedWord].push_back(theWord);
	}
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
	string theWord(word);
	sort(theWord.begin(), theWord.end());
	if (dict.count(theWord) != 0)
		return dict.at(theWord);
	else    
		return vector<string>();
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
	vector<vector<string>> all_anagrams;
	for (pair<string, vector<string>> theValue : dict)
	{
		vector<string> anagrams = theValue.second;
		if (anagrams.size() >= 2)
			all_anagrams.push_back(anagrams);
	}
		return all_anagrams;
}
