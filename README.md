# Full-Stack_GPX_File_Parser
A full stack GPX File Parser which utilizes C on the backend,  and HTML  / CSS and JavaScript on the front-end. A server-side connection is established through Node.JS to pass data from the front-end to the back-end algorithms. A MySQL database is used for user login, and for querying data parsed from the GPX file.

TO RUN THE APPLICATION:

1. After cloning the repository, go into the same directory as "app.js". 
2. Enter the command "npm install" to download the necessary modules. This step is asssuming Node.JS is downloaded already.
3. Then, cd into the "parser" library and enter "make" to compile the C code.
4. Next, cd back out into the same directory as "app.js" again, and then launch the site with "npm run dev 8123".
5. Lastly, view the website on "localhost:8123".

IF THE SCHOOL SERVER IS BEING USED OR A SPECIFIC PORT NUMBER:
1. Instead of "8123", add the personal port number there.
2. Run "npm run dev personalPort", where "personalPort" is your port number, and view it on the server (e.g. The University of Guelph's servers would be "cis2750.socs.uoguelph.ca:pesronalPort".
