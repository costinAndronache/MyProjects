/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package test;
import gobangpa.*;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Costinel
 */
public class TestFrame extends javax.swing.JFrame implements GameboardPanelListener {

    private Gameboard gb  = new Gameboard(10, 10);
    /**
     * Creates new form TestFrame
     */
    public TestFrame() {
        try {
            initComponents();
            

            
            gb.setCircleAt(CircleType.CircleTypeBlack, 1, 0);
            gb.setCircleAt(CircleType.CircleTypeWhite, 1, 1);
            gb.setCircleAt(CircleType.CircleTypeWhite, 1, 2);
            gb.setCircleAt(CircleType.CircleTypeBlack, 1, 3);
            
            this.gameboardPanel1.setCircleRadius(20);
            this.gameboardPanel1.setGameboard(gb);
            this.gameboardPanel1.repaint();
            
            this.gameboardPanel1.setListener(this);
            
        } catch (Exception ex) {
            Logger.getLogger(TestFrame.class.getName()).log(Level.SEVERE, null, ex);
        }
        
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        gameboardPanel1 = new gobangpa.GameboardPanel();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);

        gameboardPanel1.addMouseMotionListener(new java.awt.event.MouseMotionAdapter() {
            public void mouseMoved(java.awt.event.MouseEvent evt) {
                gameboardPanel1MouseMoved(evt);
            }
        });

        javax.swing.GroupLayout gameboardPanel1Layout = new javax.swing.GroupLayout(gameboardPanel1);
        gameboardPanel1.setLayout(gameboardPanel1Layout);
        gameboardPanel1Layout.setHorizontalGroup(
            gameboardPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 380, Short.MAX_VALUE)
        );
        gameboardPanel1Layout.setVerticalGroup(
            gameboardPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 278, Short.MAX_VALUE)
        );

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(gameboardPanel1, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(gameboardPanel1, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addContainerGap())
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void gameboardPanel1MouseMoved(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_gameboardPanel1MouseMoved
        // TODO add your handling code here:
        
        
    }//GEN-LAST:event_gameboardPanel1MouseMoved

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
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
            java.util.logging.Logger.getLogger(TestFrame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(TestFrame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(TestFrame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(TestFrame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            @Override
            public void run() {
                new TestFrame().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private gobangpa.GameboardPanel gameboardPanel1;
    // End of variables declaration//GEN-END:variables

    @Override
    public void gameboardPanelDidClickAt(GameboardPanel gbp, int i, int j) 
    {
        if(this.gb.isCellFree(i, j))
        {
            try {
                this.gb.setCircleAt(CircleType.CircleTypeWhite, i, j);
            } catch (Exception ex) {
                Logger.getLogger(TestFrame.class.getName()).log(Level.SEVERE, null, ex);
            }
            
            this.gameboardPanel1.repaint();
            
        }
    }


}
