/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package viewInterfaces;
import models.Track;
/**
 *
 * @author costin
 */
public interface TrackDialogListener 
{
    public void trackDialogDidEditTrack(Track t);
    public void trackDialogDidCreateTrack(Track t);
}
