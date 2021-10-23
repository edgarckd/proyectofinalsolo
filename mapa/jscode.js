import {readFile} from "./con.js"

var map = L.map('map').setView([14.0860746, 100.608406], 6);
// map.addControl(new L.Control.Fullscreen());
var osm = L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
    attribution: '&copy; <a href="https://www.openstreetmap.org/copyright">OpenStreetMap</a> contributors',
    maxZoom: 18, minZoom: 2,
    });
osm.addTo(map);

setInterval(() => {
    navigator.geolocation.getCurrentPosition(getPosition)
}, 1000);

var marker, circle

function getPosition(position){
    // console.log(position) 
    var lat = position.coords.latitude
    var long = position.coords.longitude
    var accuracy = position.coords.accuracy
    console.log("funciona")
    if(marker) {
        map.removeLayer(marker)
    }

    if(circle) {
        map.removeLayer(circle)
    }

    marker = L.marker([lat, long])
    circle = L.circle([lat, long], {radius: accuracy})

    var featureGroup = L.featureGroup([marker, circle]).addTo(map)

    map.fitBounds(featureGroup.getBounds())

    console.log("Your coordinate is: Lat: "+ lat +" Long: "+ long+ " Accuracy: "+ accuracy)

}