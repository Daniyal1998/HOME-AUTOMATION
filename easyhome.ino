#include "Gsender.h"
#include <WiFiClientSecure.h>   // Include the HTTPS library
#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include <ESP8266WiFiMulti.h>   // Include the Wi-Fi-Multi library

ESP8266WiFiMulti wifiMulti;     // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'
String getTime();
void check();
void again();
void data_from_local();
void receive_data_from_arduino();



int totalunread = 0, glowBulb = D3, state = 0, totalunread2 = 0;
int totalunread3 = 0, glowBulb2 = D4, state2 = LOW, totalunread4 = 0;
int totalunread5 = 0, glowBulb3 = D1, state3 = LOW, totalunread6 = 0;

int person_coming_outside_sensor = 0;
int person_coming_inside_sensor = 0;
int person_going_outside_sensor = 0;
int person_going_inside_sensor = 0;
int check_inside = 0, check_outside = 0;
String counting_state = "";
int person_inside_house = 0;
int door_state = 0;
unsigned int Time;

int data=0;

int val = 0;


char* cString = "coming";

WiFiServer server(80);
String request;


const byte thief = 14;
volatile byte thiefcounter = 0;
int choraaya = 0;


int personcount = 0, outsidecount = 0, insidecount = 0;
String s = "";
const byte outcounter = 12;
const byte insidecounter = 13;



const char* host = "mail.google.com"; // the Gmail server
const char* url = "/mail/feed/atom";  // the Gmail feed url
const int httpsPort = 443;            // the port to connect to the email server

// The SHA-1 fingerprint of the SSL certificate for the Gmail server (see below)
const char* fingerprint = "D3 90 FC 82 07 E6 0D C2 CE F9 9D 79 7F EC F6 E6 3E CB 8B B3";

// The Base64 encoded version of your Gmail login credentials (see below)
const char* credentials = "dGVjaG5va3JhdHNidWxiMW9uQGdtYWlsLmNvbTp0ZWNobm9rcmF0cw==";
const char* credentials2 = "dGVjaG5va3JhdHNidWxiMW9mZkBnbWFpbC5jb206dGVjaG5va3JhdHM=";
const char* credentials3 = "dGVjaG5va3JhdHNidWxiMm9uQGdtYWlsLmNvbTp0ZWNobm9rcmF0cw==";
const char* credentials4 = "dGVjaG5va3JhdHNidWxiMm9mZkBnbWFpbC5jb206dGVjaG5va3JhdHM=";
const char* credentials5 = "dGVjaG5va3JhdHNidWxiM29uQGdtYWlsLmNvbTp0ZWNobm9rcmF0cw==";
const char* credentials6 = "dGVjaG5va3JhdHNidWxiM29mZkBnbWFpbC5jb206dGVjaG5va3JhdHM=";





void setup()
{
  Serial.begin(115200);




  delay(10);

  pinMode(glowBulb, OUTPUT);

  pinMode(glowBulb2, OUTPUT);

  pinMode(glowBulb3, OUTPUT);

    pinMode(thief, INPUT);
    attachInterrupt(digitalPinToInterrupt(thief), handleInterrupt, RISING);

  pinMode(outcounter, INPUT);
  attachInterrupt(digitalPinToInterrupt(outcounter), outside_sensor_interrupt, RISING);

  pinMode(insidecounter, INPUT);
  attachInterrupt(digitalPinToInterrupt(insidecounter), inside_sensor_interrupt, RISING);





  wifiMulti.addAP("network!75", "network75");   // add Wi-Fi networks you want to connect to
  //  wifiMulti.addAP("network!7", "prash@123");
  wifiMulti.addAP("Daniyal_desk", "12345678");


  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
    delay(250);

  }



  server.begin();
  Serial.print("http://");
  Serial.print(WiFi.localIP());


  Gsender *gsender = Gsender::Instance();
  String subject = "BULB  OFF!";
  gsender->Subject(subject)->Send("technokratsbulb1off@gmail.com", "Setup test");
  gsender->Subject(subject)->Send("technokratsbulb2off@gmail.com", "Setup test");
  gsender->Subject(subject)->Send("technokratsbulb3off@gmail.com", "Setup test");


  totalunread = getUnread();
  totalunread2 = getUnread2();
  totalunread3 = getUnread3();
  totalunread4 = getUnread4();
  totalunread5 = getUnread5();
  totalunread6 = getUnread6();


}



void handleInterrupt()
{
  if(person_inside_house==0)
  {Serial.write("chor aaya\n");
  choraaya = 1;}
  
}





void bulb1()
{
  int unread = getUnread();
  //Serial.println("bulb 1 ");

  if (state == 0 && ((unread - totalunread) >= 1 || (s == "bulb 1 on") || (request.indexOf("/LED=1ON") != -1)))
  {
    Serial.write("bulb 1 is on\n");
    state = 1;
    digitalWrite(glowBulb, HIGH);
    Gsender *gsender = Gsender::Instance();    // Getting pointer to class instance
    String subject = "BULB 1 ON!";
    if (gsender->Subject(subject)->Send("technokratsbulb1on@gmail.com", "Setup test")) {

    }
    if (unread - totalunread >= 1)
    {

      totalunread = unread + 1;
    }

  }
  else
    totalunread = unread;
  int unread2 = getUnread2();
  if (state == 1  && (((unread2 - totalunread2) >= 1)  || (s == "bulb 1 off") || (request.indexOf("/LED=1OFF") != -1)))
  {

    Serial.write("bulb 1 is off\n");
    state = 0;
    digitalWrite(glowBulb, LOW);
    Gsender *gsender = Gsender::Instance();    // Getting pointer to class instance
    String subject = "BULB 1 OFF!";
    if (gsender->Subject(subject)->Send("technokratsbulb1off@gmail.com", "Setup test")) {

    }
    if (unread2 - totalunread2 >= 1)
    {
      totalunread2 = unread2 + 1;
    }

  }
  else
    totalunread2 = unread2;
}

void bulb2()
{
  int unread = getUnread3();
  //Serial.println("bulb 2 ");
  if (state2 != HIGH && ((unread - totalunread3) >= 1 || (s == "bulb 2 on") || (request.indexOf("/LED=2ON") != -1)))
  {
    state2 = HIGH;
    Serial.write("bulb 2 is on\n");
    digitalWrite(glowBulb2, HIGH);
    Gsender *gsender = Gsender::Instance();    // Getting pointer to class instance
    String subject = "BULB 2 ON!";
    if (gsender->Subject(subject)->Send("technokratsbulb2on@gmail.com", "Setup test")) {

    }
    if (unread - totalunread3 >= 1)
    {
      totalunread3 = unread + 1;
    }

  }
  else
    totalunread3 = unread;


  int unread2 = getUnread4();
  if (state2 != LOW && ((unread2 - totalunread4) >= 1  || (s == "bulb 2 off") || (request.indexOf("/LED=2OFF") != -1)))
  {
    state2 = LOW;
    Serial.write("bulb 2 is off\n");
    digitalWrite(glowBulb2, LOW);
    Gsender *gsender = Gsender::Instance();    // Getting pointer to class instance
    String subject = "BULB 2 OFF!";
    if (gsender->Subject(subject)->Send("technokratsbulb2off@gmail.com", "Setup test")) {

    }
    if (unread2 - totalunread4 >= 1)
    {
      totalunread4 = unread2 + 1;
    }


  }
  else
    totalunread4 = unread2;
}


void bulb3()
{
  // Serial.println("bulb 3 ");
  int unread = getUnread5();
  if (state3 != HIGH && ((unread - totalunread5) >= 1 || (s == "bulb 3 on") || (request.indexOf("/LED=3ON") != -1)))
  {
    state3 = HIGH;
    Serial.write("bulb 3 is on\n");
    digitalWrite(glowBulb3, HIGH);
    Gsender *gsender = Gsender::Instance();    // Getting pointer to class instance
    String subject = "BULB 3 ON!";
    if (gsender->Subject(subject)->Send("technokratsbulb3on@gmail.com", "Setup test")) {

    }
    if (unread - totalunread5 >= 1)
    {
      totalunread5 = unread + 1;
    }

  }
  else
    totalunread5 = unread;


  int unread2 = getUnread6();
  if (state3 != LOW && ((unread2 - totalunread6) >= 1  || (s == "bulb 3 off") || (request.indexOf("/LED=3OFF") != -1)))
  {
    state3 = LOW;
    Serial.write("bulb 3 is off\n");
    digitalWrite(glowBulb3, LOW);
    Gsender *gsender = Gsender::Instance();    // Getting pointer to class instance
    String subject = "BULB 3 OFF!";
    if (gsender->Subject(subject)->Send("technokratsbulb3off@gmail.com", "Setup test")) {

    }
    if (unread2 - totalunread6 >= 1)
    {
      totalunread6 = unread2 + 1;
    }

  }
  else
    totalunread6 = unread2;
}


void loop() {



  Serial.write("time is\n");
  String date_time = getTime().substring(0);
  cString = (char*) malloc(sizeof(char) * (date_time.length() + 1));
  date_time.toCharArray(cString, date_time.length() + 1);
  Serial.write("time is\n");
  Serial.write(cString);
  Serial.println("");


  again();
  bulb1();

  again();
  bulb2();

  again();
  bulb3();





  //  date_time=getTime().substring(5,16);
  //  cString = (char*) malloc(sizeof(char)*(date_time.length() + 1));
  //  date_time.toCharArray(cString, date_time.length() + 1);
  //  Serial.write("date is\n");
  //  Serial1.write(cString);
  //
  //  date_time=getTime().substring(17);
  //  cString = (char*) malloc(sizeof(char)*(date_time.length() + 1));
  //  date_time.toCharArray(cString, date_time.length() + 1);
  //  Serial.write("time is\n");
  //  Serial1.write(cString);

  //Serial.write(date_time);

}


void again()
{
  //  Serial.println("again ");
  //  delay(1000);
  if (choraaya == 1)
  {
    choraaya = 0;
    Gsender *gsender = Gsender::Instance();    // Getting pointer to class instance
    String subject = "!!!CHOOR AAYA!!!";
    if (gsender->Subject(subject)->Send("gauravbansal233@gmail.com", "Take Action") && gsender->Subject(subject)->Send("technokratschoraaya@gmail.com", "Take Action")) {

    }
  }
  delay(100);
  data_from_local();
  receive_data_from_arduino();
  check();
  if (s == "someone is at your door")
  {
    Gsender *gsender = Gsender::Instance();    // Getting pointer to class instance
    String subject = "!!!SOMEONE IS AT YOUR DOOR!!!";
    if (gsender->Subject(subject)->Send("gauravbansal233@gmail.com", "Setup test") && gsender->Subject(subject)->Send("technokratschorgya@gmail.com", "Setup test")) {

    }
  }
  Serial.write("no of person\n");
  Serial.println(person_inside_house);



  Serial.write("time is\n");
  Serial.write(cString);
  Serial.println("");
}



int getUnread() {
  // Serial.println("getUnread ");
  // a function to get the number of unread emails in your Gmail inbox
  WiFiClientSecure client; // Use WiFiClientSecure class to create TLS (HTTPS) connection
  // Serial.printf("Connecting to %s:%d ... \r\n", host, httpsPort);
  if (!client.connect(host, httpsPort)) {   // Connect to the Gmail server, on port 443
    //   Serial.println("Connection failed");    // If the connection fails, stop and return
    return -1;
  }

  //  Serial.print("Requesting URL: ");
  //  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Authorization: Basic " + credentials + "\r\n" +
               "User-Agent: ESP8266\r\n" +
               "Connection: close\r\n\r\n"); // Send the HTTP request headers

  //Serial.println("Request sent");

  int unread = -1;

  while (client.connected()) {                          // Wait for the response. The response is in XML format
    client.readStringUntil('<');                        // read until the first XML tag
    String tagname = client.readStringUntil('>');       // read until the end of this tag to get the tag name
    if (tagname == "fullcount") {                       // if the tag is <fullcount>, the next string will be the number of unread emails
      String unreadStr = client.readStringUntil('<');   // read until the closing tag (</fullcount>)
      unread = unreadStr.toInt();                       // convert from String to int
      break;                                            // stop reading
    }                                                   // if the tag is not <fullcount>, repeat and read the next tag
  }
  //  Serial.println("Connection closed");

  return unread;                                        // Return the number of unread emails
}








int getUnread2() {    // a function to get the number of unread emails in your Gmail inbox
  // Serial.println("getunread 2");
  WiFiClientSecure client; // Use WiFiClientSecure class to create TLS (HTTPS) connection
  //Serial.printf("Connecting to %s:%d ... \r\n", host, httpsPort);
  if (!client.connect(host, httpsPort)) {   // Connect to the Gmail server, on port 443
    //  Serial.println("Connection failed");    // If the connection fails, stop and return
    return -1;
  }

  // Serial.print("Requesting URL: ");
  // Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Authorization: Basic " + credentials2 + "\r\n" +
               "User-Agent: ESP8266\r\n" +
               "Connection: close\r\n\r\n"); // Send the HTTP request headers

  // Serial.println("Request sent");

  int unread = -1;

  while (client.connected()) {                          // Wait for the response. The response is in XML format
    client.readStringUntil('<');                        // read until the first XML tag
    String tagname = client.readStringUntil('>');       // read until the end of this tag to get the tag name
    if (tagname == "fullcount") {                       // if the tag is <fullcount>, the next string will be the number of unread emails
      String unreadStr = client.readStringUntil('<');   // read until the closing tag (</fullcount>)
      unread = unreadStr.toInt();                       // convert from String to int
      break;                                            // stop reading
    }                                                   // if the tag is not <fullcount>, repeat and read the next tag
  }
  // Serial.println("Connection closed");

  return unread;                                        // Return the number of unread emails
}






int getUnread3() {    // a function to get the number of unread emails in your Gmail inbox
  // Serial.println("getunread3");
  WiFiClientSecure client; // Use WiFiClientSecure class to create TLS (HTTPS) connection
  // Serial.printf("Connecting to %s:%d ... \r\n", host, httpsPort);
  if (!client.connect(host, httpsPort)) {   // Connect to the Gmail server, on port 443
    // Serial.println("Connection failed");    // If the connection fails, stop and return
    return -1;
  }



  // Serial.print("Requesting URL: ");
  // Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Authorization: Basic " + credentials3 + "\r\n" +
               "User-Agent: ESP8266\r\n" +
               "Connection: close\r\n\r\n"); // Send the HTTP request headers

  // Serial.println("Request sent");

  int unread = -1;

  while (client.connected()) {                          // Wait for the response. The response is in XML format
    client.readStringUntil('<');                        // read until the first XML tag
    String tagname = client.readStringUntil('>');       // read until the end of this tag to get the tag name
    if (tagname == "fullcount") {                       // if the tag is <fullcount>, the next string will be the number of unread emails
      String unreadStr = client.readStringUntil('<');   // read until the closing tag (</fullcount>)
      unread = unreadStr.toInt();                       // convert from String to int
      break;                                            // stop reading
    }                                                   // if the tag is not <fullcount>, repeat and read the next tag
  }
  //  Serial.println("Connection closed");

  return unread;                                        // Return the number of unread emails
}






int getUnread4() {    // a function to get the number of unread emails in your Gmail inbox
  //Serial.println("getunread4");
  WiFiClientSecure client; // Use WiFiClientSecure class to create TLS (HTTPS) connection
  // Serial.printf("Connecting to %s:%d ... \r\n", host, httpsPort);
  if (!client.connect(host, httpsPort)) {   // Connect to the Gmail server, on port 443
    //   Serial.println("Connection failed");    // If the connection fails, stop and return
    return -1;
  }

  /*if (client.verify(fingerprint, host)) {   // Check the SHA-1 fingerprint of the SSL certificate
    Serial.println("Certificate matches");
    } else {                                  // if it doesn't match, it's not safe to continue
    Serial.println("Certificate doesn't match");
    return -1;
    }*/

  // Serial.print("Requesting URL: ");
  // Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Authorization: Basic " + credentials4 + "\r\n" +
               "User-Agent: ESP8266\r\n" +
               "Connection: close\r\n\r\n"); // Send the HTTP request headers

  // Serial.println("Request sent");

  int unread = -1;

  while (client.connected()) {                          // Wait for the response. The response is in XML format
    client.readStringUntil('<');                        // read until the first XML tag
    String tagname = client.readStringUntil('>');       // read until the end of this tag to get the tag name
    if (tagname == "fullcount") {                       // if the tag is <fullcount>, the next string will be the number of unread emails
      String unreadStr = client.readStringUntil('<');   // read until the closing tag (</fullcount>)
      unread = unreadStr.toInt();                       // convert from String to int
      break;                                            // stop reading
    }                                                   // if the tag is not <fullcount>, repeat and read the next tag
  }
  // Serial.println("Connection closed");

  return unread;                                        // Return the number of unread emails
}




int getUnread5() {    // a function to get the number of unread emails in your Gmail inbox
  //Serial.println("getunread5");
  WiFiClientSecure client; // Use WiFiClientSecure class to create TLS (HTTPS) connection
  // Serial.printf("Connecting to %s:%d ... \r\n", host, httpsPort);
  if (!client.connect(host, httpsPort)) {   // Connect to the Gmail server, on port 443
    // Serial.println("Connection failed");    // If the connection fails, stop and return
    return -1;
  }

  /*if (client.verify(fingerprint, host)) {   // Check the SHA-1 fingerprint of the SSL certificate
    Serial.println("Certificate matches");
    } else {                                  // if it doesn't match, it's not safe to continue
    Serial.println("Certificate doesn't match");
    return -1;
    }*/

  // Serial.print("Requesting URL: ");
  // Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Authorization: Basic " + credentials5 + "\r\n" +
               "User-Agent: ESP8266\r\n" +
               "Connection: close\r\n\r\n"); // Send the HTTP request headers

  //Serial.println("Request sent");

  int unread = -1;

  while (client.connected()) {                          // Wait for the response. The response is in XML format
    client.readStringUntil('<');                        // read until the first XML tag
    String tagname = client.readStringUntil('>');       // read until the end of this tag to get the tag name
    if (tagname == "fullcount") {                       // if the tag is <fullcount>, the next string will be the number of unread emails
      String unreadStr = client.readStringUntil('<');   // read until the closing tag (</fullcount>)
      unread = unreadStr.toInt();                       // convert from String to int
      break;                                            // stop reading
    }                                                   // if the tag is not <fullcount>, repeat and read the next tag
  }
  // Serial.println("Connection closed");

  return unread;                                        // Return the number of unread emails
}





int getUnread6() {    // a function to get the number of unread emails in your Gmail inbox
  // Serial.println("getunread6");
  WiFiClientSecure client; // Use WiFiClientSecure class to create TLS (HTTPS) connection
  //Serial.printf("Connecting to %s:%d ... \r\n", host, httpsPort);
  if (!client.connect(host, httpsPort)) {   // Connect to the Gmail server, on port 443
    //Serial.println("Connection failed");    // If the connection fails, stop and return
    return -1;
  }

  /*if (client.verify(fingerprint, host)) {   // Check the SHA-1 fingerprint of the SSL certificate
    Serial.println("Certificate matches");
    } else {                                  // if it doesn't match, it's not safe to continue
    Serial.println("Certificate doesn't match");
    return -1;
    }*/

  //Serial.print("Requesting URL: ");
  //Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Authorization: Basic " + credentials6 + "\r\n" +
               "User-Agent: ESP8266\r\n" +
               "Connection: close\r\n\r\n"); // Send the HTTP request headers

  //Serial.println("Request sent");

  int unread = -1;

  while (client.connected()) {                          // Wait for the response. The response is in XML format
    client.readStringUntil('<');                        // read until the first XML tag
    String tagname = client.readStringUntil('>');       // read until the end of this tag to get the tag name
    if (tagname == "fullcount") {                       // if the tag is <fullcount>, the next string will be the number of unread emails
      String unreadStr = client.readStringUntil('<');   // read until the closing tag (</fullcount>)
      unread = unreadStr.toInt();                       // convert from String to int
      break;                                            // stop reading
    }                                                   // if the tag is not <fullcount>, repeat and read the next tag
  }
  //Serial.println("Connection closed");

  return unread;                                        // Return the number of unread emails
}






void receive_data_from_arduino()
{
  if (Serial.available())
  {
    //Serial.println("how the data is cominng from arduino");
    s = Serial.readStringUntil('\n');
    if (s == "door is opened")
    {
      door_state = 1;
      counting_state = "coming";
      if(data==1)
      {
        counting_state="going";
        data=0;
      }
      Time = millis();
      person_coming_outside_sensor = 0;
      person_coming_inside_sensor = 0;
      person_going_outside_sensor = 0;
      person_going_inside_sensor = 0;

      Serial.write("bulb 1 is on\n");
      state = 1;
      digitalWrite(glowBulb, HIGH);
      Gsender *gsender = Gsender::Instance();    // Getting pointer to class instance
      String subject = "BULB 1 ON!";
      if (gsender->Subject(subject)->Send("technokratsbulb1on@gmail.com", "Setup test")) {

      }
    }
    else if (s == "door is closed")
    {
      door_state = 0;
      person_coming_outside_sensor = 0;
      person_coming_inside_sensor = 0;
      person_going_outside_sensor = 0;
      person_going_inside_sensor = 0;
      Time = millis();
    }
    //Serial.println(s);
  }
}




void outside_sensor_interrupt()
{
  Serial.println("outsensor");
  int a = millis();
  check_outside = 1;
  if (door_state == 1 && counting_state == "coming")
  {
    if (a > Time + 1000)
    {
      Time = millis();
      person_coming_outside_sensor++;
      Serial.print("person coming outside sensor while coming:-");
      Serial.println(person_coming_outside_sensor);
    }
  }
  else if (door_state == 1 && counting_state == "going")
  {
    if (a > Time + 1000)
    {
      Time = millis();
      person_going_outside_sensor++;

      Serial.print("person coming outside sensor while going:-");
      Serial.println(person_going_outside_sensor);
    }
  }
}

void inside_sensor_interrupt()
{
  if(person_inside_house==0 && counting_state!="coming")
  {
     Gsender *gsender = Gsender::Instance();    // Getting pointer to class instance
      String subject = "CHOR AAYA!";
      if (gsender->Subject(subject)->Send("gauravbansal233@gmail.com", "choor")) {

      }
      return;
  }
    Serial.println("inside sensor");
    int a = millis();
    check_inside = 1;
    if (door_state == 1 && counting_state == "coming")
    {
      if (a > Time + 1000)
      {
        Time = millis();
        person_coming_inside_sensor++;

        Serial.print("person coming inside sensor while coming:-");
        Serial.println(person_coming_inside_sensor);
      }
    }
    else 
    {
      if (a > Time + 1000)
      {
        Time = millis();
        counting_state = "going";
        data=1;
        person_going_inside_sensor++;
        Serial.write("open front door\n");
        Serial.print("person coming inside inside while going:-");
        Serial.println(person_going_inside_sensor);
        door_state = 1;
      }
    }

  }




void check()
{
  // Serial.println("check");
  int a = millis();
  if (a > Time + 5000)
  {
    // Serial.print("Number of person inside house:- ");
    // Serial.println(person_inside_house);
    if (counting_state == "coming" && person_coming_outside_sensor > 0 )
    {
      person_inside_house += person_coming_inside_sensor;
      if ((person_coming_outside_sensor - person_coming_inside_sensor) % 2 == 0)
      {
        Serial.write("close front door\n");
        counting_state = "";
        person_coming_outside_sensor = 0;
        person_coming_inside_sensor = 0;
        door_state = 0;
      }
      check_inside = 0;
      //      Serial.print("Number of person inside house:- ");
      //      Serial.println(person_inside_house);
      if (check_inside)
      {
        return;
      }
      Serial.println("coming");
      person_coming_outside_sensor -= person_coming_inside_sensor;
      person_coming_inside_sensor = 0;
      //door_state = 1;
    }
    else if (counting_state == "going" && person_going_inside_sensor > 0)
    {
      person_inside_house -= person_going_outside_sensor;
      if ((person_going_inside_sensor - person_going_outside_sensor) % 2 == 0)
      {
        Serial.write("close front door\n");
        counting_state = "";
        person_going_inside_sensor = 0;
        person_going_outside_sensor = 0;
        door_state = 0;
      }
      check_outside = 0;
      //          Serial.print("Number of person inside house:- ");
      //    Serial.println(person_inside_house);
      if (check_outside)
        return;
      Serial.println("going");
      person_going_inside_sensor -= person_going_outside_sensor;
      person_going_outside_sensor = 0;
      //door_state = 1;
    }
  }
}



void data_from_local()
{
  WiFiClient client = server.available();
  delay(10);
  if (!client) {
    return;
  }
  while (!client.available()) {
    delay(1);
  }
  request = client.readStringUntil('\r');
  client.flush();





  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  // client.println("Refresh: 15");  // refresh the page automatically every 5 sec
  client.println();
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("This is my room :)");
  client.println("<br><br>");



  client.println("<br><br>");
  client.println("<a href=\"/LED=1ON\"\"><button>Turn 1 On </button></a>");
  client.println("<a href=\"/LED=1OFF\"\"><button>Turn 1 Off </button></a><br />");
  client.println("<a href=\"/LED=2ON\"\"><button>Turn 2 On</button></a>");
  client.println("<a href=\"/LED=2OFF\"\"><button>Turn 2 Off </button></a><br />");
  client.println("<a href=\"/LED=3ON\"\"><button>Turn 3 On</button></a>");
  client.println("<a href=\"/LED=3OFF\"\"><button>Turn 3 Off </button></a><br />");
  client.println("<a href=\"/b1\"\"><button>buzzer on</button></a>");
  client.println("<a href=\"/b0\"\"><button>buzzer off</button></a><br />");
  client.println("<a href=\"/ALL_OFF\"\"><button>All off :) </button></a><br />");
  client.println("</html>");
  delay(1);
}





String getTime() {
  Serial.println("get time");
  WiFiClient client;
  while (!!!client.connect("google.com", 80)) {
    //Serial.println("connection failed, retrying...");
  }

  client.print("HEAD / HTTP/1.1\r\n\r\n");

  while (!!!client.available()) {
    yield();
  }

  while (client.available()) {
    if (client.read() == '\n') {
      if (client.read() == 'D') {
        if (client.read() == 'a') {
          if (client.read() == 't') {
            if (client.read() == 'e') {
              if (client.read() == ':') {
                client.read();
                String theDate = client.readStringUntil('\r');
                client.stop();
                return theDate;
              }
            }
          }
        }
      }
    }
  }
}
