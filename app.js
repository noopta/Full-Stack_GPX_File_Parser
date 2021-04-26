'use strict'

// C library API
const ffi = require('ffi-napi');

// Express App (Routes)
const express = require("express");
const app = express();
const path = require("path");
const fileUpload = require('express-fileupload');

app.use(fileUpload());
app.use(express.static(path.join(__dirname + '/uploads')));

// Minimization
const fs = require('fs');
const JavaScriptObfuscator = require('javascript-obfuscator');

// Important, pass in port as in `npm run dev 1234`, do not change
const portNum = process.argv[2];

// Send HTML at root, do not change
app.get('/', function (req, res) {
  res.sendFile(path.join(__dirname + '/public/index.html'));
});

// Send Style, do not change
app.get('/style.css', function (req, res) {
  //Feel free to change the contents of style.css to prettify your Web app
  res.sendFile(path.join(__dirname + '/public/style.css'));
});

// Send obfuscated JS, do not change
app.get('/index.js', function (req, res) {
  fs.readFile(path.join(__dirname + '/public/index.js'), 'utf8', function (err, contents) {
    const minimizedContents = JavaScriptObfuscator.obfuscate(contents, { compact: true, controlFlowFlattening: true });
    res.contentType('application/javascript');
    res.send(minimizedContents._obfuscatedCode);
  });
});

//Respond to POST requests that upload files to uploads/ directory
app.post('/upload', function (req, res) {
  if (!req.files) {
    return res.status(400).send('No files were uploaded.');
  }

  let uploadFile = req.files.uploadFile;

  // Use the mv() method to place the file somewhere on your server
  uploadFile.mv('uploads/' + uploadFile.name, function (err) {
    if (err) {
      return res.status(500).send(err);
    }

    res.redirect('/');
  });
});

//Respond to GET requests for files in the uploads/ directory
app.get('/uploads/:name', function (req, res) {
  fs.stat('uploads/' + req.params.name, function (err, stat) {
    if (err == null) {
      res.sendFile(path.join(__dirname + '/uploads/' + req.params.name));
    } else {
      console.log('Error in file downloading route: ' + err);
      res.send('');
    }
  });
});

//******************** Your code goes here ********************


//Sample endpoint
app.get('/endpoint1', function (req, res) {

  let retStr = req.query.data1 + " " + req.query.data2;

  res.send(
    {
      somethingElse: retStr
    }
  );
});

app.get('/getFiles', function (req, res) {
  let stringName = "tempString";

  res.send({
    returnString: stringName
  });
});

app.get('/testFiles', function (req, res) {

  console.log("TESTING");
  let sharedLib = ffi.Library('./libgpxparser', {
    //'JsSVG' : ['string', ['string']],
    'newCreateGPX': ['string', ['string']],
    'newRouteToJSON': ['string', ['string']],
  });


  let stringName = "tempString";
  const fs = require('fs');
  let fileNames = [];
  let fileInfo = [];
  let routeList = [];
  // make an array of the file information
  // add to the array and call newCreateGPX for each gpx files
  // parse the string
  // add the parsed string to fileInfo
  // return the fileInfo array to the front end

  fs.readdirSync("uploads/").forEach(file => {


    var lastFour = file.substr(file.length - 4);

    if (lastFour == ".gpx") {
      var temporaryVal = sharedLib.newCreateGPX('uploads/' + file);
      if (temporaryVal != "INVALID") {
        fileInfo.push(temporaryVal);
        fileNames.push(file);
      } else {
        console.log("INVALID FILE FOUND");
      }
      //  let tempVarTwo = JSON.parse(temporaryVal);
      //console.log(tempVarTwo);
    }


  });
  res.send({
    returnString: stringName,
    returnArray: fileNames,
    returnInfo: fileInfo,
  });
});

app.get('/getRouteList', function (req, res) {

  console.log("GET ROUTE LIST REACHED ");
  let sharedLib = ffi.Library('./libgpxparser', {
    //'JsSVG' : ['string', ['string']],
    'newCreateGPX': ['string', ['string']],
    'newRouteToJSON': ['string', ['string']],
    'newTrackToJSON': ['string', ['string']],
    'routeDataListToJSON': ['string', ['string']],
    'trackDataListToJSON': ['string', ['string']],

  });

  const fs = require('fs');

  let routeList = [];
  let trackList = [];
  let dataList = [];
  let trackDataList = [];
  // make an array of the file information
  // add to the array and call newCreateGPX for each gpx files
  // parse the string
  // add the parsed string to fileInfo
  // return the fileInfo array to the front end

  let tempString = sharedLib.newRouteToJSON('uploads/' + req.query.data1);
  let secondTempString = sharedLib.newTrackToJSON('uploads/' + req.query.data1);
  let thirdTempString = sharedLib.routeDataListToJSON('uploads/' + req.query.data1);
  let fourthTempString = sharedLib.trackDataListToJSON('uploads/' + req.query.data1);

  //console.log(tempString);
  // console.log("TRACKS " + secondTempString);
  console.log("TESTING GPX DATA LIST CALLBACK: " + fourthTempString);

  trackList.push(secondTempString);
  routeList.push(tempString);
  dataList.push(thirdTempString);
  trackDataList.push(fourthTempString);


  res.send({
    docRouteInfo: routeList,
    docTrackInfo: trackList,
    docRouteData: dataList,
    docTrackData: trackDataList,
  });
});


app.get('/convertJSONtoGPX', function (req, res) {

  console.log("GET TRACK LIST REACHED ");
  let sharedLib = ffi.Library('./libgpxparser', {
    //'JsSVG' : ['string', ['string']],
    'newCreateGPX': ['string', ['string']],
    'newTrackToJSON': ['string', ['string']],
    'newJSONtoGPX': ['string', ['string']],
  });

  const fs = require('fs');

  var parsedString = req.query.data1;
  console.log("DATA = " + req.query.data1);

  let tempVar = sharedLib.newJSONtoGPX(req.query.data1);
  console.log("MADE IT TO APP.JS " + tempVar);

  var oldPath = './' + tempVar;
  var newPath = 'uploads/' + tempVar;

  fs.rename(oldPath, newPath, function (err) {
    if (err) {
      console.log("CANNOT UPLOAD FILE");
    }
    console.log('Successfully renamed - AKA moved!')
  });

  // call the c function
  // pass the values from the front end to the c function
  // create the gpx doc and gpx file
  // also send the returned values to the front end to upload the file to the file log panel


  res.send({
    // docRouteInfo: trackList,
  });
});

app.get('/addRoute', function (req, res) {

  // console.log("ADD ROUTE REACHED ");
  let sharedLib = ffi.Library('./libgpxparser', {
    //'JsSVG' : ['string', ['string']],
    'newCreateGPX': ['string', ['string']],
    'newTrackToJSON': ['string', ['string']],
    'newJSONtoGPX': ['string', ['string']],
    'newAddRoute': ['string', ['string', 'string', 'string']],
  });

  const fs = require('fs');

  let tempVar = sharedLib.newAddRoute(req.query.data1, req.query.data2, 'uploads/' + req.query.data3);
  tempVar = JSON.parse(tempVar)
  console.log("MADE IT TO NEW ADD ROUTE" + tempVar.numRoutes);

  // var oldPath = './' + tempVar;
  // var newPath = 'uploads/' + tempVar;

  //fs.rename(oldPath, newPath, function (err) {
  // if (err) {
  //   console.log("CANNOT UPLOAD FILE");
  // }
  // console.log('Success')
  // });

  // call the c function
  // pass the values from the front end to the c function
  // create the gpx doc and gpx file
  // also send the returned values to the front end to upload the file to the file log panel


  res.send({
    gpxInfo: tempVar,
    fileName: req.query.data3,
    numRoutes: tempVar.numRoutes,
  });
});


app.get('/addToDoc', function (req, res) {

  // console.log("ADD ROUTE REACHED ");
  let sharedLib = ffi.Library('./libgpxparser', {
    //'JsSVG' : ['string', ['string']],
    'newCreateGPX': ['string', ['string']],
    'newTrackToJSON': ['string', ['string']],
    'newJSONtoGPX': ['string', ['string']],
    'newAddRoute': ['string', ['string', 'string', 'string']],
    'updateDoc': ['string', ['string']]
  });

  const fs = require('fs');

  var tempVar = sharedLib.updateDoc('uploads/' + req.query.theData);
  console.log("TESTING IT OUT " + tempVar);


  res.send({
    gpxInfo: tempVar,
    fileName: req.query.data3
  });
});


app.get('/createConnection', function (req, res) {

  // console.log("ADD ROUTE REACHED ");
  let sharedLib = ffi.Library('./libgpxparser', {
    //'JsSVG' : ['string', ['string']],
    'newCreateGPX': ['string', ['string']],
    'newTrackToJSON': ['string', ['string']],
    'newJSONtoGPX': ['string', ['string']],
    'newAddRoute': ['string', ['string', 'string', 'string']],
    'updateDoc': ['string', ['string']]
  });

  const fs = require('fs');
  // use data passed in to create an SQL connection
  // remember to create a variable to provide the host name
  // then start implementing the SQL queries and commands

  // STORE ALL FILES
  // create a counter for the number of files in the file log panel
  // the counter should be passed into here, app.js
  // then itererate through the files in the file log panel where 
  // the number of routes is greater than 0

  let dbConf = {
    host: 'dursley.socs.uoguelph.ca',
    user: req.query.userName,
    password: req.query.password,
    database: req.query.databaseName,
  };

  let insRec = "INSERT INTO newerStudent (last_name, first_name, mark) VALUES ('Hugo','Victor','B+'),('Rudin','Walter','A-'),('Stevens','Richard','C')";

  async function main() {
    // get the client
    const mysql = require('mysql2/promise');

    let connection;

    var numberOfFiles = req.query.nFiles;

    try {
      // create the connection
      connection = await mysql.createConnection(dbConf);

      // **** uncomment if you want to create the table on the fly ****
      // connection.execute("create table student (id int not null auto_increment,  last_name char(15),  first_name char(15), mark char(2), primary key(id) )");


      // CREATING THE THREE FILES

      await connection.execute('CREATE TABLE IF NOT EXISTS `FILE` (gpx_id INT AUTO_INCREMENT PRIMARY KEY, file_name VARCHAR(60) NOT NULL, ver DECIMAL(2,1) NOT NULL, creator VARCHAR(256) NOT NULL)');
      await connection.execute('CREATE TABLE IF NOT EXISTS  `ROUTE` (route_id INT AUTO_INCREMENT PRIMARY KEY, route_name VARCHAR(256), route_len FLOAT(15,7) NOT NULL)');
      await connection.execute('CREATE TABLE IF NOT EXISTS `POINT` (point_id INT AUTO_INCREMENT PRIMARY KEY, point_index INT NOT NULL, latitude DECIMAL(11,7) NOT NULL, point_name VARCHAR(256), route_id INT NOT NULL)');
      //Populate the table
      await connection.execute(insRec);

      //Run select query, wait for results
      const [rows1, fields1] = await connection.execute('SELECT * from `newerStudent` ORDER BY `last_name`');

      // console.log("\nSorted by last name:");
      // for (let row of rows1) {
      //  console.log("ID: " + row.id + " Last name: " + row.last_name + " First name: " + row.first_name + " mark: " + row.mark);
      // }

      //Run select query, wait for results
      // console.log("\nSorted by first name:");
      // const [rows2, fields2] = await connection.execute('SELECT * from `newerStudent` ORDER BY `first_name`');
      // for (let row of rows2) {
      //   console.log("ID: " + row.id + " Last name: " + row.last_name + " First name: " + row.first_name + " mark: " + row.mark);
      // }

      await connection.execute("DELETE FROM newerStudent");
    } catch (e) {
      console.log("Query error: " + e);
    } finally {
      if (connection && connection.end) connection.end();
    }

  }

  main();

  res.send({
    // what is sent back
    gpxInfo: "something",
    fileName: "fileName"
  });
});


app.get('/populateTables', function (req, res) {

  // console.log("ADD ROUTE REACHED ");
  let sharedLib = ffi.Library('./libgpxparser', {
    //'JsSVG' : ['string', ['string']],
    'newCreateGPX': ['string', ['string']],
    'newTrackToJSON': ['string', ['string']],
    'newJSONtoGPX': ['string', ['string']],
    'newAddRoute': ['string', ['string', 'string', 'string']],
    'updateDoc': ['string', ['string']],
    'newRouteToJSON': ['string', ['string']],
    'waypointToJSON': ['string', ['string', 'string']],
  });



  const fs = require('fs');

  var fileName = req.query.theFile;
  var fileCreator = req.query.theCreator;
  var fileVersion = req.query.theVersion;
  var totalWaypoints = req.query.numWaypoints;
  var totalRoutes = req.query.numRoutes;
  var totalTracks = req.query.numTracks;

  // create MySQL connection and add the values into the FILE table

  let dbConf = {
    host: 'dursley.socs.uoguelph.ca',
    user: req.query.username,
    password: req.query.password,
    database: req.query.databaseName,
  };

  async function main() {
    // get the client
    const mysql = require('mysql2/promise');

    let connection;

    var numberOfFiles = req.query.nFiles;

    try {
      // create the connection
      connection = await mysql.createConnection(dbConf);

      // **** uncomment if you want to create the table on the fly ****
      // connection.execute("create table student (id int not null auto_increment,  last_name char(15),  first_name char(15), mark char(2), primary key(id) )");


      // CREATING THE THREE FILES
      //  await connection.execute("DROP TABLE `POINT`");
      await connection.execute('CREATE TABLE IF NOT EXISTS `FILE` (gpx_id INT AUTO_INCREMENT PRIMARY KEY, file_name VARCHAR(60) NOT NULL, ver DECIMAL(2,1) NOT NULL, creator VARCHAR(256) NOT NULL)');
      await connection.execute('CREATE TABLE IF NOT EXISTS  `ROUTE` (route_id INT AUTO_INCREMENT PRIMARY KEY, route_name VARCHAR(256), route_len FLOAT(15,7) NOT NULL, gpx_id INT NOT NULL)');
      await connection.execute('CREATE TABLE IF NOT EXISTS `POINT` (point_id INT AUTO_INCREMENT PRIMARY KEY, point_index INT NOT NULL, latitude DECIMAL(11,7) NOT NULL, longitude DECIMAL(11,7) NOT NULL, point_name VARCHAR(256), route_id INT NOT NULL)');
      //Populate the table

      let values = " VALUES (" + "'" + fileName + "'," + "'" + fileVersion + "'," + "'" + fileCreator + "')";

      let insRec = "INSERT INTO FILE (file_name, ver, creator)" + values;
      await connection.execute(insRec);

      //Run select query, wait for results
      const [rows1, fields1] = await connection.execute('SELECT * from `FILE` ORDER BY `file_name`');
      var loopCounter = 0;

      for (let row of rows1) {
        console.log("ID: " + row.gpx_id + " FILE NAME: " + row.file_name + " VERSION: " + row.ver + " CREATOR: " + row.creator);

        // for each row of each file, run createGPXdoc on the file and then pass the data onto the Route table
        var findFileName = "uploads/" + row.file_name;
        var routeListInfo = sharedLib.newRouteToJSON(findFileName);


        if (routeListInfo == "[") {

        } else {
          console.log("ROUTE LIST INFO: " + routeListInfo);
          var convertedJSON = JSON.parse(routeListInfo);
          var objLen = convertedJSON.length;



          //    if (loopCounter < objLen) {
          for (let tempRow of convertedJSON) {

            // this loop is iterating through each route converted to JSON, for the current FILE

            await connection.execute("DELETE FROM `ROUTE` WHERE route_name = " + "'" + tempRow.name + "'");

            let rteValues = " VALUES (" + "'" + tempRow.name + "'," + "'" + tempRow.len + "'," + "'" + row.gpx_id + "')";
            let insRte = "INSERT INTO ROUTE (route_name, route_len, gpx_id)" + rteValues;

            await connection.execute(insRte);
            loopCounter = loopCounter + 1;

            // create another loop that will populate the POINT table for each ROUTE
            // convert each point in the route to JSON
            // then add the JSON containing the point info the the POINT table 

            // create a C function that accepts a f
            // CALLING C FUNCTION BELOW

            var temporaryVar = sharedLib.waypointToJSON(tempRow.name, row.file_name);

            console.log(temporaryVar);
            console.log(temporaryVar.charAt(1));
            // parse the temporaryVar variable and add the points into the points table
            var parsedVar = JSON.parse(temporaryVar);

            for (let pointRow of parsedVar) {

              await connection.execute("DELETE FROM `POINT` WHERE latitude = '" + pointRow.latitude + "' && longitude ='" + pointRow.longitude + "'");
              let pointValues = " VALUES (" + "'" + pointRow.point_index + "'," + "'" + pointRow.latitude + "'," + "'" + pointRow.longitude + "'," + "'" + pointRow.point_name + "'," + "'" + tempRow.route_id + "')";
              let insPoint = "INSERT INTO POINT (point_index, latitude, longitude, point_name, route_id)" + pointValues;

              await connection.execute(insPoint);

            }

          }
          //}
        }
      }

      const [rows3, fields3] = await connection.execute('SELECT * from `ROUTE` ORDER BY `route_name`');
      for (let secondTempRow of rows3) {
        console.log(" ROUTE_NAME: " + secondTempRow.route_name + " ROUTE_LEN: " + secondTempRow.route_len + " ROUTE_ID: " + secondTempRow.route_id);
      }

      const [row4, fields4] = await connection.execute('SELECT * FROM `POINT`');
      for (let thirdTempRow of row4) {
        //console.log("POINT ID: " + thirdTempRow.point_id + " POINT INDEX: " + thirdTempRow.point_index + " LATITUDE: " + thirdTempRow.latitude + " LONGITUDE: " + thirdTempRow.longitude + " ROUTE ID: " + thirdTempRow.route_id);
      }



      // await connection.execute("DELETE FROM `FILE`");
      // await connection.execute("DELETE FROM `ROUTE`");
      // await connection.execute("DELETE FROM `POINT`");

    } catch (e) {
      console.log("Query error: " + e);
    } finally {
      if (connection && connection.end) connection.end();
    }

  }

  main();


  res.send({
    gpxInfo: "something",
    fileName: "fileName"
  });
});


app.get('/clearAllTables', function (req, res) {

  // console.log("ADD ROUTE REACHED ");
  let sharedLib = ffi.Library('./libgpxparser', {
    //'JsSVG' : ['string', ['string']],
    'newCreateGPX': ['string', ['string']],
    'newTrackToJSON': ['string', ['string']],
    'newJSONtoGPX': ['string', ['string']],
    'newAddRoute': ['string', ['string', 'string', 'string']],
    'updateDoc': ['string', ['string']]
  });

  const fs = require('fs');
  // use data passed in to create an SQL connection
  // remember to create a variable to provide the host name
  // then start implementing the SQL queries and commands

  // STORE ALL FILES
  // create a counter for the number of files in the file log panel
  // the counter should be passed into here, app.js
  // then itererate through the files in the file log panel where 
  // the number of routes is greater than 0

  let dbConf = {
    host: 'dursley.socs.uoguelph.ca',
    user: req.query.userName,
    password: req.query.password,
    database: req.query.databaseName,
  };

  //let insRec = "INSERT INTO newerStudent (last_name, first_name, mark) VALUES ('Hugo','Victor','B+'),('Rudin','Walter','A-'),('Stevens','Richard','C')";

  async function main() {
    // get the client
    const mysql = require('mysql2/promise');

    let connection;

    // var numberOfFiles = req.query.nFiles;

    try {
      // create the connection
      connection = await mysql.createConnection(dbConf);

      // **** uncomment if you want to create the table on the fly ****
      // connection.execute("create table student (id int not null auto_increment,  last_name char(15),  first_name char(15), mark char(2), primary key(id) )");


      // CREATING THE THREE FILES


      //Run select query, wait for results
      //   const [rows1, fields1] = await connection.execute('SELECT * from `newerStudent` ORDER BY `last_name`');


      await connection.execute("DELETE FROM `POINT`");
      await connection.execute("DELETE FROM `ROUTE`");
      await connection.execute("DELETE FROM `FILE`");


      await connection.execute("DROP TABLE `POINT`");
      await connection.execute("DROP TABLE `ROUTE`");
      await connection.execute("DROP TABLE `FILE`");


      await connection.execute('CREATE TABLE IF NOT EXISTS `FILE` (gpx_id INT AUTO_INCREMENT PRIMARY KEY, file_name VARCHAR(60) NOT NULL, ver DECIMAL(2,1) NOT NULL, creator VARCHAR(256) NOT NULL)');
      await connection.execute('CREATE TABLE IF NOT EXISTS  `ROUTE` (route_id INT AUTO_INCREMENT PRIMARY KEY, route_name VARCHAR(256), route_len FLOAT(15,7) NOT NULL, gpx_id INT NOT NULL)');
      await connection.execute('CREATE TABLE IF NOT EXISTS `POINT` (point_id INT AUTO_INCREMENT PRIMARY KEY, point_index INT NOT NULL, latitude DECIMAL(11,7) NOT NULL, longitude DECIMAL(11,7) NOT NULL, point_name VARCHAR(256), route_id INT NOT NULL)');

      console.log("ALL TABLES CLEARED");

    } catch (e) {
      console.log("Query error: " + e);
    } finally {
      if (connection && connection.end) connection.end();
    }

  }

  main();

  res.send({
    // what is sent back
    gpxInfo: "something",
    fileName: "fileName"
  });
});



app.get('/displayDB', function (req, res) {

  // console.log("ADD ROUTE REACHED ");
  let sharedLib = ffi.Library('./libgpxparser', {
    //'JsSVG' : ['string', ['string']],
    'newCreateGPX': ['string', ['string']],
    'newTrackToJSON': ['string', ['string']],
    'newJSONtoGPX': ['string', ['string']],
    'newAddRoute': ['string', ['string', 'string', 'string']],
    'updateDoc': ['string', ['string']]
  });

  const fs = require('fs');
  // use data passed in to create an SQL connection
  // remember to create a variable to provide the host name
  // then start implementing the SQL queries and commands

  // STORE ALL FILES
  // create a counter for the number of files in the file log panel
  // the counter should be passed into here, app.js
  // then itererate through the files in the file log panel where 
  // the number of routes is greater than 0

  let dbConf = {
    host: 'dursley.socs.uoguelph.ca',
    user: req.query.userName,
    password: req.query.password,
    database: req.query.databaseName,
  };

  //let insRec = "INSERT INTO newerStudent (last_name, first_name, mark) VALUES ('Hugo','Victor','B+'),('Rudin','Walter','A-'),('Stevens','Richard','C')";

  let numFileRows = 0;
  let numRouteRows = 0;
  let numPointRows = 0;

  async function main() {
    // get the client
    const mysql = require('mysql2/promise');

    let connection;

    // var numberOfFiles = req.query.nFiles;

    try {
      // create the connection
      connection = await mysql.createConnection(dbConf);

      // **** uncomment if you want to create the table on the fly ****
      // connection.execute("create table student (id int not null auto_increment,  last_name char(15),  first_name char(15), mark char(2), primary key(id) )");


      // CREATING THE THREE FILES


      //Run select query, wait for results
      const [rows1, fields1] = await connection.execute('SELECT * from `FILE`');
      const [rows2, fields2] = await connection.execute('SELECT * from `ROUTE`');
      const [rows3, fields3] = await connection.execute('SELECT * from `POINT`');

      // iterate through each table and increment their respective counters on each iter

      for (let tempRow of rows1) {
        numFileRows++;
      }

      for (let secondTempRow of rows2) {
        numRouteRows++;
      }

      for (let thirdTempRow of rows3) {
        numPointRows++;
      }

      console.log("FILE ROWS = " + numFileRows + " ROUTE ROWS = " + numRouteRows + " POINT ROWS = " + numPointRows);

      res.send({
        // what is sent back
        totalFileRows: numFileRows,
        totalRouteRows: numRouteRows,
        totalPointRows: numPointRows,
      });




    } catch (e) {
      console.log("Query error: " + e);
    } finally {
      if (connection && connection.end) connection.end();
    }

  }

  main();

});


app.get('/orderByRouteNames', function (req, res) {

  // console.log("ADD ROUTE REACHED ");
  let sharedLib = ffi.Library('./libgpxparser', {
    //'JsSVG' : ['string', ['string']],
    'newCreateGPX': ['string', ['string']],
    'newTrackToJSON': ['string', ['string']],
    'newJSONtoGPX': ['string', ['string']],
    'newAddRoute': ['string', ['string', 'string', 'string']],
    'updateDoc': ['string', ['string']]
  });

  const fs = require('fs');
  // use data passed in to create an SQL connection
  // remember to create a variable to provide the host name
  // then start implementing the SQL queries and commands

  // STORE ALL FILES
  // create a counter for the number of files in the file log panel
  // the counter should be passed into here, app.js
  // then itererate through the files in the file log panel where 
  // the number of routes is greater than 0

  let dbConf = {
    host: 'dursley.socs.uoguelph.ca',
    user: req.query.userName,
    password: req.query.password,
    database: req.query.databaseName,
  };

  //let insRec = "INSERT INTO newerStudent (last_name, first_name, mark) VALUES ('Hugo','Victor','B+'),('Rudin','Walter','A-'),('Stevens','Richard','C')";

  async function main() {
    // get the client
    const mysql = require('mysql2/promise');

    let connection;

    // var numberOfFiles = req.query.nFiles;

    try {
      // create the connection
      connection = await mysql.createConnection(dbConf);

      // **** uncomment if you want to create the table on the fly ****
      // connection.execute("create table student (id int not null auto_increment,  last_name char(15),  first_name char(15), mark char(2), primary key(id) )");


      // CREATING THE THREE FILES


      //Run select query, wait for results
      const [rows1, fields1] = await connection.execute('SELECT * from `ROUTE` ORDER BY `route_name`');
      var obj = {};
      var i = 0;

      for (let row of rows1) {
        console.log("ROUTE_NAME: " + row.route_name + " ROUTE_ID: " + row.route_id + " ROUTE_LEN: " + row.route_len + " GPX_ID: " + row.gpx_id);
        obj[i] = row;
        i++;
      }

      console.log(obj);

      res.send({
        // what is sent back
        gpxInfo: "something",
        fileName: "fileName",
        returnObj: obj,
      });


    } catch (e) {
      console.log("Query error: " + e);
    } finally {
      if (connection && connection.end) connection.end();
    }

  }

  main();

});


app.get('/orderByRouteLen', function (req, res) {

  // console.log("ADD ROUTE REACHED ");
  let sharedLib = ffi.Library('./libgpxparser', {
    //'JsSVG' : ['string', ['string']],
    'newCreateGPX': ['string', ['string']],
    'newTrackToJSON': ['string', ['string']],
    'newJSONtoGPX': ['string', ['string']],
    'newAddRoute': ['string', ['string', 'string', 'string']],
    'updateDoc': ['string', ['string']]
  });

  const fs = require('fs');
  // use data passed in to create an SQL connection
  // remember to create a variable to provide the host name
  // then start implementing the SQL queries and commands

  // STORE ALL FILES
  // create a counter for the number of files in the file log panel
  // the counter should be passed into here, app.js
  // then itererate through the files in the file log panel where 
  // the number of routes is greater than 0

  let dbConf = {
    host: 'dursley.socs.uoguelph.ca',
    user: req.query.userName,
    password: req.query.password,
    database: req.query.databaseName,
  };

  //let insRec = "INSERT INTO newerStudent (last_name, first_name, mark) VALUES ('Hugo','Victor','B+'),('Rudin','Walter','A-'),('Stevens','Richard','C')";

  async function main() {
    // get the client
    const mysql = require('mysql2/promise');

    let connection;

    // var numberOfFiles = req.query.nFiles;

    try {
      // create the connection
      connection = await mysql.createConnection(dbConf);

      // **** uncomment if you want to create the table on the fly ****
      // connection.execute("create table student (id int not null auto_increment,  last_name char(15),  first_name char(15), mark char(2), primary key(id) )");


      // CREATING THE THREE FILES


      //Run select query, wait for results
      const [rows1, fields1] = await connection.execute('SELECT * from `ROUTE` ORDER BY `route_len`');
      var obj = {};
      var i = 0;

      for (let row of rows1) {
        //  console.log("ROUTE_NAME: " + row.route_name + " ROUTE_ID: " + row.route_id + " ROUTE_LEN: " + row.route_len + " GPX_ID: " + row.gpx_id);
        obj[i] = row;
        i++;
      }

      console.log(obj);

      res.send({
        // what is sent back
        gpxInfo: "something",
        fileName: "fileName",
        returnObj: obj,
      });


    } catch (e) {
      console.log("Query error: " + e);
    } finally {
      if (connection && connection.end) connection.end();
    }

  }

  main();

});

app.get('/getFileNameAndID', function (req, res) {

  // console.log("ADD ROUTE REACHED ");
  let sharedLib = ffi.Library('./libgpxparser', {
    //'JsSVG' : ['string', ['string']],
    'newCreateGPX': ['string', ['string']],
    'newTrackToJSON': ['string', ['string']],
    'newJSONtoGPX': ['string', ['string']],
    'newAddRoute': ['string', ['string', 'string', 'string']],
    'updateDoc': ['string', ['string']]
  });

  const fs = require('fs');
  // use data passed in to create an SQL connection
  // remember to create a variable to provide the host name
  // then start implementing the SQL queries and commands

  // STORE ALL FILES
  // create a counter for the number of files in the file log panel
  // the counter should be passed into here, app.js
  // then itererate through the files in the file log panel where 
  // the number of routes is greater than 0

  let dbConf = {
    host: 'dursley.socs.uoguelph.ca',
    user: req.query.userName,
    password: req.query.password,
    database: req.query.databaseName,
  };

  //let insRec = "INSERT INTO newerStudent (last_name, first_name, mark) VALUES ('Hugo','Victor','B+'),('Rudin','Walter','A-'),('Stevens','Richard','C')";

  async function main() {
    // get the client
    const mysql = require('mysql2/promise');

    let connection;

    // var numberOfFiles = req.query.nFiles;

    try {
      // create the connection
      connection = await mysql.createConnection(dbConf);

      // **** uncomment if you want to create the table on the fly ****
      // connection.execute("create table student (id int not null auto_increment,  last_name char(15),  first_name char(15), mark char(2), primary key(id) )");


      // CREATING THE THREE FILES


      //Run select query, wait for results
      const [rows1, fields1] = await connection.execute('SELECT * from `FILE`');
      var obj = {};
      var i = 0;

      for (let row of rows1) {
        //  console.log("ROUTE_NAME: " + row.route_name + " ROUTE_ID: " + row.route_id + " ROUTE_LEN: " + row.route_len + " GPX_ID: " + row.gpx_id);
        obj[i] = row;
        i++;
      }

      console.log(obj);

      res.send({
        // what is sent back
        gpxInfo: "something",
        fileName: "fileName",
        returnObj: obj,
      });


    } catch (e) {
      console.log("Query error: " + e);
    } finally {
      if (connection && connection.end) connection.end();
    }

  }

  main();

});



app.get('/getSpecifiedRouteInfo', function (req, res) {

  // console.log("ADD ROUTE REACHED ");
  let sharedLib = ffi.Library('./libgpxparser', {
    //'JsSVG' : ['string', ['string']],
    'newCreateGPX': ['string', ['string']],
    'newTrackToJSON': ['string', ['string']],
    'newJSONtoGPX': ['string', ['string']],
    'newAddRoute': ['string', ['string', 'string', 'string']],
    'updateDoc': ['string', ['string']]
  });

  const fs = require('fs');
  // use data passed in to create an SQL connection
  // remember to create a variable to provide the host name
  // then start implementing the SQL queries and commands

  // STORE ALL FILES
  // create a counter for the number of files in the file log panel
  // the counter should be passed into here, app.js
  // then itererate through the files in the file log panel where 
  // the number of routes is greater than 0

  let dbConf = {
    host: 'dursley.socs.uoguelph.ca',
    user: req.query.userName,
    password: req.query.password,
    database: req.query.databaseName,
  };

  //let insRec = "INSERT INTO newerStudent (last_name, first_name, mark) VALUES ('Hugo','Victor','B+'),('Rudin','Walter','A-'),('Stevens','Richard','C')";

  async function main() {
    // get the client
    const mysql = require('mysql2/promise');

    let connection;

    // var numberOfFiles = req.query.nFiles;

    try {
      // create the connection
      connection = await mysql.createConnection(dbConf);

      // **** uncomment if you want to create the table on the fly ****
      // connection.execute("create table student (id int not null auto_increment,  last_name char(15),  first_name char(15), mark char(2), primary key(id) )");


      // CREATING THE THREE FILES


      //Run select query, wait for results
      var theID = req.query.gpxID;

      const [rows1, fields1] = await connection.execute("SELECT * from `ROUTE` WHERE gpx_id = " + "'" + theID + "' ORDER BY route_name");
      var obj = {};
      var i = 0;

      for (let row of rows1) {
        //  console.log("ROUTE_NAME: " + row.route_name + " ROUTE_ID: " + row.route_id + " ROUTE_LEN: " + row.route_len + " GPX_ID: " + row.gpx_id);
        obj[i] = row;
        i++;
      }

      console.log("SPECIFIED FILE ROUTES: " + obj);

      res.send({
        // what is sent back
        gpxInfo: "something",
        fileName: "fileName",
        returnObj: obj,
      });


    } catch (e) {
      console.log("Query error: " + e);
    } finally {
      if (connection && connection.end) connection.end();
    }

  }

  main();

});



app.get('/getSpecifiedPoints', function (req, res) {

  // console.log("ADD ROUTE REACHED ");
  let sharedLib = ffi.Library('./libgpxparser', {
    //'JsSVG' : ['string', ['string']],
    'newCreateGPX': ['string', ['string']],
    'newTrackToJSON': ['string', ['string']],
    'newJSONtoGPX': ['string', ['string']],
    'newAddRoute': ['string', ['string', 'string', 'string']],
    'updateDoc': ['string', ['string']]
  });

  const fs = require('fs');
  // use data passed in to create an SQL connection
  // remember to create a variable to provide the host name
  // then start implementing the SQL queries and commands

  // STORE ALL FILES
  // create a counter for the number of files in the file log panel
  // the counter should be passed into here, app.js
  // then itererate through the files in the file log panel where 
  // the number of routes is greater than 0

  let dbConf = {
    host: 'dursley.socs.uoguelph.ca',
    user: req.query.userName,
    password: req.query.password,
    database: req.query.databaseName,
  };

  //let insRec = "INSERT INTO newerStudent (last_name, first_name, mark) VALUES ('Hugo','Victor','B+'),('Rudin','Walter','A-'),('Stevens','Richard','C')";

  async function main() {
    // get the client
    const mysql = require('mysql2/promise');

    let connection;

    // var numberOfFiles = req.query.nFiles;

    try {
      // create the connection
      connection = await mysql.createConnection(dbConf);

      // **** uncomment if you want to create the table on the fly ****
      // connection.execute("create table student (id int not null auto_increment,  last_name char(15),  first_name char(15), mark char(2), primary key(id) )");


      // CREATING THE THREE FILES


      //Run select query, wait for results
      var theID = req.query.gpxID;

      const [rows1, fields1] = await connection.execute("SELECT * from `POINT` ORDER BY point_index");
      var obj = {};
      var i = 0;

      for (let row of rows1) {
        console.log("POINT ID: " + row.route_id + " LATITUDE: " + row.latitude + " LONGITUDE: " + row.longitude);
        obj[i] = row;
        console.log(row.latitude);
        i++;
      }

      console.log("SPECIFIED FILE ROUTES: " + obj);

      res.send({
        // what is sent back
        gpxInfo: "something",
        fileName: "fileName",
        returnObj: obj,
      });


    } catch (e) {
      console.log("Query error: " + e);
    } finally {
      if (connection && connection.end) connection.end();
    }

  }

  main();

});


app.get('/getNRoutes', function (req, res) {

  // console.log("ADD ROUTE REACHED ");
  let sharedLib = ffi.Library('./libgpxparser', {
    //'JsSVG' : ['string', ['string']],
    'newCreateGPX': ['string', ['string']],
    'newTrackToJSON': ['string', ['string']],
    'newJSONtoGPX': ['string', ['string']],
    'newAddRoute': ['string', ['string', 'string', 'string']],
    'updateDoc': ['string', ['string']]
  });

  const fs = require('fs');
  // use data passed in to create an SQL connection
  // remember to create a variable to provide the host name
  // then start implementing the SQL queries and commands

  // STORE ALL FILES
  // create a counter for the number of files in the file log panel
  // the counter should be passed into here, app.js
  // then itererate through the files in the file log panel where 
  // the number of routes is greater than 0

  let dbConf = {
    host: 'dursley.socs.uoguelph.ca',
    user: req.query.userName,
    password: req.query.password,
    database: req.query.databaseName,
  };

  //let insRec = "INSERT INTO newerStudent (last_name, first_name, mark) VALUES ('Hugo','Victor','B+'),('Rudin','Walter','A-'),('Stevens','Richard','C')";

  async function main() {
    // get the client
    const mysql = require('mysql2/promise');

    let connection;

    // var numberOfFiles = req.query.nFiles;

    try {
      // create the connection
      connection = await mysql.createConnection(dbConf);

      // **** uncomment if you want to create the table on the fly ****
      // connection.execute("create table student (id int not null auto_increment,  last_name char(15),  first_name char(15), mark char(2), primary key(id) )");


      // CREATING THE THREE FILES


      //Run select query, wait for results
      console.log("GPX ID: " + req.query.gpxID);
      const [rows1, fields1] = await connection.execute("SELECT * from `ROUTE` WHERE gpx_id = " + req.query.gpxID + " ORDER BY `route_len` ASC LIMIT " + req.query.nRoutes);
      var obj = {};
      var i = 0;

      for (let row of rows1) {
        console.log("ROUTE_NAME: " + row.route_name + " ROUTE_ID: " + row.route_id + " ROUTE_LEN: " + row.route_len + " GPX_ID: " + row.gpx_id);
        obj[i] = row;
        i++;
      }

      console.log(obj);

      res.send({
        // what is sent back
        gpxInfo: "something",
        fileName: "fileName",
        returnObj: obj,
      });


    } catch (e) {
      console.log("Query error: " + e);
    } finally {
      if (connection && connection.end) connection.end();
    }

  }

  main();

});


app.get('/getNLongestRoutes', function (req, res) {

  // console.log("ADD ROUTE REACHED ");
  let sharedLib = ffi.Library('./libgpxparser', {
    //'JsSVG' : ['string', ['string']],
    'newCreateGPX': ['string', ['string']],
    'newTrackToJSON': ['string', ['string']],
    'newJSONtoGPX': ['string', ['string']],
    'newAddRoute': ['string', ['string', 'string', 'string']],
    'updateDoc': ['string', ['string']]
  });

  const fs = require('fs');
  // use data passed in to create an SQL connection
  // remember to create a variable to provide the host name
  // then start implementing the SQL queries and commands

  // STORE ALL FILES
  // create a counter for the number of files in the file log panel
  // the counter should be passed into here, app.js
  // then itererate through the files in the file log panel where 
  // the number of routes is greater than 0

  let dbConf = {
    host: 'dursley.socs.uoguelph.ca',
    user: req.query.userName,
    password: req.query.password,
    database: req.query.databaseName,
  };

  //let insRec = "INSERT INTO newerStudent (last_name, first_name, mark) VALUES ('Hugo','Victor','B+'),('Rudin','Walter','A-'),('Stevens','Richard','C')";

  async function main() {
    // get the client
    const mysql = require('mysql2/promise');

    let connection;

    // var numberOfFiles = req.query.nFiles;

    try {
      // create the connection
      connection = await mysql.createConnection(dbConf);

      // **** uncomment if you want to create the table on the fly ****
      // connection.execute("create table student (id int not null auto_increment,  last_name char(15),  first_name char(15), mark char(2), primary key(id) )");


      // CREATING THE THREE FILES


      //Run select query, wait for results
      console.log("GPX ID: " + req.query.gpxID);
      const [rows1, fields1] = await connection.execute("SELECT * from `ROUTE` WHERE gpx_id = " + req.query.gpxID + " ORDER BY `route_len` DESC LIMIT " + req.query.nRoutes);
      var obj = {};
      var i = 0;

      for (let row of rows1) {
        console.log("ROUTE_NAME: " + row.route_name + " ROUTE_ID: " + row.route_id + " ROUTE_LEN: " + row.route_len + " GPX_ID: " + row.gpx_id);
        obj[i] = row;
        i++;
      }

      console.log(obj);

      res.send({
        // what is sent back
        gpxInfo: "something",
        fileName: "fileName",
        returnObj: obj,
      });


    } catch (e) {
      console.log("Query error: " + e);
    } finally {
      if (connection && connection.end) connection.end();
    }

  }

  main();

});






app.listen(portNum);
console.log('Running app at localhost: ' + portNum);


