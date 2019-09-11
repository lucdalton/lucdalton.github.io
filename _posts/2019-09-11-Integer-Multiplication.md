---
layout: post
title:  "Integer multiplication modulo"
date:   2018-09-25 17:14:23 +0800
categories: programming 
permalink: multiplication
---

<!--![tree](/assets/tree.png){: .center-image }-->

This post takes a look at the AVL tree (named after inventors Adelson-Velsky and Landis).  AVL trees are self balancing binary search trees.  After each insertion/removal of a node it will remain balanced. 


<br>
<h3 id="red_black_comparison">AVL vs Red Black</h3>
An AVL tree will have better balancing than an RB tree, so lookup time will generally be better.  This is at the tradeoff of insertion/deletion performance.  So if lookup speed is more important, or there will be fewer insertions, an AVL tree will probably perform better.




