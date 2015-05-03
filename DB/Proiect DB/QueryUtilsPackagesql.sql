DROP TYPE ConductorInfoTable;
DROP TYPE StationInfoTable;
DROP TYPE ScheduleInfoTable;
DROP TYPE TrainInfoTable;
DROP TYPE TrackInfoTable;
DROP TYPE TrackInfo;
DROP TYPE TrainInfo;
DROP TYPE ScheduleInfo;
DROP TYPE StationInfo;
DROP TYPE ConductorInfo;
/
CREATE TYPE TrackInfo 
AS OBJECT
(
  trackID NUMBER,
  trackLength NUMBER,
  fromStation NUMBER,
  toStation NUMBER
);
/



CREATE TYPE TrackInfoTable
   AS TABLE OF TrackInfo;
/ 


CREATE TYPE StationInfo 
AS OBJECT
(
  stationID NUMBER,
  stationName VARCHAR2(30),
  stationAddress VARCHAR(30)
);
/



CREATE TYPE StationInfoTable
   AS TABLE OF StationInfo;
/ 



CREATE TYPE TrainInfo 
AS OBJECT
(
  trainID NUMBER,
  trainName VARCHAR2(30),
  numOfWagons NUMBER
);
/

CREATE TYPE TrainInfoTable
   AS TABLE OF TrainInfo;
/ 

CREATE TYPE ConductorInfo 
AS OBJECT
(
  conductorID NUMBER,
  firstName VARCHAR2(30),
  lastName VARCHAR2(30)
);
/

CREATE TYPE ConductorInfoTable
   AS TABLE OF ConductorInfo;
/ 



CREATE TYPE ScheduleInfo
AS OBJECT
(
  trainID NUMBER,
  trackID NUMBER,
  startHour NUMBER,
  stopHour NUMBER,
  conductorID NUMBER
);
/

CREATE TYPE ScheduleInfoTable
   AS TABLE OF ScheduleInfo;
/

CREATE OR REPLACE PACKAGE QUERY_UTILS
 IS
 
 FUNCTION getStationsAt(startRow NUMBER, rowCount NUMBER) RETURN StationInfoTable;
 FUNCTION getTracksAt(startRow NUMBER, rowCount NUMBER) RETURN TrackInfoTable;
 FUNCTION getTrainsAt(startRow NUMBER, rowCount NUMBER) RETURN TrainInfoTable;
 FUNCTION getConductorsAt(startRow NUMBER, rowCount NUMBER) RETURN ConductorInfoTable;
 
 
 FUNCTION getTracksBetweenStations(st1 VARCHAR, st2 VARCHAR, fromRow NUMBER, rowCount Number) Return TrackInfoTable;
 FUNCTION getTrainsBetweenStations(st1 VARCHAR, st2 VARCHAR, fromRow Number, rowCount Number) Return TrainInfoTable;
 FUNCTION getTrainsLeavingFromStation(st VARCHAR, startHour NUMBER, fromRow NUMBER, rowCount NUMBER) Return TrainInfoTable;
 FUNCTION getTRainsArrivingAtStation(st VARCHAR, stopHour NUMBER, fromRow NUMBER, rowCount NUMBER) RETURN TrainInfoTable;
 FUNCTION getSchedulesForTrain(trainName VARCHAR, fromRow NUMBER, rowCount NUMBER) RETURN ScheduleInfoTable;
 FUNCTION getSchedulesForConductor(firstName VARCHAR, lastName VARCHAR, fromRow NUMBER, rowCount NUMBER) RETURN ScheduleInfoTable;
 
END QUERY_UTILS;
/

CREATE OR REPLACE PACKAGE BODY QUERY_UTILS
 IS
  
 FUNCTION getStationIDForName(stName VARCHAR) RETURN NUMBER
 IS
   v_result NUMBER := 0;
 BEGIN
   SELECT stationID into v_result FROM STATIONS
   WHERE TRIM(stationName) LIKE TRIM(stName);
   
   RETURN v_result;
 END;
   
 FUNCTION getTrainIDForName(trName VARCHAR) RETURN NUMBER
 IS
   v_result NUMBER := 0;
 BEGIN
   SELECT trainID into v_result FROM TRAINS
   WHERE TRIM(trainName) LIKE TRIM(trName);
   
   RETURN v_result;
 END;
 
 
  FUNCTION getStationsAt(startRow NUMBER, rowCount NUMBER) RETURN StationInfoTable
  IS
  
    CURSOR curs(startR NUMBER, countR NUMBER) IS
    
     SELECT * FROM STATIONS
     WHERE stationID BETWEEN startRow AND startRow+rowCount;
 
  resultTable StationInfoTable := StationInfoTable(); 
    --ares StationInfo;
 BEGIN
 
  FOR rec IN curs(startRow, rowCount) LOOP
    BEGIN
      resultTable.extend;
      resultTable(resultTable.last) := StationInfo(rec.stationID, rec.stationName, rec.stationAddress);
    END;
  END LOOP;
  RETURN resultTable;
 END;
 
 
 
  FUNCTION getTracksAt(startRow NUMBER, rowCount NUMBER) RETURN TrackInfoTable
  IS
    CURSOR curs(startR NUMBER, countR NUMBER) IS
     SELECT * FROM TRACKS
     WHERE trackID BETWEEN startRow AND startRow+rowCount;
 
  resultTable TrackInfoTable := TrackInfoTable(); 
    --ares StationInfo;
 BEGIN
 
  FOR rec IN curs(startRow, rowCount) LOOP
    BEGIN
      resultTable.extend;
      resultTable(resultTable.last) := TrackInfo(rec.trackID, rec.trackLength, rec.fromStation, rec.toStation);
    END;
  END LOOP;
  RETURN resultTable;
 END;
 

   FUNCTION getTrainsAt(startRow NUMBER, rowCount NUMBER) RETURN TrainInfoTable
   IS
    CURSOR curs(startR NUMBER, countR NUMBER) IS
     SELECT * FROM TRAINS
     WHERE trainID BETWEEN startRow AND startRow+rowCount;
 
  resultTable TrainInfoTable := TrainInfoTable(); 
    --ares StationInfo;
 BEGIN
 
  FOR rec IN curs(startRow, rowCount) LOOP
    BEGIN
      resultTable.extend;
      resultTable(resultTable.last) :=  TrainInfo(rec.trainID, rec.trainName, rec.numOfWagons);
    END;
  END LOOP;
  RETURN resultTable;
 END;


  FUNCTION getConductorsAt(startRow NUMBER, rowCount NUMBER) RETURN ConductorInfoTable
   IS
    CURSOR curs(startR NUMBER, countR NUMBER) IS
     SELECT * FROM CONDUCTORS
     WHERE conductorID BETWEEN startRow AND startRow+rowCount;
 
  resultTable ConductorInfoTable := ConductorInfoTable(); 
    --ares StationInfo;
 BEGIN
 
  FOR rec IN curs(startRow, rowCount) LOOP
    BEGIN
      resultTable.extend;
      resultTable(resultTable.last) := ConductorInfo(rec.conductorID, rec.firstName, rec.lastName);
    END;
  END LOOP;
  RETURN resultTable;
 END;
   
   
 FUNCTION getTracksBetweenStations(st1 VARCHAR, st2 VARCHAR, fromRow NUMBER, rowCount Number) Return TrackInfoTable
 IS
  
  CURSOR curs(firstStation VARCHAR2, lastStation VARCHAR2, startR NUMBER, countR NUMBER) IS
    SELECT outer.*
      FROM (SELECT ROWNUM rn, inner.*
                  FROM (  SELECT t.trackID, t.trackLength, t.fromStation, t.toStation
                          FROM TRACKS t, STATIONS s1, STATIONS s2
                          WHERE TRIM(s1.stationName) LIKE TRIM(firstStation) AND
                                TRIM(s2.stationName) LIKE TRIM(lastStation) AND
                                t.fromStation = s1.stationID AND
                                t.toStation = s2.stationID
                          ORDER BY t.trackID) inner) outer
    WHERE outer.rn >=startR  AND outer.rn <= startR+countR;
 
  resultTable TrackInfoTable := TrackInfoTable(); 
 
 BEGIN
    FOR rec IN curs(st1, st2, fromRow, rowCount) LOOP
      BEGIN
        resultTable.extend;
        resultTable(resultTable.last) := TrackInfo(rec.trackID, rec.trackLength, rec.fromStation, rec.toStation);
      END;
    END LOOP;
 
    RETURN resultTable;
 
 END;
 
 FUNCTION getTrainsBetweenStations(st1 VARCHAR, st2 VARCHAR, fromRow Number, rowCount Number) Return TrainInfoTable
 IS
  CURSOR curs(firstStation VARCHAR2, lastStation VARCHAR2, startR NUMBER, countR NUMBER) IS
    SELECT outer.*
      FROM (SELECT ROWNUM rn, inner.*
                  FROM (  SELECT t.trainID, t.trainName, t.numOfWagons
                          FROM TRAINS t, TRACKS trks, STATIONS s1, STATIONS s2, TRAIN_SCHEDULES sch
                          WHERE
                          sch.trackID = trks.trackID AND trks.fromStation = s1.stationID 
                          AND trks.toStation = s2.stationID AND TRIM(s1.stationName) LIKE TRIM(st1)
                          AND TRIM(s2.stationName) LIKE TRIM(s2.stationName) 
                          AND sch.trainID = t.trainID
                          ORDER BY t.trainID) inner) outer
    WHERE outer.rn >=startR  AND outer.rn <= startR+countR;
 
  resultTable TrainInfoTable := TrainInfoTable(); 
 
 BEGIN
 
    FOR rec IN curs(st1, st2, fromRow, rowCount) LOOP
      BEGIN
        resultTable.extend;
        resultTable(resultTable.last) := TrainInfo(rec.trainID, rec.trainName, rec.numOfWagons);
      END;
    END LOOP;
 
    RETURN resultTable;
 
 END;
 
 
 
 FUNCTION getTrainsLeavingFromStation(st VARCHAR, startHour NUMBER, fromRow NUMBER, rowCount NUMBER) Return TrainInfoTable
 IS
 CURSOR curs(firstStation VARCHAR2, startHour NUMBER, startR NUMBER, countR NUMBER) IS
    SELECT outer.*
      FROM (SELECT ROWNUM rn, inner.*
                  FROM (  SELECT t.trainID, t.trainName, t.numOfWagons
                          FROM TRAINS t, TRACKS trks, STATIONS s1, TRAIN_SCHEDULES sch
                          WHERE
                          sch.trackID = trks.trackID AND trks.fromStation = s1.stationID 
                          AND TRIM(s1.stationName) LIKE TRIM(s1.stationName) 
                          AND sch.trainID = t.trainID
                          AND sch.startHour = startHour
                          ORDER BY t.trainID) inner) outer
    WHERE outer.rn >=startR  AND outer.rn <= startR+countR;
 
  resultTable TrainInfoTable := TrainInfoTable(); 
 
 BEGIN
 
    FOR rec IN curs(st, startHour, fromRow, rowCount) LOOP
      BEGIN
        resultTable.extend;
        resultTable(resultTable.last) := TrainInfo(rec.trainID, rec.trainName, rec.numOfWagons);
      END;
    END LOOP;
 
    RETURN resultTable;
 
 END;
 
 FUNCTION getTRainsArrivingAtStation(st VARCHAR, stopHour NUMBER, fromRow NUMBER, rowCount NUMBER) RETURN TrainInfoTable
 IS
 CURSOR curs(firstStation VARCHAR2, stopHour NUMBER, startR NUMBER, countR NUMBER) IS
    SELECT outer.*
      FROM (SELECT ROWNUM rn, inner.*
                  FROM (  SELECT t.trainID, t.trainName, t.numOfWagons
                          FROM TRAINS t, TRACKS trks, STATIONS s1, TRAIN_SCHEDULES sch
                          WHERE
                          sch.trackID = trks.trackID AND trks.fromStation = s1.stationID 
                          AND TRIM(s1.stationName) LIKE TRIM(s1.stationName) 
                          AND sch.trainID = t.trainID
                          AND sch.stopHour = stopHour
                          ORDER BY t.trainID) inner) outer
    WHERE outer.rn >=startR  AND outer.rn <= startR+countR;
 
  resultTable TrainInfoTable := TrainInfoTable(); 
 
 BEGIN
 
    FOR rec IN curs(st, stopHour, fromRow, rowCount) LOOP
      BEGIN
        resultTable.extend;
        resultTable(resultTable.last) := TrainInfo(rec.trainID, rec.trainName, rec.numOfWagons);
      END;
    END LOOP;
 
    RETURN resultTable;
 
 END;
 
 
 FUNCTION getSchedulesForTrain(trainName VARCHAR, fromRow NUMBER, rowCount NUMBER) RETURN ScheduleInfoTable
 IS
  CURSOR curs(trainName VARCHAR2, startR NUMBER, countR NUMBER) IS 
  SELECT outer.*
      FROM (SELECT ROWNUM rn, inner.*
                  FROM (  
                  
        SELECT sch.trainID, sch.trackID, sch.startHour, sch.stopHour, sch.conductorID
        FROM TRAIN_SCHEDULES sch, TRAINS t
        WHERE t.trainID = sch.trainID AND TRIM(t.trainName) LIKE TRIM(trainName)
        ORDER BY sch.trainID
                        
                        ) inner) outer
    WHERE outer.rn >=startR  AND outer.rn <= startR+countR;
    
    
   resultT ScheduleInfoTable := ScheduleInfoTable();
   
   v_trainID NUMBER;
   
 BEGIN
 
    FOR rec IN curs(trainName, fromRow, rowCount) LOOP
      BEGIN
      resultT.extend;
      resultT(resultT.last) := ScheduleInfo(rec.trainID, rec.trackID, rec.startHour, rec.stopHour, rec.conductorID);
      END;
    END LOOP;
    
    RETURN resultT;
    
  END;
  
 
 FUNCTION getSchedulesForConductor(firstName VARCHAR, lastName VARCHAR, fromRow NUMBER, rowCount NUMBER) RETURN ScheduleInfoTable
 IS
 CURSOR curs(firstName VARCHAR2, lastName VARCHAR2, startR NUMBER, countR NUMBER) IS 
  SELECT outer.*
      FROM (SELECT ROWNUM rn, inner.*
                  FROM (  
                  
        SELECT sch.trainID, sch.trackID, sch.startHour, sch.stopHour, sch.conductorID
        FROM TRAIN_SCHEDULES sch, CONDUCTORS cd
        WHERE cd.conductorID = sch.conductorID AND TRIM(cd.firstName) LIKE TRIM(firstName) 
        AND TRIM(cd.lastName) LIKE TRIM(lastName)
        ORDER BY sch.trainID
                        
                        ) inner) outer
    WHERE outer.rn >=startR  AND outer.rn <= startR+countR;
    
    
   resultT ScheduleInfoTable := ScheduleInfoTable();
   
   v_trainID NUMBER;
   
 BEGIN
 
    FOR rec IN curs(firstName, lastName, fromRow, rowCount) LOOP
      BEGIN
      resultT.extend;
      resultT(resultT.last) := ScheduleInfo(rec.trainID, rec.trackID, rec.startHour, rec.stopHour, rec.conductorID);
      END;
    END LOOP;
    
    RETURN resultT;
    
  END;
 
END QUERY_UTILS;
/


