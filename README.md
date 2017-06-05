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
1. Create a public - private key pair (see placeholders in functions)
2. Encrypt and decrypt text using a private key (see placeholders in functions)
3. Call the various API's (see placeholders in functions)

Set up a web server.

Create API's on the webserver:
things we need the server API's to do: 
1. Sign in users: API validates user name and password are correct after receiving username & password 
2. Return a JSON string containing message names and message id numbers.
3. Get a message id, then send back the encrypted message text.
4. Store a public key in the database after receiving a username, password and public key.
