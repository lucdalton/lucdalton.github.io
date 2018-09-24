---
layout: post
title:  "Self balancing Binary Search Trees"
date:   2018-05-25 17:14:23 +0800
categories: programming c++
permalink: avltrees
---

![tree](/assets/tree.png){: .center-image }

The repository used for this post can be found here: [AVL Tree](https://github.com/lucdalton/AVLTree)






Binary search trees are an efficient data structure for organising data that needs to be searched.  They come in many varieties and variations, the one looked at in this post is the AVL tree (named after inventors Adelson-Velsky and Landis).  AVL trees are self balancing trees, meaning that after any insertion or deletion of a node, it will remain balanced.  Any data type which can be ordered can be arranged in this data structure.  The tree consists of nodes, starting from the root node at the top of the tree.  A node consists of a key, an optional value, and 2 children.  


For this example, `int` data type is used for simplicity.
{% highlight c %}
typedef struct node{
    int key;
    node* left;
    node* right;
    int height;
}node;
{% endhighlight %}


A value can be searched for starting at the root node and traversing the tree.  Each left node will have a lower key value than it's parent node, and each right node will have a larger key value than it's parent node.  Take an example tree:

{% highlight ruby %}

        4
     /    \
    2      6
   / \    / \
  1   3  5   7

{% endhighlight %}

Searching for key 5, starting at the root.  5 > 4 so move to the right node. 5 < 6 so move to the left node. 6 = 6 so we have found the key, and it only took 2 comparisons to find.  If the data was arranged randomly we'd have to compare against possibly each value.


A binary seach tree has a lookup time of O(log(n)), as the depth of the tree will be equal to at most log_2(n).  However, if the tree becomes unbalanced it can become worst case lookup O(n).  For example, the following tree

{% highlight ruby %}

      4
     / 
    3
   /
  2
 /
1

{% endhighlight %}

isn't particularly useful.  It's become a linked list.  Searching for the node with key=1 would take 4 passes.

AVL trees are one possible binary search tree data structure which keeps the tree balanced.  After each node insertion, the structure of the tree is updated to keep the balance.  Similarly, when a node is removed the tree structure is updated.  This is done by comparing the subtree height after each insertion.  A re balancing of the tree is required if the absolute difference in height between the left and right subtrees is greater than 1.  For example,

{% highlight ruby %}

     3
    /
   2
  / 
 1



{% endhighlight %}

Looking at the node with key 3, the right subtree has height 0 and the left subtree has height 2.  
In this case the height difference of the subtrees is `|0-2| = 2`, so a rebalance is required.  

{% highlight ruby %}

    3                   2
   /                   / \
  2         ->        1   3
 /
1

{% endhighlight %}




<h2>Node Insertion</h2>
Node insertion is pretty easy.  Assuming that the key doesn't already exist somewhere in the tree, you traverse the tree the same as doing a search and find the lowest node in the tree which is closest to the key you're inserting.  For example,

{% highlight ruby %}

  2       add 4       2
 / \       ->        / \
1   3               1   3
                         \
                          4
{% endhighlight %}



In This case, the tree remains balanced.  We still need to deal with the case when the tree becomes unbalanced after the insertion.  There are actually only 4 cases where rebalancing is required after insertion.

<h1>Case 1: "left left"</h1>
Example:
{% highlight ruby %}

      5       add 1        5        shiftLeft(node3)             5
     / \       ->        /  \              ->                   / \
    3   6               3    6                                 2   6
   /                   /                                      / \
  2                   2                                      1   3
                     /                    
                    1                          
{% endhighlight %}

The left node of 5 is height 3, the right side is height 1.  The rule is the the difference can be at most 1, so a rebalance is required.  The node inserted is n->left->left (hence "left left") where n is a pointer to node with key 5.  The `shiftLeft` function shifts the left side of the node up a level:

{% highlight C %}
node* shiftLeft(node* n){
/*
         n                 2
        / \               / \
       2   T1     ->     1   n
      /\                    / \
     1  T2                 T2   T1
*/
    node* p = n->left;
    n->left = n->left->right;
    p->right = n;
    n->height = max(height(n->left), height(n->right)) + 1;
    return p;
}
{% endhighlight %}



<br>
<br>

<h1>Case 2: "left right"</h1>
Example:
{% highlight ruby %}

      5       add 3        5        shiftLeft_v(node2)           5
     / \       ->        /  \              ->                   / \
    2   6               2    6                                 2   6
   /                   /                                      / \
  1                   1                                      1   3
                       \                   
                        3                       
{% endhighlight %}

Similar to case 1, except the node inserted is "left right" to the node with key 2.

{% highlight C %}

node* shiftLeft_v(node* n){
/*
         n                 n              2
        /                 /              / \
       0        ->       2      ->      0   n
        \               /
         2             0
 */
    n->left = shiftRight(n->left);
    return shiftLeft(n);
}
{% endhighlight %}

<br>
<br>

<h1>Case 3: "right right"</h1>
The same as case 1 except to the right.

{% highlight C %}

node* shiftRight(node* n){
/*
      n                        2
     / \                      / \
    T1  2         ->         n   3
       / \                  / \
      T2  3                T1 T2
     
*/
    node* p = n->right;
    n->right = n->right->left;
    p->left = n;
    n->height = max(height(n->left), height(n->right)) + 1;
    return p;
}

{% endhighlight %}


<br>
<br>

<h1>Case 4: "right left"</h1>
The same as case 2 except the other way around.

{% highlight C %}

node* shiftRight_v(node* n){
/*
       n                 n                  0
        \                 \                / \
         2        ->       0      ->      n   2
        /                   \
       0                     2
     
*/
    n->right = shiftLeft(n->right);
    return shiftRight(n);
}

{% endhighlight %}


<h2>Deleting a node</h2>
Removing a node from the tree is a little more complicated, but not much.  In the example code it is implemented recursively similar to the node insertion function.  Once the node n to be removed has been found through traversing the tree, the smallest node in its right subtree is found, and switches key value with it.  The tree is then traversed from that node, to remove the node that has just replaced it.

{% highlight C %}

node* BinaryTree::Remove(int key, node* n){
    
    node* temp;
    
    if(n==nullptr)
        return nullptr;
    
    if(key < n->key){
        n->left = Remove(key, n->left);
    }
    else if(key > n->key){
        n->right = Remove(key, n->right);
    }
    // when control reaches here we have arrived at the node to remove
    else if(n->right && n->left){
        
        // node has 2 children
        temp = minNode(n->right);
        n->key = temp->key;
        n->right = Remove(n->key, n->right);
        
    }else{
       
        // node has 1 or 0 children
        temp = n;
        if(n->left==nullptr){
            n = n->right;
        }else if(n->right==nullptr){
            n = n->left;
        }else{
            return nullptr;
        }
        delete temp;
    }
    
    if(n==nullptr)
        return n;
    
    //n->height = max(height(n->left), height(n->right))+1;
    n->height = maxHeight(n->left, n->right)+1;

    // check node balancing
    if(height(n->left) - height(n->right) == REBALANCE_HEIGHT)
    {
        // left left case
        if(height(n->left->left) - height(n->left->right) == REBALANCE_HEIGHT-1)
            return shiftLeft(n);
        // left right case
        else
            return shiftLeft_v(n);
    }
    // If right node is deleted, left case
    else if(height(n->right) - height(n->left) == REBALANCE_HEIGHT)
    {
        // right right case
        if(height(n->right->right) - height(n->right->left) == REBALANCE_HEIGHT-1)
            return shiftRight(n);
        // right left case
        else
            return shiftRight_v(n);
    }
    return n;
}

{% endhighlight %}
