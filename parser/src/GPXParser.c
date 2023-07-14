/**
 * section: Tree
 * synopsis: Navigates a tree to print element names
 * purpose: Parse a file to a tree, use xmlDocGetRootElement() to
 *          get the root element, then walk the document and print
 *          all the element name in document order.
 * usage: tree1 filename_or_URL
 * test: tree1 test2.xml > tree1.tmp && diff tree1.tmp $(srcdir)/tree1.res
 * copy: see Copyright for the status of this software.
 */
#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "GPXParser.h"
#include "LinkedListAPI.h"


//printFunc will return a string that contains a humanly readable copy of the list contents
// EDIT THIS TO FORMAT TO THE NODE WE WILL BE USING
char* printFunc(void *toBePrinted){

	char* tmpStr;

	if (toBePrinted == NULL){
		return NULL;
	}

	/*
	Length of the string is:
	length of the first and last names+3 spaces+4 chars for "Age:"+1 character for '\0'+20 digits to represent the age
	While we only need 3 digits to represent the human age, if the age is uninitialised, it can be any int value
	An int is 4 bytes, and needs up to 20 chars to represent it
	If we don't do this, our code will crash if age is uninitialized
	*/

    // create temp string for now for testing purposes
    // FIX LATER

    tmpStr = (char*)malloc(sizeof(char) * 30);
    strcpy(tmpStr, "Anupta");
    /*
	len = strlen(tmpName->data)+28;
	tmpStr = (char*)malloc(sizeof(char)*len);

	sprintf(tmpStr, "Data: %s", tmpName->data);
    */

	return tmpStr;
}

//We compare names by last name
// EDIT THIS TO FORMAT TO THE NODE WE WILL BE USING
int compareFunc(const void *first, const void *second){

	Node* tmpName1;
	Node* tmpName2;
    int checkIfEqual = 0;

	if (first == NULL || second == NULL){
		return 0;
	}

	tmpName1 = (Node*)first;
	tmpName2 = (Node*)second;

    if(tmpName1->data == tmpName2->data){
        checkIfEqual = 1;
    } else {
        checkIfEqual = 0;
    }

	return checkIfEqual;
}

//We need to free the first and last names, and then the Name struct itself
// EDIT THIS TO FORMAT TO THE NODE WE WILL BE USING
void deleteFunc(void *toBeDeleted){

	Node* tmpName;

	if (toBeDeleted == NULL){
		return;
	}

	tmpName = (Node*)toBeDeleted;

	free(tmpName->data);
    free(tmpName->previous);
    free(tmpName->next);

    free(tmpName);
}

int compareGpxData(const void *first, const void *second){
    GPXData *firstGPXData = (GPXData*) first;
    GPXData *secondGPXData = (GPXData*) second;

    // check what values I am required to return
    if(firstGPXData == secondGPXData){
        return 1;
    } else {
        return 0;
    }
}

char *gpxDataToString(void *data){
    char *toString = (char*)malloc(sizeof(char) * 100);
    strcpy(toString, "You have reached a GPX data node!\n");

    return toString;
}

void deleteGPXData(void* data){
    // printf("Reached free GPXData\n");
    GPXData *tempGPXData = (GPXData*)data;

    if(tempGPXData == NULL){
        return;
    } else {
       // free(tempGPXData->value);
      //  printf("GPX data to be deleted:name = %s value = %s\n", tempGPXData->name, tempGPXData->value);
        free(tempGPXData);

     //   printf("Finished delete GPXData\n");
        tempGPXData = NULL;
    }
    /*
    if(tempGPXData->name){
        free(tempGPXData->name);
    }

    if(tempGPXData->value){
        free(tempGPXData->value);
    }  */


}

char *trackToString(void* data){
    char *toString = (char*)malloc(sizeof(char) * 100);

    strcpy(toString, "You have reached a track node!\n");

    return toString;
}

void deleteTrack(void* data){
    Track *tempTrk = (Track*) data;
    if(tempTrk == NULL){
        return;
    } else {
      //   printf("Reached free track \n");
       //  printf("Track data to be deleted: name = %s\n", tempTrk->name);
        if(tempTrk->segments){

            freeList(tempTrk->segments);
            tempTrk->segments = NULL;
        }

        if(tempTrk->otherData){
            freeList(tempTrk->otherData);
            tempTrk->otherData = NULL;
        }

        if(tempTrk->name){
            free(tempTrk->name);
            tempTrk->name = NULL;
        }
        /*
        if(tempTrk->name){
            free(tempTrk->name);
            tempTrk->name = NULL;
        }
        */
        free(tempTrk);
        tempTrk = NULL;
    }
}

int compareTracks(const void *first, const void *second){
    Track *firstTrack = (Track*) first;
    Track *secondTrack = (Track*) second;

    // check what values I have to return
    if(firstTrack == secondTrack){
        return 1;
    } else {
        return 0;
    }
}

char *trackSegmentToString(void *data){
    char *toString = (char*) malloc(sizeof(char) * 100);
    strcpy(toString, "You have reached a track segment!\n");
    return toString;
}

void deleteTrackSegment(void *data){
    TrackSegment *tempSgmnt = (TrackSegment*) data;

    if(tempSgmnt == NULL){
        return;
    } else {
        if(tempSgmnt->waypoints){
        //    printf("Reached free track segment\n");
            freeList(tempSgmnt->waypoints);
            tempSgmnt->waypoints = NULL;
        }
        free(tempSgmnt);
        tempSgmnt = NULL;
    }
}

int compareTrackSegments(const void *first, const void *second){
    if(first == NULL){
        return 0;
    }

    if(second == NULL){
        return 0;
    }


    TrackSegment *firstSegment = (TrackSegment*) first;
    TrackSegment *secondSegment = (TrackSegment*) second;

    if(firstSegment == secondSegment){
        // check what value I will be required to return
        return 1;
    } else {
        return 0;
    }
}

char *waypointToString(void* data){
    char *toString = (char*)malloc(sizeof(char) * 100);

    strcpy(toString, "You have reached a waypoint node!\n");

    return toString;
}

void deleteWaypoint(void* data){
    Waypoint *tempWaypoint = (Waypoint*) data;
    if(tempWaypoint == NULL){
        return;
    } else {

        if(tempWaypoint->otherData){
         //   printf("To be deleted wpt lon and lat: %f and %f\n", tempWaypoint->longitude, tempWaypoint->latitude);
            freeList(tempWaypoint->otherData);
            tempWaypoint->otherData = NULL;
        }


        if(tempWaypoint->name){
            //printf("To be deleted wpt name: %s\n", tempWaypoint->name);
            free(tempWaypoint->name);
            tempWaypoint->name = NULL;
        }

        //free(tempWaypoint->name);
       // tempWaypoint->name = NULL;
        free(tempWaypoint);
        tempWaypoint = NULL;

    }

}

int compareWaypoints(const void *first, const void *second){
    Waypoint *firstWpt = (Waypoint*) first;
    Waypoint *secondWpt = (Waypoint*) second;

    // check what is required for return values
   if (firstWpt == secondWpt){
       return 1;
   } else {
       return 0;
   }
}

void deleteRoute(void* data){
    Route *toDelete = (Route*) data;

    if(toDelete == NULL){
        return;
    } else {

  //     printf("Route data to be deleted: %s\n", toDelete->name);

        if(toDelete->waypoints){
        freeList(toDelete->waypoints);
        }

  //      printf("waypoints deleted\n");

        if(toDelete->otherData){
            freeList(toDelete->otherData);
        }

   //     printf("otherData deleted\n");
        if(toDelete->name){
            free(toDelete->name);
            toDelete->name = NULL;
        }
        free(toDelete);
    }
}

char *routeToString(void* data){
    char *toString = (char*)malloc(sizeof(char) * 100);
    //printf("Made it to the toString method\n");
    strcpy(toString, "You have recieved a route object!\n");

    return toString;
}

int compareRoutes(const void *first, const void *second){
    Route *firstRoute = (Route*) first;
    Route *secondRoute = (Route*) second;

    // check what is required for return values
    if(firstRoute == secondRoute){
        return 1;
    } else {
        return 0;
    }
}


/***************    MODULE TWO FUNCTIONS BELOW AND ARE UNTIL THE print_element_names FUNCTION*/

int getNumWaypoints(const GPXdoc* doc){
    // there is a list of waypoint objects in the GPXDoc object (in the waypoints list)
    // iterate through the list and increment a counter variable upon each waypoint found
    // return the counter variable
    int numWaypoints = 0;
    Waypoint* tempWpt = NULL;
    ListIterator *tempIterator = NULL;
    ListIterator temp;

    if(doc == NULL){
        return 0;
    } else {
       // List *allWaypoints = doc->waypoints;

            if(doc->waypoints->head != NULL){
                temp = createIterator(doc->waypoints);
                // the iterator pointer is then pointed to the new iterator, which is for the tracks lists
                tempIterator = &temp;
                // a temporary track variable is used to get the next element in the list using the iterator
                // this works because the iterator contains the list of tracks
                // therefore, if nextElement is called with the iterator pointer as the parameter,
                // then the iterator goes to the next element in the list, which is technically the
                // next element in the track list
                // tempTrack is the now the first track
                tempWpt = (Waypoint*) nextElement(tempIterator);
                for(;tempWpt != NULL; tempWpt = (Waypoint*) nextElement(tempIterator)) {
                    numWaypoints++;
                    // insertBack(pathList, tempPath);
                }
            }
    return numWaypoints;
    }
}

int getNumRoutes(const GPXdoc* doc){

    // there is a list of route objects in the GPXDoc object (in the routes list)
    // iterate through the list and increment a counter variable upon each route found
    // return the counter variable
    int numRoutes = 0;
    Route *tempRoute;
    ListIterator *tempIterator = NULL;
    ListIterator temp;

    if(doc == NULL){
        return 0;
    } else {
      //  List *allRoutes = doc->routes;

            if(doc->routes->head != NULL){
                temp = createIterator(doc->routes);
                // the iterator pointer is then pointed to the new iterator, which is for the tracks lists
                tempIterator = &temp;
                // a temporary track variable is used to get the next element in the list using the iterator
                // this works because the iterator contains the list of tracks
                // therefore, if nextElement is called with the iterator pointer as the parameter,
                // then the iterator goes to the next element in the list, which is technically the
                // next element in the track list
                // tempTrack is the now the first track
                tempRoute = (Route*) nextElement(tempIterator);
                for(;tempRoute != NULL; tempRoute = (Route*) nextElement(tempIterator)) {
                    numRoutes++;
                    // insertBack(pathList, tempPath);
                }
            }

    return numRoutes;
    }
}

int getNumTracks(const GPXdoc* doc){

    // there is a list of track objects in the GPXDoc object (in the tracks list)
    // iterate through the list and increment a counter variable upon each track found
    // return the counter variable
    int numTracks = 0;
    Track *tempTrack = NULL;
    ListIterator* tempIterator = NULL;
    ListIterator temp;


    if(doc == NULL){
        return 0;
    } else {
       // List *allTracks = doc->tracks;

        if(doc->tracks->head != NULL){
            temp = createIterator(doc->tracks);
                // the iterator pointer is then pointed to the new iterator, which is for the tracks lists
                tempIterator = &temp;
                // a temporary track variable is used to get the next element in the list using the iterator
                // this works because the iterator contains the list of tracks
                // therefore, if nextElement is called with the iterator pointer as the parameter,
                // then the iterator goes to the next element in the list, which is technically the
                // next element in the track list
                // tempTrack is the now the first track
                tempTrack = (Track*) nextElement(tempIterator);
                for(;tempTrack != NULL; tempTrack = (Track*) nextElement(tempIterator)) {
                    numTracks++;
                   // insertBack(pathList, tempPath);
                }
        }
        /*
            while (allTracks->head != NULL){
            // list->deleteData(list->head->data);
                numTracks++;
                allTracks->head = allTracks->head->next;
            } */
    return numTracks;
    }
}

int getNumSegments(const GPXdoc* doc){

    // there is a list of track segment objects in the GPXDoc object (in the track segment list under each track)
    // iterate through the list and increment a counter variable upon each segment found
    // return the counter variable
    int numSegments = 0;

    if(doc == NULL){
        return 0;
    } else {

        // iterate through each track
        // at each track, iterate through each track segment
        // increment counter at each track segment

      //  List* trackList = NULL;
        ListIterator* tempIterator = NULL;
        Track* tempTrack = NULL;
        ListIterator temp;
        List *segmentsList = NULL;

       // trackList = initializeList(trackToString, deleteTrack, compareTracks);

        if(doc->tracks != NULL) {
            if(doc->tracks->head != NULL) {
              //  printf("TRACK HEAD IS NOT NULL\n");
                // iterator is created for the tracks list
                temp = createIterator(doc->tracks);
                // the iterator pointer is then pointed to the new iterator, which is for the tracks lists
                tempIterator = &temp;
                // a temporary track variable is used to get the next element in the list using the iterator
                // this works because the iterator contains the list of tracks
                // therefore, if nextElement is called with the iterator pointer as the parameter,
                // then the iterator goes to the next element in the list, which is technically the
                // next element in the track list
                // tempTrack is the now the first track
                tempTrack = (Track*) nextElement(tempIterator);
                for(;tempTrack != NULL; tempTrack = (Track*) nextElement(tempIterator)) {

                    // then find the length of each tracks, track segment list
                    segmentsList = tempTrack->segments;
                    if(segmentsList != NULL){
                        // add the length of the segments list of each track to the numSegments counter variable
                        numSegments += getLength(segmentsList);
                    }

                   // insertBack(pathList, tempPath);
                }
            }
        }
        return numSegments;

    }


}

int getNumGPXData(const GPXdoc* doc){
    int dataCounter = 0;
    if(doc == NULL){
        return 0;
    } else {
        // each Track has a GPX data list
        // each trkpt has a GPX data list (waypoint)
        // each Route has a GPX data list
        // each routePte has a GPX data list
        // each rtept has a GPX data list
        // each Waypoint has a GPX data list

        List *allTracks = doc->tracks;
        List *allTrkSegments = NULL;
        List *allRoutes = doc->routes;
      //  List *allWaypoints = doc->waypoints;

        Track *tempTrack = NULL;
        TrackSegment *tempSegment = NULL;
        Route *tempRte = NULL;
        ListIterator *tempIterator = NULL;
        ListIterator *secondIterator = NULL;
        ListIterator *thirdIterator = NULL;
        List *tempOtherData = NULL;
      //  GPXData *tempData = NULL;
        Waypoint *tempWpt = NULL;
        ListIterator temp;
        ListIterator secondTemp;
        ListIterator thirdTemp;

        if(doc->tracks != NULL){
            if(doc->tracks->head != NULL){
                temp = createIterator(allTracks);
                tempIterator = &temp;

                // in each track, get the length of the otherData list
                tempTrack = (Track*) nextElement(tempIterator);
                for(;tempTrack != NULL; tempTrack = (Track*) nextElement(tempIterator)) {
                    if(tempTrack->name){
                     //   printf("Data counter before a track name: %d\n", dataCounter);
                        dataCounter++;
                      //   printf("Data counter after a track name: %d\n", dataCounter);
                    }

                    if(tempTrack->otherData != NULL){
                        // if the otherData list is not NULL, point tempOtherData to it
                        tempOtherData = tempTrack->otherData;
                        // increment the dataCounter variable by the length of the tempOtherData list
                      //   printf("Data counter before a otherData list in a track: %d\n", dataCounter);
                        dataCounter = dataCounter + getLength(tempOtherData);
                       //  printf("Data counter after a otherData list in a track: %d\n", dataCounter);
                    }

                    // for each track segment associated with the track
                    // iterate through each of the trackpoints in each track segment
                    allTrkSegments = tempTrack->segments;
                    thirdTemp = createIterator(allTrkSegments);
                    // iterator for the track segments list
                    thirdIterator = &thirdTemp;
                    tempSegment = (TrackSegment*) nextElement(thirdIterator);

                    for(; tempSegment != NULL; tempSegment = (TrackSegment*) nextElement(thirdIterator)){
                        List *segmentTrkPoints = tempSegment->waypoints;
                        ListIterator fourthTemp;
                        ListIterator *fourthIterator = NULL;

                        fourthTemp = createIterator(segmentTrkPoints);
                        fourthIterator = &fourthTemp;

                        // segmentTrkPoints is all the points in the track segment
                        // each item in this list has an otherData list

                        Waypoint *tempTrkPt = (Waypoint*) nextElement(fourthIterator);
                        for(; tempTrkPt != NULL; tempTrkPt = (Waypoint*) nextElement(fourthIterator)){
                            if(tempTrkPt->otherData){
                                dataCounter += getLength(tempTrkPt->otherData);
                            }
                        }



                    }

                    // iterate through the track points in the current track's, other data list



                }
            } else if (doc->tracks->head == NULL){
              //  printf("NULL\n");
            }
        }

        // checking waypoints

        if(doc->waypoints != NULL){
            tempOtherData = NULL;

            if(doc->waypoints->head != NULL){
                thirdTemp = createIterator(doc->waypoints);
                tempIterator = &thirdTemp;

                tempWpt = (Waypoint*) nextElement(tempIterator);
                for(; tempWpt != NULL; tempWpt = (Waypoint*) nextElement(tempIterator)){

                    if(tempWpt->name != NULL){
                    //    printf("Data counter before a waypoints name is detected: %d\n", dataCounter);
                        dataCounter++;
                     //   printf("Data counter after a waypoints name is detected: %d\n", dataCounter);
                    }


                    if(tempWpt->otherData != NULL){
                        // tempOtherData is set to the waypoints "otherData" list
                        // tempOtherData is therefore a list of GPXData structs
                        tempOtherData = tempWpt->otherData;
                     //   GPXData *tempData = getFromFront(tempOtherData);
                      //  printf("Data counter before a waypoints otherData list: %d\n", dataCounter);
                        dataCounter += getLength(tempOtherData);
                      //  printf("Data counter after a waypoints otherData list: %d\n", dataCounter);


                    }
                }

            }
        }

        // checking routes
        if(doc->routes != NULL){
            if(doc->routes->head != NULL){
                temp = createIterator(allRoutes);
                tempIterator = &temp;
                tempRte = (Route*) nextElement(tempIterator);

                for(; tempRte != NULL; tempRte = (Route*) nextElement(tempIterator)){
                    if(tempRte->name != NULL){
                        // may have to change the name check to use strcmp in the future
                   //     printf("Data counter before a route name is detected: %d\n", dataCounter);
                        dataCounter++;
                   //     printf("Data counter after a route name is detected: %d\n", dataCounter);
                    }

                    if(tempRte->otherData != NULL){
                   //     printf("Data counter before a route otherData list is detected: %d\n", dataCounter);
                        dataCounter += getLength(tempRte->otherData);
                   //     printf("Data counter after a route otherData list is detected: %d\n", dataCounter);
                    }

                    List *routePoints = tempRte->waypoints;
                    secondTemp = createIterator(routePoints);
                    secondIterator = &secondTemp;

                    // in each track segmenent, search each track point for other data structs
                    tempWpt = (Waypoint*) nextElement(secondIterator);
                    // iterate through the track points in the current track's, other data list
                    for(; tempWpt != NULL; tempWpt = (Waypoint*) nextElement(secondIterator)){
                        if(tempWpt->otherData != NULL){
                            tempOtherData = tempWpt->otherData;
                            // increment the data counter by the length of the list
                       //     printf("Data before a rtept otherData value is detected: %d\n", dataCounter);
                            dataCounter += getLength(tempOtherData);
                       //     printf("Data after a rtept otherData value is detected: %d\n", dataCounter);
                        }
                    }
                }

            }
        }

        //

    return dataCounter;
    }

}


bool compareWaypointNames(const void* first, const void* searchString){
    Waypoint *firstWpt = (Waypoint*) first;
    char *theString = (char*) searchString;

    // check what is required for return values
    // check if waypoint names are the same
    // check if waypoint longitude and latitudes are the same

    if((strcmp(firstWpt->name, theString) == 0)){
        // if between both waypoints, the name is the same, the longitude is the same, and the latitude is the same, then proceed
        return true;
    } else {
        return false;
    }
}


Waypoint* getWaypoint(const GPXdoc* doc, char* name){
   // Returns a pointer to a waypoint with the given name.  If more than one exists, return the first one.
   // Return NULL if the waypoint is not found, or any of the arguments are NULL
   // iterate through the GPX doc's waypoints list
   // compare the name of the waypoint with the names of all the waypoints in the waypoints list
   // if there is a matching value, return a pointer to that Waypoint object
   // if not then return NULL;

    if((doc == NULL)  || (name == NULL)){
        // if the GPX doc passed in is null, or the name is null, return
        return NULL;
    }

    Waypoint *tempWaypoint = NULL;
    List *docWptList = doc->waypoints;

    tempWaypoint = (Waypoint*) findElement(docWptList, &compareWaypointNames, name);

    return tempWaypoint;
}

bool compareTrackNames(const void* first, const void* searchString){
    Track *firstTrack = (Track*) first;
    char *theString = (char*) searchString;

    // check what is required for return values
    // check if waypoint names are the same
    // check if waypoint longitude and latitudes are the same

    if((strcmp(firstTrack->name, theString) == 0)){
        // if between both waypoints, the name is the same, the longitude is the same, and the latitude is the same, then proceed
        return true;
    } else {
        return false;
    }
}

Track* getTrack(const GPXdoc* doc, char* name){

//Function that returns a pointer to a track with the given name.  If more than one exists, return the first one.
//Return NULL if the track is not found, or any of the arguments are NULL.
    if(doc == NULL || name == NULL){
        // if any of the arguments are NULL, return NULL
        return NULL;
    }

    List *allDocTracks = doc->tracks;
    Track *tempTrack = NULL;

    tempTrack = (Track*) findElement(allDocTracks, &compareTrackNames, name);

    return tempTrack;
}

bool compareRouteNames(const void* first, const void* searchString){
    Route *firstRoute = (Route*) first;
    char *theString = (char*) searchString;

    // check what is required for return values
    // check if waypoint names are the same
    // check if waypoint longitude and latitudes are the same

    if((strcmp(firstRoute->name, theString) == 0)){
        // if between both waypoints, the name is the same, the longitude is the same, and the latitude is the same, then proceed
        return true;
    } else {
        return false;
    }
}

Route* getRoute(const GPXdoc* doc, char* name){

//Function that returns a pointer to a track with the given name.  If more than one exists, return the first one.
//Return NULL if the track is not found, or any of the arguments are NULL.
    if(doc == NULL || name == NULL){
        // if any of the arguments are NULL, return NULL
        return NULL;
    }

    List *allDocRoutes = doc->routes;
    Route *tempRoute = NULL;

    tempRoute = (Route*) findElement(allDocRoutes, &compareRouteNames, name);

    return tempRoute;
}


/*
 *To compile this file using gcc you can type.  Alternatively, see the Makefile for include path settings
 *gcc `xml2-config --cflags --libs` -o xmlexample libxml2-example.c
 */

/**
 * print_element_names:
 * @a_node: the initial xml node to consider.
 *
 * Prints the names of the all the xml elements
 * that are siblings or children of a given xml node.
 *  pass in GPXDoc Struct
 *  fill in GPXDoc Struct on each iteration
 *  provide checks / if statements to see what the atrribute name is and then
 *  create the struct based off that
 */
static void
print_element_names(xmlNode * a_node, GPXdoc *theDoc)
{
  //  int nodeCheckedVal = 2;
  //  int validInput = 2;
    xmlNode *cur_node = NULL;
   // GPXdoc *tempDoc = NULL;
   // xmlNode *tempChildNode = NULL;
    char *eptr;
    xmlAttr *tempAttr;
   // xmlAttr *tempTrackAttr;
  //  int checkParentIsTrack = 0;

    // FREE this variable later
   // TrackSegment *tempSegment = (TrackSegment*) malloc(sizeof(TrackSegment));
   // Track *tempTrack = (Track*) malloc(sizeof(Track*));
 //   tempDoc = (GPXdoc*) malloc(sizeof(GPXdoc*));


    if(theDoc == NULL){
        return;
    }

    for (cur_node = a_node; cur_node != NULL; cur_node = cur_node->next) {

        char *tempString = (char*)malloc(sizeof(char) * 50);


        if (cur_node->type == XML_ELEMENT_NODE) {


            // checking if the parsed file is valid
            // if it is currently an XML node

         //   printf("node type: Element, name: %s\n", cur_node->name);

            // CHECK HERE FOR MEMORY LEAKS LATER
            // if it is a gpx node
            if(strcmp((char*)cur_node->name, "gpx") == 0){
                // Iterate through every attribute of the current node

                for (tempAttr = cur_node->properties; tempAttr != NULL; tempAttr = tempAttr->next)
                {
                    xmlNode *theValue = tempAttr->children;
                    char *attributeName = (char *)tempAttr->name;
                    char *theCont = (char *)(theValue->content);

                    // if the property name is schemaLocation
                    if(strcmp(attributeName, "schemaLocation") == 0){
                      //  strcpy(theDoc->namespace, theCont);
                    //    printf("Testing namespace value: %s\n", theDoc->namespace);
                    } else if (strcmp(attributeName, "version") == 0){
                        // convert string to double and then pass in to the GPX doc
                        strcpy(tempString, theCont);
                        theDoc->version = strtod(tempString, &eptr);
                     //   free(tempString);
                     //   printf("Temp Version Value: %.1f\n", theDoc->version);
                    } else if(strcmp(attributeName, "creator") == 0){
                        strcpy(theDoc->creator, theCont);
                    }
                //  printf("\tattribute name: %s, attribute value = %s\n", attrName, cont);
                }
            }  else if ((strcmp((char*)cur_node->name, "wpt") == 0) && (strcmp((char*)cur_node->parent->name, "gpx") == 0)){
                // create a Waypoint object
                Waypoint *temporaryWpt = (Waypoint*)malloc(sizeof(Waypoint));
                temporaryWpt->name = (char*)malloc(sizeof(char*) * 100);
                temporaryWpt->longitude = 0.0;
                temporaryWpt->latitude = 0.0;
                temporaryWpt->otherData = initializeList(&gpxDataToString, &deleteGPXData, &compareGpxData);
                char tmpString[200];

                   for (tempAttr = cur_node->properties; tempAttr != NULL; tempAttr = tempAttr->next)
                    {
                        xmlNode *theValue = tempAttr->children;
                        char *attributeName = (char *)tempAttr->name;
                        char *theCont = (char *)(theValue->content);

                        // if the property name indicates it is referring to the latitude
                        if(strcmp(attributeName, "lat") == 0){
                            // converting string value to double and then adding it to the waypoints latitude
                            strcpy(tmpString, theCont);
                            temporaryWpt->latitude = strtod(tmpString, &eptr);
                        //    printf("testing waypoint latitude: %f\n", temporaryWpt->latitude);
                           // free(tempString);
                        //    else if the property name indicates it is referring to the longitude
                        } else if (strcmp(attributeName, "lon") == 0){
                            // converting string value to double and then adding it to the waypoints longitude
                            // convert string to double and then pass in to the GPX doc
                            strcpy(tmpString, theCont);
                            temporaryWpt->longitude = strtod(tmpString, &eptr);
                        //    printf("testing waypoint longitude: %f\n", temporaryWpt->longitude);
                           // free(tempString);
                        }

                    }
                    // add the latitude and longitude to the waypoint object
                    // add the waypoint object to the back of the GPX document's Waypoint's list

                    insertBack(theDoc->waypoints, temporaryWpt);


            } else if ((strcmp((char*)cur_node->name, "name") == 0) && (strcmp((char*)cur_node->parent->name, "wpt") == 0)) {
                // if the current node name value is "name", and the parent node name is "wpt", then I know it is a valid node
                // get the last wpt in the waypoints list in the GPX doc
                // add the name content to the name of the waypoint
                if((strcmp((char*)cur_node->parent->parent->name, "gpx") == 0)){
                    Waypoint *lastWpt = getFromBack(theDoc->waypoints);
                    strcpy(lastWpt->name,(char*)cur_node->children->content);
                }
            } else if ( (strcmp((char*)cur_node->name, "ele") == 0) && (strcmp((char*)cur_node->parent->name, "wpt") == 0)){

                // if it is a sub element of a waypoint instance and the parent node name is "wpt", then I know it is a valid node
                // this data will go int othe other data list of a waypoint object
                // create a GPX Data object
                // add the name of the current node to the name of the GPX data object
                // add the content of the current node to the value[] variable in the GPX data object
                // get the last waypoint in the GPX doc list
                // add the GPX doc object to the end of the last waypoint's otherData list

                GPXData *newData = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(newData->value[0]));



                if((char*)cur_node->name){
                    strcpy(newData->name, (char*)cur_node->name);
                }

                if((char*)cur_node->children->content){
                    strcpy(newData->value, (char*)cur_node->children->content);
                }

                Waypoint *lastWaypoint = getFromBack(theDoc->waypoints);
                insertBack(lastWaypoint->otherData, newData);


            } else if ((strcmp((char*)cur_node->name, "time") == 0) && (strcmp((char*)cur_node->parent->name, "wpt") == 0) ){
                // if it is a sub element of a waypoint instance and the parent node name is "wpt", then I know it is a valid node
                // this data will go int othe other data list of a waypoint object
                // create a GPX Data object
                // add the name of the current node to the name of the GPX data object
                // add the content of the current node to the value[] variable in the GPX data object
                // get the last waypoint in the GPX doc list
                // add the GPX doc object to the end of the last waypoint's otherData list
                GPXData *newData = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(newData->value[0]));



                if((char*)cur_node->name){
                    strcpy(newData->name, (char*)cur_node->name);
                }

                if((char*)cur_node->children->content){
                    strcpy(newData->value, (char*)cur_node->children->content);
                }

                Waypoint *lastWaypoint = getFromBack(theDoc->waypoints);
                insertBack(lastWaypoint->otherData, newData);

            } else if ((strcmp((char*)cur_node->name, "magvar") == 0) && (strcmp((char*)cur_node->parent->name, "wpt") == 0) ){
                // if it is a sub element of a waypoint instance and the parent node name is "wpt", then I know it is a valid node
                // this data will go int othe other data list of a waypoint object
                // create a GPX Data object
                // add the name of the current node to the name of the GPX data object
                // add the content of the current node to the value[] variable in the GPX data object
                // get the last waypoint in the GPX doc list
                // add the GPX doc object to the end of the last waypoint's otherData list
                GPXData *newData = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(newData->value[0]));



                if((char*)cur_node->name){
                    strcpy(newData->name, (char*)cur_node->name);
                }

                if((char*)cur_node->children->content){
                    strcpy(newData->value, (char*)cur_node->children->content);
                }

                Waypoint *lastWaypoint = getFromBack(theDoc->waypoints);
                insertBack(lastWaypoint->otherData, newData);

            } else if ((strcmp((char*)cur_node->name, "geoidheight") == 0) && (strcmp((char*)cur_node->parent->name, "wpt") == 0) ){
                // if it is a sub element of a waypoint instance and the parent node name is "wpt", then I know it is a valid node
                // this data will go int othe other data list of a waypoint object
                // create a GPX Data object
                // add the name of the current node to the name of the GPX data object
                // add the content of the current node to the value[] variable in the GPX data object
                // get the last waypoint in the GPX doc list
                // add the GPX doc object to the end of the last waypoint's otherData list
                GPXData *newData = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(newData->value[0]));



                if((char*)cur_node->name){
                    strcpy(newData->name, (char*)cur_node->name);
                }

                if((char*)cur_node->children->content){
                    strcpy(newData->value, (char*)cur_node->children->content);
                }

                Waypoint *lastWaypoint = getFromBack(theDoc->waypoints);
                insertBack(lastWaypoint->otherData, newData);

            } else if ((strcmp((char*)cur_node->name, "cmt") == 0) && (strcmp((char*)cur_node->parent->name, "wpt") == 0) ){
                // if it is a sub element of a waypoint instance and the parent node name is "wpt", then I know it is a valid node
                // this data will go int othe other data list of a waypoint object
                // create a GPX Data object
                // add the name of the current node to the name of the GPX data object
                // add the content of the current node to the value[] variable in the GPX data object
                // get the last waypoint in the GPX doc list
                // add the GPX doc object to the end of the last waypoint's otherData list
                GPXData *newData = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(newData->value[0]));



                if((char*)cur_node->name){
                    strcpy(newData->name, (char*)cur_node->name);
                }

                if((char*)cur_node->children->content){
                    strcpy(newData->value, (char*)cur_node->children->content);
                }

                Waypoint *lastWaypoint = getFromBack(theDoc->waypoints);
                insertBack(lastWaypoint->otherData, newData);

            } else if ((strcmp((char*)cur_node->name, "desc") == 0) && (strcmp((char*)cur_node->parent->name, "wpt") == 0) ){
                // if it is a sub element of a waypoint instance and the parent node name is "wpt", then I know it is a valid node
                // this data will go int othe other data list of a waypoint object
                // create a GPX Data object
                // add the name of the current node to the name of the GPX data object
                // add the content of the current node to the value[] variable in the GPX data object
                // get the last waypoint in the GPX doc list
                // add the GPX doc object to the end of the last waypoint's otherData list
                GPXData *newData = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(newData->value[0]));



                if((char*)cur_node->name){
                    strcpy(newData->name, (char*)cur_node->name);
                }

                if((char*)cur_node->children->content){
                    strcpy(newData->value, (char*)cur_node->children->content);
                }

                Waypoint *lastWaypoint = getFromBack(theDoc->waypoints);
                insertBack(lastWaypoint->otherData, newData);

            } else if ((strcmp((char*)cur_node->name, "src") == 0) && (strcmp((char*)cur_node->parent->name, "wpt") == 0) ){
                // if it is a sub element of a waypoint instance and the parent node name is "wpt", then I know it is a valid node
                // this data will go int othe other data list of a waypoint object
                // create a GPX Data object
                // add the name of the current node to the name of the GPX data object
                // add the content of the current node to the value[] variable in the GPX data object
                // get the last waypoint in the GPX doc list
                // add the GPX doc object to the end of the last waypoint's otherData list
                GPXData *newData = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(newData->value[0]));



                if((char*)cur_node->name){
                    strcpy(newData->name, (char*)cur_node->name);
                }

                if((char*)cur_node->children->content){
                    strcpy(newData->value, (char*)cur_node->children->content);
                }

                Waypoint *lastWaypoint = getFromBack(theDoc->waypoints);
                insertBack(lastWaypoint->otherData, newData);

            } else if ((strcmp((char*)cur_node->name, "sym") == 0) && (strcmp((char*)cur_node->parent->name, "wpt") == 0) ){
                // if it is a sub element of a waypoint instance and the parent node name is "wpt", then I know it is a valid node
                // this data will go int othe other data list of a waypoint object
                // create a GPX Data object
                // add the name of the current node to the name of the GPX data object
                // add the content of the current node to the value[] variable in the GPX data object
                // get the last waypoint in the GPX doc list
                // add the GPX doc object to the end of the last waypoint's otherData list
                GPXData *newData = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(newData->value[0]));



                if((char*)cur_node->name){
                    strcpy(newData->name, (char*)cur_node->name);
                }

                if((char*)cur_node->children->content){
                    strcpy(newData->value, (char*)cur_node->children->content);
                }

                Waypoint *lastWaypoint = getFromBack(theDoc->waypoints);
                insertBack(lastWaypoint->otherData, newData);

            } else if ((strcmp((char*)cur_node->name, "type") == 0) && (strcmp((char*)cur_node->parent->name, "wpt") == 0) ){
                // if it is a sub element of a waypoint instance and the parent node name is "wpt", then I know it is a valid node
                // this data will go int othe other data list of a waypoint object
                // create a GPX Data object
                // add the name of the current node to the name of the GPX data object
                // add the content of the current node to the value[] variable in the GPX data object
                // get the last waypoint in the GPX doc list
                // add the GPX doc object to the end of the last waypoint's otherData list
                GPXData *newData = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(newData->value[0]));



                if((char*)cur_node->name){
                    strcpy(newData->name, (char*)cur_node->name);
                }

                if((char*)cur_node->children->content){
                    strcpy(newData->value, (char*)cur_node->children->content);
                }

                Waypoint *lastWaypoint = getFromBack(theDoc->waypoints);
                insertBack(lastWaypoint->otherData, newData);

            } else if ((strcmp((char*)cur_node->name, "sat") == 0) && (strcmp((char*)cur_node->parent->name, "wpt") == 0) ){
                // if it is a sub element of a waypoint instance and the parent node name is "wpt", then I know it is a valid node
                // this data will go int othe other data list of a waypoint object
                // create a GPX Data object
                // add the name of the current node to the name of the GPX data object
                // add the content of the current node to the value[] variable in the GPX data object
                // get the last waypoint in the GPX doc list
                // add the GPX doc object to the end of the last waypoint's otherData list
                GPXData *newData = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(newData->value[0]));



                if((char*)cur_node->name){
                    strcpy(newData->name, (char*)cur_node->name);
                }

                if((char*)cur_node->children->content){
                    strcpy(newData->value, (char*)cur_node->children->content);
                }

                Waypoint *lastWaypoint = getFromBack(theDoc->waypoints);
                insertBack(lastWaypoint->otherData, newData);

            } else if ((strcmp((char*)cur_node->name, "hdop") == 0) && (strcmp((char*)cur_node->parent->name, "wpt") == 0) ){
                // if it is a sub element of a waypoint instance and the parent node name is "wpt", then I know it is a valid node
                // this data will go int othe other data list of a waypoint object
                // create a GPX Data object
                // add the name of the current node to the name of the GPX data object
                // add the content of the current node to the value[] variable in the GPX data object
                // get the last waypoint in the GPX doc list
                // add the GPX doc object to the end of the last waypoint's otherData list
                GPXData *newData = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(newData->value[0]));



                if((char*)cur_node->name){
                    strcpy(newData->name, (char*)cur_node->name);
                }

                if((char*)cur_node->children->content){
                    strcpy(newData->value, (char*)cur_node->children->content);
                }

                Waypoint *lastWaypoint = getFromBack(theDoc->waypoints);
                insertBack(lastWaypoint->otherData, newData);

            } else if ((strcmp((char*)cur_node->name, "vdop") == 0) && (strcmp((char*)cur_node->parent->name, "wpt") == 0) ){
                // if it is a sub element of a waypoint instance and the parent node name is "wpt", then I know it is a valid node
                // this data will go int othe other data list of a waypoint object
                // create a GPX Data object
                // add the name of the current node to the name of the GPX data object
                // add the content of the current node to the value[] variable in the GPX data object
                // get the last waypoint in the GPX doc list
                // add the GPX doc object to the end of the last waypoint's otherData list
                GPXData *newData = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(newData->value[0]));



                if((char*)cur_node->name){
                    strcpy(newData->name, (char*)cur_node->name);
                }

                if((char*)cur_node->children->content){
                    strcpy(newData->value, (char*)cur_node->children->content);
                }

                Waypoint *lastWaypoint = getFromBack(theDoc->waypoints);
                insertBack(lastWaypoint->otherData, newData);

            } else if ((strcmp((char*)cur_node->name, "pdop") == 0) && (strcmp((char*)cur_node->parent->name, "wpt") == 0) ){
                // if it is a sub element of a waypoint instance and the parent node name is "wpt", then I know it is a valid node
                // this data will go int othe other data list of a waypoint object
                // create a GPX Data object
                // add the name of the current node to the name of the GPX data object
                // add the content of the current node to the value[] variable in the GPX data object
                // get the last waypoint in the GPX doc list
                // add the GPX doc object to the end of the last waypoint's otherData list
                GPXData *newData = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(newData->value[0]));



                if((char*)cur_node->name){
                    strcpy(newData->name, (char*)cur_node->name);
                }

                if((char*)cur_node->children->content){
                    strcpy(newData->value, (char*)cur_node->children->content);
                }

                Waypoint *lastWaypoint = getFromBack(theDoc->waypoints);
                insertBack(lastWaypoint->otherData, newData);

            } else if ((strcmp((char*)cur_node->name, "ageofdgpsdata") == 0) && (strcmp((char*)cur_node->parent->name, "wpt") == 0) ){
                // if it is a sub element of a waypoint instance and the parent node name is "wpt", then I know it is a valid node
                // this data will go int othe other data list of a waypoint object
                // create a GPX Data object
                // add the name of the current node to the name of the GPX data object
                // add the content of the current node to the value[] variable in the GPX data object
                // get the last waypoint in the GPX doc list
                // add the GPX doc object to the end of the last waypoint's otherData list
                GPXData *newData = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(newData->value[0]));

                if((char*)cur_node->name){
                    strcpy(newData->name, (char*)cur_node->name);
                }

                if((char*)cur_node->children->content){
                    strcpy(newData->value, (char*)cur_node->children->content);
                }

                Waypoint *lastWaypoint = getFromBack(theDoc->waypoints);
                insertBack(lastWaypoint->otherData, newData);

            }/* new code being added */ else if ((strcmp((char*)cur_node->name, "rte") == 0) && (strcmp((char*)cur_node->parent->name, "gpx") == 0)){
                Route *tempRoute = (Route*) malloc(sizeof(Route));
                tempRoute->name = (char*)malloc(sizeof(char) * 100);
                tempRoute->waypoints = initializeList(&waypointToString, &deleteWaypoint, &compareWaypoints);
                tempRoute->otherData = initializeList(&gpxDataToString, &deleteGPXData, &compareGpxData);
                strcpy(tempRoute->name, "");
                insertBack(theDoc->routes, tempRoute);
            }



            else if ((strcmp((char*)cur_node->name, "name") == 0) && (strcmp((char*)cur_node->parent->name, "rte") == 0)){
             //   printf("Route node found\n");
                // if the current node has the name route, and the parent node is rte then I know it is the route node child(name) and valid
                // create a route object

              //  Route *tempRoute = (Route*) malloc(sizeof(Route));
              //  tempRoute->name = (char*)malloc(sizeof(char) * 100);
              //  tempRoute->waypoints = initializeList(&waypointToString, &deleteWaypoint, &compareWaypoints);
              //  tempRoute->otherData = initializeList(&GPXDataToString, &deleteGPXData, &compareGpxData);
                Route *tempRte = NULL;

                if(cur_node->children->content){
                    tempRte = getFromBack(theDoc->routes);
                // get the last route and copy the name to the route name
                    strcpy(tempRte->name, (char*)cur_node->children->content);
                   // strcpy(routeName, (char*)cur_node->children->content);
                }
                // add the route object to the GPXDoc
                // add to back ensures that I am adding the routes in order as they are parsed


            } else if ((strcmp((char*)cur_node->name, "cmt") == 0) && (strcmp((char*)cur_node->parent->name, "rte") == 0)){
               // printf("Route node found\n");
                // if the current node has a sub property of route, and the parent node is rte then I know it is the route node child and valid
                // create a GPX Data object
                // add the node name to the GPX object
                // add the content of the node to the GPX object value[] variable
                // get the most recent route
                // add the GPX data object to the otherData list of the most recent route

                GPXData *otherInfo = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(otherInfo->value[0]));

                if((char*)cur_node->name){
                    strcpy(otherInfo->name, (char*)cur_node->name);
                }

                if((char*)cur_node->children->content){
                    strcpy(otherInfo->value, (char*)cur_node->children->content);
                }
                Route *mostRecent = getFromBack(theDoc->routes);
                insertBack(mostRecent->otherData, otherInfo);

            } else if ((strcmp((char*)cur_node->name, "desc") == 0) && (strcmp((char*)cur_node->parent->name, "rte") == 0)){
               // printf("Route node found\n");
                // if the current node has a sub property of route, and the parent node is rte then I know it is the route node child and valid
                // create a GPX Data object
                // add the node name to the GPX object
                // add the content of the node to the GPX object value[] variable
                // get the most recent route
                // add the GPX data object to the otherData list of the most recent route

                GPXData *otherInfo = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(otherInfo->value[0]));

                if((char*)cur_node->name){
                    strcpy(otherInfo->name, (char*)cur_node->name);
                }

                if((char*)cur_node->children->content){
                    strcpy(otherInfo->value, (char*)cur_node->children->content);
                }
                Route *mostRecent = getFromBack(theDoc->routes);
                insertBack(mostRecent->otherData, otherInfo);

            } else if ((strcmp((char*)cur_node->name, "src") == 0) && (strcmp((char*)cur_node->parent->name, "rte") == 0)){
               // printf("Route node found\n");
                // if the current node has a sub property of route, and the parent node is rte then I know it is the route node child and valid
                // create a GPX Data object
                // add the node name to the GPX object
                // add the content of the node to the GPX object value[] variable
                // get the most recent route
                // add the GPX data object to the otherData list of the most recent route

                GPXData *otherInfo = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(otherInfo->value[0]));

                if((char*)cur_node->name){
                    strcpy(otherInfo->name, (char*)cur_node->name);
                }

                if((char*)cur_node->children->content){
                    strcpy(otherInfo->value, (char*)cur_node->children->content);
                }
                Route *mostRecent = getFromBack(theDoc->routes);
                insertBack(mostRecent->otherData, otherInfo);

            } else if ((strcmp((char*)cur_node->name, "number") == 0) && (strcmp((char*)cur_node->parent->name, "rte") == 0)){
               // printf("Route node found\n");
                // if the current node has a sub property of route, and the parent node is rte then I know it is the route node child and valid
                // create a GPX Data object
                // add the node name to the GPX object
                // add the content of the node to the GPX object value[] variable
                // get the most recent route
                // add the GPX data object to the otherData list of the most recent route

                GPXData *otherInfo = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(otherInfo->value[0]));

                if((char*)cur_node->name){
                    strcpy(otherInfo->name, (char*)cur_node->name);
                }

                if((char*)cur_node->children->content){
                    strcpy(otherInfo->value, (char*)cur_node->children->content);
                }
                Route *mostRecent = getFromBack(theDoc->routes);
                insertBack(mostRecent->otherData, otherInfo);

            } else if ((strcmp((char*)cur_node->name, "type") == 0) && (strcmp((char*)cur_node->parent->name, "rte") == 0)){
               // printf("Route node found\n");
                // if the current node has a sub property of route, and the parent node is rte then I know it is the route node child and valid
                // create a GPX Data object
                // add the node name to the GPX object
                // add the content of the node to the GPX object value[] variable
                // get the most recent route
                // add the GPX data object to the otherData list of the most recent route

                GPXData *otherInfo = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(otherInfo->value[0]));

                if((char*)cur_node->name){
                    strcpy(otherInfo->name, (char*)cur_node->name);
                }

                if((char*)cur_node->children->content){
                    strcpy(otherInfo->value, (char*)cur_node->children->content);
                }
                Route *mostRecent = getFromBack(theDoc->routes);
                insertBack(mostRecent->otherData, otherInfo);

            } else if ((strcmp((char*)cur_node->name, "rtept") == 0) && (strcmp((char*)cur_node->parent->name, "rte") == 0)) {
                // if the current node name is "rtept" and the parent node name is "rte", then I know it is a valid "rtept" node
                // create waypoint object that holds the "rtept" info
                // realloc memory to the waypoints list in routes, and add the waypoint object to that list
                char tmpString[200];
                Waypoint *tempRte = (Waypoint*)malloc(sizeof(Waypoint));
                tempRte->name = (char*)malloc(sizeof(char) * 100);
                tempRte->longitude = 0.0;
                tempRte->latitude = 0.0;
                tempRte->otherData = initializeList(&gpxDataToString, &deleteGPXData, &compareGpxData);



                // loop that iterates through the XML attributes and stores the longitude and latitude
                // values into the tempRte node
                for (tempAttr = cur_node->properties; tempAttr != NULL; tempAttr = tempAttr->next)
                    {
                        xmlNode *theValue = tempAttr->children;
                        char *attributeName = (char *)tempAttr->name;
                        char *theCont = (char *)(theValue->content);

                        // if the property name indicates it is referring to the latitude
                        if(strcmp(attributeName, "lat") == 0){
                            // converting string value to double and then adding it to the waypoints latitude
                            strcpy(tmpString, theCont);
                            tempRte->latitude = strtod(tmpString, &eptr);
                          //  printf("testing waypoint latitude: %f\n", tempRte->latitude);
                           // free(tempString);
                        //    else if the property name indicates it is referring to the longitude
                        } else if (strcmp(attributeName, "lon") == 0){
                            // converting string value to double and then adding it to the waypoints longitude
                            // convert string to double and then pass in to the GPX doc
                            strcpy(tmpString, theCont);
                            tempRte->longitude = strtod(tmpString, &eptr);
                        //    printf("testing waypoint longitude: %f\n", tempRte->longitude);
                           // free(tempString);
                        }

                    }
              //  printf("made it past the loop\n");
                Route *tempCurrentRoute = getFromBack(theDoc->routes);
                //tempCurrentRoute->waypoints = (List*)realloc(tempCurrentRoute->waypoints, sizeof(Node*) + 1);

                // CHECK FOR OTHER DATA AFTER
                insertBack(tempCurrentRoute->waypoints, tempRte);

            } /* new code being added */else if ((strcmp((char*)cur_node->name, "name") == 0) &&  (strcmp((char*)cur_node->parent->name, "rtept") == 0) ){
                // if it is a rtept description
                GPXData *tempData = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(tempData->value[0]));
                Route *lastRoute = getFromBack(theDoc->routes);
                Waypoint *lastRoutePte = getFromBack(lastRoute->waypoints);

                strcpy(tempData->name, (char*)cur_node->name);
                strcpy(tempData->value, (char*)cur_node->children->content);

                insertBack(lastRoutePte->otherData, tempData);

            } else if ((strcmp((char*)cur_node->name, "desc") == 0) && (strcmp((char*)cur_node->parent->name, "rtept") == 0)){
                // if it is a valid named node for an object of GPXData type  and the parent is rtept, then I know it is a valid node
                GPXData *tempData = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(tempData->value[0]));
                Route *lastRoute = getFromBack(theDoc->routes);
                Waypoint *lastRoutePte = getFromBack(lastRoute->waypoints);

                strcpy(tempData->name, (char*)cur_node->name);
                strcpy(tempData->value, (char*)cur_node->children->content);

                insertBack(lastRoutePte->otherData, lastRoutePte);

            } else if ((strcmp((char*)cur_node->name, "src") == 0) && (strcmp((char*)cur_node->parent->name, "rtept") == 0)){
                // if it is a valid named node for an object of GPXData type  and the parent is rtept, then I know it is a valid node
                GPXData *tempData = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(tempData->value[0]));
                Route *lastRoute = getFromBack(theDoc->routes);
                Waypoint *lastRoutePte = getFromBack(lastRoute->waypoints);

                strcpy(tempData->name, (char*)cur_node->name);
                strcpy(tempData->value, (char*)cur_node->children->content);

                insertBack(lastRoutePte->otherData, lastRoutePte);

            }  else if ((strcmp((char*)cur_node->name, "cmt") == 0) && (strcmp((char*)cur_node->parent->name, "rtept") == 0)){
                // if it is a valid named node for an object of GPXData type  and the parent is rtept, then I know it is a valid node
                GPXData *tempData = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(tempData->value[0]));
                Route *lastRoute = getFromBack(theDoc->routes);
                Waypoint *lastRoutePte = getFromBack(lastRoute->waypoints);

                strcpy(tempData->name, (char*)cur_node->name);
                strcpy(tempData->value, (char*)cur_node->children->content);

                insertBack(lastRoutePte->otherData, lastRoutePte);

            } else if ((strcmp((char*)cur_node->name, "name") == 0) && (strcmp((char*)cur_node->parent->name, "trk") == 0)){
                // if the current node is the name node, and the parent node is trk, then I know that it is the track name
                Track *tempTrack = (Track*)malloc(sizeof(Track));
                tempTrack->name = (char*)malloc(sizeof(char) * 100);
                tempTrack->segments = initializeList(&trackSegmentToString, &deleteTrackSegment, &compareTrackSegments);
                tempTrack->otherData = initializeList(&gpxDataToString, &deleteGPXData, &compareGpxData);


                // the child of the name XML node is a text node
                // therefore, put the content of the child text node as the track name
                strcpy(tempTrack->name, (char*)cur_node->children->content);
             //   printf("Track name: %s", tempTrack->name);

                insertBack(theDoc->tracks, tempTrack);
                // FREE TRACK

            }  else if ((strcmp((char*)cur_node->name, "type") == 0) && (strcmp((char*)cur_node->parent->name, "rtept") == 0)){
                // if it is a valid named node for an object of GPXData type  and the parent is rtept, then I know it is a valid node
                GPXData *tempData = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(tempData->value[0]));
                Route *lastRoute = getFromBack(theDoc->routes);
                Waypoint *lastRoutePte = getFromBack(lastRoute->waypoints);

                strcpy(tempData->name, (char*)cur_node->name);
                strcpy(tempData->value, (char*)cur_node->children->content);

                insertBack(lastRoutePte->otherData, lastRoutePte);

            } else if ((strcmp((char*)cur_node->name, "cmt") == 0) && (strcmp((char*)cur_node->parent->name, "trk") == 0)){
                // if the current node is a piece of other data, and the parent node is trk, then I know that it is a valid node
                // create a GPXData object
                GPXData *otherInfo = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(otherInfo->value[0]));

                // add the name of the node to the otherData object's name variable
                strcpy(otherInfo->name, (char*)cur_node->name);
                // add the node child content to the otherData object's value[] variable
                // add the GPXData object to the back of the last track's otherData list
                strcpy(otherInfo->value, (char*)cur_node->children->content);

                // get the most recent
                Track *lastTrk = getFromBack(theDoc->tracks);
                // add to the most recent
                insertBack(lastTrk->otherData, otherInfo);

            }  else if ((strcmp((char*)cur_node->name, "desc") == 0) && (strcmp((char*)cur_node->parent->name, "trk") == 0)){
                // if the current node is a piece of other data, and the parent node is trk, then I know that it is a valid node
                // create a GPXData object
                GPXData *tempOtherData = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(tempOtherData->value[0]));

                // add the name of the node to the otherData object's name variable
                strcpy(tempOtherData->name, (char*)cur_node->name);
                // add the node child content to the otherData object's value[] variable
                // add the GPXData object to the back of the last track's otherData list
                strcpy(tempOtherData->value, (char*)cur_node->children->content);

                // get the most recent
                Track *lastTrk = getFromBack(theDoc->tracks);
                // add to the most recent
                insertBack(lastTrk->otherData, tempOtherData);

            }  else if ((strcmp((char*)cur_node->name, "src") == 0) && (strcmp((char*)cur_node->parent->name, "trk") == 0)){
                // if the current node is a piece of other data, and the parent node is trk, then I know that it is a valid node
                // create a GPXData object
                GPXData *tempOtherData = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(tempOtherData->value[0]));

                // add the name of the node to the otherData object's name variable
                strcpy(tempOtherData->name, (char*)cur_node->name);
                // add the node child content to the otherData object's value[] variable
                // add the GPXData object to the back of the last track's otherData list
                strcpy(tempOtherData->value, (char*)cur_node->children->content);

                // get the most recent
                Track *lastTrk = getFromBack(theDoc->tracks);
                // add to the most recent
                insertBack(lastTrk->otherData, tempOtherData);

            }  else if ((strcmp((char*)cur_node->name, "link") == 0) && (strcmp((char*)cur_node->parent->name, "trk") == 0)){
                // if the current node is a piece of other data, and the parent node is trk, then I know that it is a valid node
                // create a GPXData object
                GPXData *tempOtherData = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(tempOtherData->value[0]));

                // add the name of the node to the otherData object's name variable
                strcpy(tempOtherData->name, (char*)cur_node->name);
                // add the node child content to the otherData object's value[] variable
                // add the GPXData object to the back of the last track's otherData list
                strcpy(tempOtherData->value, (char*)cur_node->children->content);

                // get the most recent
                Track *lastTrk = getFromBack(theDoc->tracks);
                // add to the most recent
                insertBack(lastTrk->otherData, tempOtherData);

            }  else if ((strcmp((char*)cur_node->name, "number") == 0) && (strcmp((char*)cur_node->parent->name, "trk") == 0)){
                // if the current node is a piece of other data, and the parent node is trk, then I know that it is a valid node
                // create a GPXData object
                GPXData *tempOtherData = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(tempOtherData->value[0]));

                // add the name of the node to the otherData object's name variable
                strcpy(tempOtherData->name, (char*)cur_node->name);
                // add the node child content to the otherData object's value[] variable
                // add the GPXData object to the back of the last track's otherData list
                strcpy(tempOtherData->value, (char*)cur_node->children->content);

                // get the most recent
                Track *lastTrk = getFromBack(theDoc->tracks);
                // add to the most recent
                insertBack(lastTrk->otherData, tempOtherData);

            }  else if ((strcmp((char*)cur_node->name, "type") == 0) && (strcmp((char*)cur_node->parent->name, "trk") == 0)){
                // if the current node is a piece of other data, and the parent node is trk, then I know that it is a valid node
                // create a GPXData object
                GPXData *tempOtherData = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(tempOtherData->value[0]));

                // add the name of the node to the otherData object's name variable
                strcpy(tempOtherData->name, (char*)cur_node->name);
                // add the node child content to the otherData object's value[] variable
                // add the GPXData object to the back of the last track's otherData list
                strcpy(tempOtherData->value, (char*)cur_node->children->content);

                // get the most recent
                Track *lastTrk = getFromBack(theDoc->tracks);
                // add to the most recent
                insertBack(lastTrk->otherData, tempOtherData);

            }  else if ((strcmp((char*)cur_node->name, "trkseg") == 0) && (strcmp((char*)cur_node->parent->name, "trk") == 0)){
                // if the current node is trkseg and the parent is trk, then I know for sure it is the trkseg node
                // create a track segment object
                TrackSegment *tempTrkSegment = (TrackSegment*)malloc(sizeof(TrackSegment));
                // get the latest track as this will be the one being updated
                Track *trackBeingUpdated = getFromBack(theDoc->tracks);
                tempTrkSegment->waypoints = initializeList(&waypointToString, &deleteWaypoint, &compareWaypoints);
                // inserting the new track segment object to the track at the back of the GPXdoc track list
                // the track object then has the tempTrkSegment object added as a node in it's "segments" list
                insertBack(trackBeingUpdated->segments, tempTrkSegment);

                // iterate through each trkpoint and create a waypoint struct for each one

                // add the track segment object to the GPXDoc struct's tracks segments list

                // add them to the trkseg list
            } else if ((strcmp((char*)cur_node->name, "trkpt") == 0) && (strcmp((char*)cur_node->parent->name, "trkseg") == 0)){
                // if it is a track point and the parent is a track segment then I know it is a valid trackpoint for the most recent track segment
                // store the longitude and latitude values into a temporary waypoint object
                // add the waypoint object containing the longitude, latitude, name and other data into the last track segment (trkseg)
                // add to the back of the trkseg object on each iteration
                Waypoint *tempWpt = (Waypoint*)malloc(sizeof(Waypoint));
                tempWpt->name = (char*) malloc(sizeof(char) * 10);
                tempWpt->longitude = 0.0;
                tempWpt->latitude = 0.0;
                // would contain the ele data
                tempWpt->otherData = initializeList(&gpxDataToString, &deleteGPXData, &compareGpxData);

                for (tempAttr = cur_node->properties; tempAttr != NULL; tempAttr = tempAttr->next)
                {
                    xmlNode *theValue = tempAttr->children;
                    char *attributeName = (char *)tempAttr->name;
                    char *theCont = (char *)(theValue->content);

                    // if the property name indicates it is referring to the latitude
                    if(strcmp(attributeName, "lat") == 0){
                        // converting string value to double and then adding it to the waypoints latitude
                        strcpy(tempString, theCont);
                        tempWpt->latitude = strtod(tempString, &eptr);
                     //   printf("testing waypoint latitude: %f\n", tempWpt->latitude);
                      //  free(tempString);
                    //    else if the property name indicates it is referring to the longitude
                    } else if (strcmp(attributeName, "lon") == 0){
                        // converting string value to double and then adding it to the waypoints longitude
                        // convert string to double and then pass in to the GPX doc
                        strcpy(tempString, theCont);
                        tempWpt->longitude = strtod(tempString, &eptr);
                     //    printf("testing waypoint longitude: %f\n", tempWpt->longitude);
                   //      free(tempString);
                    }
                }
                Track *tempTrk = getFromBack(theDoc->tracks);
             //   printf("Track name: %s\n", tempTrk->name);
                TrackSegment *tempSgmnt = getFromBack(tempTrk->segments);
              //  tempSgmnt->waypoints = (List*)realloc(tempSgmnt->waypoints, sizeof(Node*) + 1);
                insertBack(tempSgmnt->waypoints,tempWpt);
            } else if((strcmp((char*)cur_node->name, "ele") == 0) && (strcmp((char*)cur_node->parent->name, "trkpt") == 0)){
             //   printf("testing ele node content: %s\n", (char*)cur_node->children->content);
                // if the current node is "ele" and the parennt is "trkpt", then I know it is a valid piece of additional information for the track point node
                // create GPX data object
                GPXData *tempAdditionalInfo = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(tempAdditionalInfo->value[0]));

                strcpy(tempAdditionalInfo->name, (char*)cur_node->name);
                strcpy(tempAdditionalInfo->value, (char*)cur_node->children->content);
                // add node name, in this case "ele" to the GPXdata name variable
                // add the node string to the GPXdata value[] variable
                // realloc memory in the otherData list in the very last trkpt
                Track *theTrk = getFromBack(theDoc->tracks);
                TrackSegment *tempTrkSgmnt = getFromBack(theTrk->segments);
                Waypoint *lastWpt = getFromBack(tempTrkSgmnt->waypoints);
             //   lastWpt->otherData = (List*)realloc(lastWpt->otherData, sizeof(Node*) * 1);
                insertBack(lastWpt->otherData,tempAdditionalInfo);
                // add the GPXdata to the last trkpt node in the GPX doc

            } else if ((strcmp((char*)cur_node->name, "time") == 0) && (strcmp((char*)cur_node->parent->name, "trkpt") == 0)){
                // if the current node is "time" and the parent node is "trkpt", then I know it is a valid node under "trkpt"
                // create GPXData object
                GPXData *tempTimeInfo = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(tempTimeInfo->value[0]));
                strcpy(tempTimeInfo->name, (char*)cur_node->name);
                strcpy(tempTimeInfo->value, (char*)cur_node->children->content);
                // add the name, in this case "time", to the GPXData name variable
                // add the string form of the time into the GPXData value[] variable
                Track *lastTrk = getFromBack(theDoc->tracks);
                TrackSegment *lastTrkSgmnt = getFromBack(lastTrk->segments);
                Waypoint *lastWaypoint = getFromBack(lastTrkSgmnt->waypoints);
                // add the GPXData to the back of the last trkpt node's otherData list in the GPX doc
                insertBack(lastWaypoint->otherData, tempTimeInfo);
             //   printf("Found a time element\n");

            } else if ((strcmp((char*)cur_node->name, "magvar") == 0) && (strcmp((char*)cur_node->parent->name, "trkpt") == 0)){
                // if the current node is "magvar" and the parent node is "trkpt", then I know it is a valid node under "trkpt"
                // create GPXData object
                GPXData *tempMagvarInfo = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(tempMagvarInfo->value[0]));
                strcpy(tempMagvarInfo->name, (char*)cur_node->name);
                strcpy(tempMagvarInfo->value, (char*)cur_node->children->content);
                // add the name, in this case "Magvar", to the GPXData name variable
                // add the degrees in string form into the GPXData value[] variable
                Track *lastTrk = getFromBack(theDoc->tracks);
                TrackSegment *lastTrkSgmnt = getFromBack(lastTrk->segments);
                Waypoint *lastWaypoint = getFromBack(lastTrkSgmnt->waypoints);
                // add the GPXData to the back of the last trkpt node's otherData list in the GPX doc
                insertBack(lastWaypoint->otherData, tempMagvarInfo);
             //   printf("Found a Magvar element\n");

            } else if ((strcmp((char*)cur_node->name, "geoidheight") == 0) && (strcmp((char*)cur_node->parent->name, "trkpt") == 0)){
                // if the current node is "geoidheight" and the parent node is "trkpt", then I know it is a valid node under "trkpt"
                // create GPXData object
                GPXData *tempGeoidHeight = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(tempGeoidHeight->value[0]));
                strcpy(tempGeoidHeight->name, (char*)cur_node->name);
                strcpy(tempGeoidHeight->value, (char*)cur_node->children->content);
                // add the name, in this case "time", to the GPXData name variable
                // add the string form of the time into the GPXData value[] variable
                Track *lastTrk = getFromBack(theDoc->tracks);
                TrackSegment *lastTrkSgmnt = getFromBack(lastTrk->segments);
                Waypoint *lastWaypoint = getFromBack(lastTrkSgmnt->waypoints);
                // add the GPXData to the back of the last trkpt node's otherData list in the GPX doc
                insertBack(lastWaypoint->otherData, tempGeoidHeight);
            //    printf("Found a Geoid element\n");

            } else if ((strcmp((char*)cur_node->name, "cmt") == 0) && (strcmp((char*)cur_node->parent->name, "trkpt") == 0)){
                // if the current node is "cmt" and the parent node is "trkpt", then I know it is a valid node under "trkpt"
                // create GPXData object
                GPXData *tempCmt = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(tempCmt->value[0]));
                strcpy(tempCmt->name, (char*)cur_node->name);
                strcpy(tempCmt->value, (char*)cur_node->children->content);
                // add the name, in this case "cmt", to the GPXData name variable
                // add the string form of the cmt into the GPXData value[] variable
                Track *lastTrk = getFromBack(theDoc->tracks);
                TrackSegment *lastTrkSgmnt = getFromBack(lastTrk->segments);
                Waypoint *lastWaypoint = getFromBack(lastTrkSgmnt->waypoints);
                // add the GPXData to the back of the last trkpt node's otherData list in the GPX doc
                insertBack(lastWaypoint->otherData, tempCmt);
             //   printf("Found a cmt element\n");

            } else if ((strcmp((char*)cur_node->name, "name") == 0) && (strcmp((char*)cur_node->parent->name, "trkpt") == 0)){
                // if the current node is "name" and the parent node is "trkpt", then I know it is a valid node under "trkpt"
                // create GPXData object
                GPXData *tempWptName = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(tempWptName->value[0]));
                strcpy(tempWptName->name, (char*)cur_node->name);
                strcpy(tempWptName->value, (char*)cur_node->children->content);
                // add the name, in this case "name", to the GPXData name variable
                // add the string form of the name into the GPXData value[] variable
                Track *lastTrk = getFromBack(theDoc->tracks);
                TrackSegment *lastTrkSgmnt = getFromBack(lastTrk->segments);
                Waypoint *lastWaypoint = getFromBack(lastTrkSgmnt->waypoints);
                // add the GPXData to the back of the last trkpt node's otherData list in the GPX doc
                insertBack(lastWaypoint->otherData, tempWptName);
            //    printf("Found a waypoint name element\n");

            } else if ((strcmp((char*)cur_node->name, "desc") == 0) && (strcmp((char*)cur_node->parent->name, "trkpt") == 0)){
                // if the current node is "desc" and the parent node is "trkpt", then I know it is a valid node under "trkpt"
                // create GPXData object
                GPXData *tempDesc = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(tempDesc->value[0]));
                strcpy(tempDesc->name, (char*)cur_node->name);
                strcpy(tempDesc->value, (char*)cur_node->children->content);
                // add the name, in this case "desc", to the GPXData name variable
                // add the string form of the description into the GPXData value[] variable
                Track *lastTrk = getFromBack(theDoc->tracks);
                TrackSegment *lastTrkSgmnt = getFromBack(lastTrk->segments);
                Waypoint *lastWaypoint = getFromBack(lastTrkSgmnt->waypoints);
                // add the GPXData to the back of the last trkpt node's otherData list in the GPX doc
                insertBack(lastWaypoint->otherData, tempDesc);
             //   printf("Found a description element\n");

            } else if ((strcmp((char*)cur_node->name, "src") == 0) && (strcmp((char*)cur_node->parent->name, "trkpt") == 0)){
                // if the current node is "src" and the parent node is "trkpt", then I know it is a valid node under "trkpt"
                // create GPXData object
                GPXData *tempSrc = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(tempSrc->value[0]));
                strcpy(tempSrc->name, (char*)cur_node->name);
                strcpy(tempSrc->value, (char*)cur_node->children->content);
                // add the name, in this case "src", to the GPXData name variable
                // add the string form of the SRC into the GPXData value[] variable
                Track *lastTrk = getFromBack(theDoc->tracks);
                TrackSegment *lastTrkSgmnt = getFromBack(lastTrk->segments);
                Waypoint *lastWaypoint = getFromBack(lastTrkSgmnt->waypoints);
                // add the GPXData to the back of the last trkpt node's otherData list in the GPX doc
                insertBack(lastWaypoint->otherData, tempSrc);
             //   printf("Found an src element\n");

            } else if ((strcmp((char*)cur_node->name, "link") == 0) && (strcmp((char*)cur_node->parent->name, "trkpt") == 0)){
                // if the current node is "link" and the parent node is "trkpt", then I know it is a valid node under "trkpt"
                // create GPXData object
                GPXData *tempLink = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(tempLink->value[0]));
                strcpy(tempLink->name, (char*)cur_node->name);
                strcpy(tempLink->value, (char*)cur_node->children->content);
                // add the name, in this case "link", to the GPXData name variable
                // add the string form of the link into the GPXData value[] variable
                Track *lastTrk = getFromBack(theDoc->tracks);
                TrackSegment *lastTrkSgmnt = getFromBack(lastTrk->segments);
                Waypoint *lastWaypoint = getFromBack(lastTrkSgmnt->waypoints);
                // add the GPXData to the back of the last trkpt node's otherData list in the GPX doc
                insertBack(lastWaypoint->otherData, tempLink);
             //   printf("Found a link element\n");

            } else if ((strcmp((char*)cur_node->name, "sym") == 0) && (strcmp((char*)cur_node->parent->name, "trkpt") == 0)){
                // if the current node is "sym" and the parent node is "trkpt", then I know it is a valid node under "trkpt"
                // create GPXData object
                GPXData *tempSym = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(tempSym->value[0]));
                strcpy(tempSym->name, (char*)cur_node->name);
                strcpy(tempSym->value, (char*)cur_node->children->content);
                // add the name, in this case "sym", to the GPXData name variable
                // add the string form of the sym into the GPXData value[] variable
                Track *lastTrk = getFromBack(theDoc->tracks);
                TrackSegment *lastTrkSgmnt = getFromBack(lastTrk->segments);
                Waypoint *lastWaypoint = getFromBack(lastTrkSgmnt->waypoints);
                // add the GPXData to the back of the last trkpt node's otherData list in the GPX doc
                insertBack(lastWaypoint->otherData, tempSym);
             //   printf("Found a sym element\n");

            } else if ((strcmp((char*)cur_node->name, "type") == 0) && (strcmp((char*)cur_node->parent->name, "trkpt") == 0)){
                // if the current node is "type" and the parent node is "trkpt", then I know it is a valid node under "trkpt"
                // create GPXData object
                GPXData *tempType = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(tempType->value[0]));
                strcpy(tempType->name, (char*)cur_node->name);
                strcpy(tempType->value, (char*)cur_node->children->content);
                // add the name, in this case "type", to the GPXData name variable
                // add the string form of the type into the GPXData value[] variable
                Track *lastTrk = getFromBack(theDoc->tracks);
                TrackSegment *lastTrkSgmnt = getFromBack(lastTrk->segments);
                Waypoint *lastWaypoint = getFromBack(lastTrkSgmnt->waypoints);
                // add the GPXData to the back of the last trkpt node's otherData list in the GPX doc
                insertBack(lastWaypoint->otherData, tempType);
             //   printf("Found a type element\n");

            } else if ((strcmp((char*)cur_node->name, "fix") == 0) && (strcmp((char*)cur_node->parent->name, "trkpt") == 0)){
                // if the current node is "fix" and the parent node is "trkpt", then I know it is a valid node under "trkpt"
                // create GPXData object
                GPXData *tempFix = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(tempFix->value[0]));
                strcpy(tempFix->name, (char*)cur_node->name);
                strcpy(tempFix->value, (char*)cur_node->children->content);
                // add the name, in this case "fix", to the GPXData name variable
                // add the string form of the fix into the GPXData value[] variable
                Track *lastTrk = getFromBack(theDoc->tracks);
                TrackSegment *lastTrkSgmnt = getFromBack(lastTrk->segments);
                Waypoint *lastWaypoint = getFromBack(lastTrkSgmnt->waypoints);
                // add the GPXData to the back of the last trkpt node's otherData list in the GPX doc
                insertBack(lastWaypoint->otherData, tempFix);
             //   printf("Found a fix element\n");

            } else if ((strcmp((char*)cur_node->name, "sat") == 0) && (strcmp((char*)cur_node->parent->name, "trkpt") == 0)){
                // if the current node is "sat" and the parent node is "trkpt", then I know it is a valid node under "trkpt"
                // create GPXData object
                GPXData *tempSat = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(tempSat->value[0]));
                strcpy(tempSat->name, (char*)cur_node->name);
                strcpy(tempSat->value, (char*)cur_node->children->content);
                // add the name, in this case "sat", to the GPXData name variable
                // add the string form of the sat into the GPXData value[] variable
                Track *lastTrk = getFromBack(theDoc->tracks);
                TrackSegment *lastTrkSgmnt = getFromBack(lastTrk->segments);
                Waypoint *lastWaypoint = getFromBack(lastTrkSgmnt->waypoints);
                // add the GPXData to the back of the last trkpt node's otherData list in the GPX doc
                insertBack(lastWaypoint->otherData, tempSat);
             //   printf("Found a sat element\n");

            } else if ((strcmp((char*)cur_node->name, "hdop") == 0) && (strcmp((char*)cur_node->parent->name, "trkpt") == 0)){
                // if the current node is "hdop" and the parent node is "trkpt", then I know it is a valid node under "trkpt"
                // create GPXData object
                GPXData *tempHdop = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(tempHdop->value[0]));
                strcpy(tempHdop->name, (char*)cur_node->name);
                strcpy(tempHdop->value, (char*)cur_node->children->content);
                // add the name, in this case "hdop", to the GPXData name variable
                // add the string form of the hdop into the GPXData value[] variable
                Track *lastTrk = getFromBack(theDoc->tracks);
                TrackSegment *lastTrkSgmnt = getFromBack(lastTrk->segments);
                Waypoint *lastWaypoint = getFromBack(lastTrkSgmnt->waypoints);
                // add the GPXData to the back of the last trkpt node's otherData list in the GPX doc
                insertBack(lastWaypoint->otherData, tempHdop);
             //   printf("Found a hdop element\n");

            } else if ((strcmp((char*)cur_node->name, "vdop") == 0) && (strcmp((char*)cur_node->parent->name, "trkpt") == 0)){
                // if the current node is "vdop" and the parent node is "trkpt", then I know it is a valid node under "trkpt"
                // create GPXData object
                GPXData *tempVdop = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(tempVdop->value[0]));
                strcpy(tempVdop->name, (char*)cur_node->name);
                strcpy(tempVdop->value, (char*)cur_node->children->content);
                // add the name, in this case "vdop", to the GPXData name variable
                // add the string form of the vdop into the GPXData value[] variable
                Track *lastTrk = getFromBack(theDoc->tracks);
                TrackSegment *lastTrkSgmnt = getFromBack(lastTrk->segments);
                Waypoint *lastWaypoint = getFromBack(lastTrkSgmnt->waypoints);
                // add the GPXData to the back of the last trkpt node's otherData list in the GPX doc
                insertBack(lastWaypoint->otherData, tempVdop);
               // printf("Found a vdop element\n");

            } else if ((strcmp((char*)cur_node->name, "pdop") == 0) && (strcmp((char*)cur_node->parent->name, "trkpt") == 0)){
                // if the current node is "pdop" and the parent node is "trkpt", then I know it is a valid node under "trkpt"
                // create GPXData object
                GPXData *tempPdop = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(tempPdop->value[0]));
                strcpy(tempPdop->name, (char*)cur_node->name);
                strcpy(tempPdop->value, (char*)cur_node->children->content);
                // add the name, in this case "pdop", to the GPXData name variable
                // add the string form of the pdop into the GPXData value[] variable
                Track *lastTrk = getFromBack(theDoc->tracks);
                TrackSegment *lastTrkSgmnt = getFromBack(lastTrk->segments);
                Waypoint *lastWaypoint = getFromBack(lastTrkSgmnt->waypoints);
                // add the GPXData to the back of the last trkpt node's otherData list in the GPX doc
                insertBack(lastWaypoint->otherData, tempPdop);
              //  printf("Found a pdop element\n");

            } else if ((strcmp((char*)cur_node->name, "ageofdgpsdata") == 0) && (strcmp((char*)cur_node->parent->name, "trkpt") == 0)){
                // if the current node is "ageofdgpsdata" and the parent node is "trkpt", then I know it is a valid node under "trkpt"
                // create GPXData object
                GPXData *tempDgpsData = (GPXData*)malloc(sizeof(GPXData) + 100 * sizeof(tempDgpsData->value[0]));
                strcpy(tempDgpsData->name, (char*)cur_node->name);
                strcpy(tempDgpsData->value, (char*)cur_node->children->content);
                // add the name, in this case "ageofdgpsdata", to the GPXData name variable
                // add the string form of the ageofdgpsdata into the GPXData value[] variable
                Track *lastTrk = getFromBack(theDoc->tracks);
                TrackSegment *lastTrkSgmnt = getFromBack(lastTrk->segments);
                Waypoint *lastWaypoint = getFromBack(lastTrkSgmnt->waypoints);
                // add the GPXData to the back of the last trkpt node's otherData list in the GPX doc
                insertBack(lastWaypoint->otherData, tempDgpsData);
               // printf("Found a ageofdgpsdata element\n");

            }
        }

        // Uncomment the code below if you want to see the content of every node.

         if (cur_node->content != NULL ){
          //   printf("  content: %s\n", cur_node->content);
         }

        // Iterate through every attribute of the current node
      //  xmlAttr *attr;
       // for (attr = cur_node->properties; attr != NULL; attr = attr->next)
       // {
         //   xmlNode *value = attr->children;
           // char *attrName = (char *)attr->name;
          //  char *cont = (char *)(value->content);
          //  printf("\tattribute name: %s, attribute value = %s\n", attrName, cont);
        //}

        //add frees
        //deleteGPXdoc(tempDoc);

        free(tempString);
        print_element_names(cur_node->children, theDoc);
    }


}


// HELPER FUNCTION TO CONVERT GPX TO XML
xmlDoc* gpxToXML(GPXdoc* theDoc){

 //   xmlDoc* returnDoc = NULL;
    xmlDocPtr doc = NULL; /* document pointer */
    // node pointers below
    xmlNodePtr root_node = NULL;
  //  xmlNodePtr node = NULL;
    xmlNodePtr trackNode = NULL;
    //xmlNodePtr node1 = NULL;
    ListIterator attrList;
    ListIterator *theList = NULL;
    xmlNs* nameSpace = NULL;

   // xmlAttr tempAttr;


    LIBXML_TEST_VERSION;

     /*
     * Creates a new document, a node and set it as a root node
     */
    doc = xmlNewDoc(BAD_CAST "1.0");
    root_node = xmlNewNode(NULL, BAD_CAST "gpx");

   // printf("NAMESPACE: %s\n", theDoc->namespace);
    nameSpace = xmlNewNs(root_node, BAD_CAST theDoc->namespace, NULL);
    xmlSetNs(root_node, nameSpace);

    // if the GPX doc has a namespace
   // if(theDoc->namespace != NULL){
    //    xmlNewProp(root_node, BAD_CAST "xmlns", BAD_CAST theDoc->namespace);
    //}

    // if the GPX doc has a version value in string form
    if(theDoc->version >= 0.0){
        // convert the version from double to string
        // pass the converted double to the xmlNewProp function as a string variable
        char tempVersion[100];
        snprintf(tempVersion, 50, "%.1f", theDoc->version);
        xmlNewProp(root_node, BAD_CAST "version", BAD_CAST tempVersion);
    }

    // if the GPX doc has the string form of the creator
    if(theDoc->creator != NULL){
        xmlNewProp(root_node, BAD_CAST "creator", BAD_CAST theDoc->creator);
    }

    xmlDocSetRootElement(doc, root_node);

    /*
     * Creates a DTD declaration. Isn't mandatory.
     */
    xmlCreateIntSubset(doc, BAD_CAST "root", NULL, BAD_CAST "tree2.dtd");


    // must iterate through TRACK, ROUTE, and WAYPOINT lists
    // these are all xmlNodes
    // all content in the objects are considered xmlAttr
    // other data is considered node content

    /*
     * xmlNewChild() creates a new node, which is "attached" as child node
     * of root_node node.
     */
    //xmlNodePtr xmlGPX = xmlNewChild(root_node, NULL, BAD_CAST "gpx",
          //      BAD_CAST theDoc->namespace);


    // ITERATING THROUGH WAYPOINTS BELOW

    if(theDoc->waypoints != NULL){
        Waypoint *tempWaypoint = NULL;
        attrList = createIterator(theDoc->waypoints);
        theList = &attrList;

        tempWaypoint = (Waypoint*) nextElement(theList);

        for(; tempWaypoint != NULL; tempWaypoint = (Waypoint*) nextElement(theList)){
            // iterating through all objects in the waypoint list

            if(tempWaypoint->name != NULL){
                // if there is a waypoint name
                char tempWptName[200];
                strcpy(tempWptName, tempWaypoint->name);
                xmlNodePtr wptNode = xmlNewChild(root_node, NULL, BAD_CAST "wpt", NULL);

                xmlNewChild(wptNode, NULL, BAD_CAST "name", BAD_CAST tempWptName);

                if(tempWaypoint->latitude != 0.0){
                    char tempLat[200];

                    snprintf(tempLat, 300, "%f",tempWaypoint->latitude);
                    // adding the longitude as an xml attribute
                    xmlNewProp(wptNode, BAD_CAST "lat", BAD_CAST tempLat);
                }

                if(tempWaypoint->longitude != 0.0){
                    char tempLon[200];
                    snprintf(tempLon, 300, "%f",tempWaypoint->longitude);
                    // adding the longitude as an xml attribute
                    xmlNewProp(wptNode, BAD_CAST "lon", BAD_CAST tempLon);
                }



                if(tempWaypoint->otherData != NULL){
                 // ADD CODE HERE TO CREATE XMLNODES FOR WAYPOINT OTHER DATA
                    GPXData *tempOtherData = NULL;
                    List *otherData = tempWaypoint->otherData;
                    ListIterator otherIter;
                    ListIterator *otherIterPtr = NULL;

                    otherIter = createIterator(otherData);
                    otherIterPtr = &otherIter;

                    tempOtherData = (GPXData*) nextElement(otherIterPtr);

                    for(; tempOtherData != NULL; tempOtherData = (GPXData*)nextElement(otherIterPtr)){
                        if((tempOtherData->name != NULL) && (tempOtherData->value != NULL)){
                            // create an xmlNode for each otherData node found in the current track point
                            xmlNewChild(wptNode, NULL, BAD_CAST tempOtherData->name, BAD_CAST tempOtherData->value);
                        }
                    }
                }


            } else {
                // if there is no waypoint name
                xmlNodePtr wptNode = xmlNewChild(root_node, NULL, BAD_CAST "wpt", NULL);

                if(tempWaypoint->latitude != 0.0){
                    char tempLat[200];
                    snprintf(tempLat, 300, "%f",tempWaypoint->latitude);
                    // adding the longitude as an xml attribute
                    xmlNewProp(wptNode, BAD_CAST "lat", BAD_CAST tempLat);
                }

                if(tempWaypoint->longitude != 0.0){
                    char tempLon[200];
                    snprintf(tempLon, 300, "%f",tempWaypoint->longitude);
                    // adding the longitude as an xml attribute
                    xmlNewProp(wptNode, BAD_CAST "lon", BAD_CAST tempLon);
                }



                if(tempWaypoint->otherData != NULL){
                // ADD CODE HERE TO CREATE XMLNODES FOR WAYPOINT OTHER DATA
                GPXData *tempOtherData = NULL;
                List *otherData = tempWaypoint->otherData;
                ListIterator otherIter;
                ListIterator *otherIterPtr = NULL;

                otherIter = createIterator(otherData);
                otherIterPtr = &otherIter;

                tempOtherData = (GPXData*) nextElement(otherIterPtr);

                for(; tempOtherData != NULL; tempOtherData = (GPXData*)nextElement(otherIterPtr)){
                    if((tempOtherData->name != NULL) && (tempOtherData->value != NULL)){
                        // create an xmlNode for each otherData node found in the current track point
                        xmlNewChild(wptNode, NULL, BAD_CAST tempOtherData->name, BAD_CAST tempOtherData->value);
                    }
                }
            }
        }



        }

    }

    // ITERATING THROUGH THE ROUTES LIST BELOW
    if(theDoc->routes != NULL){
        Route *tempRte = NULL;
        attrList = createIterator(theDoc->routes);
        theList = &attrList;

        tempRte = (Route*) nextElement(theList);

        for(; tempRte != NULL; tempRte = (Route*) nextElement(theList)){
            // loop to iterate through the route list
            // route has an other data list, and a route point list
            // route can also have a name

            if(tempRte->name != NULL){
                char rteName[200];
                strcpy(rteName, tempRte->name);
                xmlNodePtr routeNode = xmlNewChild(root_node, NULL, BAD_CAST "rte", NULL);

                xmlNewChild(routeNode, NULL, BAD_CAST "name", BAD_CAST rteName);

                    if(tempRte->otherData != NULL){
                        // ADD CODE HERE TO CREATE XMLNODES FOR WAYPOINT OTHER DATA
                    GPXData *tempOtherData = NULL;
                    List *otherData = tempRte->otherData;
                    ListIterator otherIter;
                    ListIterator *otherIterPtr = NULL;

                    otherIter = createIterator(otherData);
                    otherIterPtr = &otherIter;

                    tempOtherData = (GPXData*) nextElement(otherIterPtr);

                    for(; tempOtherData != NULL; tempOtherData = (GPXData*)nextElement(otherIterPtr)){
                        if((tempOtherData->name != NULL) && (tempOtherData->value != NULL)){
                            // create an xmlNode for each otherData node found in the current route node
                            xmlNewChild(routeNode, NULL, BAD_CAST tempOtherData->name, BAD_CAST tempOtherData->value);
                        }
                    }
                }

                if(tempRte->waypoints != NULL){
                    // iterating through the route points
                    // route points are of type waypoint
                    Waypoint *currentRoutePoint;
                    List *routePoints = tempRte->waypoints;
                    ListIterator routePtIter;
                    ListIterator *routePtIterPtr = NULL;

                    routePtIter = createIterator(routePoints);
                    routePtIterPtr = &routePtIter;

                    currentRoutePoint = (Waypoint*) nextElement(routePtIterPtr);

                    for(; currentRoutePoint != NULL; currentRoutePoint = (Waypoint*) nextElement(routePtIterPtr)){
                        if(currentRoutePoint->name != NULL){

                            // create an xml node for a route point
                            xmlNodePtr xmlRtePt = NULL;

                          //  if(strcmp(currentRoutePoint->name, "") == 0){
                           //     printf("NO ROUTE NAME\n");
                            //    xmlRtePt = xmlNewChild(routeNode, NULL, BAD_CAST "rtept", BAD_CAST NULL);
                           // } else {
                              //  strcpy(tempPtName, tempTrkPt->name);
                                xmlRtePt = xmlNewChild(routeNode, NULL, BAD_CAST "rtept", NULL);
                           // }
                                if(currentRoutePoint->otherData != NULL){
                                // if the routePoint otherData list is not NULL
                                // ADD CODE HERE TO CREATE XMLNODES FOR WAYPOINT OTHER DATA
                                GPXData *tempOtherData = NULL;
                                List *otherData = currentRoutePoint->otherData;
                                ListIterator otherIter;
                                ListIterator *otherIterPtr = NULL;

                                otherIter = createIterator(otherData);
                                otherIterPtr = &otherIter;

                                tempOtherData = (GPXData*) nextElement(otherIterPtr);

                                for(; tempOtherData != NULL; tempOtherData = (GPXData*)nextElement(otherIterPtr)){
                                    if((tempOtherData->name != NULL) && (tempOtherData->value != NULL)){
                                        // create an xmlNode for each otherData node found in the current track point
                                        xmlNewChild(xmlRtePt, NULL, BAD_CAST tempOtherData->name, BAD_CAST tempOtherData->value);
                                    }
                                }

                            }


                            if(currentRoutePoint->latitude != 0.0){
                                char tempLat[200];
                                snprintf(tempLat, 300, "%f",currentRoutePoint->latitude);
                                // adding the latitude as an xml attribute
                                xmlNewProp(xmlRtePt, BAD_CAST "lat", BAD_CAST tempLat);
                            }

                             if(currentRoutePoint->longitude != 0.0){
                                char tempLon[200];
                                snprintf(tempLon, 300, "%f",currentRoutePoint->longitude);
                                // adding the longitude as an xml attribute
                                xmlNewProp(xmlRtePt, BAD_CAST "lon", BAD_CAST tempLon);
                            }

                       } else  {
                           xmlNodePtr xmlRtePt = xmlNewChild(routeNode, NULL, BAD_CAST "rtept", NULL);
                           if(currentRoutePoint->latitude != 0.0){
                                char tempLat[200];
                                snprintf(tempLat, 50, "%f",currentRoutePoint->latitude);
                                // adding the latitude as an xml attribute
                                xmlNewProp(xmlRtePt, BAD_CAST "lat", BAD_CAST tempLat);
                            }

                             if(currentRoutePoint->longitude != 0.0){
                                char tempLon[200];
                                snprintf(tempLon, 50, "%f",currentRoutePoint->longitude);
                                // adding the longitude as an xml attribute
                                xmlNewProp(xmlRtePt, BAD_CAST "lon", BAD_CAST tempLon);
                            }

                            if(currentRoutePoint->otherData != NULL){
                                // if the routePoint otherData list is not NULL
                                // ADD CODE HERE TO CREATE XMLNODES FOR WAYPOINT OTHER DATA
                                GPXData *tempOtherData = NULL;
                                List *otherData = currentRoutePoint->otherData;
                                ListIterator otherIter;
                                ListIterator *otherIterPtr = NULL;

                                otherIter = createIterator(otherData);
                                otherIterPtr = &otherIter;

                                tempOtherData = (GPXData*) nextElement(otherIterPtr);

                                for(; tempOtherData != NULL; tempOtherData = (GPXData*)nextElement(otherIterPtr)){
                                    if((tempOtherData->name != NULL) && (tempOtherData->value != NULL)){
                                        // create an xmlNode for each otherData node found in the current track point
                                        xmlNewChild(xmlRtePt, NULL, BAD_CAST tempOtherData->name, BAD_CAST tempOtherData->value);
                                    }
                                }

                            }
                       }


                    }


                }


            } else {
                // else if there is no route name
            }
        }
    }

    if(theDoc->tracks != NULL){
        Track *tempTrack = NULL;
        attrList = createIterator(theDoc->tracks);
        theList = &attrList;

        tempTrack = (Track*) nextElement(theList);

        for(; tempTrack != NULL; tempTrack = (Track*)nextElement(theList)){
         //   printf("at a track\n");
            // track node is created
            trackNode = xmlNewChild(root_node, NULL, BAD_CAST "trk", NULL);
            // create a track xmlNode and attach it as a child of the gpx root node

            if(tempTrack->name != NULL){
                char tempName[500]; // this variable holds the track name
                //xmlNodePtr trackName = NULL;
                strcpy(tempName, tempTrack->name);
           //     printf("TRACK NAME: %s\n", tempName);

                // track name xmlNode is added under the track node
                xmlNewChild(trackNode, NULL, BAD_CAST  "name", BAD_CAST tempName);
            }

            if(tempTrack->otherData != NULL){
                // if the routePoint otherData list is not NULL
                // ADD CODE HERE TO CREATE XMLNODES FOR WAYPOINT OTHER DATA
                GPXData *tempOtherData = NULL;
                List *otherData = tempTrack->otherData;
                ListIterator otherIter;
                ListIterator *otherIterPtr = NULL;

                otherIter = createIterator(otherData);
                otherIterPtr = &otherIter;

                tempOtherData = (GPXData*) nextElement(otherIterPtr);

                for(; tempOtherData != NULL; tempOtherData = (GPXData*)nextElement(otherIterPtr)){
                    if((tempOtherData->name != NULL) && (tempOtherData->value != NULL)){
                        // create an xmlNode for each otherData node found in the current track point
                        xmlNewChild(trackNode, NULL, BAD_CAST tempOtherData->name, BAD_CAST tempOtherData->value);
                    }
                }

            }
            // at a track
            // at each track, extract the track name
            // iterate through the segments list (of type track segment)
            // create a xmlNode for track segment
            // create an xmlNode for name
            // set the track name as the namea xmlNode->node content
            // iterate through the other data list

            if(tempTrack->segments != NULL){
                TrackSegment *tempSegment = NULL;
                List *segmentList = tempTrack->segments;
                ListIterator segmentIter;
                ListIterator *segmentIterator = NULL;

                segmentIter = createIterator(segmentList);
                segmentIterator = &segmentIter;

                tempSegment = (TrackSegment*)nextElement(segmentIterator);

                // iterate through each tracks, track segment list
                // each segment will have a list of trackpoints (of type waypoint)
                // each waypoint has an xmlattr of longitude and latitude

                for(; tempSegment != NULL; tempSegment = (TrackSegment*)nextElement(segmentIterator)){
                //    printf("reached a segment\n");
                    xmlNodePtr segmentNode = NULL;
                    // attaching the "trkSeg" xmlnode to the track node
                    segmentNode = xmlNewChild(trackNode, NULL, BAD_CAST "trkseg", NULL);
                    if(tempSegment->waypoints != NULL){
                        // iterate through each segments waypoints list
                        // list of track points

                            List *trkPts = tempSegment->waypoints;
                            Waypoint *tempTrkPt = NULL;
                            ListIterator trkIter;
                            ListIterator *trkIterPtr = NULL;

                            trkIter = createIterator(trkPts);
                            trkIterPtr = &trkIter;

                            tempTrkPt = (Waypoint*) nextElement(trkIterPtr);
                            for(; tempTrkPt != NULL; tempTrkPt = (Waypoint*)nextElement(trkIterPtr)){
                                // track point reached
                             //   char tempPtName[200];

                                if(tempTrkPt->name != NULL){
                                    xmlNodePtr tempTrkPtNode = NULL;
                                    //strcpy(tempPtName, tempTrkPt->name);
                                    // creating a track point xmlNode with a name
                                //    if(strcmp(tempTrkPt->name, "") == 0){
                              //          printf("NO NAME\n");
                                 //     tempTrkPtNode = xmlNewChild(segmentNode, NULL, BAD_CAST "trkPt", BAD_CAST tempTrkPt->name);
                                  //  } else {
                                     //   strcpy(tempPtName, tempTrkPt->name);
                                      tempTrkPtNode = xmlNewChild(segmentNode, NULL, BAD_CAST "trkpt", NULL);
                                   // }


                                    if(tempTrkPt->longitude != 0.00){
                                   // printf("REACHED TRACK POINT\n");
                                    char tempLon[200];
                                    snprintf(tempLon, 50, "%f",tempTrkPt->longitude);
                                    // adding the longitude as an xml attribute
                                    xmlNewProp(tempTrkPtNode, BAD_CAST "lon", BAD_CAST tempLon);
                                    }

                                    if(tempTrkPt->latitude != 0.00){
                                        char tempLat[200];
                                        snprintf(tempLat, 50, "%f", tempTrkPt->latitude);
                                        xmlNewProp(tempTrkPtNode, BAD_CAST "lat", BAD_CAST tempLat);
                                    }

                                    if(tempTrkPt->otherData != NULL){
                                    // ADD CODE HERE TO CREATE XMLNODES FOR TRACK POINT OTHER DATA
                                    GPXData *tempOtherData = NULL;
                                    List *otherData = tempTrkPt->otherData;
                                    ListIterator otherIter;
                                    ListIterator *otherIterPtr = NULL;

                                    otherIter = createIterator(otherData);
                                    otherIterPtr = &otherIter;

                                    tempOtherData = (GPXData*) nextElement(otherIterPtr);

                                    for(; tempOtherData != NULL; tempOtherData = (GPXData*)nextElement(otherIterPtr)){
                                        if((tempOtherData->name != NULL) && (tempOtherData->value != NULL)){
                                            // create an xmlNode for each otherData node found in the current track point
                                            xmlNewChild(tempTrkPtNode, NULL, BAD_CAST tempOtherData->name, BAD_CAST tempOtherData->value);
                                        }
                                    }


                                    }
                                } else if((tempTrkPt->name == NULL) || (strcmp(tempTrkPt->name, "") == 0)){
                                    // creating a track point xmlNode without a name
                                    xmlNodePtr tempTrkPtNode = xmlNewChild(segmentNode, NULL, BAD_CAST "trkPt", BAD_CAST "");

                                    if(tempTrkPt->longitude != 0.00){
                                        char tempLon[200];
                                        snprintf(tempLon, 300, "%f",tempTrkPt->longitude);
                                        // adding the longitude as an xml attribute
                                        xmlNewProp(tempTrkPtNode, BAD_CAST "lon", BAD_CAST tempLon);

                                    }

                                    if(tempTrkPt->latitude != 0.00){
                                    char tempLat[200];
                                    snprintf(tempLat, 300, "%f", tempTrkPt->latitude);
                                    xmlNewProp(tempTrkPtNode, BAD_CAST "lat", BAD_CAST tempLat);
                                    }

                                   if(tempTrkPt->otherData != NULL){
                                        // if the routePoint otherData list is not NULL
                                        // ADD CODE HERE TO CREATE XMLNODES FOR WAYPOINT OTHER DATA
                                        GPXData *tempOtherData = NULL;
                                        List *otherData = tempTrkPt->otherData;
                                        ListIterator otherIter;
                                        ListIterator *otherIterPtr = NULL;

                                        otherIter = createIterator(otherData);
                                        otherIterPtr = &otherIter;

                                        tempOtherData = (GPXData*) nextElement(otherIterPtr);

                                        for(; tempOtherData != NULL; tempOtherData = (GPXData*)nextElement(otherIterPtr)){
                                            if((tempOtherData->name != NULL) && (tempOtherData->value != NULL)){
                                                // create an xmlNode for each otherData node found in the current track point
                                                xmlNewChild(tempTrkPtNode, NULL, BAD_CAST tempOtherData->name, BAD_CAST tempOtherData->value);
                                            }
                                        }

                                    }
                                }

                            }



                    }
                }


            }
        }
    }

  //  xmlSaveFormatFileEnc("test.xml", doc, "UTF-8", 1000);

    return doc;
}



/************************************** ASSIGNMENT TWO FUNCTIONS BELOW ************************/

GPXdoc *createValidGPXdoc(char* fileName, char* gpxSchemaFile){

    if((fileName == NULL) || (gpxSchemaFile == NULL)){
        return NULL;
    }
    // variable declerations
    //xmlDoc *newDoc = NULL;
    xmlNode *root_element = NULL;
    GPXdoc *theGPXDoc = (GPXdoc*)malloc(sizeof(GPXdoc));

    xmlDocPtr doc;
    xmlSchemaPtr schema = NULL;
    xmlSchemaParserCtxtPtr ctxtPtr = NULL;

    xmlLineNumbersDefault(1);

    ctxtPtr = xmlSchemaNewParserCtxt(gpxSchemaFile);
    schema = xmlSchemaParse(ctxtPtr);
    xmlSchemaFreeParserCtxt(ctxtPtr);

    // creating the XML tree with libxml2 similar to before
    doc = xmlReadFile(fileName, NULL, 0);

    // then do error checking
    if (doc == NULL){
    //    printf("Could not parse\n");
        return NULL;
    } else {
        // if the XML tree has been succesfully created
        xmlSchemaValidCtxtPtr ctxt;
        int ret;

        ctxt = xmlSchemaNewValidCtxt(schema);
        xmlSchemaSetValidErrors(ctxt, (xmlSchemaValidityErrorFunc) fprintf, (xmlSchemaValidityWarningFunc) fprintf, stderr);

        ret = xmlSchemaValidateDoc(ctxt, doc);

        if(ret == 0){
            // if the xml tree is valid
            // use the code for creating the GPX doc

            // initializing the GPXDoc Struct
            strcpy(theGPXDoc->namespace, "namespace");
            theGPXDoc->version = 0.0;
            theGPXDoc->creator = (char*) malloc(sizeof(char) * 50);
            theGPXDoc->waypoints = initializeList(&waypointToString, &deleteWaypoint, &compareWaypoints);
            theGPXDoc->routes = initializeList(&routeToString, &deleteRoute, &compareRoutes);
            theGPXDoc->tracks = initializeList(&trackToString, &deleteTrack, &compareTracks);



            /*Get the root element node */
            root_element = xmlDocGetRootElement(doc);

            // initializing the namespace
            strcpy(theGPXDoc->namespace, (char*)root_element->ns->href);

            if(strcmp((char*)root_element->name, "gpx") == 0){
                print_element_names(root_element, theGPXDoc);
            }

            // freeing the xml tree
            xmlSchemaFreeValidCtxt(ctxt);
            xmlFreeDoc(doc);

            // free the resource
            // this may cause a double free
            if(schema != NULL){
                xmlSchemaFree(schema);
            }

            xmlSchemaCleanupTypes();
            xmlCleanupParser();
            xmlMemoryDump();

            return theGPXDoc;
        } else if (ret > 0){
         //   printf("%s fails to validate\n", fileName);
                 // freeing the xml tree
            xmlSchemaFreeValidCtxt(ctxt);
            xmlFreeDoc(doc);

            // free the resource
            if(schema != NULL)
            xmlSchemaFree(schema);
            xmlSchemaCleanupTypes();
            xmlCleanupParser();
            xmlMemoryDump();
            return NULL;
        } else {
         //   printf("%s validation generate an internal error\n", fileName);
                 // freeing the xml tree
            xmlSchemaFreeValidCtxt(ctxt);
            xmlFreeDoc(doc);

            // free the resource
            if(schema != NULL)
            xmlSchemaFree(schema);
            xmlSchemaCleanupTypes();
            xmlCleanupParser();
            xmlMemoryDump();
            return NULL;
        }

    }




}

bool writeGPXdoc(GPXdoc* doc, char*fileName){
    // error checking for inputs
    // ADD CHECKING FOR INVALID OUTPUT FILE NAME
    xmlDoc* xmlDoc = NULL;
    int validationCheck = 0;
    bool returnValue = false;
   // char tempString[100];

    if((doc == NULL) || (fileName == NULL)){
        return returnValue;
    } else {

        xmlDoc = gpxToXML(doc);
        validationCheck = xmlSaveFormatFileEnc(fileName, xmlDoc, "UTF-8", 1);

        if(validationCheck == -1){
            xmlFreeDoc(xmlDoc);
        } else if (validationCheck > 0){
        //    printf("FILE IS VALID AND HAS BEEN WRITTEN\n");
            returnValue = true;
            xmlFreeDoc(xmlDoc);
           // return true;
        }
        return returnValue;
    }

}

bool validateGPXDoc(GPXdoc* gpxDoc, char* gpxSchemaFile){

    // error checking for inputs
    // ADD CHECKING FOR INVALID GPX SCHEMA FILE
    if((gpxDoc == NULL) || (gpxSchemaFile == NULL)){
        return false;
    }


    // converting the gpx doc to an xml tree
  //  newDoc = gpxToXML(gpxDoc);
  //  xmlNode *root_element = NULL;

    xmlDocPtr doc = NULL;
   // char *XMLFileName = "test.xml";
    xmlSchemaPtr schema = NULL;
    xmlSchemaParserCtxtPtr ctxtParser;
    xmlLineNumbersDefault(1);


    ctxtParser = xmlSchemaNewParserCtxt(gpxSchemaFile);

    xmlSchemaSetParserErrors(ctxtParser, (xmlSchemaValidityErrorFunc) fprintf, (xmlSchemaValidityWarningFunc) fprintf, stderr);
    schema = xmlSchemaParse(ctxtParser);
    xmlSchemaFreeParserCtxt(ctxtParser);

    doc = gpxToXML(gpxDoc);

  //  root_element = xmlDocGetRootElement(doc);
  //  printf("ROOT ELEMENT NAME IS %s\n", root_element->name);

  //  ctxt = xmlSchemaNewParserCtxt(gpxSchemaFile);

      // then do error checking
    if (doc == NULL){
      //  printf("Could not parse\n");
        return false;
    } else {
        // if the XML tree has been succesfully created

        xmlSchemaValidCtxtPtr ctxt;
        int ret;

        ctxt = xmlSchemaNewValidCtxt(schema);
        xmlSchemaSetValidErrors(ctxt, (xmlSchemaValidityErrorFunc) fprintf, (xmlSchemaValidityWarningFunc) fprintf, stderr);

        ret = xmlSchemaValidateDoc(ctxt, doc);

        if(ret == 0){
         //   printf("VALIDATES\n");
            // if the xml tree is valid
            // use the code for creating the GPX doc

            /*Get the root element node */
//            root_element = xmlDocGetRootElement(doc);

            // initializing the namespace
//            strcpy(gpxDoc->namespace, (char*)root_element->properties->children->content);


            // freeing the xml tree
            xmlSchemaFreeValidCtxt(ctxt);

            xmlFreeDoc(doc);

            // free the resource
            // this may cause a double free
            if(schema != NULL){
                xmlSchemaFree(schema);
            }

            xmlSchemaCleanupTypes();
            xmlCleanupParser();
            xmlMemoryDump();

            return true;
        } else if (ret > 0){
        //    printf("%s fails to validate\n", gpxSchemaFile);
                // freeing the xml tree
            xmlSchemaFreeValidCtxt(ctxt);

            xmlFreeDoc(doc);

            // free the resource
            // this may cause a double free
            if(schema != NULL){
                xmlSchemaFree(schema);
            }

            xmlSchemaCleanupTypes();
            xmlCleanupParser();
            xmlMemoryDump();
            return false;
        } else {
         //   printf("%s validation generate an internal error\n", gpxSchemaFile);
                // freeing the xml tree
            xmlSchemaFreeValidCtxt(ctxt);

            xmlFreeDoc(doc);

            // free the resource
            // this may cause a double free
            if(schema != NULL){
                xmlSchemaFree(schema);
            }

            xmlSchemaCleanupTypes();
            xmlCleanupParser();
            xmlMemoryDump();
            return false;
        }


        // freeing the xml tree
        xmlSchemaFreeValidCtxt(ctxt);
        xmlFreeDoc(doc);

        // free the resource
        if(schema != NULL)
        xmlSchemaFree(schema);
        xmlSchemaCleanupTypes();
        xmlCleanupParser();
        xmlMemoryDump();

    }
}

// MODULE TWO FUNCTIONS BELOW
float round10(float len){
    float roundedFloat = 0.0;
    float floatDecimal = 0.0;
    int tempInt = 0;
    int onesColumn = 0;
    double integral;

    // if the input is has a ones column value of 5 or more
    // then round up
    // else round down
    floatDecimal = modf(len, &integral);
    roundedFloat = len - floatDecimal;
    tempInt = (int) roundedFloat;

    onesColumn = tempInt % 10;

    if(onesColumn >= 5){
    // if the ones column is of value 5 or above round up
        tempInt = tempInt + (10 - onesColumn);

    } else {
        // if the ones column value is of 4 or lower round down

        tempInt = tempInt - onesColumn;
    }


    // convert int back to float for return value
    roundedFloat = (float) tempInt;
    return roundedFloat;
}

float getRouteLen(const Route *rt){
    float returnLen = 0.0;
    Waypoint *ptOne = NULL;

    Waypoint *ptTwo = NULL;

    List *allRtePts = NULL;
    ListIterator rteIter;
    ListIterator *rteIterPtr = NULL;
    // error checking

    if(rt == NULL){
        return 0;
    }

    if(rt->waypoints != NULL){
        allRtePts = rt->waypoints;
        rteIter = createIterator(allRtePts);
        rteIterPtr = &rteIter;

        ptOne = (Waypoint*) nextElement(rteIterPtr);
        ptTwo = (Waypoint*) nextElement(rteIterPtr);

        // grab route points in pairs for the haversine formula
        while(ptTwo != NULL){
            // grab the next point
            //ptTwo = (Waypoint*) nextElement(rteIterPtr);

            if(ptTwo != NULL){

                float rVal = 6371e3;
                float thetaOne = ptOne->latitude * M_PI/180.0;
                float thetaTwo = ptTwo->latitude * M_PI/180.0;
                float deltaVal = (ptTwo->latitude - ptOne->latitude) * M_PI/180.0;
                float lambdaVal = (ptTwo->longitude - ptOne->longitude) * M_PI/180.0;

                float aVal = sin(deltaVal/2) * sin(deltaVal/2) + cos(thetaOne) * cos(thetaTwo) * sin(lambdaVal/2) * sin(lambdaVal/2);
                float cVal = 2 * atan2(sqrt(aVal), sqrt(1-aVal));
                float dVal = rVal * cVal;
             //   printf("distance value = %f\n", dVal);
                returnLen += dVal;

            }
            ptOne = ptTwo;
            ptTwo = (Waypoint*)nextElement(rteIterPtr);
        }
        return returnLen;
    } else {
        return 0;
    }
}

float getTrackLen(const Track *tr){
    float returnLen = 0.0;
    float tempLon = 0.0;
    float tempLat = 0.0;
   // float firstSegmentWpt = 0.0;
    int segmentCounter = 0;
    int switchingSegments = 0;
  //  int numSegments = 0;
    int listLength = 0;
    Waypoint *ptOne = NULL;
    Waypoint *ptTwo = NULL;
  //  Waypoint *tempPt = NULL;
    TrackSegment *currentSegment = NULL;
    List *allTrkPts = NULL;
    List *allSegments = NULL;
    ListIterator segmentIter;
    ListIterator *segmentIterPtr = NULL;
    ListIterator trkIter;
    ListIterator *trkIterPtr = NULL;
    // error checking

    if(tr == NULL){
        return 0;
    }
    if(tr->segments == NULL){
        return 0;
    }

    // iterate through each track segment in the track
    // in each track segment, iterate through each track point

    allSegments = tr->segments;
    //numSegments = getLength(allSegments);
    segmentIter = createIterator(allSegments);
    segmentIterPtr = &segmentIter;


    currentSegment = (TrackSegment*) nextElement(segmentIterPtr);

    for(; currentSegment != NULL; currentSegment = (TrackSegment*) nextElement(segmentIterPtr)){
        // iterating through each track segment

        if(currentSegment->waypoints == NULL){
            return 0;
        }

        if(currentSegment->waypoints != NULL){
            // if there are track points

            allTrkPts = currentSegment->waypoints;
            listLength = getLength(allTrkPts);
           // printf("TESTING LIST LENGTH: %d\n", listLength);
            trkIter = createIterator(allTrkPts);
            trkIterPtr = &trkIter;
            ptOne = (Waypoint*) nextElement(trkIterPtr);
            ptTwo = (Waypoint*) nextElement(trkIterPtr);

            while(ptTwo != NULL){

                if((segmentCounter > 0) && (switchingSegments == 1)){

                    // if the segment amount is greater than 1
                    // find distance between last point of last segment
                    // and the first point of the new segment
                    float rValue = 6371000;
                //    printf("TESTING LAST WPT %f and FIRST WPT %f\n", tempLat, ptOne->latitude);
                    float tOne = tempLat * M_PI/180;
                    float tTwo = ptOne->latitude * M_PI/180;
                    float dVal = (ptOne->latitude - tempLat) * M_PI/180;
                    float lVal = (ptOne->longitude - tempLon) * M_PI/180;

                    float aValueDistance = sin(dVal/2) * sin(dVal/2) + cos(tOne) * cos(tTwo) * sin(lVal/2) * sin(lVal/2);
                    float cValueDistance = 2 * atan2(sqrt(aValueDistance), sqrt(1-aValueDistance));
                    float dValueDistance = rValue * cValueDistance;
                    returnLen += dValueDistance;
                    switchingSegments = 0;
                }


                if(ptTwo != NULL){

                    float rVal = 6371000;
                    float thetaOne = ptOne->latitude * M_PI/180;
                    float thetaTwo = ptTwo->latitude * M_PI/180;
                    float deltaVal = (ptTwo->latitude - ptOne->latitude) * M_PI/180;
                    float lambdaVal = (ptTwo->longitude - ptOne->longitude) * M_PI/180;

                    float aVal = sin(deltaVal/2) * sin(deltaVal/2) + cos(thetaOne) * cos(thetaTwo) * sin(lambdaVal/2) * sin(lambdaVal/2);
                    float cVal = 2 * atan2(sqrt(aVal), sqrt(1-aVal));
                    float dVal = rVal * cVal;

               //     printf("DISTANCE CALCULATED = %f\n\n\n", dVal);
                    returnLen += dVal;

                }

                ptOne = ptTwo;
                ptTwo = (Waypoint*)nextElement(trkIterPtr);

                if(listLength % 2 == 0){
               //      printf("YO\n");
                    if(ptTwo != NULL){
                        tempLat = ptTwo->latitude;
                        tempLon = ptTwo->longitude;
                    }
                }  else {

                    tempLat = ptOne->latitude;
                    tempLon = ptOne->longitude;
               //     printf("YO2\n");
                }
            }
        }
    }

    return returnLen;
}

int numRoutesWithLength(const GPXdoc* doc, float len, float delta){
    int numRoutes = 0;
    float secondLen = 0.0;
    float toleranceCheck = 0.0;
    List *allRoutes = NULL;
    ListIterator rteIter;
    ListIterator *rteIterPtr = NULL;
    Route *routeOne = NULL;
 //   Route *routeTwo = NULL;

    // error checking
    if(doc == NULL){
        return 0;
    }

    if((len < 0) || (delta < 0)){
        return 0;
    }

    allRoutes = doc->routes;
    // creating the iterator
    rteIter = createIterator(allRoutes);
    // assigning the iterator pointer to the created iterator
    rteIterPtr = &rteIter;

    if(allRoutes != NULL){
        // if there are route points in the list
        routeOne = (Route*) nextElement(rteIterPtr);

        for(; routeOne != NULL; routeOne = (Route*)nextElement(rteIterPtr)){

                // if the route after the current route is not NULL
                // get the lengths of the two consecutive routes
               // firstLen = getRouteLen(routeOne);
                secondLen = getRouteLen(routeOne);
                // test tolerance
                if(len == secondLen){
                    numRoutes++;
                //    printf("EQUAL ROUTES\n");
                } else {
                    if(len > secondLen){
                        // calculating the difference
                        toleranceCheck = len - secondLen;
                        // subtract delta from toleranceCheck
                        // if toleranceCheck is greater than, or equal to 0 then
                        // the routes can be considered equal

                        toleranceCheck = delta - toleranceCheck;
                        if(toleranceCheck >= 0){
                            // the two routes can be considered equal as they fall in the tolerance range
                      //      printf("EQUAL ROUTES\n");
                            numRoutes++;
                        }

                    } else if (secondLen > len){
                        // calculating the difference
                        // subtract delta from toleranceCheck
                        // if toleranceCheck is greater than, or equal to 0 then
                        // the routes can be considered equal
                        toleranceCheck = secondLen - len;

                        toleranceCheck = delta - toleranceCheck;
                        if(toleranceCheck >= 0){
                            // the two routes can be considered equal as they fall in the tolerance range
                     //       printf("EQUAL ROUTES\n");
                            numRoutes++;
                        }
                    }
                }
            }
        }
    // get the length of each route using the getRouteLen function
    // compare consecutive routes with the tolerance allowed
    // if they are equal, then increment numRoutes

    return numRoutes;
}

int numTracksWithLength(const GPXdoc* doc, float len, float delta){
    int numTracks = 0;
    float secondLen = 0.0;
    float toleranceCheck = 0.0;
    List *allTracks = NULL;
    ListIterator trkIter;
    ListIterator *trkIterPtr = NULL;
    Track *trackOne = NULL;
    //Track *trackTwo = NULL;

    // error checking
    if(doc == NULL){
        return 0;
    }

    if((len < 0) || (delta < 0)){
        return 0;
    }

    allTracks = doc->tracks;
    // creating the iterator
    trkIter = createIterator(allTracks);
    // assigning the iterator pointer to the created iterator
    trkIterPtr = &trkIter;

    if(allTracks != NULL){
        // if there are route points in the list
        trackOne = (Track*) nextElement(trkIterPtr);

        for(; trackOne != NULL; trackOne = (Track*)nextElement(trkIterPtr)){

                // if the route after the current route is not NULL
                // get the lengths of the two consecutive routes
               // firstLen = getRouteLen(routeOne);
                secondLen = getTrackLen(trackOne);
                // test tolerance
                if(len == secondLen){
                    numTracks++;
                //    printf("EQUAL ROUTES\n");
                } else {
                    if(len > secondLen){
                        // calculating the difference
                        toleranceCheck = len - secondLen;
                        // subtract delta from toleranceCheck
                        // if toleranceCheck is greater than, or equal to 0 then
                        // the routes can be considered equal

                        toleranceCheck = delta - toleranceCheck;
                        if(toleranceCheck >= 0){
                            // the two routes can be considered equal as they fall in the tolerance range
                      //      printf("EQUAL ROUTES\n");
                            numTracks++;
                        }

                    } else if (secondLen > len){
                        // calculating the difference
                        // subtract delta from toleranceCheck
                        // if toleranceCheck is greater than, or equal to 0 then
                        // the routes can be considered equal

                        toleranceCheck = secondLen - len;
                        toleranceCheck = delta - toleranceCheck;

                        if(toleranceCheck >= 0){
                            // the two routes can be considered equal as they fall in the tolerance range
                     //       printf("EQUAL ROUTES\n");
                            numTracks++;
                        }
                    }
                }
            }
        }
    // get the length of each route using the getRouteLen function
    // compare consecutive routes with the tolerance allowed
    // if they are equal, then increment numRoutes

    return numTracks;
}

bool isLoopRoute(const Route* rt, float delta){
    bool returnValue = false;
    int numWaypoints = 0;
    Waypoint *firstPoint = NULL;
    Waypoint *lastPoint = NULL;

    // error checking
    if((rt == NULL) || (delta < 0) ){
        return returnValue;
    }

    numWaypoints = getLength(rt->waypoints);

    if(numWaypoints >= 4){

        if(rt->waypoints == NULL){
            return returnValue;
        }
        // if the route has four or more waypoints
        // use the getFromFront and getFromBack functions to retrieve the first and last waypoints
        // calculate the distance between the two waypoints
        // if the distance is less than delta betwee nthe first and last points, the route has a loop and returnValue will be set to "true"
        firstPoint = getFromFront(rt->waypoints);
        lastPoint = getFromBack(rt->waypoints);

        float rVal = 6371000;
        float thetaOne = firstPoint->latitude * M_PI/180;
        float thetaTwo = lastPoint->latitude * M_PI/180;
        float deltaVal = (lastPoint->latitude - firstPoint->latitude) * M_PI/180;
        float lambdaVal = (lastPoint->longitude - firstPoint->longitude) * M_PI/180;

        float aVal = sin(deltaVal/2) * sin(deltaVal/2) + cos(thetaOne) * cos(thetaTwo) * sin(lambdaVal/2) * sin(lambdaVal/2);
        float cVal = 2 * atan2(sqrt(aVal), sqrt(1-aVal));
        float dVal = rVal * cVal;

        if(dVal < delta){
            returnValue = true;
            return returnValue;
        }

    } else {
        return returnValue;
    }
    return returnValue;
}

bool isLoopTrack(const Track *tr, float delta){
    bool returnValue = false;
    int numWaypoints = 0;
    bool hasMinWaypoints = false;
    int numSegments = 0;
    Waypoint *firstPoint = NULL;
    Waypoint *lastPoint = NULL;
    ListIterator segmentIter;
    ListIterator *segmentIterPtr = NULL;
    TrackSegment *currentSegment = NULL;
    List *allSegments = NULL;
    TrackSegment *firstSegment = NULL;
    TrackSegment *lastSegment = NULL;

    // error checking
    if((tr == NULL) || (delta < 0) ){
        return returnValue;
    }

    // iteraete through the segments
    // if the combined length of all segment waypoints > 4, then execute the code


    if(tr->segments == NULL){
        return returnValue;
    }

    allSegments = tr->segments;
    numSegments = getLength(allSegments);

    segmentIter = createIterator(allSegments);
    segmentIterPtr = &segmentIter;

    currentSegment = (TrackSegment*) nextElement(segmentIterPtr);

    for(; currentSegment != NULL; currentSegment = (TrackSegment*) nextElement(segmentIterPtr)){
        // iterate through each track segment and increment numWaypoints by the size of each track point list
        numWaypoints = getLength(currentSegment->waypoints);
        if(numWaypoints >= 4){
            hasMinWaypoints = true;
        }
    }

    if(hasMinWaypoints == true){


        // if the track has four or more waypoints
        // use the getFromFront and getFromBack functions to retrieve the first and last waypoints
        // calculate the distance between the two waypoints
        // if the distance is less than delta betwee nthe first and last points, the route has a loop and returnValue will be set to "true"

        // for a track, get the first point from the front of the first segment
        // for the last point, get the last point from the last segment

        if(numSegments == 1){
            firstSegment = getFromFront(tr->segments);
            firstPoint = getFromFront(firstSegment->waypoints);
            lastPoint = getFromBack(firstSegment->waypoints);

            float rVal = 6371000;
            float thetaOne = firstPoint->latitude * M_PI/180;
            float thetaTwo = lastPoint->latitude * M_PI/180;
            float deltaVal = (lastPoint->latitude - firstPoint->latitude) * M_PI/180;
            float lambdaVal = (lastPoint->longitude - firstPoint->longitude) * M_PI/180;

            float aVal = sin(deltaVal/2) * sin(deltaVal/2) + cos(thetaOne) * cos(thetaTwo) * sin(lambdaVal/2) * sin(lambdaVal/2);
            float cVal = 2 * atan2(sqrt(aVal), sqrt(1-aVal));
            float dVal = rVal * cVal;

            if(dVal < delta){
                returnValue = true;
                return returnValue;
            }
        } else {
            firstSegment = getFromFront(tr->segments);
            firstPoint = getFromFront(firstSegment->waypoints);

            lastSegment = getFromBack(tr->segments);
            lastPoint = getFromBack(lastSegment->waypoints);

            float rVal = 6371000;
            float thetaOne = firstPoint->latitude * M_PI/180;
            float thetaTwo = lastPoint->latitude * M_PI/180;
            float deltaVal = (lastPoint->latitude - firstPoint->latitude) * M_PI/180;
            float lambdaVal = (lastPoint->longitude - firstPoint->longitude) * M_PI/180;

            float aVal = sin(deltaVal/2) * sin(deltaVal/2) + cos(thetaOne) * cos(thetaTwo) * sin(lambdaVal/2) * sin(lambdaVal/2);
            float cVal = 2 * atan2(sqrt(aVal), sqrt(1-aVal));
            float dVal = rVal * cVal;

            if(dVal < delta){
                returnValue = true;
                return returnValue;
            }
        }
    } else {
        return returnValue;
    }

    return returnValue;
}

// HELPER FUNCTION
void unofficialDeleteRoute(void* data){

}

// HELPER FUNCTION
void unofficialDeleteTrack(void* data){

}

List* getRoutesBetween(const GPXdoc* doc, float sourceLat, float sourceLong, float destLat, float destLong, float delta){
    List *allRoutesBetween = NULL;
    List *theRoutes = NULL;
  //  Route *headRoute = NULL;
    //Route *tailRoute = NULL;
    Waypoint *startingPoint = NULL;
    Waypoint *endingPoint = NULL;
    ListIterator routeIter;
    ListIterator *routeIterPtr = NULL;
    Route *currentRoute = NULL;
    float haversineOne = 0.0;
    float haversineTwo = 0.0;


    if(doc == NULL){
        return NULL;
    }

    // if the head waypoint of the route is within the delta of the start,
    // and the tail is within the delta of the dest, then it is a route between those two points

    // iterate through each route
    // on each iteration, get the head node and tail node
    // for the head node, the head node will be "ptOne" and sourceLat and sourceLong will be "ptTwo"
    // for the tail node, the tail node will be "ptOne" and the destLat and destLong will be "ptTwo"
    allRoutesBetween = initializeList(&routeToString, &unofficialDeleteRoute, &compareRoutes);

    if(doc->routes != NULL){
        theRoutes = doc->routes;
        routeIter = createIterator(theRoutes);
        routeIterPtr = &routeIter;

        currentRoute = (Route*) nextElement(routeIterPtr);

        for(; currentRoute != NULL; currentRoute = (Route*)nextElement(routeIterPtr)){
            // iterating through the GPX document routes
            // get the waypoint at the front of the list and the waypoint at the end

            if(currentRoute->waypoints != NULL){
                startingPoint = getFromFront(currentRoute->waypoints);
                endingPoint = getFromBack(currentRoute->waypoints);

                // REMEMBER TO CREATE HELPED FUNCTION FOR HAVERSINE FORMULA

                float rVal = 6371000;
                float thetaOne = startingPoint->latitude * M_PI/180;
                float thetaTwo = sourceLat * M_PI/180;
                float deltaVal = (sourceLat - startingPoint->latitude) * M_PI/180;
                float lambdaVal = (sourceLong - startingPoint->longitude) * M_PI/180;

                float aVal = sin(deltaVal/2) * sin(deltaVal/2) + cos(thetaOne) * cos(thetaTwo) * sin(lambdaVal/2) * sin(lambdaVal/2);
                float cVal = 2 * atan2(sqrt(aVal), sqrt(1-aVal));
                float dVal = rVal * cVal;

                // distance from the head waypoint and the starting points
                haversineOne = dVal;

                float tOne = endingPoint->latitude * M_PI/180;
                float tTwo = destLat * M_PI/180;
                float secondDeltaVal = (destLat - endingPoint->latitude) * M_PI/180;
                float secondLambdaVal = (destLong - endingPoint->longitude) * M_PI/180;

                float aValue = sin(secondDeltaVal/2) * sin(secondDeltaVal/2) + cos(tOne) * cos(tTwo) * sin(secondLambdaVal/2) * sin(secondLambdaVal/2);
                float cValue = 2 * atan2(sqrt(aValue), sqrt(1-aValue));
                float secondDistanceVal = rVal * cValue;

                haversineTwo = secondDistanceVal;

                if((haversineOne <= delta) && (haversineTwo <= delta)){
                    insertBack(allRoutesBetween, currentRoute);
                }
            }
        }
    }

    if((getLength(allRoutesBetween)) == 0){
        return NULL;
    }

    return allRoutesBetween;
}

List* getTracksBetween(const GPXdoc* doc, float sourceLat, float sourceLong, float destLat, float destLong, float delta){
    List *allTracksBetween = NULL;
    List *theTracks = NULL;
    //Track *headTrack = NULL;
    //Track *tailTrack = NULL;
    Waypoint *startingPoint = NULL;
    Waypoint *endingPoint = NULL;
    ListIterator trackIter;
    ListIterator *trackIterPtr = NULL;
    int numSegments = 0;
    Track *currentTrack = NULL;
    float haversineOne = 0.0;
    float haversineTwo = 0.0;

    if(doc == NULL){
        return NULL;
    }

    // if the head waypoint of the route is within the delta of the start,
    // and the tail is within the delta of the dest, then it is a route between those two points

    // iterate through each track
    // on each iteration, get the head node and tail node
    // get the first node of the first segment as the head starting point
    // get the last note of the last segment of the current track as the ending point
    // for the head node, the head node will be "ptOne" and sourceLat and sourceLong will be "ptTwo"
    // for the tail node, the tail node will be "ptOne" and the destLat and destLong will be "ptTwo"
    allTracksBetween = initializeList(&trackToString, &unofficialDeleteTrack, &compareTracks);

    if(doc->tracks != NULL){
        theTracks = doc->tracks;
        trackIter = createIterator(theTracks);
        trackIterPtr = &trackIter;

        currentTrack = (Track*) nextElement(trackIterPtr);

        for(; currentTrack != NULL; currentTrack = (Track*) nextElement(trackIterPtr)){
            if(currentTrack->segments != NULL){
                TrackSegment *firstSegment = NULL;
                TrackSegment *lastSegment = NULL;

                numSegments = getLength(currentTrack->segments);

                if(numSegments == 1){

                    firstSegment = getFromFront(currentTrack->segments);
                    startingPoint = getFromFront(firstSegment->waypoints);
                    endingPoint = getFromBack(firstSegment->waypoints);

                    // now calculate the haversine formula
                    float rVal = 6371000;
                    float thetaOne = startingPoint->latitude * M_PI/180;
                    float thetaTwo = sourceLat * M_PI/180;
                    float deltaVal = (sourceLat - startingPoint->latitude) * M_PI/180;
                    float lambdaVal = (sourceLong - startingPoint->longitude) * M_PI/180;

                    float aVal = sin(deltaVal/2) * sin(deltaVal/2) + cos(thetaOne) * cos(thetaTwo) * sin(lambdaVal/2) * sin(lambdaVal/2);
                    float cVal = 2 * atan2(sqrt(aVal), sqrt(1-aVal));
                    float dVal = rVal * cVal;

                    // distance from the head waypoint and the starting points
                    haversineOne = dVal;

                    float tOne = endingPoint->latitude * M_PI/180;
                    float tTwo = destLat * M_PI/180;
                    float secondDeltaVal = (destLat - endingPoint->latitude) * M_PI/180;
                    float secondLambdaVal = (destLong - endingPoint->longitude) * M_PI/180;

                    float aValue = sin(secondDeltaVal/2) * sin(secondDeltaVal/2) + cos(tOne) * cos(tTwo) * sin(secondLambdaVal/2) * sin(secondLambdaVal/2);
                    float cValue = 2 * atan2(sqrt(aValue), sqrt(1-aValue));
                    float secondDistanceVal = rVal * cValue;

                    haversineTwo = secondDistanceVal;

                    if((haversineOne <= delta) && (haversineTwo <= delta)){
                        insertBack(allTracksBetween, currentTrack);
                    }



                } else if (numSegments > 1){

                    firstSegment = getFromFront(currentTrack->segments);
                    startingPoint = getFromFront(firstSegment->waypoints);

                    lastSegment = getFromBack(currentTrack->segments);
                    endingPoint = getFromBack(lastSegment->waypoints);

                    // now calculate the haversine formula
                    float rVal = 6371000;
                    float thetaOne = startingPoint->latitude * M_PI/180;
                    float thetaTwo = sourceLat * M_PI/180;
                    float deltaVal = (sourceLat - startingPoint->latitude) * M_PI/180;
                    float lambdaVal = (sourceLong - startingPoint->longitude) * M_PI/180;

                    float aVal = sin(deltaVal/2) * sin(deltaVal/2) + cos(thetaOne) * cos(thetaTwo) * sin(lambdaVal/2) * sin(lambdaVal/2);
                    float cVal = 2 * atan2(sqrt(aVal), sqrt(1-aVal));
                    float dVal = rVal * cVal;

                    // distance from the head waypoint and the starting points
                    haversineOne = dVal;

                    float tOne = endingPoint->latitude * M_PI/180;
                    float tTwo = destLat * M_PI/180;
                    float secondDeltaVal = (destLat - endingPoint->latitude) * M_PI/180;
                    float secondLambdaVal = (destLong - endingPoint->longitude) * M_PI/180;

                    float aValue = sin(secondDeltaVal/2) * sin(secondDeltaVal/2) + cos(tOne) * cos(tTwo) * sin(secondLambdaVal/2) * sin(secondLambdaVal/2);
                    float cValue = 2 * atan2(sqrt(aValue), sqrt(1-aValue));
                    float secondDistanceVal = rVal * cValue;

                    haversineTwo = secondDistanceVal;

                    if((haversineOne <= delta) && (haversineTwo <= delta)){
                        insertBack(allTracksBetween, currentTrack);
                    }
                }
            }
        }
    }

    if((getLength(allTracksBetween)) == 0){
        return NULL;
    }

    return allTracksBetween;
}
// MODULE TWO FUNCTIONS END

// MODULE THREE FUNCTIONS BEGIN

char* routeToJSON(const Route *rt){
    char* returnString = (char*)malloc(sizeof(char) * 1000);
   // char *rteName = (char*)malloc(sizeof(char) * 200);
   char rteName[300];
   char intToString[200];
   char floatToString[200];
   // char *intToString = (char*)malloc(sizeof(char)* 200);
   // char *floatToString = (char*)malloc(sizeof(char) * 200);
    int numPoints = 0.0;
    float routeLen = 0.0;
    bool loopVal = false;

    if(rt == NULL){
        strcpy(returnString, "{}");
        return returnString;
    }

    if(strcmp(rt->name, "") == 0){
        // route does not have a name
        strcpy(rteName, "None");
    } else if (strcmp(rt->name, "") != 0){
        // route has a name
        strcpy(rteName, rt->name);
        routeLen = getRouteLen(rt);
        routeLen = round10(routeLen);
        numPoints = getLength(rt->waypoints);
        loopVal = isLoopRoute(rt, 10);

        sprintf(intToString, "%d", numPoints);
        sprintf(floatToString, "%.1f", routeLen);


        strcpy(returnString, "");
        strcat(returnString, "{\"name\":");
        strcat(returnString, "\"");
        strcat(returnString, rteName);
        strcat(returnString, "\"");
        strcat(returnString, ",\"numPoints\":");
        strcat(returnString, intToString);
        strcat(returnString, ",\"len\":");
        strcat(returnString, floatToString);
        strcat(returnString, ",\"loop\":");

        if(loopVal == false){
            strcat(returnString, "false}");
        } else if (loopVal == true){
            strcat(returnString, "true}");
        }
    }

    return returnString;
}

char* trackToJSON(const Track *tr){
    char* returnString = (char*)malloc(sizeof(char) * 1000);
   // char *trkName = (char*)malloc(sizeof(char) * 200);
    char trkName[300];
   // char *floatToString = (char*)malloc(sizeof(char) * 200);
    char floatToString[200];
    float routeLen = 0.0;
    bool loopVal = false;

    if(tr == NULL){
        strcpy(returnString, "{}");
        return returnString;
    }

    if(strcmp(tr->name, "") == 0){
        // route does not have a name
        strcpy(trkName, "None");
    } else if (strcmp(tr->name, "") != 0){
        // route has a name
        strcpy(trkName, tr->name);
        routeLen = getTrackLen(tr);
        routeLen = round10(routeLen);
        loopVal = isLoopTrack(tr, 10);


        sprintf(floatToString, "%.1f", routeLen);


        strcpy(returnString, "");
        strcat(returnString, "{\"name\":");
        strcat(returnString, "\"");
        strcat(returnString, trkName);
        strcat(returnString, "\"");
        strcat(returnString, ",\"len\":");
        strcat(returnString, floatToString);
        strcat(returnString, ",\"loop\":");

        if(loopVal == false){
            strcat(returnString, "false}");
        } else if (loopVal == true){
            strcat(returnString, "true}");
        }
    }

    return returnString;
}

char* routeListToJSON(const List *routeList){
    char* returnString = (char*)malloc(sizeof(char) * 1000);
    Route *currentRoute = NULL;
    int routeLen = 0;
    int i= 1;
    ListIterator listIter;
    ListIterator *listIterPtr = NULL;

    // iterate through the list of routes
    // on each iteration store the result of routeToJSON in an array of strings

    // error checking
    if(routeList == NULL){
        strcpy(returnString, "[]");
        return returnString;
    } else {
        strcpy(returnString, "");
        strcat(returnString, "[");
    }

    routeLen = getLength((List*)routeList);


    listIter = createIterator((List*)routeList);
    listIterPtr = &listIter;

    currentRoute = (Route*) nextElement(listIterPtr);

    for(; currentRoute != NULL; currentRoute = (Route*) nextElement(listIterPtr)){
        strcat(returnString, routeToJSON(currentRoute));
        if(i == routeLen){
        strcat(returnString, "]");
        } else {
             strcat(returnString, ",");
             i++;
        }
    }


    return returnString;
}

char* trackListToJSON(const List *trackList){
    char* returnString = (char*)malloc(sizeof(char) * 1000);
    Track *currentTrack = NULL;
    int trackLen = 0;
    int i= 1;
    ListIterator listIter;
    ListIterator *listIterPtr = NULL;

    // iterate through the list of routes
    // on each iteration store the result of routeToJSON in an array of strings

    // error checking
    if(trackList == NULL){
        strcpy(returnString, "[]");
        return returnString;
    } else {
        strcpy(returnString, "");
        strcat(returnString, "[");
    }

    trackLen = getLength((List*)trackList);


    listIter = createIterator((List*)trackList);
    listIterPtr = &listIter;

    currentTrack = (Track*) nextElement(listIterPtr);

    for(; currentTrack != NULL; currentTrack = (Track*) nextElement(listIterPtr)){
        strcat(returnString, trackToJSON(currentTrack));
        if(i == trackLen){
        strcat(returnString, "]");
        } else {
             strcat(returnString, ",");
             i++;
        }
    }


    return returnString;
}

char *GPXtoJSON(const GPXdoc* gpx){
    char* returnString = (char*) malloc(sizeof(char) * 1000);
    char docVersion[100];
    char docCreator[200];
    int numWaypoints = 0;
    int numRoutes = 0;
    int numTracks = 0;
   // char *waypointString = (char*) malloc(sizeof(char) * 100);
   char waypointString[200];
   char routeString[200];
   char trackString[200];
   // char *routeString = (char*) malloc(sizeof(char) * 100);
   // char *trackString = (char*) malloc(sizeof(char)* 100);

    // error checking
    if(gpx == NULL){
        strcpy(returnString, "{}");
    } else {
        strcpy(returnString, "");
    }

    numWaypoints = getLength(gpx->waypoints);
    numRoutes = getLength(gpx->routes);
    numTracks = getLength(gpx->tracks);

    // converting the integer values to string
    sprintf(waypointString, "%d", numWaypoints);
    sprintf(routeString, "%d", numRoutes);
    sprintf(trackString, "%d", numTracks);

    sprintf(docVersion, "%.1f", gpx->version);

    if(gpx->creator != NULL){
        strcpy(docCreator, gpx->creator);
    }

    strcat(returnString, "{\"version\":");
    strcat(returnString, "\"");
    strcat(returnString, docVersion);
    strcat(returnString, "\"");
    strcat(returnString, ",\"creator\":");
    strcat(returnString, "\"");
    strcat(returnString, docCreator);
    strcat(returnString, "\"");
    strcat(returnString, ",\"numWaypoints\":");
    strcat(returnString, waypointString);
    strcat(returnString, ",\"numRoutes\":");
    strcat(returnString, routeString);
    strcat(returnString, ",\"numTracks\":");
    strcat(returnString, trackString);
    strcat(returnString, "}");



    return returnString;
}

// MODULE THREE FUNCTIONS END

// MODULE THREE BONUS FUNCTIONS BELOW
void addWaypoint(Route *rt, Waypoint *pt){

}

void addRoute(GPXdoc* doc, Route *rt){

}

GPXdoc *JSONtoGPX(const char* gpxString){
    return NULL;
}

char *newJSONtoGPX(const char* gpxString){
    // json formatted string will be passed from the front end to the back end
    // format of string will be fileName,namespace,version,creator
   // char str[] ="1,2,3,4,5";
    char *pt;
    char *returnString = (char*)malloc(sizeof(char) * 200);
    //char tempChar[100];
    char *tempString = (char*)malloc(sizeof(char)*300);
    char fileName[300];
    char namespaceValue[300];
    char versionValue[300];
    char creatorValue[300];
    char allValues[4][200];
   // char number[24];
    int i = 0;
    char *eptr;
    bool isValid = false;
    double versionResult = 0.0;

    GPXdoc *tempDoc = (GPXdoc*) malloc(sizeof(GPXdoc));
    tempDoc->version = 0.0;
    tempDoc->creator = (char*) malloc(sizeof(char) * 100);
    tempDoc->waypoints = initializeList(&waypointToString, &deleteWaypoint, &compareWaypoints);
    tempDoc->routes = initializeList(&routeToString, &deleteRoute, &compareRoutes);
    tempDoc->tracks = initializeList(&trackToString, &deleteTrack, &compareTracks);


    strcpy(tempString, gpxString);
    pt = strtok (tempString,",");
    while (pt != NULL) {
      //  int a = atoi(pt);
        strcpy(allValues[i], pt);
     //   printf("%s\n", allValues[i]);
        i++;
        pt = strtok (NULL, ",");
    }

    strcpy(fileName, allValues[0]);
    strcpy(namespaceValue, allValues[1]);
    strcpy(versionValue, allValues[2]);
    strcpy(creatorValue, allValues[3]);

    // adding values to the gpx doc

    // converting the version from string to double
    
    versionResult = strtod(versionValue, &eptr);
   // printf("TESTING %f\n", versionResult);
    //sprintf(number, "%.1f",versionResult);
    //printf("%s\n", number);
    
    //versionResult = strtod(number, &eptr);

    strcpy(tempDoc->namespace, namespaceValue);
    strcpy(tempDoc->creator, creatorValue);
    tempDoc->version = versionResult;

    
    free(tempString);

    isValid = writeGPXdoc(tempDoc, fileName);

    if(isValid == false){
        strcpy(returnString, "false");
    } else if (isValid == true){
        strcpy(returnString, fileName);
    }
   // printf("TESTING RETURNED DOCUMENT %s %f %s\n", tempDoc->namespace, tempDoc->creator, tempDoc->version);
    return returnString;
}



Waypoint* JSONtoWaypoint(const char* gpxString){
    return NULL;
}

Route* JSONtoRoute(const char* gpxString){
    return NULL;
}


// MODULE THREE BONUS FUNCTIONS END

/************************************** ASSIGNMENT TWO FUNCTIONS END **************************/

GPXdoc* createGPXdoc(char* fileName){

    if(fileName == NULL){
        return NULL;
    }
    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;
    GPXdoc *theGPXDoc = (GPXdoc*)malloc(sizeof(GPXdoc));

   // Track *testTrack;
  //  Waypoint *testWpt;

    //initializing the GPXDoc Struct
    strcpy(theGPXDoc->namespace, "namespace");
    theGPXDoc->version = 0.0;
    theGPXDoc->creator = (char*) malloc(sizeof(char) * 100);
    theGPXDoc->waypoints = initializeList(&waypointToString, &deleteWaypoint, &compareWaypoints);
    theGPXDoc->routes = initializeList(&routeToString, &deleteRoute, &compareRoutes);
    theGPXDoc->tracks = initializeList(&trackToString, &deleteTrack, &compareTracks);

    /*parse the file and get the DOM */
    // creating the XML tree
    doc = xmlReadFile(fileName, NULL, 0);

    if (doc == NULL) {
      //  printf("Invalid file");
        deleteGPXdoc(theGPXDoc);
        return NULL;
    }

    /*Get the root element node */
    root_element = xmlDocGetRootElement(doc);

    // initializing the namespace
    strcpy(theGPXDoc->namespace, (char*)root_element->properties->children->content);

    if(strcmp((char*)root_element->name, "gpx") == 0){
        print_element_names(root_element, theGPXDoc);
     //   printf("GPX Doc Test: Creator = %s\n", theGPXDoc->creator);

        // JAMES VICTORIA ROUTE TESTING BELOW
      //  Route *testRoute = getFromBack(theGPXDoc->routes);
       // printf("%s\n", toString(testRoute->waypoints));
       // Waypoint *testRte = getFromBack(testRoute->waypoints);
       // printf("Testing route point data: lon = %f, lat = %f\n", testRte->longitude, testRte->latitude);

        // TRACK GPX FILE TESTIN BELOW
    //    testTrack = getFromFront(theGPXDoc->tracks);
     //   printf("Track to be deleted: %s\n", testTrack->name);
     //   TrackSegment *aSegment = getFromBack(testTrack->segments);
     //   Waypoint *aWpt = getFromBack(aSegment->waypoints);
       // List *allOtherData = aWpt->otherData;
     //   List *allSegments = testTrack->segments;
      //  TrackSegment *tempSgmnt = getFromBack(testTrack->segments);

     //   printf("%s\n", toString(allOtherData));
     //   Waypoint *tmpWpt = getFromBack(tempSgmnt->waypoints);
     //   printf("Waypoint before deletion: %s\n", tmpWpt->name);
        //char tempString[100];
        //strcpy(tempString, waypointToString(tmpWpt));
        //printf("Testing toString method for waypoints: %s\n", tempString);
        //deleteTrack(testTrack);
      // deleteWaypoint(tmpWpt);
       // printf("Waypoint after deletion: %s\n", tmpWpt->name);




        // execute parsing code below
    } else {
     //   printf("Invalid input\n");
    }



 //   printf("made it to after the parsing\n");
    /*free the document */
    xmlFreeDoc(doc);
    /*
     *Free the global variables that may
     *have been allocated by the parser.
     */
    xmlCleanupParser();

    return theGPXDoc;
}

char *GPXdocToString(GPXdoc* doc){
    if(doc == NULL){
        char *emptyString = ((char*) malloc(sizeof(char)));
        return emptyString;
    } else {
        char *toString = (char*) malloc(sizeof(char) * 100);

        strcpy(toString, "This is the GPXDoc struct\n");

        return toString;
    }

}

void deleteGPXdoc(GPXdoc* doc){
    if(doc == NULL){
        return;
    } else {
        if(doc->creator){
        free(doc->creator);
        doc->creator = NULL;
        }

     //   printf("made it to before deleting waypoints\n");
        if(doc->waypoints){
            freeList(doc->waypoints);
        }
      //  printf("made it to after deleting waypoints\n");
        if(doc->routes){
           //     printf("BEFORE DELETING ROUTES\n");
            freeList(doc->routes);
        }
     //   printf("made it to after deleting routes\n");
      //  printf("made it to before deleting tracks\n");
        if(doc->tracks){
            freeList(doc->tracks);
        }
      //  printf("made it to after deleting tracks\n");
        free(doc);
    }
}

/** ASSIGHMENT THREE NEW FUNCTIONS BELOW **/
char *newCreateGPX(char* fileName){
	char* returnString = (char*)malloc(sizeof(char) * 300);
	//char* returnString = (char*)malloc(sizeof(char) * 300);
	GPXdoc *tempDoc = NULL;

	tempDoc = createValidGPXdoc(fileName, "gpx.xsd");
    if(tempDoc == NULL){
       // printf("INVALID FILE\n");
        strcpy(returnString, "INVALID");
    } else{
        printf("VALID FILE\n");
        strcpy(returnString, GPXtoJSON(tempDoc));
	    deleteGPXdoc(tempDoc);   
    }


	// the input is the file name from the front ending
	// run createGPX with that file name and create a GPXdoc object
	// then convert the gpxddoc to json and store that in the returnString variables
	// free the created GPX doc before returning by calling the delete function
	return returnString;
}

char *newTrackToJSON(char* fileName){
		// accepts filename, it will be a gpx file
		// create a gpx document from the fileName
		// get all the routes from the gpx fileName
		// convert
		char *returnString = (char*)malloc(sizeof(char) * 3000);
		GPXdoc *tempDoc = NULL;
		List *allTracks = NULL;

		tempDoc = createGPXdoc(fileName);
		if(tempDoc->tracks != NULL){
			allTracks = tempDoc->tracks;
		}

		strcpy(returnString, trackListToJSON(allTracks));

		deleteGPXdoc(tempDoc);

		return returnString;
}

char *newRouteToJSON(char* fileName){
		// accepts filename, it will be a gpx file
		// create a gpx document from the fileName
		// get all the routes from the gpx fileName
		// convert
		char *returnString = (char*)malloc(sizeof(char) * 3000);
		GPXdoc *tempDoc = NULL;
		List *allRoutes = NULL;

		tempDoc = createGPXdoc(fileName);
		if(tempDoc->routes != NULL){
			allRoutes = tempDoc->routes;
		}

		strcpy(returnString, routeListToJSON(allRoutes));

		deleteGPXdoc(tempDoc);

		return returnString;
}

char *dataToJSON(GPXData *theData, char *inputName){
    char *returnString = (char*)malloc(sizeof(char) * 1000);

        if(strcmp(theData->name, "") == 0){
        // route does not have a name
        strcpy(returnString, "None");
        } else if (strcmp(theData->name, "") != 0){
        // route has a name
        //strcpy(rteName, rt->name);
        //routeLen = getRouteLen(rt);
       // routeLen = round10(routeLen);
      //  numPoints = getLength(rt->waypoints);
     //   loopVal = isLoopRoute(rt, 10);

       // sprintf(intToString, "%d", numPoints);
       // sprintf(floatToString, "%.1f", routeLen);


            strcpy(returnString, "");
            strcat(returnString, "{\"name\":");
            strcat(returnString, "\"");
            strcat(returnString, theData->name);
            strcat(returnString, "\"");
            strcat(returnString, ",\"value\":");
            strcat(returnString, "\"");
            strcat(returnString, theData->value);
            strcat(returnString, "\"");
            strcat(returnString, ",\"componentName\":");
            strcat(returnString, "\"");
            strcat(returnString, inputName);
            strcat(returnString, "\"");
            strcat(returnString, "}");

        }

    return returnString;
}

char *gpxDataListToJSON(List *theDataList, char *componentName){
    char *returnString = (char*)malloc(sizeof(char) * 2000);
    GPXData *currentData = NULL;
    int dataLen = 0;
    int i = 1;
   // int i= 1;
    ListIterator listIter;
    ListIterator *listIterPtr = NULL;

    // iterate through the list of routes
    // on each iteration store the result of routeToJSON in an array of strings

    // error checking
    if(theDataList == NULL){
        strcpy(returnString, "[]");
        return returnString;
    } else {
        strcpy(returnString, "");
        strcat(returnString, "[");
    }

    dataLen = getLength((List*)theDataList);


    listIter = createIterator((List*)theDataList);
    listIterPtr = &listIter;

    currentData = (GPXData*) nextElement(listIterPtr);

    for(; currentData != NULL; currentData = (GPXData*) nextElement(listIterPtr)){
        strcat(returnString, dataToJSON(currentData, componentName));
        if(i == dataLen){
        strcat(returnString, "]");
        } else {
             strcat(returnString, ",");
             i++;
        }
    }

    return returnString;
}

char *routeDataListToJSON(char *fileName){
    char *returnString = (char*)malloc(sizeof(char) * 2000);
    GPXdoc *tempDoc = NULL;
    Route *currentRoute = NULL;
   //s GPXData *tempData = NULL;
    List *allRoutes = NULL;
    List *currentDataList = NULL;
    ListIterator listIter;
    ListIterator *listIterPtr = NULL;
   // ListIterator secondIter;
   // ListIterator *secondIterPtr = NULL;

    tempDoc = createGPXdoc(fileName);

    allRoutes = tempDoc->routes;

    listIter = createIterator(allRoutes);
    listIterPtr = &listIter;

    currentRoute = (Route*) nextElement(listIterPtr);

    for(; currentRoute != NULL; currentRoute = (Route*)nextElement(listIterPtr)){
        if(currentRoute->otherData != NULL){

            currentDataList = currentRoute->otherData;
            strcpy(returnString, gpxDataListToJSON(currentDataList, currentRoute->name));
        }
    }

    // create a gpx object from the filename 
    // grab the routes list
    // iterate through each route and grab the otherData list 
    // run the gpxDataListToJSON function


    return returnString;
}

char *waypointToJSON(char *rteName, char *fileName){
    char *returnString = (char*) malloc(sizeof(char) * 5000);
    char  wptName[300];

    // one approach to this task is to create a GPX doc from the filename, then iterate through all the routes
    // when the route with a matching rteName is found then grab its waypoints / routepoints 
    // convert the routepoints into a JSON formatted object, similar to routeListToJSON

    GPXdoc *tempDoc = NULL;
    List *allRoutes = NULL;
    ListIterator iter;
    ListIterator *iterPtr = NULL;
    Route *currentRoute = NULL;
    char *fileRoute = (char*) malloc(sizeof(char) * 1000);
    int i = 0;
    int listLen = 0;
    int wptIndex = 0;
    char intToString[100];
    char convertedLat[100];
    char convertedLon[100];

    printf("TESTING\n");

    strcpy(fileRoute, "uploads/");
    strcat(fileRoute,fileName);

    printf("TESTING 2\n");

    tempDoc = createGPXdoc(fileRoute);
    allRoutes = tempDoc->routes;

    iter = createIterator(allRoutes);
    iterPtr = &iter;

    currentRoute = (Route*) nextElement(iterPtr);

    strcpy(returnString, "");
    strcat(returnString, "[");

    for(; currentRoute != NULL; currentRoute = (Route*)nextElement(iterPtr)){
        if(strcmp(currentRoute->name, rteName) == 0 ){
            
          // if this if statement is reached that means the current route is the one to be used
          
          if(currentRoute->waypoints != NULL){

             // List *allWaypoints = NULL;
              ListIterator wptIter;
              ListIterator *wptIterPtr = NULL;
              Waypoint *tempWpt = NULL;
              listLen = getLength(currentRoute->waypoints);
              wptIter = createIterator(currentRoute->waypoints);
              wptIterPtr = &wptIter;

              tempWpt = (Waypoint*) nextElement(wptIterPtr);

              for(; tempWpt != NULL; tempWpt = (Waypoint*) nextElement(wptIterPtr)){
                    // looping through the current routes waypoints
                    // route has a name

                    strcpy(wptName, "");
                    
                    
                   // routeLen = getRouteLen(rt);
                   // routeLen = round10(routeLen);
                  //  numPoints = getLength(rt->waypoints);
                  //  loopVal = isLoopRoute(rt, 10);

                   // sprintf(intToString, "%d", numPoints);
                   // sprintf(floatToString, "%.1f", routeLen);


                  //  strcpy(returnString, "");
                    strcat(returnString, "{\"name\":");
                    strcat(returnString, "\"");
                 //   strcat(returnString, rteName);
                    strcat(returnString, wptName);
                    strcat(returnString, "\"");
                    strcat(returnString, ",\"point_index\":");

                    sprintf(intToString, "%d", wptIndex);
                    strcat(returnString, intToString);
                
                    strcat(returnString, ",\"latitude\":");
                    sprintf(convertedLat, "%f", tempWpt->latitude);
                    strcat(returnString, convertedLat);

                   // strcat(returnString, floatToString);
                    strcat(returnString, ",\"longitude\":");
                    sprintf(convertedLon, "%f", tempWpt->longitude);
                    strcat(returnString, convertedLon);

                    strcat(returnString, "}");
                

                

                    if(i == listLen - 1){
                    strcat(returnString, "]");
                    } else {
                        if(i >= 0){
                            strcat(returnString, ",");
                        
                        }
                        i++;
                        wptIndex++;
                    }
              }
          }

        }
    }

    deleteGPXdoc(tempDoc);
    free(fileRoute);
    printf("\n\n RETURN STRING: %s\n\n", returnString);

    return returnString;
}


char *trackDataListToJSON(char *fileName){
    char *returnString = (char*)malloc(sizeof(char) * 2000);
    GPXdoc *tempDoc = NULL;
    Track *currentTrack = NULL;
   //s GPXData *tempData = NULL;
    List *allTracks = NULL;
    List *currentDataList = NULL;
    ListIterator listIter;
    ListIterator *listIterPtr = NULL;
   // ListIterator secondIter;
   // ListIterator *secondIterPtr = NULL;

    tempDoc = createGPXdoc(fileName);

    allTracks = tempDoc->tracks;

    listIter = createIterator(allTracks);
    listIterPtr = &listIter;

    currentTrack = (Track*) nextElement(listIterPtr);

    for(; currentTrack != NULL; currentTrack = (Track*)nextElement(listIterPtr)){
        if(currentTrack->otherData != NULL){

            currentDataList = currentTrack->otherData;
            strcpy(returnString, gpxDataListToJSON(currentDataList, currentTrack->name));
        }
    }

    // create a gpx object from the filename 
    // grab the routes list
    // iterate through each route and grab the otherData list 
    // run the gpxDataListToJSON function


    return returnString;
}

char *newAddRoute(char *routeJSON, char *routeWaypoints, char *fileName){
    GPXdoc *tempDoc = NULL;
    char *returnString = (char*) malloc(sizeof(char) * 1000);
    char *testString = (char*) malloc(sizeof(char) * 1000);
    strcpy(testString, routeWaypoints);
    double theValues[2000];
    char *pt;
    char *ptr;
    char allValues[100][200];
    int i = 0;
    int j = 0;
    int arrayLen = 0;
    Route *tempRoute = (Route*)malloc(sizeof(Route));
   // Waypoint *tempWaypoint = (Waypoint*)malloc(sizeof(Waypoint));

    //FOR TESTING 
   // strcpy(testString, "47.2,128.3,45.1,129.89");

    pt = strtok (testString,",");
    while (pt != NULL) {
      //  int a = atoi(pt);
       strcpy(allValues[i], pt);
       theValues[i] = strtod(allValues[i], &ptr);
       printf("%f\n", theValues[i]);
        i++;
        pt = strtok (NULL, ",");
    }

    i = 0;
    while(strcmp(allValues[i], "") != 0){
        arrayLen++;
        i++;
    }

    printf("ARRAY LEN = %d\n", arrayLen);
    tempRoute->name = (char*)malloc(sizeof(char) * 200);
    strcpy(tempRoute->name, routeJSON);
    tempRoute->waypoints = initializeList(&waypointToString, &deleteWaypoint, &compareWaypoints);
    tempRoute->otherData = initializeList(&gpxDataToString, &deleteGPXData, &compareGpxData);
    // the routeJSON will have the route name attached to it
    // routeWaypoints will have all the waypoints attached to it
    // parse through the routewaypoints, that are seperated by commas
    // e.g. lat,lon,lat,long
    // store the parsed values into an array
    // iterate through the array of doubles
    for(i = 0; i < arrayLen ; i++){
        // get the current latitude
        // also get the longitude at i++;
        double tempLat = theValues[i];
        j = i;
        j++;
        double tempLon = theValues[j];

        Waypoint *tempWpt = (Waypoint*)malloc(sizeof(Waypoint));
        tempWpt->otherData = initializeList(&gpxDataToString, &deleteGPXData, &compareGpxData);
        tempWpt->name = (char*)malloc(sizeof(char) * 100);
        strcpy(tempWpt->name, "");
        tempWpt->latitude = tempLat;
        printf("LAT = %f\n", tempWpt->latitude);
        tempWpt->longitude = tempLon;
        printf("LON = %f\n", tempWpt->longitude);
        insertBack(tempRoute->waypoints, tempWpt);

        i++;
    }

    //insertBack(tempDoc->routes, tempRoute);

    tempDoc = createGPXdoc(fileName);
    printf("BEFORE: %d\n", getLength(tempDoc->routes));
    insertBack(tempDoc->routes, tempRoute);
    printf("AFTER: %d\n", getLength(tempDoc->routes));

    strcpy(returnString, GPXtoJSON(tempDoc));

    return returnString;
    // on each iteration create a waypoint for each pair of values in the array
    // then create a waypoint for the pair
    // add the completed pair to the tempRoute->waypoints list 
    // create a gpx doc and add the route to the route list
    // save the gpx doc as a file and upload it to the server
    // send back the new gpx doc content as a string  
}

char *updateDoc(char *fileName){
    char *returnString = (char*)malloc(sizeof(char) * 200);
    GPXdoc *tempDoc = createGPXdoc(fileName);
    writeGPXdoc(tempDoc, fileName);

    strcpy(returnString, fileName);
    return returnString;
}




/**
 * Simple example to parse a file called "file.xml",
 * walk down the DOM, and print the name of the
 * xml elements nodes.
 * DELETE MAIN BEFORE SUBMITING
 */
