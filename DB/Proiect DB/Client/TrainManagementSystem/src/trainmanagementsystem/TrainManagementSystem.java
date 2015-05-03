/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package trainmanagementsystem;

import models.*;
import managers.*;
import java.util.*;
/**
 *
 * @author costin
 */
public class TrainManagementSystem {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws Exception {
        // TODO code application logic here
        
        //List<Station> list1 = ApiManager.getSharedInstance().getStationsAt(0, 10);
        //System.out.println(list1);
        
        
        Station s = new Station();
        s.setAddress("Another address1");
        s.setName("Another name1");
        
        Train t = new Train();
        t.setID(1);
        t.setName("Chuchuu");
        t.setType(1);
        t.setNumOfWagons(100);
        
        Track tr = new Track();
        tr.setLength(10);
        tr.setSourceID(5);
        tr.setDestinationID(10);
        
        Conductor c = new Conductor();
        c.setFirstName("Mr.2");
        c.setLastName("Mario2");
        
        TrainSchedule ts = new TrainSchedule();
        ts.setConductorID(1);
        ts.setStartHour(10);
        ts.setStopHour(12);
        ts.setTrackID(3);
        ts.setTrainID(2);
        
        /*ApiManager.getSharedInstance().insertNewTrain(t);
        ApiManager.getSharedInstance().insertNewTrack(tr);
        ApiManager.getSharedInstance().insertNewConductor(c);
        ApiManager.getSharedInstance().insertNewSchedule(ts);
        */
        
        ApiManager.getSharedInstance().alterTrain(t);
        
        List<Train> list2 = ApiManager.getSharedInstance().getTrainsAt(0, 10);
        System.out.println(list2);
        
    }
    
}
