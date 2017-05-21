# EncryptedMessaging
This is an encrypted messaging app. 

The application is under development. 

Files: 
EncryptedMessaging.cpp = this is the Windows PC based client for interacting with the service.

Team Members:
Matt Nutsch
Tony Quach
Daniel Jackson
Yoav Gill
Shawn Harmsen

Things to do:

Add code to the encyrptedmessaging.cpp client to:
1. create a public - private key pair (see placeholders in functions)
2. encrypt and decrypt text using a private key (see placeholders in functions)
3. call the various API's (see placeholders in functions)

Set up a web server.

Create API's on the webserver:
things we need the server API's to do: 
1. receives username password sign in API validates user name and password are correct 
2. return a JSON string of message names and message id numbers 
3. gets a message id, sends back the encrypted message body 
4. receives a username password and public key, API should store the key in the database
