/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package viewInterfaces;
import models.Conductor;
/**
 *
 * @author costin
 */
public interface ConductorDialogListener 
{
    public void conductorDialogDidCreateConductor(Conductor c);
    public void conductorDialogDidEditConductor(Conductor c);
}
