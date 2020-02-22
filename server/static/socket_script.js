$(document).ready(function(){
    var socket = io.connect('https://' + document.domain + ':' + location.port + '/socket');
    socket.on('server response', function(msg) {
        console.log("received " + msg.data);
        $('#log').append('<p>' + msg.data + '</p>');
    });
});