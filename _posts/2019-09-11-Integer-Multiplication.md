---
layout: post
title:  "Integer multiplication modulo"
date:   2018-09-25 17:14:23 +0800
categories: programming 
permalink: multiplication
---



<canvas id="myCanvas" width="100" height="700" style="border:1px solid #d3d3d3;">
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

function Update(width, n, m){
    var c = document.getElementById("myCanvas");
    c.width = width;
    c.height = width;
    var ctx = c.getContext("2d");
    ctx.lineWidth = 0.5;
    let centre = {x:width/2, y:width/2};
    let radius = width/2;
    drawCircle(ctx, centre, radius);
    let circlePoints = getPointsOnCircle(centre, radius, n);
    for(let i=0; i<n; i++){
        let j = (i*m)%n;
        drawLine(ctx, circlePoints[i], circlePoints[j]);
    }
}

Update(100, 10, 2);

</script>
    <input type="number" placeholder="Type something..." id="myInput1">
    <input type="text" placeholder="Type something..." id="myInput2">

<button type="button" onclick="Update(200, 15, 7)">Click Me!</button>


