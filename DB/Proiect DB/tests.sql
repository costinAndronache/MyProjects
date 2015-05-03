DROP TABLE TRAIN_SCHEDULES;
DROP TABLE TRACKS;
DROP TABLE STATIONS;
DROP TABLE TRAINS;
DROP TABLE CONDUCTORS;
/
COMMIT;


select object_name, object_type
from dba_objects
where object_name||object_type in
   (select object_name||object_type 
    from dba_objects
    where owner = 'SYS')
and owner = 'SYSTEM'; 