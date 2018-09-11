#include "rotate_gtest_class.h"

TEST_F(RotateTest, Test13_TransformLeftLLToRightLL) 
{
	using Key = int;
	using Value = double;
	InsSeq<Key, Value> ins1{
		std::make_pair(1, 0.0),
		std::make_pair(2, 0.0),
		std::make_pair(3, 0.0),
		std::make_pair(4, 0.0),
	};
	InsSeq<Key, Value> ins2{
		std::make_pair(4, 4.0),
		std::make_pair(3, 3.0),
		std::make_pair(2, 2.0),
		std::make_pair(1, 1.0),
	};
	NodeSeq<Key, Value> seq1{
		NodeValidation<Key, Value>{1, 0.0, 4, false, true},
		NodeValidation<Key, Value>{2, 0.0, 3, false, true},
		NodeValidation<Key, Value>{3, 0.0, 2, false, true},
		NodeValidation<Key, Value>{4, 0.0, 1, false, false},
	};
	NodeSeq<Key, Value> seq2{
		NodeValidation<Key, Value>{1, 1.0, 4, false, true},
		NodeValidation<Key, Value>{2, 2.0, 3, false, true},
		NodeValidation<Key, Value>{3, 3.0, 2, false, true},
		NodeValidation<Key, Value>{4, 4.0, 1, false, false},
	};

	InheritedRotate<Key, Value> t1, t2;
	InsertInTree(t1, ins1);
	InsertInTree(t2, ins2);
	t1.transform(t2);
	TreeStructureCheck(t1.getRoot(), seq1, true);
	TreeStructureCheck(t2.getRoot(), seq2, true);
}