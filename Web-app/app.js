// connect to the OOCSI server
OOCSI.connect("wss://oocsi.id.tue.nl/ws");

// subscribe to a channel and add data to HTML
OOCSI.subscribe("PLANT-testchannel", function (e) {
  $("#color").css({ width: (e.data.ldr / 255) * 100 + "%" });
});

function forward() {
  OOCSI.send("PLANT-testchannel", { movement: "forward" });
  console.log("forward");
}
function backward() {
  OOCSI.send("PLANT-testchannel", { movement: "backward" });
  console.log("backward");
}
function right() {
  OOCSI.send("PLANT-testchannel", { movement: "left" });
  console.log("right");
}
function left() {
  OOCSI.send("PLANT-testchannel", { movement: "right" });
  console.log("left");
}
function stop() {
  OOCSI.send("PLANT-testchannel", { movement: "stop" });
  console.log("stop");
}
