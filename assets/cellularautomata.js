
        /******************
        *  Global vars
        ********************/

        let width = 740; //px
        let height = 740; //px

        let w = 1;       // width of cell
        let N = width/w; // number of cells across
        let state = [];        
        let currentRule = null;    
        let ruleNumber = null;    
        let T = 5;       // ms between each line draw

        let pause = true;
        let redraw = false;

        let imageData = null;
        let RULE_NUMBER_ELEMENT = "ruleNumberInput";
        let START_BUTTON = "startButton";
        /********************/


        function drawSquare(ctx, x,y){
            ctx.fillRect(x, y, w, w);
        }  

      function writeToImageData(i,j,w,col)
      {
          let index = (j*width + i) * 4;

          for(let k=0; k<w-1; k++)
          {
            for(let l=0; l<w-1; l++)
            {
              let px = i + k;
              let py = j + l;
              writeToImageData(px,py, 1, 0);
            }
          }

          imageData.data[index + 0] = 0;
          imageData.data[index + 1] = 0;
          imageData.data[index + 2] = 0;
          imageData.data[index + 3] = 255;

          //ctx.putImageData(imageData, 0, 0);
        }

      function initState()
      {
        let s_0 = [];
        for(let i=0; i<N; ++i)
        {
            if(i == N/2)
            {
                s_0.push(1);
            }
            else
            {
                s_0.push(0);
            }
        }
        state.push(s_0);
/*        
        for(let i=0; i<N; ++i)
        {
            if(i == N/2)
            {
                imageData[4*i + 0] = 255;
                imageData[4*i + 1] = 255;
                imageData[4*i + 2] = 255;
                imageData[4*i + 3] = 255;
            }
            else
            {
            }
        }
*/
      }

      function updateState(rule)
      {
        if(state.length == 0)
        {
            return initState();
        }
        let last = state[state.length - 1];
        state.push(rule(last));
      }

      function updateImageData()
      {
        let last = state[state.length - 1];
        for(let i=0; i<last.length; ++i)
        {
          if(last[i]==1)
          {
            writeToImageData(i*w, state.length*w, w+1);
          }
        }         
      }
        
      function drawState(ctx)
      {
          //for(let i=state.length-1; i<state.length; ++i)
          for(let i=0; i<state.length; ++i)
          {
              for(let j=0; j<state[i].length; ++j)
              {
                  if(state[i][j] == 1)
                  {
                    drawSquare(ctx, j*w, i*w);
                  }     
              }
          }
      }
    
      // return rule as binary array 
      function getRule(num)
      {
          let bin = num.toString(2);
          let bin_a = bin.split("");
          let bin_num = [];
          for(let i=0; i<bin_a.length; ++i)
          {
              bin_num.push(parseInt(bin_a[i], 2));
          }
          //pad
          while(bin_num.length<8)
          {
              bin_num.unshift(0);
          }
          //console.log(bin_num.length);
          return bin_num;
      }

      let step = (last) => {
            
          let _last = last.slice();
          _last.unshift(0);
          _last.push(0);
          let ret = [];

          for(let i=1; i< _last.length -1; ++i)
          {
            let s = _last[i-1].toString() + _last[i].toString() + _last[i+1].toString();
            let d = parseInt(s,2);
            //console.log(d);
            ret.push(currentRule[d]);
          }
          return ret;
      };

      /*
      let rule110 = (last) => {
          let _last = last.slice();
          _last.unshift(0);
          _last.push(0);
          let ret = [];

          //let r = [0,1,1,0,1,1,1,0];
          //let r = [0,1,1,1,0,1,1,0];
          let r = [0,1,1,0,1,1,0,1];
          //let r = [1,0,0,1,0,1,0,1];

          for(let i=1; i< _last.length -1; ++i)
          {
            let s = _last[i-1].toString() + _last[i].toString() + _last[i+1].toString();
            let d = parseInt(s,2);
            console.log(d);
            ret.push(r[d]);
          }
          return ret;
      };
      */

      function Restart()
      {
        state = [];
        redraw = true;
        setTimeout(()=>{
          redraw = false;
          draw();
        }, 10);
      }

      function buttonClick()
      {
          pause = !pause;
          if(pause)
          {
            document.getElementById(START_BUTTON).innerHTML = "Start";
          }else{
            document.getElementById(START_BUTTON).innerHTML = "Stop";            
          }


          //console.log('click');
          let c = document.getElementById(RULE_NUMBER_ELEMENT).value;
          if(c != ruleNumber)
          {
            ruleNumber = parseInt(c);
            Restart();
            //console.log(c);
          }
        }

      function draw() {
        var canvas = document.getElementById('tutorial');
        if (canvas.getContext) {
          var ctx = canvas.getContext('2d');

          let container_w = document.getElementById("canvasContainer").offsetWidth;
          let container_h = document.getElementById("canvasContainer").offsetHeight;
          console.log(container_w, container_h);
          width = container_w;
          height = container_h;
          height = container_w;
          N = width/w;
          ctx.canvas.width = width;
          ctx.canvas.height = height;
          //ctx.canvas.width  = window.innerWidth;
          //ctx.canvas.height = window.innerHeight;
          //drawSquare(ctx, 0,0,10);
          imageData = ctx.createImageData(width,height*100);
          initState();
          
          /* 
          for(let i=0; i<N/2; ++i)
            {

                updateState(rule110);
                drawState(ctx);
            }
          */
          
          let count = 0;
          //let T = 5;
          let update = ()=>{

            if(redraw)
            {
              return;
            }
            else if(pause)
            {
              setTimeout(update, 5);
            }
            else if(count<N*100)
            {
              updateState(step);
              //updateState(rule110);
              //drawState(ctx);
              updateImageData();
              let py = 0;

              if(count>N)
              {
                py = -1 * (count - N);
              }

              //console.log(count, py);
              ctx.putImageData(imageData, 0, py);
              setTimeout(update, T);
              count++;
            }
            else{
              return;
            }

          };

          if(ruleNumber == null)
            ruleNumber = 91;
          currentRule = getRule(ruleNumber);
          //console.log(currentRule);

          writeToImageData(0,0,1,0);
          ctx.putImageData(imageData, 0, 0);

          update();
            
          /*
          for(let i=0; i<N/2; ++i)
          {
              updateState(step);
              drawState(ctx);
              wait(500);
          }
          */
        }
      }

/************************/
/*
function CellularAutomata(ctx, px, py)
{
    this.px = px;
    this.py = py;
    this.ctx = ctx;
    this.w = 1;

    this.N = this.px / this.w; // number of cells across
    this.state = [];        
    this.currentRule = null;        
    this.T = 5;       // ms between each line draw
}

CellularAutomata.prototype.setSquareWidth = function(w) {
    this.w = w;
};

CellularAutomata.prototype.init = function() {

};
*/