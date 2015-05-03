/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package viewInterfaces;
import models.*;
/**
 *
 * @author costin
 */
public interface InfoTableListener 
{
    public void infoTableDidSelectTrack(Track t);
    public void infoTableDidSelectTrain(Train t);
    public void infoTableDidSelectConductor(Conductor c);
    public void infoTableDidSelectStation(Station s);
}
