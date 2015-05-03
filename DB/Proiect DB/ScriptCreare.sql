DROP TABLE TRAIN_SCHEDULES;
DROP TABLE TRAINS;
DROP TABLE TRACKS;
DROP TABLE STATIONS;
DROP TABLE CONDUCTORS;

CREATE TABLE STATIONS
( stationID NUMBER PRIMARY KEY,
  stationAddress VARCHAR2(30) UNIQUE,
  stationName VARCHAR2(30) UNIQUE
);
/


CREATE TABLE TRACKS
(
  trackID NUMBER PRIMARY KEY,
  trackLength NUMBER NOT NULL,
  fromStation NUMBER,
  toStation NUMBER,
  
  CONSTRAINT fk_fromStation FOREIGN KEY (fromStation) REFERENCES STATIONS(stationID),
  CONSTRAINT fk_toStation FOREIGN KEY (toStation) REFERENCES STATIONS(stationID)
);
/

CREATE TABLE TRAINS
(
  trainID NUMBER PRIMARY KEY,
  trainType NUMBER,
  trainName VARCHAR2(30) UNIQUE,
  numOfWagons NUMBER DEFAULT 1
);
/

CREATE TABLE CONDUCTORS
(
 conductorID NUMBER PRIMARY KEY,
 firstName VARCHAR2(30),
 lastName VARCHAR2(30),
 
 CONSTRAINT unique_Name UNIQUE (firstName, lastName)
 
);
/

CREATE TABLE TRAIN_SCHEDULES
(
  trainID NUMBER,
  trackID NUMBER,
  conductorID NUMBER,
  startHour NUMBER,
  stopHour NUMBER,
  
  CONSTRAINT fk_trainID FOREIGN KEY (trainID) REFERENCES TRAINS(trainID),
  CONSTRAINT fk_conductorID FOREIGN KEY (conductorID) REFERENCES CONDUCTORS(conductorID),
  CONSTRAINT fk_trackID FOREIGN KEY (trackID) REFERENCES TRACKS(trackID),
  
  CONSTRAINT unique_trainStart UNIQUE (trainID, startHour), --de adaugat conductorID
  CONSTRAINT unique_trainCond UNIQUE(trainID, conductorID)
  
);

/

DROP INDEX tracks_FromTo;
CREATE INDEX tracks_FromTo ON TRACKS(fromStation, toStation);
/

DROP INDEX schedules_trackStart;
CREATE INDEX schedules_trackStart ON TRAIN_SCHEDULES(trackID, startHour);
/


DROP INDEX unique_stationName;
CREATE UNIQUE INDEX unique_stationName ON STATIONS(TRIM(stationName));
/

DROP INDEX unique_trainName;
CREATE UNIQUE INDEX unique_trainName ON TRAINS(TRIM(trainName));
/

COMMIT;
