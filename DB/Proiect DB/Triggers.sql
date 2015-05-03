CREATE OR REPLACE TRIGGER stationsBeforeInsert
BEFORE INSERT
   ON STATIONS
   FOR EACH ROW
  
DECLARE

  v_maxId NUMBER;

BEGIN

   SELECT MAX(stationID)+1 INTO v_maxID
   FROM STATIONS;
   
   IF v_maxID IS NULL THEN
    v_maxID := 1;
   END IF;
   
   :new.stationID := v_maxId;
   
END;
/

CREATE OR REPLACE TRIGGER tracksBeforeInsert
BEFORE INSERT
   ON TRACKS
   FOR EACH ROW
  
DECLARE

  v_maxId NUMBER;

BEGIN

   SELECT MAX(trackID)+1 INTO v_maxID
   FROM TRACKS;
   
   IF v_maxID IS NULL THEN
    v_maxID := 1;
   END IF;
   
   :new.trackID := v_maxId;
   
END;
/

CREATE OR REPLACE TRIGGER trainsBeforeInsert
BEFORE INSERT
   ON TRAINS
   FOR EACH ROW
  
DECLARE

  v_maxId NUMBER;

BEGIN

   SELECT MAX(trainID)+1 INTO v_maxID
   FROM TRAINS;
   
   IF v_maxID IS NULL THEN
    v_maxID := 1;
   END IF;
   
   :new.trainID := v_maxId;
   
END;
/


CREATE OR REPLACE TRIGGER condsBeforeInsert
BEFORE INSERT
   ON CONDUCTORS
   FOR EACH ROW
  
DECLARE

  v_maxId NUMBER;

BEGIN

   SELECT MAX(conductorID)+1 INTO v_maxID
   FROM CONDUCTORS;
   
   IF v_maxID IS NULL THEN
    v_maxID := 1;
   END IF;
   
   :new.conductorID := v_maxId;
   
END;
/
