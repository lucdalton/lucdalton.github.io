#include <iostream>

typedef struct node{
	int key;
	node* left;
	node* right;
}node;


class BinaryTree{
public:
	BinaryTree(){
		root = nullptr;
		values = new std::vector<int>();
	};
	~BinaryTree();

	void Insert(int key);
	node* Search(int key);

	void PrintTree();

private:
	void Insert(int key, node* n);
	node* root;

	void PrintTree(node*);

	std::vector<int> values;
};

void BinaryTree::Insert(int key, node* n){
	if(key < n->key){
		if(n->left != nullptr)
			Insert(key, n->left);
		else{
			// reached the end of the tree branch
			n->left = new node();
			n->left->key = key;
			n->left->left = nullptr;
			n->left->right = nullptr;
		}
	}else if(key > n->key){
		if(n->right != nullptr){
			Insert(key, n->right);
		}else{
			// reached end of tree branch
			n->right = new node();
			n->right->key = key;
			n->right->left = nullptr;
			n->right->right = nullptr;
		}
	}
}

void BinaryTree::Insert(int key){
	
	values.push_back(key);

	if(root == nullptr){
		root = new node();
		root->key = key;
		root->left = nullptr;
		root->right = nullptr;
		return;
	}

	Insert(key, root);
}

void BinaryTree::PrintTree(node* n){
//	printf("%i\n", n->key);
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

	return 0;
}

