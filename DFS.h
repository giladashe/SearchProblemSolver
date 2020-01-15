//
// Created by giladasher on 14/01/2020.
//

#ifndef SEARCHPROBLEMSOLVER_DFS_H
#define SEARCHPROBLEMSOLVER_DFS_H

#include "Searcher.h"
#include <stack>

template<class Problem, class Solution>
class DFS : public Searcher<Problem, Solution> {
public:
	Solution search(Searchable<Problem> *searchable) override {
		stack<Problem> myStack;
		Searcher<Problem, Solution>::initialize(searchable);
		/*
		stack.push(root)
		while !stack.isEmpty()
		do
			node = stack.pop()
		for
		each
		node.childNodes
		do
			stack.push(stack)
		endfor
		// …
				endwhile
				*/
		return nullptr;

	}
};

#endif //SEARCHPROBLEMSOLVER_DFS_H
