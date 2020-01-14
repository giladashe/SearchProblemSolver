
#ifndef SEARCHPROBLEMSOLVER_BESTFIRSTSEARCH_H
#define SEARCHPROBLEMSOLVER_BESTFIRSTSEARCH_H

#include "Searcher.h"
template <class Problem,class Solution>
class BestFirstSearch: public Searcher<Problem,Solution>{
public:
	Solution search(Searchable<Problem> *searchable) override {
		return nullptr;
	}

	int getNumberOfNodesEvaluated() override {
		return 0;
	}
};


#endif //SEARCHPROBLEMSOLVER_BESTFIRSTSEARCH_H
