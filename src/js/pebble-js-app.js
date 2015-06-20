var xhrRequest = function (url, type, callback) {
  var xhr = new XMLHttpRequest();
  xhr.onload = function () {
    callback(this.responseText);
  };
  xhr.open(type, url);
  xhr.send();
};

function locationSuccess(pos) {
  var url = "http://api.openweathermap.org/data/2.5/weather?lat=" +
      pos.coords.latitude + "&lon=" + pos.coords.longitude;

  xhrRequest(url, 'GET',
    function(responseText) {
      var json = JSON.parse(responseText);

      var temperature = Math.round(json.main.temp - 273.15);
      console.log("Temperature is " + temperature);

      var location = json.name;
      console.log("Location " + location);

      var dictionary = {
        "KEY_TEMPERATURE": temperature,
        "KEY_LOCATION": location 
      };

      Pebble.sendAppMessage(dictionary,
        function(e) {
          console.log("Weather info sent to Pebble successfully!");
        },
        function(e) {
          console.log("Error sending weather info to Pebble!");
        }
      );
    }
  );
}

function getAareInfo() {
  var url = "http://aare.schwumm.ch/aare.json";

  xhrRequest(url, 'GET',
    function(responseText) {
      var json = JSON.parse(responseText);

      var temperature = json.temperature;
      console.log("Aare Temperature is " + temperature);

      var flow = json.flow;
      console.log("Aare Flow is " + flow);

      var height = json.height;
      console.log("Aare Height is " + height);

      var dictionary = {
        "KEY_A_TEMPERATURE": temperature,
        "KEY_A_FLOW": flow,
        "KEY_A_HEIGHT": height
      };

      Pebble.sendAppMessage(dictionary,
        function(e) {
          console.log("Aare info sent to Pebble successfully!");
        },
        function(e) {
          console.log("Error sending aare info to Pebble!");
        }
      );
    }
  );
}

function locationError(err) {
  console.log("Error requesting location!");
}
function getWeather() {
  navigator.geolocation.getCurrentPosition(
    locationSuccess,
    locationError,
    {timeout: 15000, maximumAge: 60000}
  );
}

Pebble.addEventListener('ready',
  function(e) {
    console.log("PebbleKit JS ready!");
    getWeather();
    getAareInfo();
  }
);

Pebble.addEventListener('appmessage',
  function(e) {
    console.log("AppMessage received!");
    getWeather();
    getAareInfo();
  }
);
