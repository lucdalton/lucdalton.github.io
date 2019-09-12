---
layout: post
title:  "Integer multiplication modulo"
date:   2018-09-25 17:14:23 +0800
categories: programming 
permalink: multiplication
---

<!--![tree](/assets/tree.png){: .center-image }-->

This post takes a look at the AVL tree (named after inventors Adelson-Velsky and Landis).  AVL trees are self balancing binary search trees.  After each insertion/removal of a node it will remain balanced.



<canvas id="myCanvas" width="100" height="700" style="border:1px solid #d3d3d3;width: 100vw;">
</canvas>

<script>

function getPointsOnCircle(c, r, n){
    let points = [];
    for(let i=0; i<n; i++){
        let theta = 2*Math.PI/n;
        points.push({x:r*Math.sin(i*theta) + c.x, y:r*Math.cos(i*theta) + c.y});
    }
    return points;
}

function drawLine(ctx, p1, p2){
    ctx.beginPath();
    ctx.moveTo(p1.x, p1.y);
    ctx.lineTo(p2.x, p2.y);
    ctx.stroke();
}

function drawCircle(ctx, c, r){
    ctx.beginPath();
    ctx.arc(c.x, c.y, r, 0, 2 * Math.PI);
    ctx.stroke();
} 

var c = document.getElementById("myCanvas");
c.width = 400;
c.height = 300;
var ctx = c.getContext("2d");
ctx.lineWidth = 0.5;
let centre = {x:100.5, y:100.5};
let radius = 300;
let n = 301;
let m = 4;

drawCircle(ctx, centre, radius);
let circlePoints = getPointsOnCircle(centre, radius, n);
for(let i=0; i<n; i++){
    let j = (i*m)%n;
    drawLine(ctx, circlePoints[i], circlePoints[j]);
}
</script>










<br>
<h3 id="red_black_comparison">AVL vs Red Black</h3>
An AVL tree will have better balancing than an RB tree, so lookup time will generally be better.  This is at the tradeoff of insertion/deletion performance.  So if lookup speed is more important, or there will be fewer insertions, an AVL tree will probably perform better.




