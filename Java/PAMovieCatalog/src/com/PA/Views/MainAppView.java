/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.PA.Views;
import com.PA.Exceptions.AlreadyExistingMovieException;
import com.PA.Exceptions.InexistentCategoryException;
import com.PA.Interfaces.*;
import com.PA.MovieCatalog.*;
import java.io.File;
import java.util.Arrays;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JFileChooser;

/**
 *
 * @author Costinel
 */
public class MainAppView extends javax.swing.JFrame implements MovieDbTreeListener, MovieSupplierListener, 
                                                                                    MovieCategorySupplierListener
{

    /**
     * Creates new form MainAppView
     */
    
    private MovieDatabase db;
    private Movie currentSelectedMovie;
    
    public MainAppView() {
        initComponents();
        this.movieDbTreePanel.setListener(this);
        
        db = new MovieDatabase();
        this.movieDbTreePanel.setDatabase(db);
        this.movieDbTreePanel.reloadData();
        
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jSplitPane3 = new javax.swing.JSplitPane();
        jPanel3 = new javax.swing.JPanel();
        addMovieBtn = new javax.swing.JButton();
        addCategoryBtn = new javax.swing.JButton();
        editMovieBtn = new javax.swing.JButton();
        loadXMLBtn = new javax.swing.JButton();
        saveXMLBtn = new javax.swing.JButton();
        jPanel4 = new javax.swing.JPanel();
        jSplitPane2 = new javax.swing.JSplitPane();
        movieDbTreePanel = new com.PA.Views.MovieDbTreePanel();
        infoPanel = new com.PA.Views.InfoPanel();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);

        jSplitPane3.setDividerLocation(50);
        jSplitPane3.setDividerSize(4);
        jSplitPane3.setOrientation(javax.swing.JSplitPane.VERTICAL_SPLIT);

        addMovieBtn.setText("Add a new movie");
        addMovieBtn.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                addMovieBtnMouseClicked(evt);
            }
        });

        addCategoryBtn.setText("Add a new category");
        addCategoryBtn.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                addCategoryBtnMouseClicked(evt);
            }
        });

        editMovieBtn.setText("Edit Movie");
        editMovieBtn.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                editMovieBtnMouseClicked(evt);
            }
        });

        loadXMLBtn.setText("Load XML");
        loadXMLBtn.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                loadXMLBtnMouseClicked(evt);
            }
        });

        saveXMLBtn.setText("Save XML");
        saveXMLBtn.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                saveXMLBtnMouseClicked(evt);
            }
        });

        javax.swing.GroupLayout jPanel3Layout = new javax.swing.GroupLayout(jPanel3);
        jPanel3.setLayout(jPanel3Layout);
        jPanel3Layout.setHorizontalGroup(
            jPanel3Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel3Layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(addMovieBtn)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(addCategoryBtn)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(editMovieBtn)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(loadXMLBtn)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(saveXMLBtn)
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
        jPanel3Layout.setVerticalGroup(
            jPanel3Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel3Layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanel3Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(addMovieBtn)
                    .addComponent(addCategoryBtn)
                    .addComponent(editMovieBtn)
                    .addComponent(loadXMLBtn)
                    .addComponent(saveXMLBtn))
                .addContainerGap(15, Short.MAX_VALUE))
        );

        jSplitPane3.setTopComponent(jPanel3);

        jSplitPane2.setDividerLocation(180);
        jSplitPane2.setLeftComponent(movieDbTreePanel);
        jSplitPane2.setRightComponent(infoPanel);

        javax.swing.GroupLayout jPanel4Layout = new javax.swing.GroupLayout(jPanel4);
        jPanel4.setLayout(jPanel4Layout);
        jPanel4Layout.setHorizontalGroup(
            jPanel4Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jSplitPane2, javax.swing.GroupLayout.DEFAULT_SIZE, 551, Short.MAX_VALUE)
        );
        jPanel4Layout.setVerticalGroup(
            jPanel4Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jSplitPane2, javax.swing.GroupLayout.DEFAULT_SIZE, 372, Short.MAX_VALUE)
        );

        jSplitPane3.setRightComponent(jPanel4);

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jSplitPane3)
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jSplitPane3, javax.swing.GroupLayout.Alignment.TRAILING)
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void addMovieBtnMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_addMovieBtnMouseClicked
        
        MovieDialog.createWithCategoriesListAndListener(db.getCategoriesList(), this);
        
    }//GEN-LAST:event_addMovieBtnMouseClicked

    private void addCategoryBtnMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_addCategoryBtnMouseClicked
        // TODO add your handling code here:
        AddNewCategoryDialog.createWithListener(this);
    }//GEN-LAST:event_addCategoryBtnMouseClicked

    private void editMovieBtnMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_editMovieBtnMouseClicked
        // TODO add your handling code here:
        MovieDialog.editWithCategoriesListAndListenerAndMovie(db.getCategoriesList(), this, currentSelectedMovie);
    }//GEN-LAST:event_editMovieBtnMouseClicked

    private void loadXMLBtnMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_loadXMLBtnMouseClicked
        // TODO add your handling code here:
        JFileChooser chooser = new JFileChooser();
    chooser.setCurrentDirectory(new File("."));
    int retrival = chooser.showOpenDialog(this);
    if (retrival == JFileChooser.APPROVE_OPTION) 
    {
        try {
             MovieDatabaseSerializer ser = new MovieDatabaseSerializer();
             this.db = ser.deserializeFromXMLFile(chooser.getSelectedFile());
             this.movieDbTreePanel.setDatabase(db);
             this.movieDbTreePanel.reloadData();
        }
         catch (Exception ex) {
            ex.printStackTrace();
        }
          }
    }//GEN-LAST:event_loadXMLBtnMouseClicked

    private void saveXMLBtnMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_saveXMLBtnMouseClicked
        // TODO add your handling code here:
        
        JFileChooser chooser = new JFileChooser();
    chooser.setCurrentDirectory(new File("/home/me/Documents"));
    int retrival = chooser.showSaveDialog(null);
    if (retrival == JFileChooser.APPROVE_OPTION) 
    {
        try {
            
            MovieDatabaseSerializer ser = new MovieDatabaseSerializer();
            ser.serializeDatabaseToXML(this.db, chooser.getSelectedFile().getCanonicalPath());

        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }
    
    }//GEN-LAST:event_saveXMLBtnMouseClicked

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
            java.util.logging.Logger.getLogger(MainAppView.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(MainAppView.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(MainAppView.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(MainAppView.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new MainAppView().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton addCategoryBtn;
    private javax.swing.JButton addMovieBtn;
    private javax.swing.JButton editMovieBtn;
    private com.PA.Views.InfoPanel infoPanel;
    private javax.swing.JPanel jPanel3;
    private javax.swing.JPanel jPanel4;
    private javax.swing.JSplitPane jSplitPane2;
    private javax.swing.JSplitPane jSplitPane3;
    private javax.swing.JButton loadXMLBtn;
    private com.PA.Views.MovieDbTreePanel movieDbTreePanel;
    private javax.swing.JButton saveXMLBtn;
    // End of variables declaration//GEN-END:variables

    
    //DbTreeListener
    public void movieDbTreeDidSelectMovie(MovieDbTreePanel dbTreePanel, Movie m) 
    {
        this.currentSelectedMovie = m;
        this.editMovieBtn.setVisible(true);
        
        this.infoPanel.displayInfoForMovie(m);
    }

    public void movieDbTreeDidSelectCategory(MovieDbTreePanel dbTreePanel, MovieCategory mc) 
    {
        this.currentSelectedMovie = null;
        this.editMovieBtn.setVisible(false);
        this.infoPanel.displayInfoForMovieList(Arrays.asList(mc.getAllMoviesList()));
    }

    public void movieDbTreeDidSelectRootCategoryNode(MovieDbTreePanel dbTreePanel) 
    {
        
        this.editMovieBtn.setVisible(false);
        this.infoPanel.displayInfoForMovieList(db.getListOfMovies());
    }

    public void movieDbTreeDidSelectRootMoviesNode(MovieDbTreePanel dbTreePanel) 
    {
        this.editMovieBtn.setVisible(false);
        this.infoPanel.displayInfoForMovieList(db.getListOfMovies());
    }

    public void movieDbTreeDidSelectRootNode(MovieDbTreePanel dbTreePanel) 
    {
        this.editMovieBtn.setVisible(false);
        this.infoPanel.displayInfoForMovieList(db.getListOfMovies());
    }

    // Movie supplier listener
    public void movieSupplierDidCreateMovie(MovieSupplier controller, Movie movie) 
    {
        try {
            this.db.addNewMovie(movie);
        } catch (InexistentCategoryException ex) {
            Logger.getLogger(MainAppView.class.getName()).log(Level.SEVERE, null, ex);
        } catch (AlreadyExistingMovieException ex) {
            Logger.getLogger(MainAppView.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        this.movieDbTreePanel.reloadData();
        System.out.println("Should add the new movie " + movie.getName());
        
    }

    public void movieCategorySupplierDidCreateMovieCategory(MovieCategorySupplier supplier, MovieCategory movCat) 
    {
        this.db.addNewCategory(movCat);
        this.movieDbTreePanel.reloadData();
    }

    public void movieSupplierDidEditMovie(MovieSupplier supplier, Movie movie) 
    {
        this.movieDbTreePanel.reloadData();
        this.infoPanel.displayInfoForMovie(movie);
    }
}
