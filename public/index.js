
var allFiles = [];

// Put all onload AJAX calls here, and event listeners
jQuery(document).ready(function () {
  // On page-load AJAX Example
  jQuery.ajax({
    type: 'get',            //Request type
    dataType: 'json',       //Data type - we will use JSON for almost everything
    url: '/getFiles',   //The server endpoint we are connecting to
    data: {
      data1: "Value 1",
      data2: 1234.56
    },
    success: function (data) {
      /*  Do something with returned object
          Note that what we get is an object, not a string,
          so we do not need to parse it on the server.
          JavaScript really does handle JSONs seamlessly
      */
      jQuery('#blah').html("On page load, received string '" + data.returnString + "' from server");
      //We write the object to the console to show that the request was successful
      console.log(data);

    },
    fail: function (error) {
      // Non-200 return, do something with error
      $('#blah').html("On page load, received error from server");
      console.log(error);
    }
  });


  jQuery.ajax({
    type: 'get',            //Request type
    dataType: 'json',       //Data type - we will use JSON for almost everything
    url: '/getFiles',   //The server endpoint we are connecting to
    data: {
      data1: "Value 1",
      data2: 1234.56
    },
    success: function (data) {
      /*  Do something with returned object
          Note that what we get is an object, not a string,
          so we do not need to parse it on the server.
          JavaScript really does handle JSONs seamlessly
      */
      jQuery('#blah').html("On page load, received string '" + data.returnString + "' from server");
      //We write the object to the console to show that the request was successful
      console.log(data);

    },
    fail: function (error) {
      // Non-200 return, do something with error
      $('#blah').html("On page load, received error from server");
      console.log(error);
    }
  });










  // Event listener form example , we can use this instead explicitly listening for events
  // No redirects if possible
  $('#someform').submit(function (e) {
    $('#blah').html("Form has data: " + $('#entryBox').val());
    e.preventDefault();
    //Pass data to the Ajax call, so it gets passed to the server
    $.ajax({
      //Create an object for connecting to another waypoint
    });
  });



  jQuery.ajax({
    type: 'get',
    datatype: 'json',
    url: '/testFiles',
    data: {
      returnStrings: [],
    },
    success: function (data) {
      console.log("testing all the file names: " + data.returnArray);
      console.log("TESTING ALL THE INFO FROM CALLING C FUNCTIONS: " + data.returnInfo);

      // THIS VARIABLE CONTAINS ALL THE CREATEGPX FUNCTION INFO
      var jsonArray = [];

      for (var j = 0; j < data.returnInfo.length; j++) {
        jsonArray.push(JSON.parse(data.returnInfo[j]));
        console.log(jsonArray[j]);
      }


      var arrayLength = 0;
      var i = 0;
      allFiles = data.returnArray;

      var numFiles = 0;

      console.log("OLD ARRAY LENGTH = " + allFiles.length);
      for (var k = 0; k < allFiles.length; k++) {
        var lastFourChars = allFiles[k].substr(allFiles[k].length - 4); // => "Tabs1"

        if (lastFourChars == ".gpx") {
          console.log(allFiles[k]);
        } else {
          allFiles.splice(k, 1);
        }
      }

      console.log("NEW ARRAY LENGTH = " + allFiles.length);
      // get size of array that contains all the file names
      // the size will be the amount of rectangles needed for the file log panel
      // create a loop that iterates n times (n = number of elements in the array)
      // on each iteration create a rectangle in the file log panel and pass in the values
      arrayLength = allFiles.length;

      var toggleMenu = document.getElementById("theMenu").childNodes;
      // toggleMenu[5] is the list dropdown (ul)
      for (i = 0; i < arrayLength; i++) {

        // ADDING FILENAMES TO THE TOGGLE MENU BELOW
        var lastFour = allFiles[i].substr(allFiles[i].length - 4); // => "Tabs1"
        console.log("YOYOYO");

        if (lastFour == ".gpx") {

          var theAddRouteOptions = document.querySelector(".addRouteFiles");
          var newOption = document.createElement("option");
          var optionText = document.createTextNode(allFiles[i]);

          console.log(allFiles[i]);
          newOption.appendChild(optionText);
          console.log("TESTING NULL " + theAddRouteOptions);

          theAddRouteOptions.appendChild(newOption);


          var tempListPoint = document.createElement("li");
          tempListPoint.style.backgroundColor = "white";
          tempListPoint.style.margin = "10px";
          tempListPoint.style.width = "500px";

          var tempFileName = document.createTextNode(allFiles[i]);

          tempListPoint.appendChild(tempFileName);

          toggleMenu[5].appendChild(tempListPoint);

          // ADDING FILENAMES TO THE TOGGLE MENU ENDS

          // ADDING FILENAMES TO THE FILE LOG PANEL BELOW

          // incrementing the height of the main container very time a gpx file is added to the file log panel
          var getContainer = document.querySelector(".mainContainer");
          var allProperties = getComputedStyle(getContainer);
          var theHeight = allProperties.height;

          var sliceLastTwo = theHeight.substr(0, theHeight.length - 2); // => "Tabs1"
          console.log(sliceLastTwo);

          var stringToInt = parseInt(sliceLastTwo) + 100;
          console.log(stringToInt);

          var backToString = stringToInt.toString() + "px";
          console.log(backToString);

          document.querySelector(".mainContainer").style.height = backToString;

          // push down the download test too
          var getStubStuff = document.querySelector(".stubStuff");
          console.log("t1");
          var allStubProperties = getComputedStyle(getStubStuff);
          var stubHeight = allStubProperties.marginTop;
          console.log("ADJUSTING HEIGHT: " + stubHeight.top);
          var lastTwo = stubHeight.substr(0, stubHeight.length - 2); // => "Tabs1"
          console.log("t2");

          var stubStringToInt = parseInt(lastTwo) + 100;
          console.log("t3");

          var stubBackToString = stubStringToInt.toString() + "px";
          console.log("t4");

          document.querySelector(".stubStuff").style.marginTop = stubBackToString;


          var newDiv = document.createElement("div");
          newDiv.style.backgroundColor = "#FFFFFF";
          newDiv.style.margin = "10px";
          newDiv.style.width = "1147px";
          newDiv.style.height = "119px";
          newDiv.style.color = "black";


          var fileTitle = document.createElement("h3");
          fileTitle.style.fontWeight = "bold";
          fileTitle.style.fontSize = "16px";
          fileTitle.style.position = "relative";
          fileTitle.style.top = "20px";
          fileTitle.style.left = "50px";


          var text = document.createTextNode("File Name");
          fileTitle.appendChild(text);
          newDiv.appendChild(fileTitle);

          // adding the file name

          var theName = document.createElement("p");
          theName.style.fontSize = "12px";
          theName.style.position = "relative";
          theName.style.top = "20px";

          theName.style.left = "0px";

          var fileNameText = document.createTextNode(allFiles[i]);
          theName.appendChild(fileNameText);


          fileTitle.appendChild(theName);
          newDiv.appendChild(fileTitle);

          // version
          var fileVersion = document.createElement("h3");
          fileVersion.style.fontWeight = "bold";
          fileVersion.style.fontSize = "16px";
          fileVersion.style.position = "relative";
          fileVersion.style.top = "-28px";
          fileVersion.style.left = "320px";

          var secondText = document.createTextNode("Version");
          fileVersion.appendChild(secondText);

          // adding the file version
          var versionText = document.createElement("p");
          versionText.style.fontSize = "12px";
          versionText.style.position = "relative";
          versionText.style.top = "18px";
          versionText.style.left = "20px";

          var theVersionText = document.createTextNode(jsonArray[i].version);
          versionText.append(theVersionText);

          fileVersion.appendChild(versionText);
          newDiv.appendChild(fileVersion);

          // creator
          var fileCreator = document.createElement("h3");
          fileCreator.style.fontWeight = "bold";
          fileCreator.style.fontSize = "16px";
          fileCreator.style.position = "relative";
          fileCreator.style.top = "-78px";
          fileCreator.style.left = "450px";

          var thirdText = document.createTextNode("Creator");
          fileCreator.appendChild(thirdText);

          // adding the creator text
          var creatorText = document.createElement("p");
          creatorText.style.fontSize = "12px";
          creatorText.style.position = "relative";
          creatorText.style.top = "18px";
          creatorText.style.left = "-14px";

          var theCreatorText = document.createTextNode(jsonArray[i].creator);
          creatorText.appendChild(theCreatorText);

          fileCreator.appendChild(creatorText);

          newDiv.appendChild(fileCreator);



          var element = document.querySelector(".allFiles");
          element.appendChild(newDiv);

          // Number of Waypoints
          var numWaypoints = document.createElement("h3");
          numWaypoints.style.fontWeight = "bold";
          numWaypoints.style.fontSize = "16px";
          numWaypoints.style.position = "relative";
          numWaypoints.style.top = "-127px";
          numWaypoints.style.left = "570px";

          var fourthText = document.createTextNode("Number of Waypoints");
          numWaypoints.appendChild(fourthText);

          // adding the waypoints text
          var waypointText = document.createElement("p");
          waypointText.style.fontSize = "12px";
          waypointText.style.position = "relative";
          waypointText.style.top = "18px";
          waypointText.style.left = "70px";

          var sampleWptText = document.createTextNode(jsonArray[i].numWaypoints.toString());
          waypointText.appendChild(sampleWptText);
          numWaypoints.appendChild(waypointText);


          newDiv.appendChild(numWaypoints);




          var element = document.querySelector(".allFiles");
          element.appendChild(newDiv);

          // Number of Routes
          var numRoutes = document.createElement("h3");
          numRoutes.style.fontWeight = "bold";
          numRoutes.style.fontSize = "16px";
          numRoutes.style.position = "relative";
          numRoutes.style.top = "-175px";
          numRoutes.style.left = "780px";

          var fifthText = document.createTextNode("Number of Routes");

          // adding the routes text

          var routesText = document.createElement("p");
          routesText.style.fontSize = "12px";
          routesText.style.position = "relative";
          routesText.style.top = "18px";
          routesText.style.left = "70px";

          var sampleRteText = document.createTextNode(jsonArray[i].numRoutes.toString());
          routesText.appendChild(sampleRteText);

          numRoutes.appendChild(fifthText);
          numRoutes.appendChild(routesText);
          newDiv.appendChild(numRoutes);



          var element = document.querySelector(".allFiles");
          element.appendChild(newDiv);

          // Number of Tracks
          var numTracks = document.createElement("h3");
          numTracks.style.fontWeight = "bold";
          numTracks.style.fontSize = "16px";
          numTracks.style.position = "relative";
          numTracks.style.top = "-223px";
          numTracks.style.left = "970px";

          var sixthText = document.createTextNode("Number of Tracks");

          // adding the tracks text
          var trackText = document.createElement("p");
          trackText.style.fontSize = "12px";
          trackText.style.position = "relative";
          trackText.style.top = "18px";
          trackText.style.left = "70px";

          var sampleTrkText = document.createTextNode(jsonArray[i].numTracks.toString());
          trackText.appendChild(sampleTrkText);

          numTracks.appendChild(sixthText);
          numTracks.appendChild(trackText);
          newDiv.appendChild(numTracks);

          // numTracks.appendChild(sixthText);

          newDiv.appendChild(numTracks);



          var element = document.querySelector(".allFiles");
          element.appendChild(newDiv);
          numFiles++;
          document.querySelector(".numberOfFiles").innerHTML = numFiles;

          if (numFiles >= 1) {
            var storeFilesButton = document.querySelector(".secondSub-main");
            storeFilesButton.style.display = "block";
          }
        }
        else {

        }
      }

      var getTheMenu = document.getElementById("theMenu").childNodes;
      var wholeList = getTheMenu[5];
      var items = wholeList.getElementsByTagName("li");
      for (var i = 0; i < items.length; ++i) {
        // do something with items[i], which is a <li> element
        items[i].setAttribute("class", "item");
      }


    },
    fail: function (error) {
      // Non-200 return, do something with error
      $('#blah').html("On page load, received error from server");
      console.log(error);
    }
  });


});



document.getElementById("list").addEventListener("click", function (e) {
  if (e.target && e.target.matches("li.item")) {

    e.target.className = "foo"; // new class name here
    //  alert("clicked " + e.target.innerText);
    // get the html element that contains the list title
    // swap the current title with the text that was clicked on
    var currentHeader = document.querySelector(".labelTitle");
    currentHeader.innerHTML = e.target.innerText;



    var tableID = document.getElementById("routesTable").childNodes[1];


    // create a test set of strings
    // append them to the current table
    // see if it works

    tableID = document.getElementById("tracksTable").childNodes[1];

    // POPULATING TRACK TABLE NOW
    for (var i = 0; i < 3; i++) {
      var tempType = document.createElement("td");
      var tempTypeText = document.createTextNode("Track1");
      tempType.appendChild(tempTypeText);

      var tempName = document.createElement("td");
      var tempNameText = document.createTextNode("fileName");
      tempName.appendChild(tempNameText);

      var tempCreator = document.createElement("td");
      var tempCreatorText = document.createTextNode("tempCreator");
      tempCreator.appendChild(tempCreatorText);

      var tempNumPoints = document.createElement("td");
      var tempNumPointsText = document.createTextNode("2");
      tempNumPoints.appendChild(tempNumPointsText);

      var tempLen = document.createElement("td");
      var tempLenText = document.createTextNode("200m");
      tempLen.appendChild(tempLenText);

      var tempIsLoop = document.createElement("td");
      var tempIsLoopText = document.createTextNode("true");
      tempIsLoop.appendChild(tempIsLoopText);

      var tempTr = document.createElement("tr");

      tempTr.appendChild(tempType);
      tempTr.appendChild(tempCreator);
      tempTr.appendChild(tempNumPoints);
      tempTr.appendChild(tempLen);
      tempTr.appendChild(tempIsLoop);

      console.log(tempTr);
      console.log(tableID);
      tableID.appendChild(tempTr);


    }

    // console.log(tableID);

  }
});



var testString = "testName";
var testComponent = "testComponent";
var testNumPoints = "3";
var testLoopLength = "100";

function testFunction() {
  var table = document.getElementById("routesTable");
  // create an empty <tr> element and add it to the 1st position of the table:

  // getting the number of rows in the table

  var numRows = table.rows.length;
  console.log(numRows);
  var row = table.insertRow(numRows);

  // Insert new cells (<td> elements) at the 1st and 2nd position of the "new" <tr> element:
  var cell1 = row.insertCell(0);
  var cell2 = row.insertCell(1);
  var cell3 = row.insertCell(2);
  var cell4 = row.insertCell(3);
  var cell5 = row.insertCell(4);

  // Add some text to the new cells:
  //  cell1.innerHTML = testString;
  //    cell2.innerHTML = testComponent;
  //    cell3.innerHTML = testNumPoints;
  //  cell4.innerHTML = 100;
  //  cell5.innerHTML = "true";

}

function addToRouteTable(routeListString, routeListOtherData) {
  console.log(routeListOtherData[0]);
  var convertedData = "";
  if (routeListOtherData[0] == "[") {
    routeListOtherData[0] = "None";
  }

  //var convertedData = JSON.parse(routeListOtherData);

  if (routeListOtherData[0] == "None") {
    convertedData = "None";
  } else {
    convertedData = JSON.parse(routeListOtherData);
  }



  // length of the array that will be used in the for loop
  var arrayLen = routeListString.length;
  var i = 0;
  var j = 0;
  var tempLen = 0;
  var containsString = false;
  var parsedListString = JSON.parse(routeListString);
  //    var theTable = document.getElementById("routesTable");

  //  theTable.innerHTML = "";


  var tableID = document.getElementById("routesTable").childNodes[1];
  tempLen = routeListOtherData.length;

  // iterating through each json formatted string in the array list
  for (i = 0; i < arrayLen; i++) {
    var tempTr = document.createElement("tr");

    // check if the route name is equal to any of the component route names
    for (j = 0; j < tempLen; j++) {

      if (convertedData == "None") {
        var tempRow = document.createElement("td");
        var tempA = document.createElement("a");
        var tempAText = document.createTextNode("No Other Data Available");
        tempA.appendChild(tempAText);
        tempRow.appendChild(tempA);
        tempTr.appendChild(tempRow);

      } else if (convertedData[j].componentName == parsedListString[i].name) {
        console.log("MATCH FOUND, COMPONENT NAME = " + convertedData[j].componentName + " AND STRING NAME = " + parsedListString[i].name);
        // add the data from convertedData, which contains the GPX otherData information, to a popup and attach 
        // the popup to the current route
        var tempRow = document.createElement("td");
        var tempA = document.createElement("a");
        var tempAText = document.createTextNode("Name: " + convertedData[j].name + "\n" + "Value: " + convertedData[j].value);

        tempA.appendChild(tempAText);
        tempRow.appendChild(tempA);
        tempTr.appendChild(tempRow);
      }

    }

    var tempCounter = 1;
    tempCounter = i + tempCounter;

    var stringCounter = tempCounter.toString();
    // add to the table here
    var tempType = document.createElement("td");
    var tempTypeText = document.createTextNode("Route " + stringCounter);
    tempType.appendChild(tempTypeText);

    var tempName = document.createElement("td");
    var tempNameText = document.createTextNode(parsedListString[i].name);
    tempName.appendChild(tempNameText);

    var tempCreator = document.createElement("td");
    var tempCreatorText = document.createTextNode(parsedListString[i].name);
    tempCreator.appendChild(tempCreatorText);

    var tempNumPoints = document.createElement("td");
    var tempNumPointsText = document.createTextNode(parsedListString[i].numPoints);
    tempNumPoints.appendChild(tempNumPointsText);

    var tempLen = document.createElement("td");
    var tempLenText = document.createTextNode(parsedListString[i].len + "m");
    tempLen.appendChild(tempLenText);

    var tempIsLoop = document.createElement("td");
    var tempIsLoopText = document.createTextNode(parsedListString[i].loop);
    tempIsLoop.appendChild(tempIsLoopText);





    tempTr.appendChild(tempType);
    tempTr.appendChild(tempCreator);
    tempTr.appendChild(tempNumPoints);
    tempTr.appendChild(tempLen);
    tempTr.appendChild(tempIsLoop);



    console.log(tempTr);
    console.log(tableID);
    tableID.appendChild(tempTr);
  }
}


function addToTrackTable(trackListString, trackListOtherData) {
  var convertedData = "";
  var newConvertedData = "";
  console.log("TESTING " + trackListOtherData[0]);
  if (trackListOtherData[0] == "[") {
    trackListOtherData[0] = "None";
  }

  // var convertedData = JSON.parse(routeListOtherData);

  if (trackListOtherData[0] == "None") {
    convertedData = "None";
  } else {
    console.log("PARSING");

    //  convertedData = JSON.stringify(trackListOtherData);
    console.log(trackListOtherData);
    convertedData = JSON.parse(trackListOtherData);
    console.log("AFTER PARSING");
    console.log(convertedData);
  }

  console.log("TESTING LOG " + convertedData[0].name);
  // length of the array that will be used in the for loop
  var arrayLen = trackListString.length;
  var i = 0;
  var parsedListString = JSON.parse(trackListString);
  //    var theTable = document.getElementById("routesTable");

  //  theTable.innerHTML = "";


  var tableID = document.getElementById("tracksTable").childNodes[1];
  tempLen = trackListOtherData.length;
  console.log("REACHED addTrackToTable");
  // iterating through each json formatted string in the array list
  for (i = 0; i < arrayLen; i++) {
    var tempTr = document.createElement("tr");

    // check if the track name is equal to any of the component route names
    for (j = 0; j < tempLen; j++) {


      if (convertedData == "None") {
        var tempRow = document.createElement("td");
        var tempA = document.createElement("a");
        var tempAText = document.createTextNode("No Other Data Available");
        tempA.appendChild(tempAText);
        tempRow.appendChild(tempA);
        tempTr.appendChild(tempRow);

      } else if (convertedData[j].componentName == parsedListString[i].name) {
        console.log("MATCH FOUND, COMPONENT NAME = " + convertedData[j].componentName + " AND STRING NAME = " + parsedListString[i].name);
        // add the data from convertedData, which contains the GPX otherData information, to a popup and attach 
        // the popup to the current route
        var tempRow = document.createElement("td");
        var tempA = document.createElement("a");
        var tempAText = document.createTextNode("Name: " + convertedData[j].name + " " + "Value: " + convertedData[j].value);
        console.log("CREATING TEXT NODE: " + convertedData[j].value);
        tempA.appendChild(tempAText);
        tempRow.appendChild(tempA);
        tempTr.appendChild(tempRow);
      }

    }

    var tempCounter = 1;
    tempCounter = i + tempCounter;

    var stringCounter = tempCounter.toString();
    // add to the table here
    var tempType = document.createElement("td");
    var tempTypeText = document.createTextNode("Track " + stringCounter);
    tempType.appendChild(tempTypeText);

    var tempName = document.createElement("td");
    var tempNameText = document.createTextNode(parsedListString[i].name);
    tempName.appendChild(tempNameText);

    var tempCreator = document.createElement("td");
    var tempCreatorText = document.createTextNode(parsedListString[i].name);
    tempCreator.appendChild(tempCreatorText);

    var tempNumPoints = document.createElement("td");
    var tempNumPointsText = document.createTextNode(parsedListString[i].numPoints);
    tempNumPoints.appendChild(tempNumPointsText);

    var tempLen = document.createElement("td");
    var tempLenText = document.createTextNode(parsedListString[i].len + "m");
    tempLen.appendChild(tempLenText);

    var tempIsLoop = document.createElement("td");
    var tempIsLoopText = document.createTextNode(parsedListString[i].loop);
    tempIsLoop.appendChild(tempIsLoopText);

    tempTr.appendChild(tempType);
    tempTr.appendChild(tempCreator);
    tempTr.appendChild(tempNumPoints);
    tempTr.appendChild(tempLen);
    tempTr.appendChild(tempIsLoop);

    console.log(tempTr);
    console.log(tableID);
    tableID.appendChild(tempTr);
  }
}





$('#list').click(function (e) {
  console.log("TEST FUNCTION CLICKED");
  e.preventDefault();
  //Pass data to the Ajax call, so it gets passed to the server
  jQuery.ajax({
    type: 'get',            //Request type
    dataType: 'json',       //Data type - we will use JSON for almost everything
    url: '/getRouteList',   //The server endpoint we are connecting to
    data: {
      data1: e.target.innerText,
    },
    success: function (data) {
      /*  Do something with returned object
          Note that what we get is an object, not a string,
          so we do not need to parse it on the server.
          JavaScript really does handle JSONs seamlessly
      */

      //We write the object to the console to show that the request was successful
      console.log("TESTING NEW ENDPOINT " + data.docRouteInfo);
      console.log("TESTING NEW ENDPOINT " + data.docTrackInfo);
      console.log("TESTING NEW ENDPOINT " + data.docRouteData);
      console.log("TESTING NEW ENDPOINT " + data.docTrackData);
      var table = document.getElementById("routesTable");
      var rowCount = table.rows.length;
      for (var i = 1; i < rowCount; i++) {
        table.deleteRow(1);
      }


      var trackTable = document.getElementById("tracksTable");
      var secondRowCount = trackTable.rows.length;
      for (var i = 1; i < secondRowCount; i++) {
        trackTable.deleteRow(1);
      }

      if (data.docRouteInfo == "[") {
        console.log("EMPTY STRING FOUND");
      } else {
        addToRouteTable(data.docRouteInfo, data.docRouteData);
      }

      if (data.docTrackInfo == "[") {
        console.log("EMPTY STRING FOUND");
      } else {
        addToTrackTable(data.docTrackInfo, data.docTrackData);
      }




    },
    fail: function (error) {
      // Non-200 return, do something with error
      console.log("DID NOT CONNECT");
    }
  });
});


$('#clickCreate').click(function (e) {
  console.log("GPX CREATE CLICKED");
  var fileName = document.getElementById('id1').value;
  var namespaceVal = document.getElementById('id2').value;
  var versionVal = document.getElementById('id3').value;
  var creatorVal = document.getElementById('id4').value;

  var sendBack = fileName.concat("," + namespaceVal + "," + versionVal + "," + creatorVal);
  e.preventDefault();
  //Pass data to the Ajax call, so it gets passed to the server
  jQuery.ajax({
    type: 'get',            //Request type
    dataType: 'json',       //Data type - we will use JSON for almost everything
    url: '/convertJSONtoGPX',   //The server endpoint we are connecting to
    data: {
      data1: sendBack,
    },
    success: function (data) {

      console.log("TESTING FILENAME: " + fileName);
      console.log("SUCCESS");

    },
    fail: function (error) {
      // Non-200 return, do something with error
      console.log("DID NOT CONNECT");
    }
  });
});


$('#clickAddRoute').click(function (e) {
  console.log("ADD ROUTE CLICKED");
  var routeName = document.getElementById('rteName').value;
  var waypointsAsString = document.getElementById('mail').value;
  var selectionChoice = document.getElementById('choice').value;

  console.log("TESTING CLICK ADD ROUTE PARAMS = " + selectionChoice + routeName + waypointsAsString);

  //var sendBack = fileName.concat("," + namespaceVal + "," + versionVal + "," + creatorVal);
  e.preventDefault();
  //Pass data to the Ajax call, so it gets passed to the server
  jQuery.ajax({
    type: 'get',            //Request type
    dataType: 'json',       //Data type - we will use JSON for almost everything
    url: '/addRoute',   //The server endpoint we are connecting to
    data: {
      data1: routeName,
      data2: waypointsAsString,
      data3: selectionChoice,
    },
    success: function (info) {
      console.log("SUCCESS" + info.gpxInfo);
      alert("The amount of routes in: " + info.fileName + " is now: " + info.numRoutes);

    },
    fail: function (error) {
      // Non-200 return, do something with error
      console.log("DID NOT CONNECT");
    }
  });
});

$(document).click(function (event) {
  if (
    $('.toggle > input').is(':checked') &&
    !$(event.target).parents('.toggle').is('.toggle')
  ) {
    $('.toggle > input').prop('checked', false);
  }
})

function refreshPage() {
  window.location.reload();
}


$('#connectDB').click(function (e) {
  e.preventDefault();
  //Pass data to the Ajax call, so it gets passed to the server

  var dbUsername = document.getElementById("userName").value;
  var dbPassword = document.getElementById("userPassword").value;
  var dbName = document.getElementById("dbName").value;
  var numFiles = document.querySelector(".numberOfFiles").innerHTML;
  //numFiles = parseInt(numFiles);

  alert("DATABASE CONNECTED! The number of files currently on here is:" + numFiles);
  numFiles = parseInt(numFiles);



  jQuery.ajax({
    type: 'get',            //Request type
    dataType: 'json',       //Data type - we will use JSON for almost everything
    url: '/createConnection',   //The server endpoint we are connecting to
    data: {
      userName: dbUsername,
      password: dbPassword,
      databaseName: dbName,
      fileCount: numFiles,
    },
    success: function (data) {
      /*  Do something with returned object
          Note that what we get is an object, not a string,
          so we do not need to parse it on the server.
          JavaScript really does handle JSONs seamlessly
      */

      //  alert('DATABASE BUTTON CLICKED');
    },
    fail: function (error) {
      // Non-200 return, do something with error
      console.log("DID NOT CONNECT");
    }
  });
});



$('#storeFiles').click(function (e) {
  e.preventDefault();
  //Pass data to the Ajax call, so it gets passed to the server

  var divContent = $("#filePanel");

  var all = divContent.find("p");

  console.log(all);

  var i = 0;

  // create a loop that displays all the content per file

  for (i = 0; i < all.length; i = i + 6) {
    var tempFileName = all[i].innerHTML;
    var tempVersion = all[i + 1].innerHTML;
    var tempCreator = all[i + 2].innerHTML;
    var tempNumWaypoints = all[i + 3].innerHTML;
    var tempNumRoutes = all[i + 4].innerHTML;
    var tempNumTracks = all[i + 5].innerHTML;

    console.log("TESTING PARSING THE JAVASCRIPT OBJECT: fileName = " + tempFileName + " version = " + tempVersion + " creator = " + tempCreator);

    jQuery.ajax({
      type: 'get',            //Request type
      dataType: 'json',       //Data type - we will use JSON for almost everything
      url: '/populateTables',   //The server endpoint we are connecting to
      data: {
        theFile: tempFileName,
        theVersion: tempVersion,
        theCreator: tempCreator,
        numWaypoints: tempNumWaypoints,
        numRoutes: tempNumRoutes,
        numTracks: tempNumTracks,
        username: document.getElementById("userName").value,
        password: document.getElementById("userPassword").value,
        databaseName: document.getElementById("dbName").value,

      },
      success: function (data) {
        /*  Do something with returned object
            Note that what we get is an object, not a string,
            so we do not need to parse it on the server.
            JavaScript really does handle JSONs seamlessly
        */

        alert('All the files from the File Panel have been stored in the MySQL database.');
      },
      fail: function (error) {
        // Non-200 return, do something with error
        console.log("DID NOT CONNECT");
      }
    });
  }




});


$('#clearTables').click(function (e) {
  e.preventDefault();
  //Pass data to the Ajax call, so it gets passed to the server

  var dbUsername = document.getElementById("userName").value;
  var dbPassword = document.getElementById("userPassword").value;
  var dbName = document.getElementById("dbName").value;
  var numFiles = document.querySelector(".numberOfFiles").innerHTML;
  //numFiles = parseInt(numFiles);

  //  alert("NUMBER OF FILES: " + numFiles);
  // numFiles = parseInt(numFiles);



  jQuery.ajax({
    type: 'get',            //Request type
    dataType: 'json',       //Data type - we will use JSON for almost everything
    url: '/clearAllTables',   //The server endpoint we are connecting to
    data: {
      userName: dbUsername,
      password: dbPassword,
      databaseName: dbName,
    },
    success: function (data) {
      /*  Do something with returned object
          Note that what we get is an object, not a string,
          so we do not need to parse it on the server.
          JavaScript really does handle JSONs seamlessly
      */

      alert('ALL TABLES CLEARED');
    },
    fail: function (error) {
      // Non-200 return, do something with error
      console.log("DID NOT CONNECT");
    }
  });
});

$('#displayStatus').click(function (e) {
  e.preventDefault();
  //Pass data to the Ajax call, so it gets passed to the server

  var dbUsername = document.getElementById("userName").value;
  var dbPassword = document.getElementById("userPassword").value;
  var dbName = document.getElementById("dbName").value;
  var numFiles = document.querySelector(".numberOfFiles").innerHTML;
  //numFiles = parseInt(numFiles);

  //  alert("NUMBER OF FILES: " + numFiles);
  // numFiles = parseInt(numFiles);



  jQuery.ajax({
    type: 'get',            //Request type
    dataType: 'json',       //Data type - we will use JSON for almost everything
    url: '/displayDB',   //The server endpoint we are connecting to
    data: {
      userName: dbUsername,
      password: dbPassword,
      databaseName: dbName,
    },
    success: function (data) {
      /*  Do something with returned object
          Note that what we get is an object, not a string,
          so we do not need to parse it on the server.
          JavaScript really does handle JSONs seamlessly
      */
      console.log(data);
      alert('The database has ' + data.totalFileRows + ' files in the FILE table, ' + data.totalRouteRows + ' routes in the ROUTE table, and ' + data.totalPointRows + ' points in the POINT table');
    },
    fail: function (error) {
      // Non-200 return, do something with error
      console.log("DID NOT CONNECT");
    }
  });
});


$('#firstQuery').click(function (e) {
  e.preventDefault();
  //Pass data to the Ajax call, so it gets passed to the server

  var dbUsername = document.getElementById("userName").value;
  var dbPassword = document.getElementById("userPassword").value;
  var dbName = document.getElementById("dbName").value;
  var numFiles = document.querySelector(".numberOfFiles").innerHTML;
  //numFiles = parseInt(numFiles);

  //  alert("NUMBER OF FILES: " + numFiles);
  // numFiles = parseInt(numFiles);

  var firstOption = document.querySelector(".q1Options");
  firstOption.style.display = "block";

  var secondOption = document.querySelector(".q2Options");
  secondOption.style.display = "none";

  var thirdOption = document.querySelector(".q3Options");
  thirdOption.style.display = "none";

  var fourthOption = document.querySelector(".q4Options");
  fourthOption.style.display = "none";

  var fifthOption = document.querySelector(".q5Options");
  fifthOption.style.display = "none";


});


$('#orderByNames').click(function (e) {
  e.preventDefault();
  //Pass data to the Ajax call, so it gets passed to the server

  var dbUsername = document.getElementById("userName").value;
  var dbPassword = document.getElementById("userPassword").value;
  var dbName = document.getElementById("dbName").value;
  var numFiles = document.querySelector(".numberOfFiles").innerHTML;

  // THIS IS THE EVENT LISTENER FOR IF THE USER SELECTS TO SEE ALL ROUTES ORDERED BY NAMES


  // create the MySQL connection 
  // query the ROUTE table and select all and order them by name 
  // iterate through the table 

  jQuery.ajax({
    type: 'get',            //Request type
    dataType: 'json',       //Data type - we will use JSON for almost everything
    url: '/orderByRouteNames',   //The server endpoint we are connecting to
    data: {
      userName: dbUsername,
      password: dbPassword,
      databaseName: dbName,
    },
    success: function (data) {
      /*  Do something with returned object
          Note that what we get is an object, not a string,
          so we do not need to parse it on the server.
          JavaScript really does handle JSONs seamlessly
      */
      console.log(data);
      var returnedObj = data.returnObj;

      console.log("TESTING PARSING DATA: " + returnedObj[0].route_name);
      var i = 0;
      var objLen = returnedObj.length;

      var tableID = document.getElementById("queryRouteTable").childNodes[1];
      console.log(returnedObj);

      var oldTable = document.getElementById("queryRouteTable").childNodes[1];
      var tableRows = oldTable.getElementsByTagName("tr");
      var rowCount = tableRows.length;

      var j = 0;

      for (j = rowCount - 1; j > 0; j--) {
        oldTable.removeChild(tableRows[j]);
        console.log("REMOVING ROW");
      }

      for (const q1Row in returnedObj) {

        console.log(`${q1Row}: ${returnedObj[q1Row].route_name}`);



        var tempRteID = document.createElement("td");
        var tempNameText = document.createTextNode(`${returnedObj[q1Row].route_id}`);
        tempRteID.appendChild(tempNameText);

        var tempRteName = document.createElement("td");
        var tempCreatorText = document.createTextNode(`${returnedObj[q1Row].route_name}`);
        tempRteName.appendChild(tempCreatorText);

        var tempRteLen = document.createElement("td");
        var tempNumPointsText = document.createTextNode(`${returnedObj[q1Row].route_len}`);
        tempRteLen.appendChild(tempNumPointsText);

        var tempRteOtherID = document.createElement("td");
        var tempLenText = document.createTextNode(`${returnedObj[q1Row].gpx_id}`);
        tempRteOtherID.appendChild(tempLenText);

        var tempRouteRow = document.createElement("tr");

        tempRouteRow.appendChild(tempRteID);
        tempRouteRow.appendChild(tempRteName);
        tempRouteRow.appendChild(tempRteLen);
        tempRouteRow.appendChild(tempRteOtherID);

        tableID.appendChild(tempRouteRow);
      }

      //  alert('The database has ' + data.totalFileRows + ' files in the FILE table, ' + data.totalRouteRows + ' routes in the ROUTE table, and ' + data.totalPointRows + ' points in the POINT table');
    },
    fail: function (error) {
      // Non-200 return, do something with error
      console.log("DID NOT CONNECT");
    }
  });


});


$('#orderByLen').click(function (e) {
  e.preventDefault();
  //Pass data to the Ajax call, so it gets passed to the server

  var dbUsername = document.getElementById("userName").value;
  var dbPassword = document.getElementById("userPassword").value;
  var dbName = document.getElementById("dbName").value;
  var numFiles = document.querySelector(".numberOfFiles").innerHTML;

  // THIS IS THE EVENT LISTENER FOR IF THE USER SELECTS TO SEE ALL ROUTES ORDERED BY NAMES


  // create the MySQL connection 
  // query the ROUTE table and select all and order them by name 
  // iterate through the table 

  jQuery.ajax({
    type: 'get',            //Request type
    dataType: 'json',       //Data type - we will use JSON for almost everything
    url: '/orderByRouteLen',   //The server endpoint we are connecting to
    data: {
      userName: dbUsername,
      password: dbPassword,
      databaseName: dbName,
    },
    success: function (data) {
      /*  Do something with returned object
          Note that what we get is an object, not a string,
          so we do not need to parse it on the server.
          JavaScript really does handle JSONs seamlessly
      */
      console.log(data);
      var returnedObj = data.returnObj;

      //  console.log("TESTING PARSING DATA: " + returnedObj[0].route_name);
      var i = 0;
      var objLen = returnedObj.length;

      var tableID = document.getElementById("queryRouteTable").childNodes[1];
      console.log(returnedObj);

      var oldTable = document.getElementById("queryRouteTable").childNodes[1];
      var tableRows = oldTable.getElementsByTagName("tr");
      var rowCount = tableRows.length;

      var j = 0;

      for (j = rowCount - 1; j > 0; j--) {
        oldTable.removeChild(tableRows[j]);
        console.log("REMOVING ROW");
      }

      for (const q1Row in returnedObj) {

        console.log(`${q1Row}: ${returnedObj[q1Row].route_name}`);



        var tempRteID = document.createElement("td");
        var tempNameText = document.createTextNode(`${returnedObj[q1Row].route_id}`);
        tempRteID.appendChild(tempNameText);

        var tempRteName = document.createElement("td");
        var tempCreatorText = document.createTextNode(`${returnedObj[q1Row].route_name}`);
        tempRteName.appendChild(tempCreatorText);

        var tempRteLen = document.createElement("td");
        var tempNumPointsText = document.createTextNode(`${returnedObj[q1Row].route_len}`);
        tempRteLen.appendChild(tempNumPointsText);

        var tempRteOtherID = document.createElement("td");
        var tempLenText = document.createTextNode(`${returnedObj[q1Row].gpx_id}`);
        tempRteOtherID.appendChild(tempLenText);

        var tempRouteRow = document.createElement("tr");

        tempRouteRow.appendChild(tempRteID);
        tempRouteRow.appendChild(tempRteName);
        tempRouteRow.appendChild(tempRteLen);
        tempRouteRow.appendChild(tempRteOtherID);

        tableID.appendChild(tempRouteRow);
      }

      //  alert('The database has ' + data.totalFileRows + ' files in the FILE table, ' + data.totalRouteRows + ' routes in the ROUTE table, and ' + data.totalPointRows + ' points in the POINT table');
    },
    fail: function (error) {
      // Non-200 return, do something with error
      console.log("DID NOT CONNECT");
    }
  });


});



$('#selectFile').click(function (e) {
  e.preventDefault();
  // console.log("TESTING: " + extractedID);
  //Pass data to the Ajax call, so it gets passed to the server

  var dbUsername = document.getElementById("userName").value;
  var dbPassword = document.getElementById("userPassword").value;
  var dbName = document.getElementById("dbName").value;
  var numFiles = document.querySelector(".numberOfFiles").innerHTML;
  //numFiles = parseInt(numFiles);

  //  alert("NUMBER OF FILES: " + numFiles);
  // numFiles = parseInt(numFiles);

  // var firstOption = document.querySelector(".q1Options");
  // firstOption.style.display = "none";

  // var secondOption = document.querySelector(".q2Options");
  // secondOption.style.display = "block";


  var getDivContent = document.querySelector(".q2Div");
  var divText = e.target.innerHTML;
  var findIndex = divText.indexOf("ID:");

  var extractedID = divText.substr(findIndex + 3);
  console.log("TESTING: " + extractedID);

  jQuery.ajax({
    type: 'get',            //Request type
    dataType: 'json',       //Data type - we will use JSON for almost everything
    url: '/getSpecifiedRouteInfo',   //The server endpoint we are connecting to
    data: {
      userName: dbUsername,
      password: dbPassword,
      databaseName: dbName,
      gpxID: extractedID,
    },
    success: function (data) {
      /*  Do something with returned object
          Note that what we get is an object, not a string,
          so we do not need to parse it on the server.
          JavaScript really does handle JSONs seamlessly
      */
      console.log(data);
      var returnedObj = data.returnObj;

      //  console.log("TESTING PARSING DATA: " + returnedObj[0].route_name);
      var i = 0;
      var objLen = returnedObj.length;

      var tableID = document.getElementById("secondQueryRouteTable").childNodes[1];
      console.log(tableID);

      var oldTable = document.getElementById("secondQueryRouteTable").childNodes[1];
      var tableRows = oldTable.getElementsByTagName("tr");
      var rowCount = tableRows.length;

      var j = 0;

      for (j = rowCount - 1; j > 0; j--) {
        oldTable.removeChild(tableRows[j]);
        console.log("REMOVING ROW");
      }

      for (const q1Row in returnedObj) {

        console.log(`${q1Row}: ${returnedObj[q1Row].route_name}`);

        var tempRow = document.createElement("tr");

        var tempRteName = document.createElement("td");
        var tempRteNameText = document.createTextNode(`${returnedObj[q1Row].route_name}`);
        tempRteName.appendChild(tempRteNameText);

        var tempRteLen = document.createElement("td");
        var tempRteLenText = document.createTextNode(`${returnedObj[q1Row].route_len}`);
        tempRteLen.appendChild(tempRteLenText);

        var tempRteID = document.createElement("td");
        var tempRteIDText = document.createTextNode(`${returnedObj[q1Row].gpx_id}`);
        tempRteID.appendChild(tempRteIDText);

        tempRow.appendChild(tempRteName);
        tempRow.appendChild(tempRteLen);
        tempRow.appendChild(tempRteID);

        tableID.appendChild(tempRow);
      }

      //  alert('The database has ' + data.totalFileRows + ' files in the FILE table, ' + data.totalRouteRows + ' routes in the ROUTE table, and ' + data.totalPointRows + ' points in the POINT table');
    },
    fail: function (error) {
      // Non-200 return, do something with error
      console.log("DID NOT CONNECT");
    }
  });




});



$('#secondQuery').click(function (e) {
  e.preventDefault();
  //Pass data to the Ajax call, so it gets passed to the server

  var dbUsername = document.getElementById("userName").value;
  var dbPassword = document.getElementById("userPassword").value;
  var dbName = document.getElementById("dbName").value;
  var numFiles = document.querySelector(".numberOfFiles").innerHTML;
  //numFiles = parseInt(numFiles);

  //  alert("NUMBER OF FILES: " + numFiles);
  // numFiles = parseInt(numFiles);

  var firstOption = document.querySelector(".q1Options");
  firstOption.style.display = "none";

  var secondOption = document.querySelector(".q2Options");
  secondOption.style.display = "block";

  var thirdOption = document.querySelector(".q3Options");
  thirdOption.style.display = "none";

  var fourthOption = document.querySelector(".q4Options");
  fourthOption.style.display = "none";

  var fifthOption = document.querySelector(".q5Options");
  fifthOption.style.display = "none";




  jQuery.ajax({
    type: 'get',            //Request type
    dataType: 'json',       //Data type - we will use JSON for almost everything
    url: '/getFileNameAndID',   //The server endpoint we are connecting to
    data: {
      userName: dbUsername,
      password: dbPassword,
      databaseName: dbName,
    },
    success: function (data) {
      /*  Do something with returned object
          Note that what we get is an object, not a string,
          so we do not need to parse it on the server.
          JavaScript really does handle JSONs seamlessly
      */
      console.log(data);
      var returnedObj = data.returnObj;

      //  console.log("TESTING PARSING DATA: " + returnedObj[0].route_name);
      var i = 0;
      var objLen = returnedObj.length;

      var tableID = document.getElementById("secondQueryRouteTable").childNodes[1];
      console.log(returnedObj);

      var oldTable = document.getElementById("secondQueryRouteTable").childNodes[1];
      var tableRows = oldTable.getElementsByTagName("tr");
      var rowCount = tableRows.length;

      var j = 0;

      var selectDiv = document.getElementById("selectFile");

      for (j = rowCount - 1; j > 0; j--) {
        oldTable.removeChild(tableRows[j]);
        console.log("REMOVING ROW");
      }

      for (const q1Row in returnedObj) {
        // ITERATING THROUGH ALL THE FILES

        //  console.log(`${q1Row}: ${returnedObj[q1Row].route_name}`);

        var tempFileName = document.createElement("button");
        tempFileName.setAttribute("id", "q2Div");
        var tempTextNode = document.createTextNode(`${returnedObj[q1Row].file_name}` + " ID:" + `${returnedObj[q1Row].gpx_id}`);

        tempFileName.appendChild(tempTextNode);
        selectDiv.appendChild(tempFileName);


      }


      //  alert('The database has ' + data.totalFileRows + ' files in the FILE table, ' + data.totalRouteRows + ' routes in the ROUTE table, and ' + data.totalPointRows + ' points in the POINT table');
    },
    fail: function (error) {
      // Non-200 return, do something with error
      console.log("DID NOT CONNECT");
    }
  });


});






$('#secondLenBtn').click(function (e) {
  e.preventDefault();
  // console.log("TESTING: " + extractedID);
  //Pass data to the Ajax call, so it gets passed to the server

  var dbUsername = document.getElementById("userName").value;
  var dbPassword = document.getElementById("userPassword").value;
  var dbName = document.getElementById("dbName").value;
  var numFiles = document.querySelector(".numberOfFiles").innerHTML;
  //numFiles = parseInt(numFiles);

  //  alert("NUMBER OF FILES: " + numFiles);
  // numFiles = parseInt(numFiles);

  // var firstOption = document.querySelector(".q1Options");
  // firstOption.style.display = "none";

  // var secondOption = document.querySelector(".q2Options");
  // secondOption.style.display = "block";


  // var getDivContent = document.querySelector(".q2Div");
  // var divText = e.target.innerHTML;
  //  var findIndex = divText.indexOf("ID:");
  var getID = document.getElementById("secondQueryRouteTable");


  console.log("TESTING LEN: " + getID.tBodies);



  // var extractedID = divText.substr(findIndex + 3);
  // console.log("TESTING: " + extractedID);



});




$('#thirdQuery').click(function (e) {
  e.preventDefault();
  //Pass data to the Ajax call, so it gets passed to the server

  var dbUsername = document.getElementById("userName").value;
  var dbPassword = document.getElementById("userPassword").value;
  var dbName = document.getElementById("dbName").value;
  var numFiles = document.querySelector(".numberOfFiles").innerHTML;
  //numFiles = parseInt(numFiles);

  //  alert("NUMBER OF FILES: " + numFiles);
  // numFiles = parseInt(numFiles);

  var firstOption = document.querySelector(".q1Options");
  firstOption.style.display = "none";

  var secondOption = document.querySelector(".q2Options");
  secondOption.style.display = "none";

  var thirdOption = document.querySelector(".q3Options");
  thirdOption.style.display = "block";

  var fourthOption = document.querySelector(".q4Options");
  fourthOption.style.display = "none";

  var fifthOption = document.querySelector(".q5Options");
  fifthOption.style.display = "none";




  jQuery.ajax({
    type: 'get',            //Request type
    dataType: 'json',       //Data type - we will use JSON for almost everything
    url: '/orderByRouteNames',   //The server endpoint we are connecting to
    data: {
      userName: dbUsername,
      password: dbPassword,
      databaseName: dbName,
    },
    success: function (data) {
      /*  Do something with returned object
          Note that what we get is an object, not a string,
          so we do not need to parse it on the server.
          JavaScript really does handle JSONs seamlessly
      */
      console.log(data);
      var returnedObj = data.returnObj;

      //  console.log("TESTING PARSING DATA: " + returnedObj[0].route_name);
      var i = 0;
      var objLen = returnedObj.length;

      var tableID = document.getElementById("thirdQueryRouteTable").childNodes[1];
      console.log(returnedObj);

      var oldTable = document.getElementById("thirdQueryRouteTable").childNodes[1];
      var tableRows = oldTable.getElementsByTagName("tr");
      var rowCount = tableRows.length;

      var j = 0;

      var selectDiv = document.getElementById("selectRte");

      for (j = rowCount - 1; j > 0; j--) {
        oldTable.removeChild(tableRows[j]);
        console.log("REMOVING ROW");
      }



      // display all the route names 
      // on click get the route_id 
      // select and return all points with that same route_id


      for (const q1Row in returnedObj) {
        // ITERATING THROUGH ALL THE FILES

        //  console.log(`${q1Row}: ${returnedObj[q1Row].route_name}`);

        var tempFileName = document.createElement("button");
        tempFileName.setAttribute("id", "q3Div");
        var tempTextNode = document.createTextNode(`${returnedObj[q1Row].route_name}` + " ID:" + `${returnedObj[q1Row].route_id}`);

        tempFileName.appendChild(tempTextNode);
        selectDiv.appendChild(tempFileName);

      }









      //  alert('The database has ' + data.totalFileRows + ' files in the FILE table, ' + data.totalRouteRows + ' routes in the ROUTE table, and ' + data.totalPointRows + ' points in the POINT table');
    },
    fail: function (error) {
      // Non-200 return, do something with error
      console.log("DID NOT CONNECT");
    }
  });


});




$('#selectRte').click(function (e) {
  //alert("ROUTE CLICKED");
  e.preventDefault();
  // console.log("TESTING: " + extractedID);
  //Pass data to the Ajax call, so it gets passed to the server

  var dbUsername = document.getElementById("userName").value;
  var dbPassword = document.getElementById("userPassword").value;
  var dbName = document.getElementById("dbName").value;
  var numFiles = document.querySelector(".numberOfFiles").innerHTML;
  //numFiles = parseInt(numFiles);

  //  alert("NUMBER OF FILES: " + numFiles);
  // numFiles = parseInt(numFiles);

  // var firstOption = document.querySelector(".q1Options");
  // firstOption.style.display = "none";

  // var secondOption = document.querySelector(".q2Options");
  // secondOption.style.display = "block";


  var getDivContent = document.querySelector(".q3Div");
  var divText = e.target.innerHTML;
  var findIndex = divText.indexOf("ID:");

  var extractedID = divText.substr(findIndex + 3);
  // console.log("TESTING: " + extractedID);
  alert(extractedID);

  jQuery.ajax({
    type: 'get',            //Request type
    dataType: 'json',       //Data type - we will use JSON for almost everything
    url: '/getSpecifiedPoints',   //The server endpoint we are connecting to
    data: {
      userName: dbUsername,
      password: dbPassword,
      databaseName: dbName,
      gpxID: extractedID,
    },
    success: function (data) {
      /*  Do something with returned object
          Note that what we get is an object, not a string,
          so we do not need to parse it on the server.
          JavaScript really does handle JSONs seamlessly
      */
      console.log(data);
      var returnedObj = data.returnObj;

      //  console.log("TESTING PARSING DATA: " + returnedObj[0].route_name);
      var i = 0;
      var objLen = returnedObj.length;

      var tableID = document.getElementById("thirdQueryRouteTable").childNodes[1];
      console.log(tableID);

      var oldTable = document.getElementById("thirdQueryRouteTable").childNodes[1];
      var tableRows = oldTable.getElementsByTagName("tr");
      var rowCount = tableRows.length;

      var j = 0;

      for (j = rowCount - 1; j > 0; j--) {
        oldTable.removeChild(tableRows[j]);
        console.log("REMOVING ROW");
      }

      for (const q1Row in returnedObj) {

        console.log(`${q1Row}: ${returnedObj[q1Row].route_name}`);

        var tempRow = document.createElement("tr");

        var tempRteName = document.createElement("td");
        var tempRteNameText = document.createTextNode(`${returnedObj[q1Row].point_index}`);
        tempRteName.appendChild(tempRteNameText);

        var tempRteLen = document.createElement("td");
        var tempRteLenText = document.createTextNode(`${returnedObj[q1Row].latitude}`);
        tempRteLen.appendChild(tempRteLenText);

        var tempRteID = document.createElement("td");
        var tempRteIDText = document.createTextNode(`${returnedObj[q1Row].longitude}`);
        tempRteID.appendChild(tempRteIDText);

        tempRow.appendChild(tempRteName);
        tempRow.appendChild(tempRteLen);
        tempRow.appendChild(tempRteID);

        tableID.appendChild(tempRow);
      }

      //  alert('The database has ' + data.totalFileRows + ' files in the FILE table, ' + data.totalRouteRows + ' routes in the ROUTE table, and ' + data.totalPointRows + ' points in the POINT table');
    },
    fail: function (error) {
      // Non-200 return, do something with error
      console.log("DID NOT CONNECT");
    }
  });




});



$('#fourthQuery').click(function (e) {
  e.preventDefault();
  //Pass data to the Ajax call, so it gets passed to the server

  var dbUsername = document.getElementById("userName").value;
  var dbPassword = document.getElementById("userPassword").value;
  var dbName = document.getElementById("dbName").value;
  var numFiles = document.querySelector(".numberOfFiles").innerHTML;
  //numFiles = parseInt(numFiles);

  //  alert("NUMBER OF FILES: " + numFiles);
  // numFiles = parseInt(numFiles);

  var firstOption = document.querySelector(".q1Options");
  firstOption.style.display = "none";

  var secondOption = document.querySelector(".q2Options");
  secondOption.style.display = "none";

  var thirdOption = document.querySelector(".q3Options");
  thirdOption.style.display = "none";

  var fourthOption = document.querySelector(".q4Options");
  fourthOption.style.display = "block";

  var fifthOption = document.querySelector(".q5Options");
  fifthOption.style.display = "none";




  jQuery.ajax({
    type: 'get',            //Request type
    dataType: 'json',       //Data type - we will use JSON for almost everything
    url: '/getFileNameAndID',   //The server endpoint we are connecting to
    data: {
      userName: dbUsername,
      password: dbPassword,
      databaseName: dbName,
    },
    success: function (data) {
      /*  Do something with returned object
          Note that what we get is an object, not a string,
          so we do not need to parse it on the server.
          JavaScript really does handle JSONs seamlessly
      */
      console.log(data);
      var returnedObj = data.returnObj;

      //  console.log("TESTING PARSING DATA: " + returnedObj[0].route_name);
      var i = 0;
      var objLen = returnedObj.length;

      var tableID = document.getElementById("fourthQueryTable").childNodes[1];
      console.log(returnedObj);

      var oldTable = document.getElementById("fourthQueryTable").childNodes[1];
      var tableRows = oldTable.getElementsByTagName("tr");
      var rowCount = tableRows.length;

      var j = 0;

      var selectDiv = document.getElementById("selectFileForPoints");

      for (j = rowCount - 1; j > 0; j--) {
        oldTable.removeChild(tableRows[j]);
        console.log("REMOVING ROW");
      }

      for (const q1Row in returnedObj) {
        // ITERATING THROUGH ALL THE FILES

        //  console.log(`${q1Row}: ${returnedObj[q1Row].route_name}`);

        var tempFileName = document.createElement("button");
        tempFileName.setAttribute("id", "q4Div");
        var tempTextNode = document.createTextNode(`${returnedObj[q1Row].file_name}` + " ID:" + `${returnedObj[q1Row].gpx_id}`);

        tempFileName.appendChild(tempTextNode);
        selectDiv.appendChild(tempFileName);


      }


      //  alert('The database has ' + data.totalFileRows + ' files in the FILE table, ' + data.totalRouteRows + ' routes in the ROUTE table, and ' + data.totalPointRows + ' points in the POINT table');
    },
    fail: function (error) {
      // Non-200 return, do something with error
      console.log("DID NOT CONNECT");
    }
  });


});


$('#selectFileForPoints').click(function (e) {
  e.preventDefault();
  // console.log("TESTING: " + extractedID);
  //Pass data to the Ajax call, so it gets passed to the server

  var dbUsername = document.getElementById("userName").value;
  var dbPassword = document.getElementById("userPassword").value;
  var dbName = document.getElementById("dbName").value;
  var numFiles = document.querySelector(".numberOfFiles").innerHTML;
  //numFiles = parseInt(numFiles);

  //  alert("NUMBER OF FILES: " + numFiles);
  // numFiles = parseInt(numFiles);

  // var firstOption = document.querySelector(".q1Options");
  // firstOption.style.display = "none";

  // var secondOption = document.querySelector(".q2Options");
  // secondOption.style.display = "block";


  var getDivContent = document.querySelector(".q4Div");
  var divText = e.target.innerHTML;
  var findIndex = divText.indexOf("ID:");

  var extractedID = divText.substr(findIndex + 3);
  //alert("ID: " + extractedID);
  console.log("TESTING: " + extractedID);


  var superOldTable = document.getElementById("fourthQueryTable").childNodes[1];
  var firstTableRows = superOldTable.getElementsByTagName("tr");
  var firstRowCount = firstTableRows.length;

  var j = 0;

  for (j = firstRowCount - 1; j > 0; j--) {
    superOldTable.removeChild(firstTableRows[j]);
    console.log("REMOVING ROW");
  }





  jQuery.ajax({
    type: 'get',            //Request type
    dataType: 'json',       //Data type - we will use JSON for almost everything
    url: '/getSpecifiedRouteInfo',   //The server endpoint we are connecting to
    data: {
      userName: dbUsername,
      password: dbPassword,
      databaseName: dbName,
      gpxID: extractedID,
    },
    success: function (data) {
      /*  Do something with returned object
          Note that what we get is an object, not a string,
          so we do not need to parse it on the server.
          JavaScript really does handle JSONs seamlessly
      */
      console.log(data);
      var returnedObj = data.returnObj;

      //  console.log("TESTING PARSING DATA: " + returnedObj[0].route_name);
      var i = 0;
      var objLen = returnedObj.length;

      var tableID = document.getElementById("secondQueryRouteTable").childNodes[1];
      console.log(tableID);

      var oldTable = document.getElementById("secondQueryRouteTable").childNodes[1];
      var tableRows = oldTable.getElementsByTagName("tr");
      var rowCount = tableRows.length;

      var j = 0;

      for (j = rowCount - 1; j > 0; j--) {
        oldTable.removeChild(tableRows[j]);
        console.log("REMOVING ROW");
      }

      // returnedObj is an obj with all the routes

      // for each route, create an ajax call and pass in the route id
      for (const q1Row in returnedObj) {
        // ITERATING THROUGH ALL THE FILES

        //  console.log(`${q1Row}: ${returnedObj[q1Row].route_name}`);
        jQuery.ajax({
          type: 'get',            //Request type
          dataType: 'json',       //Data type - we will use JSON for almost everything
          url: '/getSpecifiedPoints',   //The server endpoint we are connecting to
          data: {
            userName: dbUsername,
            password: dbPassword,
            databaseName: dbName,
            gpxID: `${returnedObj[q1Row].route_id}`,
          },
          success: function (secondData) {
            /*  Do something with returned object
                Note that what we get is an object, not a string,
                so we do not need to parse it on the server.
                JavaScript really does handle JSONs seamlessly
            */
            console.log(" TESTING RETURN DATA FOR QUERY 4: " + secondData);
            var secondReturnedObj = secondData.returnObj;

            //  console.log("TESTING PARSING DATA: " + returnedObj[0].route_name);
            var i = 0;
            var objLen = secondReturnedObj.length;

            var tableID = document.getElementById("fourthQueryTable").childNodes[1];
            console.log(tableID);

            var oldTable = document.getElementById("fourthQueryTable").childNodes[1];
            var tableRows = oldTable.getElementsByTagName("tr");
            var rowCount = tableRows.length;

            var j = 0;

            for (j = rowCount - 1; j > 0; j--) {
              oldTable.removeChild(tableRows[j]);
              console.log("REMOVING ROW");
            }

            for (const q2Row in secondReturnedObj) {

              console.log(`${q2Row}: ${secondReturnedObj[q2Row].route_name}`);

              var tempRow = document.createElement("tr");

              var tempRteName = document.createElement("td");
              var tempRteNameText = document.createTextNode(`${secondReturnedObj[q2Row].point_index}`);
              tempRteName.appendChild(tempRteNameText);

              var tempRteLen = document.createElement("td");
              var tempRteLenText = document.createTextNode(`${secondReturnedObj[q2Row].latitude}`);
              tempRteLen.appendChild(tempRteLenText);

              var tempRteID = document.createElement("td");
              var tempRteIDText = document.createTextNode(`${secondReturnedObj[q2Row].longitude}`);
              tempRteID.appendChild(tempRteIDText);

              tempRow.appendChild(tempRteName);
              tempRow.appendChild(tempRteLen);
              tempRow.appendChild(tempRteID);

              tableID.appendChild(tempRow);
            }

            //  alert('The database has ' + data.totalFileRows + ' files in the FILE table, ' + data.totalRouteRows + ' routes in the ROUTE table, and ' + data.totalPointRows + ' points in the POINT table');
          },
          fail: function (error) {
            // Non-200 return, do something with error
            console.log("DID NOT CONNECT");
          }
        });





      }
      // on app.js, use this route id to select all the points in the points table with the same route id
      // return the points object here 
      // create another loop to iterate through all the points and add them

      //  alert('The database has ' + data.totalFileRows + ' files in the FILE table, ' + data.totalRouteRows + ' routes in the ROUTE table, and ' + data.totalPointRows + ' points in the POINT table');
    },
    fail: function (error) {
      // Non-200 return, do something with error
      console.log("DID NOT CONNECT");
    }
  });

});

$('#fifthQuery').click(function (e) {
  e.preventDefault();
  //Pass data to the Ajax call, so it gets passed to the server

  var dbUsername = document.getElementById("userName").value;
  var dbPassword = document.getElementById("userPassword").value;
  var dbName = document.getElementById("dbName").value;
  var numFiles = document.querySelector(".numberOfFiles").innerHTML;
  //numFiles = parseInt(numFiles);

  //  alert("NUMBER OF FILES: " + numFiles);
  // numFiles = parseInt(numFiles);

  var firstOption = document.querySelector(".q1Options");
  firstOption.style.display = "none";

  var secondOption = document.querySelector(".q2Options");
  secondOption.style.display = "none";

  var thirdOption = document.querySelector(".q3Options");
  thirdOption.style.display = "none";

  var fourthOption = document.querySelector(".q4Options");
  fourthOption.style.display = "none";

  var fifthOption = document.querySelector(".q5Options");
  fifthOption.style.display = "block";




  jQuery.ajax({
    type: 'get',            //Request type
    dataType: 'json',       //Data type - we will use JSON for almost everything
    url: '/getFileNameAndID',   //The server endpoint we are connecting to
    data: {
      userName: dbUsername,
      password: dbPassword,
      databaseName: dbName,
    },
    success: function (data) {
      /*  Do something with returned object
          Note that what we get is an object, not a string,
          so we do not need to parse it on the server.
          JavaScript really does handle JSONs seamlessly
      */
      console.log(data);
      var returnedObj = data.returnObj;

      //  console.log("TESTING PARSING DATA: " + returnedObj[0].route_name);
      var i = 0;
      var objLen = returnedObj.length;

      var tableID = document.getElementById("fifthQueryTable").childNodes[1];
      console.log(returnedObj);

      var oldTable = document.getElementById("fifthQueryTable").childNodes[1];
      var tableRows = oldTable.getElementsByTagName("tr");
      var rowCount = tableRows.length;

      var j = 0;

      var selectDiv = document.getElementById("selectNRoutes");

      for (j = rowCount - 1; j > 0; j--) {
        oldTable.removeChild(tableRows[j]);
        console.log("REMOVING ROW");
      }

      for (const q1Row in returnedObj) {
        // ITERATING THROUGH ALL THE FILES

        //  console.log(`${q1Row}: ${returnedObj[q1Row].route_name}`);

        var tempFileName = document.createElement("button");
        tempFileName.setAttribute("id", "q4Div");
        var tempTextNode = document.createTextNode(`${returnedObj[q1Row].file_name}` + " ID:" + `${returnedObj[q1Row].gpx_id}`);

        tempFileName.appendChild(tempTextNode);
        tempFileName.style.marginTop = "200px;";
        selectDiv.appendChild(tempFileName);


      }


      //  alert('The database has ' + data.totalFileRows + ' files in the FILE table, ' + data.totalRouteRows + ' routes in the ROUTE table, and ' + data.totalPointRows + ' points in the POINT table');
    },
    fail: function (error) {
      // Non-200 return, do something with error
      console.log("DID NOT CONNECT");
    }
  });


});



$('#selectNRoutes').click(function (e) {
  e.preventDefault();
  // console.log("TESTING: " + extractedID);
  //Pass data to the Ajax call, so it gets passed to the server

  var dbUsername = document.getElementById("userName").value;
  var dbPassword = document.getElementById("userPassword").value;
  var dbName = document.getElementById("dbName").value;
  var numFiles = document.querySelector(".numberOfFiles").innerHTML;

  // GETTING THE USER INPUT IN THE TEXT FIELDS
  var getNValue = document.getElementById("nPoints").value;
  var getSecondInput = document.getElementById("displayOption").value;

  // alert("N VALUE: " + getNValue + " SECOND INPUT: " + getSecondInput);



  //numFiles = parseInt(numFiles);

  //  alert("NUMBER OF FILES: " + numFiles);
  // numFiles = parseInt(numFiles);

  // var firstOption = document.querySelector(".q1Options");
  // firstOption.style.display = "none";

  // var secondOption = document.querySelector(".q2Options");
  // secondOption.style.display = "block";


  var getDivContent = document.querySelector(".q5Div");
  var divText = e.target.innerHTML;
  var findIndex = divText.indexOf("ID:");

  var extractedID = divText.substr(findIndex + 3);
  //alert("ID: " + extractedID);
  console.log("TESTING: " + extractedID);


  var superOldTable = document.getElementById("fifthQueryTable").childNodes[1];
  var firstTableRows = superOldTable.getElementsByTagName("tr");
  var firstRowCount = firstTableRows.length;

  var j = 0;

  for (j = firstRowCount - 1; j > 0; j--) {
    superOldTable.removeChild(firstTableRows[j]);
    console.log("REMOVING ROW");
  }


  if (getSecondInput == "Shortest") {
    jQuery.ajax({
      type: 'get',            //Request type
      dataType: 'json',       //Data type - we will use JSON for almost everything
      url: '/getNRoutes',   //The server endpoint we are connecting to
      data: {
        userName: dbUsername,
        password: dbPassword,
        databaseName: dbName,
        gpxID: extractedID,
        nRoutes: getNValue,
        textInput: getSecondInput,
      },
      success: function (data) {
        /*  Do something with returned object
            Note that what we get is an object, not a string,
            so we do not need to parse it on the server.
            JavaScript really does handle JSONs seamlessly
        */
        console.log(data);
        var returnedObj = data.returnObj;

        console.log("TESTING PARSING DATA: " + returnedObj[0].route_name);
        var i = 0;
        var objLen = returnedObj.length;

        var tableID = document.getElementById("fifthQueryTable").childNodes[1];
        console.log(returnedObj);

        var oldTable = document.getElementById("fifthQueryTable").childNodes[1];
        var tableRows = oldTable.getElementsByTagName("tr");
        var rowCount = tableRows.length;

        var j = 0;

        for (j = rowCount - 1; j > 0; j--) {
          oldTable.removeChild(tableRows[j]);
          console.log("REMOVING ROW");
        }

        for (const q1Row in returnedObj) {

          console.log(`${q1Row}: ${returnedObj[q1Row].route_name}`);



          var tempRteID = document.createElement("td");
          var tempNameText = document.createTextNode(`${returnedObj[q1Row].route_name}`);
          tempRteID.appendChild(tempNameText);

          var tempRteName = document.createElement("td");
          var tempCreatorText = document.createTextNode(`${returnedObj[q1Row].route_len}`);
          tempRteName.appendChild(tempCreatorText);

          var tempRteLen = document.createElement("td");
          var tempNumPointsText = document.createTextNode(`${returnedObj[q1Row].route_id}`);
          tempRteLen.appendChild(tempNumPointsText);

          var tempRouteRow = document.createElement("tr");

          tempRouteRow.appendChild(tempRteID);
          tempRouteRow.appendChild(tempRteName);
          tempRouteRow.appendChild(tempRteLen);
          //tempRouteRow.appendChild(tempRteOtherID);

          tableID.appendChild(tempRouteRow);
        }

        //  alert('The database has ' + data.totalFileRows + ' files in the FILE table, ' + data.totalRouteRows + ' routes in the ROUTE table, and ' + data.totalPointRows + ' points in the POINT table');
      },
      fail: function (error) {
        // Non-200 return, do something with error
        console.log("DID NOT CONNECT");
      }
    });
  } else if (getSecondInput == "Longest") {

    jQuery.ajax({
      type: 'get',            //Request type
      dataType: 'json',       //Data type - we will use JSON for almost everything
      url: '/getNLongestRoutes',   //The server endpoint we are connecting to
      data: {
        userName: dbUsername,
        password: dbPassword,
        databaseName: dbName,
        gpxID: extractedID,
        nRoutes: getNValue,
        textInput: getSecondInput,
      },
      success: function (data) {
        /*  Do something with returned object
            Note that what we get is an object, not a string,
            so we do not need to parse it on the server.
            JavaScript really does handle JSONs seamlessly
        */
        console.log(data);
        var returnedObj = data.returnObj;

        console.log("TESTING PARSING DATA: " + returnedObj[0].route_name);
        var i = 0;
        var objLen = returnedObj.length;

        var tableID = document.getElementById("fifthQueryTable").childNodes[1];
        console.log(returnedObj);

        var oldTable = document.getElementById("fifthQueryTable").childNodes[1];
        var tableRows = oldTable.getElementsByTagName("tr");
        var rowCount = tableRows.length;

        var j = 0;

        for (j = rowCount - 1; j > 0; j--) {
          oldTable.removeChild(tableRows[j]);
          console.log("REMOVING ROW");
        }

        for (const q1Row in returnedObj) {

          console.log(`${q1Row}: ${returnedObj[q1Row].route_name}`);



          var tempRteID = document.createElement("td");
          var tempNameText = document.createTextNode(`${returnedObj[q1Row].route_name}`);
          tempRteID.appendChild(tempNameText);

          var tempRteName = document.createElement("td");
          var tempCreatorText = document.createTextNode(`${returnedObj[q1Row].route_len}`);
          tempRteName.appendChild(tempCreatorText);

          var tempRteLen = document.createElement("td");
          var tempNumPointsText = document.createTextNode(`${returnedObj[q1Row].route_id}`);
          tempRteLen.appendChild(tempNumPointsText);

          var tempRouteRow = document.createElement("tr");

          tempRouteRow.appendChild(tempRteID);
          tempRouteRow.appendChild(tempRteName);
          tempRouteRow.appendChild(tempRteLen);
          //tempRouteRow.appendChild(tempRteOtherID);

          tableID.appendChild(tempRouteRow);
        }

        //  alert('The database has ' + data.totalFileRows + ' files in the FILE table, ' + data.totalRouteRows + ' routes in the ROUTE table, and ' + data.totalPointRows + ' points in the POINT table');
      },
      fail: function (error) {
        // Non-200 return, do something with error
        console.log("DID NOT CONNECT");
      }
    });

  }




  // create Ajax call and pass the user input in, as well as the fileName as usual to the already made ajax call
  // create a new one that mainly just differs with adding the "N" value and "secondInput"




});