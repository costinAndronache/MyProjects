/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package views;

import paapplets.MainnAppPanelListener;

/**
 *
 * @author Costin
 */
public class PaGraphApplet extends javax.swing.JApplet implements MainnAppPanelListener 
{

    /**
     * Initializes the applet PaGraphApplet
     */
    @Override
    public void init() {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(PaGraphApplet.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(PaGraphApplet.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(PaGraphApplet.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(PaGraphApplet.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>
        
        
        
        /* Create and display the applet */
        try {
            java.awt.EventQueue.invokeAndWait(new Runnable() {
                @Override
                public void run() {
                    initComponents();
                    
                }
            });
        } catch (Exception ex) {
            ex.printStackTrace();
        }
        
        this.mainAppPanel.setListener(this);
        PaGraphApplet appletOne = (PaGraphApplet)this.getAppletContext().getApplet("firstApplet");
        PaGraphApplet appletTwo = (PaGraphApplet)this.getAppletContext().getApplet("secondApplet");
        
        if(this == appletOne)
            this.otherApplet = appletTwo;
        else
            this.otherApplet = appletOne;
        
        this.debugLabel.setText("The other applet is " + this.otherApplet.getName() + ", I am " + this.getName());
        
        String param = this.getParameter("type");
        
        if(param == null)
        {
            this.debugLabel.setText("Did not find parameter for type");
            return;
        }
        
        if(param.equalsIgnoreCase("interpolate"))
            this.mainAppPanel.setModeFunctionInterpolate();
        else
            this.mainAppPanel.setModeFunctionInput();
     
    }

    /**
     * This method is called from within the init() method to initialize the
     * form. WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        mainAppPanel = new paapplets.MainAppFrame_1();
        debugLabel = new javax.swing.JLabel();

        debugLabel.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        debugLabel.setText("debugLabel");

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(debugLabel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(mainAppPanel, javax.swing.GroupLayout.DEFAULT_SIZE, 765, Short.MAX_VALUE))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(mainAppPanel, javax.swing.GroupLayout.PREFERRED_SIZE, 539, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(18, 18, 18)
                .addComponent(debugLabel)
                .addContainerGap(16, Short.MAX_VALUE))
        );
    }// </editor-fold>//GEN-END:initComponents


    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JLabel debugLabel;
    private paapplets.MainAppFrame_1 mainAppPanel;
    // End of variables declaration//GEN-END:variables


    private PaGraphApplet otherApplet;

    @Override
    public void mainAppPanelDidChangeZoomStep(int zoomStep) 
    {
        this.debugLabel.setText("Announced that the zoom changed");

        if(otherApplet != null && otherApplet != this)
        {
            otherApplet.setZoomTo(zoomStep);
        }
    }
    
    public void setZoomTo(int zoomStep)
    {
        this.debugLabel.setText("Received request to zoom");
        this.mainAppPanel.setZoomTo(zoomStep);
    }
    
}