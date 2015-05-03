BEGIN

  FOR counter IN 1 .. 500000 LOOP
    BEGIN
    INSERT INTO STATIONS VALUES(counter, 'Address' || counter, 'Name' || counter);
    END;
  END LOOP;

END;
/

COMMIT;

SELECT * FROM TRACKS;
SELECT * FROM CONDUCTORS;

INSERT INTO TRACKS VALUES(1, 1, 1, 2);
INSERT INTO TRACKS(trackLength, fromStation, toStation) VALUES(1, 1, 3);
INSERT INTO TRACKS(trackLength, fromStation, toStation) VALUES(2, 1, 2);
INSERT INTO TRACKS(trackLength, fromStation, toStation) VALUES(3, 1, 6);
INSERT INTO TRACKS(trackLength, fromStation, toStation) VALUES(4, 1, 8);
INSERT INTO TRACKS(trackLength, fromStation, toStation) VALUES(4, 1, 9);
INSERT INTO TRACKS(trackLength, fromStation, toStation) VALUES(4, 2, 10);
INSERT INTO TRACKS(trackLength, fromStation, toStation) VALUES(4, 3, 4);



INSERT INTO TRAINS(trainType, trainName, numOfWagons) VALUES(1, 'Train13', 4); 
INSERT INTO TRAINS(trainType, trainName, numOfWagons) VALUES(1, 'Train14', 4);
INSERT INTO TRAINS(trainType, trainName, numOfWagons) VALUES(1, 'Train15', 4);
INSERT INTO TRAINS(trainType, trainName, numOfWagons) VALUES(1, 'Train16', 4);
INSERT INTO TRAINS(trainType, trainName, numOfWagons) VALUES(1, 'Train17', 4);
INSERT INTO TRAINS(trainType, trainName, numOfWagons) VALUES(1, 'Train18', 4);



INSERT INTO STATIONS(stationName, stationAddress) VALUES('newStation1', 'newAddress6');
INSERT INTO STATIONS(stationName, stationAddress) VALUES('newStation2', 'newAddress5');
INSERT INTO STATIONS(stationName, stationAddress) VALUES('newStation3', 'newAddress4');
INSERT INTO STATIONS(stationName, stationAddress) VALUES('newStation4', 'newAddress3');
INSERT INTO STATIONS(stationName, stationAddress) VALUES('newStation5', 'newAddress2');
INSERT INTO STATIONS(stationName, stationAddress) VALUES('newStation6', 'newAddress1');



INSERT INTO CONDUCTORS(firstName, lastName) VALUES('SS1', 'SS6');
INSERT INTO CONDUCTORS(firstName, lastName) VALUES('SS2', 'SS5');
INSERT INTO CONDUCTORS(firstName, lastName) VALUES('SS3', 'SS4');
INSERT INTO CONDUCTORS(firstName, lastName) VALUES('SS4', 'SS3');
INSERT INTO CONDUCTORS(firstName, lastName) VALUES('SS5', 'SS2');
INSERT INTO CONDUCTORS(firstName, lastName) VALUES('SS6', 'SS1');



INSERT INTO TRAIN_SCHEDULES(trainID, trackID, conductorID, startHour, stopHour) VALUES(1, 1, 1, 1, 10);
INSERT INTO TRAIN_SCHEDULES(trainID, trackID, conductorID, startHour, stopHour) VALUES(2, 1, 1, 1, 10);
INSERT INTO TRAIN_SCHEDULES(trainID, trackID, conductorID, startHour, stopHour) VALUES(3, 1, 1, 1, 10);
INSERT INTO TRAIN_SCHEDULES(trainID, trackID, conductorID, startHour, stopHour) VALUES(4, 1, 1, 1, 10);
INSERT INTO TRAIN_SCHEDULES(trainID, trackID, conductorID, startHour, stopHour) VALUES(5, 1, 1, 1, 10);


/
COMMIT;