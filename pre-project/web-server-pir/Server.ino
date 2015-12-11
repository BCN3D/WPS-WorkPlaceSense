void server_function() {
  //Save client if there is anyone, else, return to loop
  WiFiClient client = server.available();
  if (!client) return;
  
  //Whats that??
  while (!client.available()) delay(1);
  
  //Save in req, the client request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  //Flush the client
  client.flush();

  //Depends on the request it continue the code or return to loop
  if (req.indexOf("/PIR") != -1) {
    //
  }
  else {
    client.stop();
    return;
  }

  //Here write the response to the request, the text and deppend on the value, if there are movement or not.
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  client.print("<span style=\"font-size:80px\">Movement detected: ");
  if (movestatus == HIGH) {
    client.print("Yes");
  } else {
    client.print("No");
  }
  client.print("</span>");

  delay(1);
  Serial.println("Client disonnected");
}
