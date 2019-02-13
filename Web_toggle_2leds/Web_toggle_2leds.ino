
/* Demonstration of a Web page toggling two LED's from two buttons.
 *  Pins 8 and 9 are being used.
 *  Variables "current and current2" are being used to store current state*/

#include <SPI.h>
#include <Ethernet.h>

//int led = 8;
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 1, 103);
EthernetServer server(80);
String readString;
int current  = 1;
int current2 = 1;
void setup() {

  Ethernet.begin(mac, ip); //starting the connection to local network
  Serial.begin(9600);          //starting the serial coms
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  server.begin();
  Serial.print("Server is at ");
  Serial.println(Ethernet.localIP());
}

void loop() {
 
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.print(c);
 
        if (readString.length() < 100) {
          readString += c;
        }
        if (c == '\n') {
          Serial.println(current);
          Serial.println(readString);
          client.println("<HTTP/1.1 200 OK>");
          client.println("<Connection-Type: text/html>");
          client.println("<Connection:close>");
          client.println();
          //******************************************************************
          client.println("<!DOCTYPE html>");            //writing the html page
          client.println("<html>");
          client.println("<head>");
          client.println("<title>'led html controller'</title>" );
          client.println("/<head>");
          client.println("<body>");
          client.println("<body>");
          client.println("<a href=\"/?button1\"\"><button>LED Red</button></a>");
          client.println("<a href=\"/?button2\"\"><button>LED Yellow</button></a>");
          client.println("<body style=background-color:grey>");
          //************************************************************************
          delay(100);
          client.stop();                                  //closing the client
          //****************follow lines toggle the LED's******************************************
            if (readString.indexOf("?button1")>0){
                if(current == 1){
                   digitalWrite(8, HIGH);
                    current =0;
                    }

                else{
                  digitalWrite(8, LOW);
                  current =1;
                    }
                }

			      if (readString.indexOf("?button2")>0){
                 if(current2 == 1){
                   digitalWrite(9, HIGH);
                   current2 =0;
                  }

                else{
                  digitalWrite(9, LOW);
                  current2 =1;
                  }         
              }
         //************************************************************************     
          readString = "";
        }    
      }
    }
  }
          client.println("</body>");
          client.println("</html>");
}


          
