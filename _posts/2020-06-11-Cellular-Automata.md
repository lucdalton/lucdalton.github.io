---
layout: post
title:  "Cellular Automata"
date:   2020-05-25 17:14:23 +0800
categories: programming 
permalink: cellularautomata
---


  <head>
    <meta charset="utf-8"/>
    <title>Canvas tutorial</title>
    <script src="{{ base.url | prepend: site.url }}/assets/cellularautomata.js"></script>
    <style type="text/css">
      canvas { border: 1px solid black; }
    </style>
  </head>
  <body onload="draw();">
    <div style="width: 50%; margin: 0 auto;">
      <div style="width: 300px;">
        <label>Rule number:</label>
        <input id="ruleNumberInput" type="number" value="91">
      </div>
      <!--
      <div>
        <label>Cell Width (px):</label>
        <input type="number">
      </div>
      -->
      <div>
        <button id="startButton" type="button" onclick="buttonClick()">Start</button>
      </div>
      <div style="height: 20px;">
      </div>
    </div>
    <div id="canvasContainer">
      <canvas id="tutorial" width="740" height="740"></canvas>
    </div>
  </body>


