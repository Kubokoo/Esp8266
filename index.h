const char MAIN_page[] PROGMEM = R"=====(
<!doctype html>
<html>

  <head>
    <title>Tempreture and humidity realtime chart - Jakub Gwiazda</title>
    <script src="https://cdn.jsdelivr.net/npm/chart.js@2.8.0"></script> 
    <style>
      canvas{
        -moz-user-select: none;
        -webkit-user-select: none;
        -ms-user-select: none;
      }

      /* Data Table Styling */
      #dataTable {
        font-family: "Trebuchet MS", Arial, Helvetica, sans-serif;
        border-collapse: collapse;
        width: 100%;
      }

      #dataTable td, #dataTable th {
        border: 1px solid #ddd;
        padding: 8px;
      }

      #dataTable tr:nth-child(even){
        background-color: #f2f2f2;
      }
      #dataTable tr:hover {
        background-color: #ddd;
      }
      #dataTable th {
        padding-top: 12px;
        padding-bottom: 12px;
        text-align: left;
        background-color: #4CAF50;
        color: white;
      }

      .chart-container{
        position: relative;
        width: 100%;
        height: 550px;
      }
      
      #chart {
        width: 100%;
        height: 400px;
      }
    </style>
  </head>

  <body>
    <div style="text-align:center;">
      <b>Real Time Tempreture and Humidity graph - Jakub Gwiazda</b>
    </div>
    <div class="chart-container">
        <canvas id="chart"></canvas>
    </div>
    <div>
      <table id="dataTable">
        <tr><th>Time</th><th>Temperature Value</th><th>Humidity Value</th></tr>
      </table>
    </div>
    <br>
    <br>  

  <script>
    var TemperatureValues = [];
    var HumidityValues = [];
    var timeStamp = [];
    function showGraph()
    {
        var ctx = document.getElementById("chart").getContext('2d');
        var Chart2 = new Chart(ctx, {
            type: 'line',
            data: {
                labels: timeStamp,
                datasets: [{
                    label: "Temperature",
                    fill: true,
                    backgroundColor: 'rgba(204, 0, 0, 0.3)',
                    borderColor: 'rgb(255, 69, 0)',
                    data: TemperatureValues
                },{
                    label: "Humidity",
                    fill: true,
                    backgroundColor: 'rgba(0, 146, 253, 0.3)',
                    borderColor: 'rgb(10, 0, 253)',
                    data: HumidityValues
                }],
            },
            options: {
                title: {
                        display: false,
                        text: "Temperature and Humidity"
                    },
                maintainAspectRatio: false,
                elements: {
                line: {
                        tension: 0.5
                    }
                },
                scales: {
                        yAxes: [{
                            ticks: {
                                suggestedMin: 20,
                                suggestedMax: 50
                            }
                        }]
                }
            }
        });

    }

    window.onload = function() {
      console.log(new Date().toLocaleTimeString());
      showGraph(5,10,4,58);
    };

    setInterval(function() {
      getData();
    }, 10000);

    function getData() {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          var time = new Date().toLocaleTimeString();
          var response = JSON.parse(this.responseText); 
          if(TemperatureValues.length >= 20){
            var lasttimeStamp = timeStamp[timeStamp.length - 1];
            var lastTemperature = TemperatureValues[TemperatureValues.length - 1];
            var lastHumidity = HumidityValues[HumidityValues.length - 1];
            
            TemperatureValues.length = 0;
            HumidityValues.length = 0;
            timeStamp.length = 0;
            
            TemperatureValues.push(lastTemperature);
            HumidityValues.push(lastHumidity);
            timeStamp.push(lasttimeStamp);
          }
          TemperatureValues.push(response.Temperature);
          HumidityValues.push(response.Humidity);
          timeStamp.push(time);
          showGraph();

          var table = document.getElementById("dataTable");
          var row = table.insertRow(1);
          var cell0 = row.insertCell(0);
          var cell1 = row.insertCell(1);
          var cell2 = row.insertCell(2);
          cell0.innerHTML = time;
          cell1.innerHTML = response.Temperature;
          cell2.innerHTML = response.Humidity;
        }
      };
      xhttp.open("GET", "readMeasurements", true);
      xhttp.send();
    }
  </script>
  </body>

</html>

)=====";
