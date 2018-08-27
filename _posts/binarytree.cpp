#include <iostream>

typedef struct node{
	int key;
	node* left;
	node* right;

	int lweight;
	int rweight;
	int height;
}node;

node* NewNode(){
	node* n = new node();
	n->left = nullptr;
	n->right = nullptr;
	n->lweight = 0;
	n->rweight = 0;
	n->height = 0;
	return n;
}

class BinaryTree{
public:
	BinaryTree(){
		root = nullptr;
	};
	~BinaryTree();

	void Insert(int key);
	node* Search(int key);

	void PrintTree();

private:
	//void Insert(int key, node* n);

	void Insert(int key, node* n, int height);

	node* root;

	void PrintTree(node*);

	void BalanceRight(node*);
	void BalanceLeft(node*);

	void RotateRight(node*);
	void RotateLeft(node*);

	void Shift(node*, node*);

};
/*
void BinaryTree::Insert(int key, node* n){
	if(key < n->key){
		if(n->left != nullptr)
		{
			n->lweight++;
			Insert(key, n->left);			
		}
		else{
			// reached the end of the tree branch
			n->left = NewNode();
			n->left->key = key;
		}
	}else if(key > n->key){
		if(n->right != nullptr){
			n->rweight++;
			Insert(key, n->right);
		}else{
			// reached end of tree branch
			n->right = NewNode();
			n->right->key = key;
		}
	}

}
*/

void BinaryTree::Insert(int key){
	
	if(root == nullptr){
		root = NewNode();
		root->key = key;
		return;
	}

	Insert(key, root, root->height);
	
	/*
	node* pc = root;
	int depth = 0;
	while(pc!=nullptr){
		pc = Insert(key, pc);
		depth++;	
	}*/
}


void BinaryTree::Insert(int key, node* n, int height){
	/*
	if(n==nullptr){
		// end of branch
		n = NewNode();
		n->key = key;
	}
	else if(key < n->key){
		n->left = Insert(key, n->left);
	}else if(key > n->key){
		n->right = Insert(key, n->right);
	}

	node* nb = root;
	int depth = 0;
	while(nb!=nullptr){

	}
	*/
	/*
	if(key < n->key){
		if(n->left==nullptr){
			n->left = NewNode();
			n->left = 
		}
		return n->left;
	}
	return n->right;
	*/

	if(key < n->key){
		if(n->left==nullptr){
			n->left = NewNode();
			n->left->key = key;
			n->left->height = height;			
		}else{
			Insert(key, n->left, height+1);
		}
	}else if(key > n->key){
		if(n->right==nullptr){
			n->right = NewNode();
			n->right->key = key;
			n->right->height = height;
		}else{
			Insert(key, n->right, height+1);
		}
	}

	/* without repeating code
	node** k;
	if(key < n->key)
		k = &(n->left);
	else
		k = &(n->right);
	if(*k==nullptr){
		*k = NewNode();
		(*k)->key = key;
		(*k)->depth = depth;
	}else{
		Insert(key, (*k), depth++);
	}
	*/

}


void BinaryTree::BalanceRight(node* n){
	// 
}

void BinaryTree::BalanceLeft(node* n){

}

void BinaryTree::RotateRight(node* n){

}

void BinaryTree::RotateLeft(node* n){

}


void Shift_0(node* n, node* parent){
	// case 0
	if(parent->left!=nullptr){
		if(parent->left->key == n->key){
			// node is on the left
			parent->left = n->left;
			n->left->right = n;
			n->left = nullptr;
		}		
	}
	else{
		// node is on the right
		parent->right = n->left;
		n->left->right = n;
		n->left = nullptr;

	}
}

void Shift_1(node* n, node* parent){
	// case 1
	if(parent->left!=nullptr){
		if(parent->left->key == n->key){
			// node is on the left
			parent->left = n->left->right;
			n->left->right->right = n;
			n->left->right->left = n->left;

			n->left->right = nullptr;
			n->left = nullptr;
			n->right = nullptr;

		}		
	}
	else{
		// node is on the right
		parent->right = n->left->right;
		n->left->right->right = n;
		n->left->right->left = n->left;

		n->left->right = nullptr;
		n->left = nullptr;
		n->right = nullptr;
	}	
}

void BinaryTree::Shift(node* n, node* parent){
	/*
		  n            1
		 / \            \
	    2   5			 5		5		3			
		   /			/		 \	     \
		  4			   3		  7	      4
		 /				\		 /	       \
		3				 4		6	        5
     case 0         case 1      case2     case3
	*/

	int first = 0;
	int second = 0;

	int p = 0;

	if(parent->left->key == n->key){
		// node is on the left
		p=0;
	}else{
		// node is on the right
		p=1;
	}


	if(n->left != nullptr){
		if(n->left->left != nullptr){
			// case 0
			/*
			if(p==0){
				parent->left = n->left;
				n->left->right = n;
				n->left = nullptr;
			}else{
				parent->right = n->left;
				n->left->right = n;
				n->left = nullptr;				
			}
			*/
			Shift_0(n, parent);
		}else{
			// case 1
			if(p==0){
				parent->left = n->left->right;

			}
		}
	}else{
		if(n->right->left != nullptr){
			// case 2
		}else{
			// case 3
		}
	}
}

void PrintNode(node* n){
	std::cout << "key: " << n->key << " height: " << n->height;
	if(n->left!=nullptr){
		std::cout << " :left " << n->left->key;
	}
	else{
		std::cout << " :left null";
	}

	if(n->right!=nullptr){
		std::cout << " right: " << n->right->key;
	}
	else{
		std::cout << " right: null";
	}
	std::cout << "\n";
}

void BinaryTree::PrintTree(node* n){
//	printf("%i\n", n->key);

	PrintNode(n);
	if(n->left!=nullptr)
		PrintNode(n->left);

	if(n->right!=nullptr)
		PrintNode(n->right);

	/*

	std::cout << "key: " << n->key << "\n";
	if(n->left == nullptr){
		std::cout << " end branch left";
	}else{
		PrintTree(n->left);
	}
	
	if(n->right == nullptr){
		std::cout << " end branch right";
	}else{
		PrintTree(n->right);
	}
	*/


}

void BinaryTree::PrintTree(){
	PrintTree(root);
}



int main(){
	
	BinaryTree* binaryTree = new BinaryTree();
	binaryTree->Insert(2);
	binaryTree->Insert(3);
	binaryTree->Insert(1);
	binaryTree->Insert(5);
	binaryTree->Insert(10);

	binaryTree->PrintTree();
	

	/*
	node* n1 = NewNode();
	node* n2 = NewNode();
	node* n3 = NewNode();
	node* n4 = NewNode();

	n1->key = 1;
	n2->key = 5;
	n3->key = 4;
	n4->key = 3;

	n1->right = n2;
	n2->left = n3;
	n3->left = n4;
	
	//std::cout << n1->key << " :left " << n1->left->key << " right: " << n1->right->key; //<< "\n";

	PrintNode(n1);
	PrintNode(n2);
	PrintNode(n3);
	PrintNode(n4);

	Shift_0(n2, n1);
	
	std::cout << "\n";
	


	PrintNode(n1);
	PrintNode(n2);
	PrintNode(n3);
	PrintNode(n4);

	*/


	return 0;
}

