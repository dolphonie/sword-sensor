#ifndef WIFI_FUNCTIONS_H
#define WIFI_FUNCTIONS_H

#include <string.h>

#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "config.h"

const int RESPONSE_TIMEOUT = 13000; //ms to wait for response from host
const uint16_t OUT_BUFFER_SIZE = 9000; //size of buffer to hold HTTP response

void setup_wifi() {
  WiFi.begin("stratus", "jeremysux");

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

/*----------------------------------
  char_append Function:
  Arguments:
    char* buff: pointer to character array which we will append a
    char c:
    uint16_t buff_size: size of buffer buff

  Return value:
    boolean: True if character appended, False if not appended (indicating buffer full)
*/
uint8_t char_append(char* buff, char c, uint16_t buff_size) {
  int len = strlen(buff);
  if (len > buff_size) return false;
  buff[len] = c;
  buff[len + 1] = '\0';
  return true;
}

/*----------------------------------
  do_http_request Function:
  Arguments:
    char* host: null-terminated char-array containing host to connect to
    char* request: null-terminated char-arry containing properly formatted HTTP request
    char* response: char-array used as output for function to contain response
    uint16_t response_size: size of response buffer (in bytes)
    uint16_t response_timeout: duration we'll wait (in ms) for a response from server
    uint8_t serial: used for printing debug information to terminal (true prints, false doesn't)

   Return value:
    void (none)
*/
void do_http_request(char* host, char* request, char* response, uint16_t response_size, uint16_t response_timeout, uint8_t serial) {
  // Adapted from 6.08 lab code/
  WiFiClient client; // instantiate a client object
  if (client.connect(host, 80)) { // try to connect to host on port 80
    if (serial) Serial.print(request);
    client.print(request);
    memset(response, 0, response_size); // Null out entire buffer
    uint32_t count = millis();
    while (client.connected()) { // while we remain connected read out data coming back
      client.readBytesUntil('\n', response, response_size);
      if (serial) Serial.println(response);
      if (strcmp(response, "\r") == 0) { // found a blank line
        break;
      }
      memset(response, 0, response_size);
      if (millis() - count > response_timeout) break;
    }
    memset(response, 0, response_size);
    count = millis();
    while (client.available()) { //read out remaining text (body of response)
      char_append(response, client.read(), OUT_BUFFER_SIZE);
    }
    if (serial) Serial.println(response);
    client.stop();
    if (serial) Serial.println("-----------");
  } else {
    if (serial) Serial.println("connection failed :/");
    if (serial) Serial.println("wait 0.5 sec...");
    client.stop();
  }
}

void http_post(char* body, char* request_buffer, char* response_buffer) {
  // Adapted from 6.08 lab code
  int body_len = strlen(body); // calculate body length (for header reporting)
  sprintf(request_buffer, "POST %s HTTP/1.1\r\n", URL);
  strcat(request_buffer, "Host: ");
  strcat(request_buffer, HOST);
  strcat(request_buffer, "\r\n");
  strcat(request_buffer, "Content-Type: application/x-www-form-urlencoded\r\n");
  sprintf(request_buffer + strlen(request_buffer), "Content-Length: %d\r\n", body_len); // append string formatted to end of request buffer
  strcat(request_buffer, "\r\n"); // new line from header to body
  strcat(request_buffer, body); // body
  strcat(request_buffer, "\r\n"); // header
//  Serial.println(request_buffer);
  do_http_request(HOST, request_buffer, response_buffer, sizeof(response_buffer), RESPONSE_TIMEOUT, false);
}

void http_get(char* params, char* request_buffer, char* response_buffer) {
  // Adapted from 6.08 lab code
  sprintf(request_buffer, "GET %s/?%s HTTP/1.1\r\n", URL, params);
  strcat(request_buffer, "Host: ");
  strcat(request_buffer, HOST);
  strcat(request_buffer, "\r\n");
  strcat(request_buffer, "\r\n"); // add blank line
  do_http_request(HOST, request_buffer, response_buffer, sizeof(response_buffer), RESPONSE_TIMEOUT, false);
}

#endif
