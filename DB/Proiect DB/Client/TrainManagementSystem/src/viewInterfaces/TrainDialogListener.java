/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package viewInterfaces;
import models.Train;
/**
 *
 * @author costin
 */
public interface TrainDialogListener 
{
    public void trainDialogDidEditTrain(Train t);
    public void trainDialogDidCreateTrain(Train t);
}
