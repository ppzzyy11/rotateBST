make:

hypercube:
	g++ hypercube.cpp -o hypercube -std=c++11

bst:
	g++ BinarySearchTree.cpp -o BinarySearchTree -std=c++11&& ./BinarySearchTree

bstrotate:
	g++ BinarySearchTreerotate.cpp -o BinarySearchTreerotate -std=c++11 && ./BinarySearchTreerotate
	
test:
		./hypercube 10000 permitted.txt

clean:
	rm hypercube BinarySearchTree BinarySearchTreerotate

VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

# run with valgrind to check for memory problems
testbst:
	 $(VALGRIND) ./BinarySearchTree
testbstrotate:
	 $(VALGRIND) ./BinarySearchTreerotate

