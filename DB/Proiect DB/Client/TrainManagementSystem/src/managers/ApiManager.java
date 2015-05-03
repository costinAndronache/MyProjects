/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package managers;
import models.*;
import java.sql.*;
import java.util.*;

/**
 *
 * @author costin
 */
public class ApiManager 
{
    private static ApiManager sharedInstance = null;

    private final Connection conn;
    
    private ApiManager() throws Exception
    {
        DriverManager.registerDriver (new oracle.jdbc.OracleDriver());
        this.conn = DriverManager.getConnection
       ("jdbc:oracle:thin:@localhost:1521:xe", "COSTIN", "mingming");
    }
    
    public static ApiManager getSharedInstance() throws Exception
    {
        if(sharedInstance == null)
        {
            sharedInstance = new ApiManager();
        }
        
        return sharedInstance;
    }
    
    public List<Station> getStationsAt(int startRow, int rowCount) throws Exception
    {
        List<Station> result = new ArrayList<>();
        PreparedStatement stmt = this.conn.prepareStatement
        ("SELECT * FROM TABLE(QUERY_UTILS.getStationsAt(?, ?))");
        stmt.setInt(1, startRow);
        stmt.setInt(2, rowCount);
        
        ResultSet rs = stmt.executeQuery();
        
        return buildStationListFromSet(rs);
    }
    
    public List<Track> getTracksAt(int startRow, int rowCount) throws Exception
    {
        List<Track> result = new ArrayList<>();
        PreparedStatement stmt = this.conn.prepareStatement
        ("SELECT * FROM TABLE(QUERY_UTILS.getTracksAt(?, ?))");
        stmt.setInt(1, startRow);
        stmt.setInt(2, rowCount);
        
        ResultSet rs = stmt.executeQuery();
        
        return buildTrackListFromSet(rs);
    }
    
    
    public List<Train> getTrainsAt(int startRow, int rowCount) throws Exception
    {
        
        PreparedStatement stmt = this.conn.prepareStatement
        ("SELECT * FROM TABLE(QUERY_UTILS.getTrainsAt(?, ?))");
        stmt.setInt(1, startRow);
        stmt.setInt(2, rowCount);
        
        ResultSet rs = stmt.executeQuery();
        return buildTrainListFromSet(rs);
    }
    
    public List<Conductor> getConductorsAt(int startRow, int rowCount) throws Exception
    {
        PreparedStatement stmt = this.conn.prepareStatement
        ("SELECT * FROM TABLE(QUERY_UTILS.getConductorsAt(?, ?))");
        stmt.setInt(1, startRow);
        stmt.setInt(2, rowCount);
        
        ResultSet rs = stmt.executeQuery();
        
        return buildConductorListFromSet(rs);
    }
    
    
 /*
     FUNCTION getTracksBetweenStations(st1 VARCHAR, st2 VARCHAR, fromRow NUMBER, rowCount Number) 
    Return TrackInfoTable;
    */ 
    
    public List<Track> getTracksBetweenStations(String st1, String st2, int fromRow, int count)
    throws Exception
    {
        PreparedStatement stmt = this.conn.prepareStatement
        ("SELECT * FROM TABLE(QUERY_UTILS.getTracksBetweenStations(?, ?, ?, ?))");
        stmt.setString(1, st1);
        stmt.setString(2, st2);
        stmt.setInt(3, fromRow);
        stmt.setInt(4, count);
        
        ResultSet rs = stmt.executeQuery();
        return buildTrackListFromSet(rs);
    }
    
/*    
   FUNCTION getTrainsBetweenStations(st1 VARCHAR, st2 VARCHAR, fromRow Number, rowCount Number) 
    Return TrainInfoTable;

    */
    
    public List<Train> getTrainsBetweenStations(String s1, String s2, int fromRow, int rowCount)
     throws Exception
    {
        PreparedStatement stmt = this.conn.prepareStatement
        ("SELECT * FROM TABLE(QUERY_UTILS.getTrainsBetweenStations(?, ?, ?, ?))");
        stmt.setString(1, s1);
        stmt.setString(2, s2);
        stmt.setInt(3, fromRow);
        stmt.setInt(4, rowCount);
        
        ResultSet rs = stmt.executeQuery();
        return buildTrainListFromSet(rs);
    }
    
 /*
  FUNCTION getTrainsLeavingFromStation(st VARCHAR, startHour NUMBER, fromRow NUMBER, rowCount NUMBER) 
    Return TrainInfoTable;
    */
    
    public List<Train> getTrainsLeavingFromStation(String st, int startHour, int fromRow, int rowCount)
    throws Exception
    {
        PreparedStatement stmt = this.conn.prepareStatement
        ("SELECT * FROM TABLE(QUERY_UTILS.getTrainsLeavingFromStation(?, ?, ?, ?))");
        stmt.setString(1, st);
        stmt.setInt(2, startHour);
        stmt.setInt(3, fromRow);
        stmt.setInt(4, rowCount);
        
        ResultSet rs = stmt.executeQuery();
        return buildTrainListFromSet(rs);
    }
    

/*
FUNCTION getTRainsArrivingAtStation(st VARCHAR, stopHour NUMBER, fromRow NUMBER, rowCount NUMBER) 
    RETURN TrainInfoTable;
    */
    
   public List<Train> getTRainsArrivingAtStation(String st, int stopHour, int fromRow, int rowCount)
    throws Exception
    {
        PreparedStatement stmt = this.conn.prepareStatement
        ("SELECT * FROM TABLE(QUERY_UTILS.getTRainsArrivingAtStation(?, ?, ?, ?))");
        stmt.setString(1, st);
        stmt.setInt(2, stopHour);
        stmt.setInt(3, fromRow);
        stmt.setInt(4, rowCount);
        
        ResultSet rs = stmt.executeQuery();
        return buildTrainListFromSet(rs);
    }
    
/*
FUNCTION getSchedulesForTrain(trainName VARCHAR, fromRow NUMBER, rowCount NUMBER) 
   RETURN ScheduleInfoTable;
   */   
   
   public List<TrainSchedule> getSchedulesForTrain(String tName, int fromRow, int rowCount)
   throws Exception
   {
       PreparedStatement stmt = this.conn.prepareStatement
        ("SELECT * FROM TABLE(QUERY_UTILS.getSchedulesForTrain(?, ?, ?))");
        stmt.setString(1, tName);
        stmt.setInt(2, fromRow);
        stmt.setInt(3, rowCount);
        
        ResultSet rs = stmt.executeQuery();
        return buildScheduleListFromSet(rs);
   }
   
   
/*
 FUNCTION getSchedulesForConductor(firstName VARCHAR, lastName VARCHAR, fromRow NUMBER, rowCount NUMBER) 
   RETURN ScheduleInfoTable;

   */
   
   
   public List<TrainSchedule> getSchedulesForConductor(String firstName, String lastName,
                                                       int fromRow, int rowCount)
    throws Exception
   {
      PreparedStatement stmt = this.conn.prepareStatement
        ("SELECT * FROM TABLE(QUERY_UTILS.getSchedulesForConductor(?, ?, ?, ?))");
        stmt.setString(1, firstName);
        stmt.setString(2, lastName);
        stmt.setInt(3, fromRow);
        stmt.setInt(4, rowCount);
        
        ResultSet rs = stmt.executeQuery();
        return buildScheduleListFromSet(rs);
   }
   
   // ---------------------- // ************************************* // 
   
   
    private static List<Station> buildStationListFromSet(ResultSet rs) throws Exception
    {
        List<Station> result = new ArrayList<>();
        
        
        while(rs.next())
        {
            Station st = new Station();
            st.setID(rs.getInt("stationID"));
            st.setName(rs.getString("stationName"));
            st.setAddress(rs.getString("stationAddress"));
            
            result.add(st);
        }
        
        return result;
    }
    
    private static List<Track> buildTrackListFromSet(ResultSet rs) throws Exception
    {
        List<Track> result = new ArrayList<>();
        while(rs.next())
        {
            Track st = new Track();
            st.setID(rs.getInt("trackID"));
            st.setLength(rs.getInt("trackLength"));
            st.setSourceID(rs.getInt("fromStation"));
            st.setDestinationID(rs.getInt("toStation"));
            
            result.add(st);
        }
        
        return result;
    }
    
    private static List<Train> buildTrainListFromSet(ResultSet rs) throws Exception
    {
        
        List<Train> result = new ArrayList<>();
        while(rs.next())
        {
            Train st = new Train();
            st.setID(rs.getInt("trainID"));
            st.setName(rs.getString("trainName"));
            st.setNumOfWagons(rs.getInt("numOfWagons"));
            result.add(st);
        }
        
        return result;
    }
    
    private static List<Conductor> buildConductorListFromSet(ResultSet rs) throws Exception
    {
        
        List<Conductor> result = new ArrayList<>();
        while(rs.next())
        {
            Conductor st = new Conductor();
            st.setID(rs.getInt("conductorID"));
            st.setFirstName(rs.getString("firstName"));
            st.setLastName(rs.getString("lastName"));
            result.add(st);
        }
        return result;
    }
    
    
    private static List<TrainSchedule> buildScheduleListFromSet(ResultSet rs) throws Exception
    {
       List<TrainSchedule> result = new ArrayList<>();
        while(rs.next())
        {
            TrainSchedule st = new TrainSchedule();
            st.setConductorID(rs.getInt("conductorID"));
            st.setStartHour(rs.getInt("startHour"));
            st.setStopHour(rs.getInt("stopHour"));
            st.setTrackID(rs.getInt("trackID"));
            st.setTrainID(rs.getInt("trainID"));
            result.add(st);
        }
        return result;
    }
    
    
    // -------------------- // ----------------------- // 
    
    public void insertNewStation(Station st) throws Exception
    {
        PreparedStatement stmt = this.conn.prepareStatement
        ("INSERT INTO STATIONS(stationName, stationAddress) VALUES(?, ?)");
        stmt.setString(1, st.getName());
        stmt.setString(2, st.getAddress());
        stmt.executeUpdate();
    }
    
    public void insertNewTrain(Train t) throws Exception
    {
        
        PreparedStatement stmt = this.conn.prepareStatement
        ("INSERT INTO TRAINS(trainType, trainName, numOfWagons) VALUES(?, ?, ?)");
        stmt.setInt(1, t.getType());
        stmt.setString(2, t.getName());
        stmt.setInt(3, t.getNumOfWagons());
        
        stmt.executeUpdate();
    }
    
    public void insertNewTrack(Track t) throws Exception
    {
        PreparedStatement stmt = this.conn.prepareStatement
        ("INSERT INTO TRACKS(trackLength, fromStation, toStation) VALUES(?, ?, ?)");
        stmt.setInt(1, t.getLength());
        stmt.setInt(2, t.getSourceStation());
        stmt.setInt(3, t.getDestinationStation());
        stmt.executeUpdate();
    }
    
    public void insertNewConductor(Conductor c) throws Exception
    {
        PreparedStatement stmt = this.conn.prepareStatement
        ("INSERT INTO CONDUCTORS(firstName, lastName) VALUES(?, ?)");
        stmt.setString(1, c.getFirstName());
        stmt.setString(2, c.getLastName());
        stmt.executeUpdate();
    }
    
    public void insertNewSchedule(TrainSchedule ts) throws Exception
    {
        PreparedStatement stmt = this.conn.prepareStatement
        ("INSERT INTO TRAIN_SCHEDULES(trainID, trackID, conductorID, startHour, stopHour) "
                + "VALUES(?, ?, ?, ?, ?)");
        
        stmt.setInt(1, ts.getTrainID());
        stmt.setInt(2, ts.getTrackID());
        stmt.setInt(3, ts.getConductorID());
        stmt.setInt(4, ts.getStartHour());
        stmt.setInt(5, ts.getStopHour());
        
        stmt.executeUpdate();
    }
    
    public void alterStation(Station st) throws Exception
    {
        PreparedStatement stmt = this.conn.prepareStatement
        ("UPDATE STATIONS "
                + "SET stationName = ?,"
                + "stationAddress = ?,"
                + "WHERE stationID = ?");
        
        stmt.setString(1, st.getName());
        stmt.setString(2, st.getAddress());
        stmt.setInt(3, st.getID());
        
        stmt.executeUpdate();
    }
    
    public void alterTrain(Train t) throws Exception
    {
        PreparedStatement stmt = this.conn.prepareStatement
        ("UPDATE TRAINS "
                + "SET trainType = ?,"
                + "trainName = ?,"
                + "numOfWagons = ?"
                + "WHERE trainID = ?");
        
        stmt.setInt(1, t.getType());
        stmt.setString(2, t.getName());
        stmt.setInt(3, t.getNumOfWagons());
        stmt.setInt(4, t.getID());
        
        stmt.executeUpdate();
    }
    
    public void alterTrack(Track t) throws Exception
    {
        PreparedStatement stmt = this.conn.prepareStatement
        ("UPDATE TRACKS "
                + "SET trackLength = ?,"
                + "fromStation = ?,"
                + "toStation = ?"
                + "WHERE trackID = ?");
        
        stmt.setInt(1, t.getLength());
        stmt.setInt(2, t.getSourceStation());
        stmt.setInt(3, t.getDestinationStation());
        stmt.setInt(4, t.getID());
        
        stmt.executeUpdate();
    }
    
    public void alterConductor(Conductor c) throws Exception
    {
        PreparedStatement stmt = this.conn.prepareStatement
        ("UPDATE CONDUCTORS "
                + "SET firstName = ?,"
                + "lastName = ?"
                + "WHERE trackID = ?");
        
        stmt.setString(1, c.getFirstName());
        stmt.setString(2, c.getLastName());
        stmt.setInt(3, c.getID());
        stmt.executeUpdate();
        
        stmt.executeUpdate();
    }
    
    
}
