// adding the required libraries 

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

// WIFI hotspot 

const char *ssid = "Chub Inspection Machine";
const char *password = "12345678";

float weight[10]={0}; 
int call=0;  
int listenn=2,approach=0;
String delayy="50",drop="50";
String predel="50",predrop="50";
String k="";
int p=9;

// specify the port 
ESP8266WebServer server(80);

//The about page 
// add required team member names in place of names given below 
void about()
{
  String r = "<!DOCTYPE html><html><style>body  {"
 "}h1{background-color:dodgerblue;text-align:center;"
"font-family:courier;width:1500;height:75px;"
"color:black;}#m {font-size:100%;"
"width:1000px;height:60px;color:black;"
"text-align:left;font-family:courier;}h2{"
"color:black;font-family:courier;}</style>"
"<body><h1>Chub Inspection Client</h1><h2> Aim of the project: </h2>"
"<pre id=\"m\">"
"The Chub Inspection machine is a automated weighing solution <br>for Chubs for process control.</br> "
"</pre><h2>Guided by:  </h2><pre id=\"m\">"
"Dr. Ravi C Guttal<br>" 
"Dr. Sachin Karadgi<br> </pre> <h2>Team members: </h2>"
"<pre id=\"m\">" 
"Akash Koparde<br>"
"Abhinav Raichur <br>"
"Chetan Bhandari<br>"
"Akhilesh O<br>"
"Kiran C Hiremath </pre>"
"</body></html>";

server.send(200, "text/html", r);
 
}

// home page (root)  
void handleRoot() {

String l = "<!DOCTYPE html> <html> <style>body  {color:black;}h1  {"
"background-color:dodgerblue;text-align:center;"
"font-family:courier;width:1500;"
"height:75px;}pre{font-size:125%;"
"color:black;text-align:center;font-family:courier;}</style>"
"<body style=\"background-image:url('file:///D:/mm.jpg')\">"
"<h1>Chub Inspection Client</h1><pre>"
"<a href=\"/about\" style=\"color:black\">About</a><br><br><br>"
"<a href=\"/graphical\" style=\"color:black;\">graphical</a><br><br><br> "
"<a href=\"/parameters\" style=\"color:black;\">parameters</a><br><br><br> "
"<a href=\"/load\" style=\"color:black;\"> load wt</a><br><br><br>"
"</pre></body></html>";
 
server.send(200, "text/html", l);
 
}


// parameters page 
void parameters()
{
  
String temp="A";

// check for arguments recieved and copy them into variables here  
if (server.args() > 0 ) { 
    for ( uint8_t i = 0; i < server.args(); i++ ) {
      if (server.argName(i) == "drop") {
        predrop = drop;
        drop = server.arg(i);
        }
    
    if (server.argName(i) == "delayy") {
        predel = delayy;
        delayy = server.arg(i);
      }
    }
  }  

// prepare the page  
String l = "<!DOCTYPE html><html><style>body{color:black;}h1{"
"background-color:dodgerblue;text-align:center;font-family:courier;width:1500;height:75px;}pre  {font-size:100%;color:black;text-align:center;font-family:courier;}"
"form{font-family:courier;font-size:100%;"
"}h2{font-family:courier;font-size:100%;}</style><body>"
"<h1>Chub Inspection Client</h1><h2>Parameters List</h2><form action='http://192.168.4.1/parameters' method='POST'>Drop distance:<br><input type='text' name='drop' value='";

l += drop +   "'><br>";
l += "Weigh delay:<br><input type='text' name='delayy' value='" + delayy + "'><br>";
l += "<input type='submit' value='submit'></form><br>";
 
l += "<pre><b>Note:</b>  enter values in percentage</pre></body></html>";

// check if there has been change from previous values
if((delayy != predel) || (predrop != drop) )
{
digitalWrite(approach,LOW);
delay(50);
digitalWrite(approach,HIGH);

Serial.print('A'); // tell the arduino, these are delay drop values
temp = "";
while(digitalRead(listenn)) // wait for arduino to listen 
{
  
}
temp = delayy + "N" + drop + "O";
Serial.print(temp); 

}

server.send(200,"text/html",l);

}





// graphical page and table page 

void graph()
{
String temp="",temp1="";

int x=10;  
String l = "<!DOCTYPE html><html><style>body{}h1{background-color:dodgerblue;"
"text-align:center;font-family:courier;width:1500;height:75px;}pre{font-size:125%;color:black;"
"text-align:center;font-family:courier;}h2{font-family:courier;text-align:center;font-size:100%;}"
"#mycanvas{ width=\"200\"; height=\"200\";border:1px solid #d3d3d3;}table, th, td {   border: 1px solid black;font-family:courier;font-size:100%;}"
"</style><body><h1>Chub Inspection Client</h1><br><h2> graphical representation of previous samples  </h2><canvas id=\"mycanvas\"  width=\"200\";"
"height=\"200\";align=center;border:1px solid #d3d3d3;>Your browser does not support the canvas element.</canvas><script>"
"var canvas = document.getElementById(\"mycanvas\");var ctx = canvas.getContext(\"2d\");";


l += "ctx.moveTo(10,0);ctx.lineTo(10,190);ctx.stroke();ctx.lineTo(200,190);ctx.stroke();ctx.moveTo(10,190);";

for(int y=0;y<10;y++)
{
x = x+30;
temp = weight[y];
temp1 = x;
l += "ctx.lineTo(" + x;
l += ","  + temp + ");ctx.stroke();";
temp = "";
} 


 l+= "</script><br><br><table><tr><th>Sample Number</th> <th>Weight</th><th> time since boot </th></tr>";
    
for(int y=1;y<11;y++)
  {
l+= "<tr><td>"; 
temp = y;
l += temp + "</td><td>"; 
temp="";
temp = String(weight[y]);
l += temp + "</td><td>" + millis() + "</td></tr>";
  }  
  
l+= "</table></body></html>";

server.send(200,"text/html",l);
}

// recieve the weights from arduino, loads one weight at a time 
void loadwt()

{
String temp="P"; 
digitalWrite(approach,LOW); // ask arduino for weights with approach pin 
delay(50);
digitalWrite(approach,HIGH);

Serial.println(temp);
temp = "";
while(digitalRead(listenn)) // wait for the listenn pin to get HIGH (waiting for Arduino)
{
  
}
while(!Serial.available()) // wait for data in the serial buffer 
{

 
}
// store only one weight for every call (max. 10 weights) 
temp = Serial.readStringUntil('N');
weight[p] = temp.toInt();
temp = "";
p--;         
if(p<=0)
{
  p=9;
}
server.send(200,"text/html","loading done!");
  
}

// final code 

void setup() {
  
  pinMode(listenn,INPUT_PULLUP);
  pinMode(approach,OUTPUT);
  digitalWrite(approach,HIGH);  // default HIGH when weights are not needed
  Serial.begin(9600);
  Serial.println();
  Serial.print("Configuring access point...");
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  
  // define the path handlers 
  server.on("/", handleRoot);
  server.on("/graphical", graph);
  server.on("/about",about);
  server.on("/parameters",parameters);
  server.on("/load",loadwt);
  
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
