/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package viewInterfaces;
import models.Station;
/**
 *
 * @author costin
 */
public interface StationDialogListener {
   
    public void stationDialogDidEditStation(Station st);
    public void stationDialogDidCreateStation(Station st);
    
}
